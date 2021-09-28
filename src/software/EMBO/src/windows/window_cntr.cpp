/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_cntr.h"
#include "ui_window_cntr.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>
#include <QPixmap>
#include <QTimer>


WindowCntr::WindowCntr(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowCntr)
{
    m_ui->setupUi(this);

    m_timer_render = new QTimer(this);

    m_msg_enable = new Msg_CNTR_Enable(this);
    m_msg_read = new Msg_CNTR_Read(this);

    connect(m_msg_enable, &Msg_CNTR_Enable::ok, this, &WindowCntr::on_msg_ok, Qt::QueuedConnection);
    connect(m_msg_enable, &Msg_CNTR_Enable::err, this, &WindowCntr::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_enable, &Msg_CNTR_Enable::result, this, &WindowCntr::on_msg_enable, Qt::QueuedConnection);

    connect(m_msg_read, &Msg_CNTR_Read::err, this, &WindowCntr::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read, &Msg_CNTR_Read::result, this, &WindowCntr::on_msg_read, Qt::QueuedConnection);

    connect(m_timer_render, &QTimer::timeout, this, &WindowCntr::on_timer_render);

    connect(m_ui->actionEMBO_Help, SIGNAL(triggered()), Core::getInstance(), SLOT(on_actionEMBO_Help()));

    m_status_enabled = new QLabel(" Disabled", this);
    QWidget* widget = new QWidget(this);
    QFont font1("Roboto", 11, QFont::Normal);
    m_status_enabled->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/img/cntr.png");

    status_img->setPixmap(status_img_icon);
    status_img->setFixedWidth(15);
    status_img->setFixedHeight(17);
    status_img->setScaledContents(true);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(status_img,0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_enabled,0,1,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);

    m_mode.addButton(m_ui->radioButton_precise);
    m_mode.addButton(m_ui->radioButton_fast);
    m_mode.setExclusive(true);

    m_ui->pushButton_enable->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_CNTR_ON);
    m_ui->pushButton_disable->setStyleSheet(CSS_BUTTON_OFF_NODIS CSS_BUTTON_CNTR_ON);

    m_ui->textBrowser_freq->setStyleSheet(CSS_TEXTBOX);
    m_ui->textBrowser_period->setStyleSheet(CSS_TEXTBOX);
}

WindowCntr::~WindowCntr()
{
    delete m_ui;
}

/* slots */

void WindowCntr::on_msg_ok(const QString, const QString)
{
    if (m_enable_wantSwitch)
    {
        m_enable_wantSwitch = false;
        m_instrEnabled = !m_instrEnabled;
    }

    if (m_instrEnabled)
        m_activeMsgs.push_back(m_msg_read);
    else
        m_activeMsgs.clear();

    enableAll(true);
}

void WindowCntr::on_msg_err(const QString text, MsgBoxType type, bool needClose)
{
    m_activeMsgs.clear();

    if (needClose)
        this->close();

    msgBox(this, text, type);
}

void WindowCntr::on_msg_enable(bool enabled, bool fastMode)
{
    m_instrEnabled = enabled;
    m_fastMode = fastMode;

    if (m_instrEnabled)
        m_activeMsgs.push_back(m_msg_read);
    else
        m_activeMsgs.clear();

    m_ui->radioButton_fast->setChecked(m_fastMode);
    m_ui->radioButton_precise->setChecked(!m_fastMode);

    enableAll(true);
}

void WindowCntr::on_msg_read(const QString freq, const QString period)
{
    m_data_freq = freq;
    m_data_period = period;
    m_data_fresh = true;
}

void WindowCntr::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

void WindowCntr::on_pushButton_disable_clicked()
{
    m_enable_wantSwitch = true;
    enableAll(false);
    sendEnable(false);
}

void WindowCntr::on_pushButton_enable_clicked()
{
    m_enable_wantSwitch = true;
    enableAll(false);
    sendEnable(true);
}

void WindowCntr::on_radioButton_precise_clicked()
{
    m_fastMode = false;
    sendEnable(m_instrEnabled);
}

void WindowCntr::on_radioButton_fast_clicked()
{
    m_fastMode = true;
    sendEnable(m_instrEnabled);
}

void WindowCntr::on_timer_render()
{
    if (m_instrEnabled)
    {
        if (!m_data_fresh)
            return;

        QString freq = m_data_freq;
        QString period = m_data_period;

        if (freq.contains("Time out"))
        {
            m_ui->textBrowser_freq->setHtml("<p align=\"right\"> " FREQ_TIMEOUT);
            m_ui->textBrowser_period->setHtml("<p align=\"right\"> " PERIOD_TIMEOUT);
        }
        else if (freq.contains("ERROR"))
        {
            //m_status_enabled->setText(" " + freq);
        }
        else // ALL GOOD
        {
            QString period2 = period;
            if (freq.contains("kHz") || freq.contains("MHz"))
                 period2 = period2.replace(" ", "&nbsp;&nbsp;");

            m_ui->textBrowser_freq->setHtml("<p align=\"right\">" + freq + " ");
            m_ui->textBrowser_period->setHtml("<p align=\"right\">" + period + " ");
        }

        m_data_fresh = false;
    }
}

/* private */

void WindowCntr::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();
    emit closing(WindowCntr::staticMetaObject.className());
}

void WindowCntr::showEvent(QShowEvent*)
{
    m_ui->textBrowser_freq->setHtml("<p align=\"right\"> " FREQ_TIMEOUT);
    m_ui->textBrowser_period->setHtml("<p align=\"right\"> " PERIOD_TIMEOUT);

    m_ui->textBrowser_freq->setEnabled(false);
    m_ui->textBrowser_period->setEnabled(false);

    enableAll(false);

    Core::getInstance()->msgAdd(m_msg_enable, true, "");
}

void WindowCntr::enableAll(bool enable)
{
    m_ui->pushButton_enable->setEnabled(enable);
    m_ui->pushButton_disable->setEnabled(enable);

    m_ui->radioButton_fast->setEnabled(enable);
    m_ui->radioButton_precise->setEnabled(enable);

    m_ui->textBrowser_freq->setEnabled(m_instrEnabled);
    m_ui->textBrowser_period->setEnabled(m_instrEnabled);

    if (enable)
    {
        if (m_instrEnabled)
        {
            m_ui->pushButton_enable->hide();
            m_ui->pushButton_disable->show();

            m_status_enabled->setText(" ON");
            m_timer_render->start(TIMER_CNTR_RENDER);
        }
        else
        {
            m_ui->pushButton_enable->show();
            m_ui->pushButton_disable->hide();

            m_status_enabled->setText(" OFF");
            m_timer_render->stop();
        }
    }
    else
    {
        m_status_enabled->setText(" Wait...");
    }
}

void WindowCntr::sendEnable(bool enable)
{
    enableAll(false);

    Core::getInstance()->msgAdd(m_msg_enable, false,
                                (enable ? QString(EMBO_SET_TRUE) : QString(EMBO_SET_FALSE)) + EMBO_DELIM2 +
                                (m_fastMode ? EMBO_SET_TRUE : EMBO_SET_FALSE));
}
