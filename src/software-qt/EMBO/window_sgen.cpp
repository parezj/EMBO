/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_sgen.h"
#include "ui_window_sgen.h"
#include "core.h"
#include "utils.h"
#include "settings.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>


WindowSgen::WindowSgen(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowSgen)
{
    m_ui->setupUi(this);
}

WindowSgen::~WindowSgen()
{
    delete m_ui;
}

void WindowSgen::closeEvent(QCloseEvent*)
{
    emit closing(WindowSgen::staticMetaObject.className());
}

void WindowSgen::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}
