/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_cntr.h"
#include "ui_window_cntr.h"
#include "core.h"
#include "utils.h"
#include "settings.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>


WindowCntr::WindowCntr(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowCntr)
{
    m_ui->setupUi(this);

    m_ui->pushButton_disable->hide();
    m_ui->pushButton_enable->setText(" Wait...");
    m_ui->pushButton_enable->setEnabled(false);

    m_msg_enable = new Msg_CNTR_Enable(this);
    m_msg_read = new Msg_CNTR_Read(this);

    connect(m_msg_enable, &Msg_CNTR_Enable::err, this, &WindowCntr::on_msg_err);
    connect(m_msg_enable, &Msg_CNTR_Enable::result, this, &WindowCntr::on_msg_enable);

    connect(m_msg_read, &Msg_CNTR_Read::err, this, &WindowCntr::on_msg_err);
    connect(m_msg_read, &Msg_CNTR_Read::result, this, &WindowCntr::on_msg_read);

    m_msg_enable->setIsQuery(true);
    Core::getInstance()->msgAdd(m_msg_enable);
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
        instrEnabled = enable;
    else
        instrEnabled = !instrEnabled;

    if (instrEnabled)
    {
        m_ui->pushButton_disable->show();
        m_ui->pushButton_enable->hide();

        m_activeMsg = Q_NULLPTR;
    }
    else
    {
        m_ui->pushButton_enable->show();
        m_ui->pushButton_disable->hide();

        m_activeMsg = m_msg_read;
    }
}

void WindowCntr::on_msg_read(QString freq, QString period)
{
    m_ui->textBrowser_freq->setText(freq);
    m_ui->textBrowser_period->setText(period);
}

void WindowCntr::closeEvent(QCloseEvent*)
{
    emit closing(WindowCntr::staticMetaObject.className());
}

void WindowCntr::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

void WindowCntr::on_pushButton_disable_clicked()
{
    m_ui->pushButton_enable->setText(" Wait...");
    m_ui->pushButton_enable->setEnabled(false);

    m_msg_enable->setIsQuery(true);
    m_msg_enable->setParams(EMBO_SET_FALSE);
    Core::getInstance()->msgAdd(m_msg_enable);
}

void WindowCntr::on_pushButton_enable_clicked()
{
    m_ui->pushButton_enable->setText(" Wait...");
    m_ui->pushButton_enable->setEnabled(false);

    m_msg_enable->setIsQuery(true);
    m_msg_enable->setParams(EMBO_SET_FALSE);
    Core::getInstance()->msgAdd(m_msg_enable);
}
