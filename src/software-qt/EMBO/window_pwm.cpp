/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_pwm.h"
#include "ui_window_pwm.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>


WindowPwm::WindowPwm(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowPwm)
{
    m_ui->setupUi(this);

    m_msg_set = new Msg_PWM_Set(this);

    connect(m_msg_set, &Msg_PWM_Set::err, this, &WindowPwm::on_msg_err);
    connect(m_msg_set, &Msg_PWM_Set::result, this, &WindowPwm::on_msg_set);

    m_status_enabled = new QLabel(" CH1: Disabled     CH2: Disabled");
    QWidget* widget = new QWidget();
    QFont font1("Roboto", 11, QFont::Normal);
    m_status_enabled->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/resources/img/pwm.png");

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

    QString style1(CSS_BUTTON_ON);

    m_ui->pushButton_ch1enable->setStyleSheet(style1);
    m_ui->pushButton_ch2enable->setStyleSheet(style1);
    m_ui->pushButton_ch1disable->setStyleSheet(style1);
    m_ui->pushButton_ch2disable->setStyleSheet(style1);

    QString style2(CSS_SPINBOX);

    m_ui->spinBox_freq->setStyleSheet(style2);
    m_ui->spinBox_duty1->setStyleSheet(style2);
    m_ui->spinBox_duty2->setStyleSheet(style2);
    m_ui->spinBox_offset->setStyleSheet(style2);
}

WindowPwm::~WindowPwm()
{
    delete m_ui;
}

void WindowPwm::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

void WindowPwm::on_msg_set(double freq, int duty, int duty2, int offset, bool en1, bool en2)
{

}

/* slots */

void WindowPwm::on_msg_err(QString text, MsgBoxType type, bool needClose)
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

void WindowPwm::on_spinBox_freq_valueChanged(int arg1)
{
    m_ui->horizontalSlider_freq->setValue(arg1);
    m_ui->dial_freq->setValue(arg1);
}

void WindowPwm::on_horizontalSlider_freq_sliderMoved(int position)
{
    m_ui->spinBox_freq->setValue(position);
    m_ui->dial_freq->setValue(position);
}

void WindowPwm::on_dial_freq_sliderMoved(int position)
{
    m_ui->spinBox_freq->setValue(position);
    m_ui->horizontalSlider_freq->setValue(position);
}

void WindowPwm::on_spinBox_duty1_valueChanged(int arg1)
{
    m_ui->dial_duty1->setValue(arg1);
}

void WindowPwm::on_dial_duty1_valueChanged(int value)
{
    m_ui->spinBox_duty1->setValue(value);
}

void WindowPwm::on_spinBox_duty2_valueChanged(int arg1)
{
    m_ui->dial_duty2->setValue(arg1);
}

void WindowPwm::on_dial_duty2_valueChanged(int value)
{
    m_ui->spinBox_duty2->setValue(value);
}

void WindowPwm::on_spinBox_offset_valueChanged(int arg1)
{
    m_ui->dial_offset->setValue(arg1);
}

void WindowPwm::on_dial_offset_valueChanged(int value)
{
    m_ui->spinBox_offset->setValue(value);
}

void WindowPwm::on_pushButton_ch2disable_clicked()
{

}

void WindowPwm::on_pushButton_ch2enable_clicked()
{

}

void WindowPwm::on_pushButton_ch1disable_clicked()
{

}

void WindowPwm::on_pushButton_ch1enable_clicked()
{

}

/* private */

void WindowPwm::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
    emit closing(WindowPwm::staticMetaObject.className());
}

void WindowPwm::showEvent(QShowEvent*)
{
    m_ui->pushButton_ch1enable->show();
    m_ui->pushButton_ch1disable->hide();

    m_ui->pushButton_ch2enable->show();
    m_ui->pushButton_ch2disable->hide();

    m_ui->pushButton_ch1enable->setText(" Wait...");
    m_ui->pushButton_ch1enable->setEnabled(false);

    m_ui->pushButton_ch2enable->setText(" Wait...");
    m_ui->pushButton_ch2enable->setEnabled(false);

    m_ui->spinBox_freq->setEnabled(false);
    m_ui->spinBox_duty1->setEnabled(false);
    m_ui->spinBox_duty2->setEnabled(false);
    m_ui->spinBox_offset->setEnabled(false);

    m_ui->dial_freq->setEnabled(false);
    m_ui->dial_duty1->setEnabled(false);
    m_ui->dial_duty2->setEnabled(false);
    m_ui->dial_offset->setEnabled(false);

    m_ui->horizontalSlider_freq->setEnabled(false);
    m_ui->label_realFreq->setEnabled(false);
    m_ui->label_realFreq->setText("? Hz");

    //m_msg_enable->setIsQuery(true);
    //Core::getInstance()->msgAdd(m_msg_enable);
}
