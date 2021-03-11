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


WindowCntr::WindowCntr(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowCntr)
{
    m_ui->setupUi(this);

    m_msg_enable = new Msg_CNTR_Enable(this);
    m_msg_read = new Msg_CNTR_Read(this);

    connect(m_msg_enable, &Msg_CNTR_Enable::ok, this, &WindowCntr::on_msg_ok);
    connect(m_msg_enable, &Msg_CNTR_Enable::err, this, &WindowCntr::on_msg_err);
    connect(m_msg_enable, &Msg_CNTR_Enable::result, this, &WindowCntr::on_msg_enable);

    connect(m_msg_read, &Msg_CNTR_Read::err, this, &WindowCntr::on_msg_err);
    connect(m_msg_read, &Msg_CNTR_Read::result, this, &WindowCntr::on_msg_read);

    m_status_enabled = new QLabel(" Disabled", this);
    QWidget* widget = new QWidget(this);
    QFont font1("Roboto", 11, QFont::Normal);
    m_status_enabled->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/resources/img/cntr.png");

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

    QString style1(CSS_BUTTON_NODIS CSS_BUTTON_CNTR_ON);

    m_ui->pushButton_enable->setStyleSheet(style1);
    m_ui->pushButton_disable->setStyleSheet(style1);

    QString style2(CSS_TEXTBOX);

    m_ui->textBrowser_freq->setStyleSheet(style2);
    m_ui->textBrowser_period->setStyleSheet(style2);
}

WindowCntr::~WindowCntr()
{
    delete m_ui;
}

/* slots */

void WindowCntr::on_msg_ok(QString, QString)
{
    if (m_enable_wantSwitch)
    {
        m_enable_wantSwitch = false;
        m_instrEnabled = !m_instrEnabled;
    }

    if (m_instrEnabled)
        m_activeMsg = m_msg_read;
    else
        m_activeMsg = Q_NULLPTR;

    enableAll(true);
}

void WindowCntr::on_msg_err(QString text, MsgBoxType type, bool needClose)
{
    m_activeMsg = Q_NULLPTR;

    if (type == INFO)
        QMessageBox::information(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::NoButton);
    else if (type == QUESTION)
        QMessageBox::question(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::Yes | QMessageBox::No);
    else if (type == WARNING)
        QMessageBox::warning(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::NoButton);
    else if (type == CRITICAL)
        QMessageBox::critical(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::NoButton);

    if (needClose)
        this->close();
}

void WindowCntr::on_msg_enable(bool enabled, bool fastMode)
{
    m_instrEnabled = enabled;
    m_fastMode = fastMode;

    if (m_instrEnabled)
        m_activeMsg = m_msg_read;
    else
        m_activeMsg = Q_NULLPTR;

    m_ui->radioButton_fast->setChecked(m_fastMode);
    m_ui->radioButton_precise->setChecked(!m_fastMode);

    enableAll(true);
}

void WindowCntr::on_msg_read(QString freq, QString period)
{
    if (m_instrEnabled)
    {
        if (freq.contains("Time out"))
        {
            m_ui->textBrowser_freq->setHtml("<p align=\"right\"> " FREQ_TIMEOUT);
            m_ui->textBrowser_period->setHtml("<p align=\"right\"> " PERIOD_TIMEOUT);
        }
        else if (freq.contains("ERROR"))
        {
            m_status_enabled->setText(" " + freq);
        }
        else // ALL GOOD
        {
            /*
            double freq_d = freq.left(freq.indexOf(" ")).toDouble();
            qInfo() << freq_d;
            if (freq.contains("kHz"))
                freq_d *= 1000;
            else if (freq.contains("MHz"))
                freq_d *= 1000000;

            if (freq_d != 0) // EXPERIMENTAL
            {
                m_ui->textBrowser_freq->setHtml("<p align=\"right\">" + format_unit(freq_d, "Hz", 3) + " ");
                m_ui->textBrowser_period->setHtml("<p align=\"right\">" + format_unit(1/freq_d, "Hz", 3) + " ");
            }
            else
            {
            */

            if (freq.contains("kHz") || freq.contains("MHz"))
                 period = period.replace(" ", "&nbsp;&nbsp;");

            m_ui->textBrowser_freq->setHtml("<p align=\"right\">" + freq + " ");
            m_ui->textBrowser_period->setHtml("<p align=\"right\">" + period + " ");
        }
    }
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

/* private */

void WindowCntr::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
    emit closing(WindowCntr::staticMetaObject.className());
}

void WindowCntr::showEvent(QShowEvent*)
{
    m_ui->textBrowser_freq->setHtml("<p align=\"right\"> " FREQ_TIMEOUT);
    m_ui->textBrowser_period->setHtml("<p align=\"right\"> " PERIOD_TIMEOUT);

    m_ui->textBrowser_freq->setEnabled(false);
    m_ui->textBrowser_period->setEnabled(false);

    enableAll(false);

    Core::getInstance()->msgAdd(m_msg_enable, true);
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

            m_status_enabled->setText(" Enabled");
        }
        else
        {
            m_ui->pushButton_enable->show();
            m_ui->pushButton_disable->hide();

            m_status_enabled->setText(" Disabled");
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
