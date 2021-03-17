/*
 * CTU/EMBO - EMBedded OscilloLAe <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_la.h"
#include "ui_window_la.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>


WindowLa::WindowLa(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowLa)
{
    m_ui->setupUi(this);

    m_msg_set = new Msg_LA_Set(this);
    m_msg_read = new Msg_LA_Read(this);
    m_msg_forceTrig = new Msg_LA_ForceTrig(this);

    connect(m_msg_set, &Msg_LA_Set::ok, this, &WindowLa::on_msg_ok, Qt::DirectConnection);
    connect(m_msg_set, &Msg_LA_Set::err, this, &WindowLa::on_msg_err, Qt::DirectConnection);
    connect(m_msg_set, &Msg_LA_Set::result, this, &WindowLa::on_msg_set, Qt::DirectConnection);

    connect(m_msg_read, &Msg_LA_Read::err, this, &WindowLa::on_msg_err, Qt::DirectConnection);
    connect(m_msg_read, &Msg_LA_Read::result, this, &WindowLa::on_msg_read, Qt::DirectConnection);

    connect(m_msg_forceTrig, &Msg_LA_ForceTrig::ok, this, &WindowLa::on_msg_ok, Qt::DirectConnection);
    connect(m_msg_forceTrig, &Msg_LA_ForceTrig::err, this, &WindowLa::on_msg_err, Qt::DirectConnection);

    connect(Core::getInstance(), &Core::daqReady, this, &WindowLa::on_msg_daqReady, Qt::QueuedConnection);
}

WindowLa::~WindowLa()
{
    delete m_ui;
}

void WindowLa::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/* slots */

void WindowLa::on_msg_ok(const QString val1, const QString val2)
{

}

void WindowLa::on_msg_err(const QString text, MsgBoxType type, bool needClose)
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

void WindowLa::on_msg_set()
{

}

void WindowLa::on_msg_read(const QString data)
{
    // PLOT DATA
}

void WindowLa::on_msg_daqReady(Ready ready)
{
    if (m_instrEnabled)
        Core::getInstance()->msgAdd(m_msg_read, true);
}

/* private */

void WindowLa::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
    m_instrEnabled = false;

    Core::getInstance()->setMode(NO_MODE);
    emit closing(WindowLa::staticMetaObject.className());
}

void WindowLa::showEvent(QShowEvent*)
{
    Core::getInstance()->setMode(LA);
    m_instrEnabled = true;

    Core::getInstance()->msgAdd(m_msg_set, true, "");
}
