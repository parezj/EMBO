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

    connect(m_msg_set, &Msg_PWM_Set::ok, this, &WindowPwm::on_msg_ok, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_PWM_Set::err, this, &WindowPwm::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_PWM_Set::result, this, &WindowPwm::on_msg_set, Qt::QueuedConnection);

    m_ui->textBrowser_realFreq->setHtml("<p align=\"right\">? Hz&nbsp;&nbsp;&nbsp;</p>");

    m_status_enabled = new QLabel(" Wait...", this);
    QWidget* widget = new QWidget(this);
    QFont font1("Roboto", 11, QFont::Normal);
    m_status_enabled->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/img/pwm.png");

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

    m_mode.addButton(m_ui->radioButton_coarse);
    m_mode.addButton(m_ui->radioButton_fine);
    m_mode.setExclusive(true);

    m_ui->radioButton_fine->setChecked(true);
    on_radioButton_fine_clicked();

    m_ui->pushButton_ch1enable->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_PWM_ON);
    m_ui->pushButton_ch2enable->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_PWM_ON);

    m_ui->pushButton_ch1disable->setStyleSheet(CSS_BUTTON_OFF_NODIS CSS_BUTTON_PWM_ON);
    m_ui->pushButton_ch2disable->setStyleSheet(CSS_BUTTON_OFF_NODIS CSS_BUTTON_PWM_ON);

    m_ui->spinBox_freq->setStyleSheet(CSS_SPINBOX_NODIS);
    m_ui->spinBox_duty1->setStyleSheet(CSS_SPINBOX_NODIS);
    m_ui->spinBox_duty2->setStyleSheet(CSS_SPINBOX_NODIS);
    m_ui->spinBox_offset->setStyleSheet(CSS_SPINBOX_NODIS);
}

WindowPwm::~WindowPwm()
{
    delete m_ui;
}

/* slots */

void WindowPwm::on_msg_ok(const QString val1, const QString)
{
    if (m_ch1_wantSwitch)
    {
        m_ch1_wantSwitch = false;
        m_ch1_enabled = !m_ch1_enabled;
    }

    if (m_ch2_wantSwitch)
    {
        m_ch2_wantSwitch = false;
        m_ch2_enabled = !m_ch2_enabled;
    }

    m_ui->textBrowser_realFreq->setHtml("<p align=\"right\">" + formatFreq(val1) + " Hz&nbsp;</p>");

    enableAll(true);
}

void WindowPwm::on_msg_err(const QString text, MsgBoxType type, bool needClose)
{
    m_activeMsgs.clear();

    if (needClose)
        this->close();
    else
        enableAll(true);

    msgBox(this, text, type);
}

void WindowPwm::on_msg_set(int freq, int duty1, int duty2, int offset, bool en1, bool en2, const QString freq_real)
{
    m_ignoreValuesChanged = true;

    m_ui->spinBox_freq->setValue(freq);
    m_ui->spinBox_duty1->setValue(duty1);
    m_ui->spinBox_duty2->setValue(duty2);
    m_ui->spinBox_offset->setValue(offset);

    m_ui->dial_freq->setValue((int)lin_to_exp_1to36M((int)freq, true));
    m_ui->dial_duty1->setValue(duty1);
    m_ui->dial_duty2->setValue(duty2);
    m_ui->dial_offset->setValue(offset);

    auto info = Core::getInstance()->getDevInfo();

    m_ui->spinBox_freq->setRange(1, info->pwm_fs);
    m_ui->dial_freq->setRange(1, info->pwm_fs);

    m_ui->textBrowser_realFreq->setHtml("<p align=\"right\">" + formatFreq(freq_real) + " Hz&nbsp;</p>");

    m_ignoreValuesChanged = false;

    m_ch1_enabled = en1;
    m_ch2_enabled = en2;

    enableAll(true);
}

void WindowPwm::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

void WindowPwm::on_spinBox_freq_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_freq->setValue((int)lin_to_exp_1to36M((int)m_ui->spinBox_freq->value(), true));
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled, m_ch2_enabled);
}

void WindowPwm::on_dial_freq_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_freq->setValue((int)lin_to_exp_1to36M((int)value));
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled, m_ch2_enabled);
}

void WindowPwm::on_spinBox_duty1_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_duty1->setValue(m_ui->spinBox_duty1->value());
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled, m_ch2_enabled);
}

void WindowPwm::on_dial_duty1_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_duty1->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled, m_ch2_enabled);
}

void WindowPwm::on_spinBox_duty2_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_duty2->setValue(m_ui->spinBox_duty2->value());
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled, m_ch2_enabled);
}

void WindowPwm::on_dial_duty2_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_duty2->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled, m_ch2_enabled);
}

void WindowPwm::on_spinBox_offset_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_offset->setValue(m_ui->spinBox_offset->value());
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled, m_ch2_enabled);
}

void WindowPwm::on_dial_offset_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_offset->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled, m_ch2_enabled);
}

void WindowPwm::on_pushButton_ch2disable_clicked()
{
    m_ch2_wantSwitch = true;
    sendSet(m_ch1_enabled, false);
}

void WindowPwm::on_pushButton_ch2enable_clicked()
{
    m_ch2_wantSwitch = true;
    sendSet(m_ch1_enabled, true);
}

void WindowPwm::on_pushButton_ch1disable_clicked()
{
    m_ch1_wantSwitch = true;
    sendSet(false, m_ch2_enabled);
}

void WindowPwm::on_pushButton_ch1enable_clicked()
{
    m_ch1_wantSwitch = true;
    sendSet(true, m_ch2_enabled);
}

void WindowPwm::on_radioButton_coarse_clicked()
{
    m_ui->dial_freq->setSingleStep(100);
    m_ui->dial_freq->setPageStep(1000);

    m_ui->spinBox_freq->setSingleStep(100);

    m_ui->dial_freq->setNotchTarget(0.5);
}

void WindowPwm::on_radioButton_fine_clicked()
{
    m_ui->dial_freq->setSingleStep(1);
    m_ui->dial_freq->setPageStep(10);

    m_ui->spinBox_freq->setSingleStep(1);

    m_ui->dial_freq->setNotchTarget(25);
}

/* private */

void WindowPwm::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();
    m_instrEnabled = false;

    emit closing(WindowPwm::staticMetaObject.className());
}

void WindowPwm::showEvent(QShowEvent*)
{
    m_ui->pushButton_ch1enable->show();
    m_ui->pushButton_ch1disable->hide();

    m_ui->pushButton_ch2enable->show();
    m_ui->pushButton_ch2disable->hide();

    enableAll(false);
    m_instrEnabled = true;

    Core::getInstance()->msgAdd(m_msg_set, true, "");
}

void WindowPwm::enableAll(bool enable)
{
    m_ui->pushButton_ch1enable->setEnabled(enable);
    m_ui->pushButton_ch2enable->setEnabled(enable);

    m_ui->pushButton_ch1disable->setEnabled(enable);
    m_ui->pushButton_ch2disable->setEnabled(enable);

    m_ui->spinBox_freq->setEnabled(enable);
    m_ui->spinBox_duty1->setEnabled(enable);
    m_ui->spinBox_duty2->setEnabled(enable);
    m_ui->spinBox_offset->setEnabled(enable);

    m_ui->dial_freq->setEnabled(enable);
    m_ui->dial_duty1->setEnabled(enable);
    m_ui->dial_duty2->setEnabled(enable);
    m_ui->dial_offset->setEnabled(enable);

    m_ui->textBrowser_realFreq->setEnabled(enable);

    if (enable)
    {
        m_status_enabled->setText(" Ch1: " + QString(m_ch1_enabled ? "Enabled" : "Disabled") +
                                  "     Ch2: " + QString(m_ch2_enabled ? "Enabled" : "Disabled"));

        if (m_ch1_enabled)
        {
            m_ui->pushButton_ch1enable->hide();
            m_ui->pushButton_ch1disable->show();
        }
        else
        {
            m_ui->pushButton_ch1enable->show();
            m_ui->pushButton_ch1disable->hide();
        }

        if (m_ch2_enabled)
        {
            m_ui->pushButton_ch2enable->hide();
            m_ui->pushButton_ch2disable->show();
        }
        else
        {
            m_ui->pushButton_ch2enable->show();
            m_ui->pushButton_ch2disable->hide();
        }
    }
    else
    {
        m_status_enabled->setText(" Wait...");
    }
}

void WindowPwm::sendSet(bool en1, bool en2)
{
    enableAll(false);

    Core::getInstance()->msgAdd(m_msg_set, false, QString::number(m_ui->spinBox_freq->value()) + EMBO_DELIM2 +
                                                  QString::number(m_ui->spinBox_duty1->value()) + EMBO_DELIM2 +
                                                  QString::number(m_ui->spinBox_duty2->value()) + EMBO_DELIM2 +
                                                  QString::number(m_ui->spinBox_offset->value()) + EMBO_DELIM2 +
                                                  (en1 ? EMBO_SET_TRUE : EMBO_SET_FALSE) + EMBO_DELIM2 +
                                                  (en2 ? EMBO_SET_TRUE : EMBO_SET_FALSE));
}

QString WindowPwm::formatFreq(QString freq)
{
    int w_size = freq.size();
    if (w_size > 7)
        freq.insert(freq.size() - 7, " ");
    if (w_size > 10)
        freq.insert(freq.size() - 11, " ");
    return freq;
}
