/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_sgen.h"
#include "ui_window_sgen.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>


WindowSgen::WindowSgen(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowSgen)
{
    m_ui->setupUi(this);

    m_msg_set = new Msg_SGEN_Set(this);

    connect(m_msg_set, &Msg_SGEN_Set::err, this, &WindowSgen::on_msg_err);
    connect(m_msg_set, &Msg_SGEN_Set::result, this, &WindowSgen::on_msg_set);

    m_status_enabled = new QLabel(" Disabled");
    QWidget* widget = new QWidget();
    QFont font1("Roboto", 11, QFont::Normal);
    m_status_enabled->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/resources/img/sgen2.png");

    status_img->setPixmap(status_img_icon);
    status_img->setFixedWidth(17);
    status_img->setFixedHeight(17);
    status_img->setScaledContents(true);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(status_img,0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_enabled,0,1,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);

    m_mode.addButton(m_ui->radioButton_const);
    m_mode.addButton(m_ui->radioButton_sine);
    m_mode.addButton(m_ui->radioButton_triangle);
    m_mode.addButton(m_ui->radioButton_saw);
    m_mode.addButton(m_ui->radioButton_square);
    m_mode.addButton(m_ui->radioButton_noise);

    m_mode.setExclusive(true);
    m_ui->radioButton_sine->setChecked(true);

    QString style1(CSS_BUTTON_ON);

    m_ui->pushButton_enable->setStyleSheet(style1);
    m_ui->pushButton_disable->setStyleSheet(style1);

    QString style2(CSS_RADIOBUTTON);

    m_ui->radioButton_const->setStyleSheet(style2);
    m_ui->radioButton_sine->setStyleSheet(style2);
    m_ui->radioButton_triangle->setStyleSheet(style2);
    m_ui->radioButton_saw->setStyleSheet(style2);
    m_ui->radioButton_square->setStyleSheet(style2);
    m_ui->radioButton_noise->setStyleSheet(style2);

    QString style3(CSS_SPINBOX);

    m_ui->spinBox_freq->setStyleSheet(style3);
    m_ui->spinBox_ampl->setStyleSheet(style3);
    m_ui->spinBox_offset->setStyleSheet(style3);
}

WindowSgen::~WindowSgen()
{
    delete m_ui;
}

void WindowSgen::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

void WindowSgen::on_msg_set(SgenMode mode, double freq, int ampl, int offset)
{

}

/* slots */

void WindowSgen::on_msg_err(QString text, MsgBoxType type, bool needClose)
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

void WindowSgen::on_spinBox_freq_valueChanged(int arg1)
{
    m_ui->dial_freq->setValue(arg1);
}

void WindowSgen::on_dial_freq_valueChanged(int value)
{
    m_ui->spinBox_freq->setValue(value);
}

void WindowSgen::on_spinBox_ampl_valueChanged(int arg1)
{
    m_ui->dial_ampl->setValue(arg1);
}

void WindowSgen::on_dial_ampl_valueChanged(int value)
{
    m_ui->spinBox_ampl->setValue(value);
}

void WindowSgen::on_spinBox_offset_valueChanged(int arg1)
{
    m_ui->dial_offset->setValue(arg1);
}

void WindowSgen::on_dial_offset_valueChanged(int value)
{
    m_ui->spinBox_offset->setValue(value);
}

void WindowSgen::on_pushButton_enable_clicked()
{

}

void WindowSgen::on_pushButton_disable_clicked()
{

}

void WindowSgen::on_radioButton_const_clicked()
{
    m_ui->dial_freq->setEnabled(false);
    m_ui->spinBox_freq->setEnabled(false);

    m_ui->dial_offset->setEnabled(false);
    m_ui->spinBox_offset->setEnabled(false);
}

void WindowSgen::on_radioButton_sine_clicked()
{
    m_ui->dial_freq->setEnabled(true);
    m_ui->spinBox_freq->setEnabled(true);

    m_ui->dial_offset->setEnabled(true);
    m_ui->spinBox_offset->setEnabled(true);
}

void WindowSgen::on_radioButton_triangle_clicked()
{
    m_ui->dial_freq->setEnabled(true);
    m_ui->spinBox_freq->setEnabled(true);

    m_ui->dial_offset->setEnabled(true);
    m_ui->spinBox_offset->setEnabled(true);
}

void WindowSgen::on_radioButton_saw_clicked()
{
    m_ui->dial_freq->setEnabled(true);
    m_ui->spinBox_freq->setEnabled(true);

    m_ui->dial_offset->setEnabled(true);
    m_ui->spinBox_offset->setEnabled(true);
}

void WindowSgen::on_radioButton_square_clicked()
{
    m_ui->dial_freq->setEnabled(true);
    m_ui->spinBox_freq->setEnabled(true);

    m_ui->dial_offset->setEnabled(true);
    m_ui->spinBox_offset->setEnabled(true);
}

void WindowSgen::on_radioButton_noise_clicked()
{
    m_ui->dial_freq->setEnabled(false);
    m_ui->spinBox_freq->setEnabled(false);

    m_ui->dial_offset->setEnabled(false);
    m_ui->spinBox_offset->setEnabled(false);
}

/* private */

void WindowSgen::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
    emit closing(WindowSgen::staticMetaObject.className());
}

void WindowSgen::showEvent(QShowEvent*)
{
    m_ui->pushButton_enable->show();
    m_ui->pushButton_disable->hide();

    m_ui->pushButton_enable->setText(" Wait...");
    m_ui->pushButton_enable->setEnabled(false);

    /*
    m_ui->spinBox_freq->setEnabled(false);
    m_ui->spinBox_ampl->setEnabled(false);
    m_ui->spinBox_offset->setEnabled(false);

    m_ui->dial_freq->setEnabled(false);
    m_ui->dial_ampl->setEnabled(false);
    m_ui->dial_offset->setEnabled(false);

    m_ui->spinBox_freq->setValue(0);
    m_ui->spinBox_ampl->setValue(0);
    m_ui->spinBox_offset->setValue(0);

    m_ui->dial_freq->setValue(0);
    m_ui->dial_ampl->setValue(0);
    m_ui->dial_offset->setValue(0);

    m_ui->radioButton_const->setEnabled(false);
    m_ui->radioButton_sine->setEnabled(false);
    m_ui->radioButton_triangle->setEnabled(false);
    m_ui->radioButton_saw->setEnabled(false);
    m_ui->radioButton_square->setEnabled(false);
    m_ui->radioButton_noise->setEnabled(false);

    m_ui->spinBox_freq->setStyleSheet(QString(CSS_SPINBOX_OFF));
    m_ui->spinBox_ampl->setStyleSheet(QString(CSS_SPINBOX_OFF));
    m_ui->spinBox_offset->setStyleSheet(QString(CSS_SPINBOX_OFF));
    */

    //m_msg_enable->setIsQuery(true);
    //Core::getInstance()->msgAdd(m_msg_enable);
}

