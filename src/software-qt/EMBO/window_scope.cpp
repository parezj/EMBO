/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_scope.h"
#include "ui_window_scope.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>


WindowScope::WindowScope(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowScope)
{
    m_ui->setupUi(this);
}

WindowScope::~WindowScope()
{
    delete m_ui;
}

void WindowScope::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/* slots */

void WindowScope::on_msg_err(const QString text, MsgBoxType type, bool needClose)
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

/* private */

void WindowScope::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
    emit closing(WindowScope::staticMetaObject.className());
}

void WindowScope::showEvent(QShowEvent*)
{
    //m_msg_enable->setIsQuery(true);
    //Core::getInstance()->msgAdd(m_msg_enable);
}
