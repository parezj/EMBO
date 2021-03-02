/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_pwm.h"
#include "ui_window_pwm.h"
#include "core.h"
#include "utils.h"
#include "settings.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>


WindowPwm::WindowPwm(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowPwm)
{
    m_ui->setupUi(this);
}

WindowPwm::~WindowPwm()
{
    delete m_ui;
}

void WindowPwm::closeEvent(QCloseEvent*)
{
    emit closing(WindowPwm::staticMetaObject.className());
}

void WindowPwm::on_actionHelp_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}
