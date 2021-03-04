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

    connect(m_msg_enable, &Msg_CNTR_Enable::err, this, &WindowCntr::on_msg_err);
    connect(m_msg_enable, &Msg_CNTR_Enable::result, this, &WindowCntr::on_msg_enable);

    connect(m_msg_read, &Msg_CNTR_Read::err, this, &WindowCntr::on_msg_err);
    connect(m_msg_read, &Msg_CNTR_Read::result, this, &WindowCntr::on_msg_read);

    m_status_enabled = new QLabel(" Disabled");
    QWidget* widget = new QWidget();
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

    QString style1(CSS_BUTTON_ON);

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

void WindowCntr::on_msg_enable(bool isQuery, bool enable)
{
    m_ui->pushButton_enable->setText(" Enable");
    m_ui->pushButton_enable->setEnabled(true);

    m_ui->pushButton_disable->setText(" Disable");
    m_ui->pushButton_disable->setEnabled(true);

    if (isQuery)
        m_instrEnabled = enable;
    else
        m_instrEnabled = !m_instrEnabled;

    if (m_instrEnabled)
    {
        m_status_enabled->setText(" Enabled");

        m_ui->pushButton_disable->show();
        m_ui->pushButton_enable->hide();

        m_ui->textBrowser_freq->setEnabled(true);
        m_ui->textBrowser_period->setEnabled(true);

        m_activeMsg = m_msg_read;
    }
    else
    {
        m_status_enabled->setText(" Disabled");

        m_ui->pushButton_enable->show();
        m_ui->pushButton_disable->hide();

        m_ui->textBrowser_freq->setEnabled(false);
        m_ui->textBrowser_period->setEnabled(false);

        m_activeMsg = Q_NULLPTR;
    }
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
        else
        {
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
    m_ui->pushButton_enable->setText(" Wait...");
    m_ui->pushButton_enable->setEnabled(false);

    Core::getInstance()->msgAdd(m_msg_enable, false, EMBO_SET_FALSE);
}

void WindowCntr::on_pushButton_enable_clicked()
{
    m_ui->pushButton_enable->setText(" Wait...");
    m_ui->pushButton_enable->setEnabled(false);

    Core::getInstance()->msgAdd(m_msg_enable, false, EMBO_SET_TRUE);
}

/* private */

void WindowCntr::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
    emit closing(WindowCntr::staticMetaObject.className());
}

void WindowCntr::showEvent(QShowEvent*)
{
    m_ui->pushButton_enable->show();
    m_ui->pushButton_disable->hide();

    m_ui->pushButton_enable->setText(" Wait...");
    m_ui->pushButton_enable->setEnabled(false);

    m_ui->textBrowser_freq->setEnabled(false);
    m_ui->textBrowser_period->setEnabled(false);

    m_ui->textBrowser_freq->setText("");
    m_ui->textBrowser_period->setText("");

    m_ui->textBrowser_freq->setHtml("<p align=\"right\"> " FREQ_TIMEOUT);
    m_ui->textBrowser_period->setHtml("<p align=\"right\"> " PERIOD_TIMEOUT);

    Core::getInstance()->msgAdd(m_msg_enable, true);
}
