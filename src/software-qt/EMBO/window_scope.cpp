/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_scope.h"
#include "ui_window_scope.h"
#include "core.h"
#include "utils.h"
#include "settings.h"

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

void WindowScope::closeEvent(QCloseEvent*)
{
    emit closing(WindowScope::staticMetaObject.className());
}

void WindowScope::on_actionHelp_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}
