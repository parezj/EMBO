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
    m_msg_set2 = new Msg_SGEN_Set(this);

    connect(m_msg_set, &Msg_SGEN_Set::ok, this, &WindowSgen::on_msg_ok, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_SGEN_Set::err, this, &WindowSgen::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_SGEN_Set::result, this, &WindowSgen::on_msg_set, Qt::QueuedConnection);

    connect(m_msg_set2, &Msg_SGEN_Set::ok, this, &WindowSgen::on_msg_ok2, Qt::QueuedConnection);
    connect(m_msg_set2, &Msg_SGEN_Set::err, this, &WindowSgen::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_set2, &Msg_SGEN_Set::result, this, &WindowSgen::on_msg_set2, Qt::QueuedConnection);

    connect(m_ui->actionEMBO_Help, SIGNAL(triggered()), Core::getInstance(), SLOT(on_actionEMBO_Help()));

    m_status_enabled = new QLabel(" Disabled", this);
    QWidget* widget = new QWidget(this);
    QFont font1("Roboto", 11, QFont::Normal);
    m_status_enabled->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/img/sgen2.png");

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
    on_radioButton_sine_clicked();

    m_mode2.addButton(m_ui->radioButton_const2);
    m_mode2.addButton(m_ui->radioButton_sine2);
    m_mode2.addButton(m_ui->radioButton_triangle2);
    m_mode2.addButton(m_ui->radioButton_saw2);
    m_mode2.addButton(m_ui->radioButton_square2);
    m_mode2.addButton(m_ui->radioButton_noise2);

    m_mode2.setExclusive(true);
    m_ui->radioButton_sine2->setChecked(true);
    on_radioButton_sine2_clicked();

    m_ui->pushButton_enable->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_SGEN_ON);
    m_ui->pushButton_disable->setStyleSheet(CSS_BUTTON_OFF_NODIS CSS_BUTTON_SGEN_ON);

    m_ui->pushButton_enable2->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_SGEN_ON);
    m_ui->pushButton_disable2->setStyleSheet(CSS_BUTTON_OFF_NODIS CSS_BUTTON_SGEN_ON);

    m_ui->radioButton_const->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_sine->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_triangle->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_saw->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_square->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_noise->setStyleSheet(CSS_RADIOBUTTON_NODIS);

    m_ui->radioButton_const2->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_sine2->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_triangle2->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_saw2->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_square2->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_noise2->setStyleSheet(CSS_RADIOBUTTON_NODIS);

    m_ui->spinBox_freq->setStyleSheet(CSS_SPINBOX_NODIS);
    m_ui->doubleSpinBox_ampl->setStyleSheet(CSS_DSPINBOX_NODIS);
    m_ui->spinBox_offset->setStyleSheet(CSS_SPINBOX_NODIS);
    m_ui->spinBox_phase->setStyleSheet(CSS_SPINBOX_NODIS);

    m_ui->spinBox_freq2->setStyleSheet(CSS_SPINBOX_NODIS);
    m_ui->doubleSpinBox_ampl2->setStyleSheet(CSS_DSPINBOX_NODIS);
    m_ui->spinBox_offset2->setStyleSheet(CSS_SPINBOX_NODIS);
    m_ui->spinBox_phase2->setStyleSheet(CSS_SPINBOX_NODIS);
}

WindowSgen::~WindowSgen()
{
    delete m_ui;
}

/* slots */

void WindowSgen::on_msg_ok(const QString real_freq, const QString N)
{
    if (m_ch_wantSwitch)
    {
        m_ch_wantSwitch = false;
        m_ch1_enabled = !m_ch1_enabled;
    }

    m_real_freq = real_freq;
    m_N = N;

    enableAll(true);
}

void WindowSgen::on_msg_ok2(const QString real_freq, const QString N)
{
    if (m_ch_wantSwitch2)
    {
        m_ch_wantSwitch2 = false;
        m_ch2_enabled = !m_ch2_enabled;
    }

    m_real_freq2 = real_freq;
    m_N2 = N;

    enableAll(true);
}

void WindowSgen::on_msg_err(const QString text, MsgBoxType type, bool needClose)
{
    m_activeMsgs.clear();

    if (needClose)
        this->close();
    else
    {
        enableAll(true);
    }

    msgBox(this, text, type);
}

void WindowSgen::on_msg_set(double freq, int ampl, int offset, int phase, SgenMode mode, bool enable, const QString real_freq, const QString N)
{
    m_ignoreValuesChanged = true;

    m_ui->spinBox_freq->setValue(freq);
    m_ui->doubleSpinBox_ampl->setValue(ampl / 10.0);
    m_ui->spinBox_offset->setValue(offset);
    m_ui->spinBox_phase->setValue(phase);

    switch (mode)
    {
        default:
        case SgenMode::CONSTANT: m_ui->radioButton_const->setChecked(true); break;
        case SgenMode::SINE: m_ui->radioButton_sine->setChecked(true); break;
        case SgenMode::TRIANGLE: m_ui->radioButton_triangle->setChecked(true); break;
        case SgenMode::SAWTOOTH: m_ui->radioButton_saw->setChecked(true); break;
        case SgenMode::SQUARE: m_ui->radioButton_square->setChecked(true); break;
        case SgenMode::NOISE: m_ui->radioButton_noise->setChecked(true); break;
    }

    m_ui->dial_freq->setValue(freq);
    m_ui->dial_ampl->setValue(ampl / 10.0);
    m_ui->dial_offset->setValue(offset);
    m_ui->dial_phase->setValue(phase);

    auto info = Core::getInstance()->getDevInfo();

    m_ui->spinBox_freq->setRange(1, info->sgen_maxf);
    m_ui->dial_freq->setRange(1, info->sgen_maxf);
    m_ui->dial_freq->setNotchTarget(info->sgen_maxf / 100000);

    m_real_freq = real_freq;
    m_N = N;

    m_ignoreValuesChanged = false;

    m_ch1_enabled = enable;

    enableAll(true);
}

void WindowSgen::on_msg_set2(double freq, int ampl, int offset, int phase, SgenMode mode, bool enable, const QString real_freq, const QString N)
{
    m_ignoreValuesChanged = true;

    m_ui->spinBox_freq2->setValue(freq);
    m_ui->doubleSpinBox_ampl2->setValue(ampl / 10.0);
    m_ui->spinBox_offset2->setValue(offset);
    m_ui->spinBox_phase2->setValue(phase);

    switch (mode)
    {
        default:
        case SgenMode::CONSTANT: m_ui->radioButton_const2->setChecked(true); break;
        case SgenMode::SINE: m_ui->radioButton_sine2->setChecked(true); break;
        case SgenMode::TRIANGLE: m_ui->radioButton_triangle2->setChecked(true); break;
        case SgenMode::SAWTOOTH: m_ui->radioButton_saw2->setChecked(true); break;
        case SgenMode::SQUARE: m_ui->radioButton_square2->setChecked(true); break;
        case SgenMode::NOISE: m_ui->radioButton_noise2->setChecked(true); break;
    }

    m_ui->dial_freq2->setValue(freq);
    m_ui->dial_ampl2->setValue(ampl / 10.0);
    m_ui->dial_offset2->setValue(offset);
    m_ui->dial_phase2->setValue(phase);

    auto info = Core::getInstance()->getDevInfo();

    m_ui->spinBox_freq2->setRange(1, info->sgen_maxf);
    m_ui->dial_freq2->setRange(1, info->sgen_maxf);
    m_ui->dial_freq2->setNotchTarget(info->sgen_maxf / 100000);

    m_real_freq2 = real_freq;
    m_N2 = N;

    m_ignoreValuesChanged = false;

    m_ch2_enabled = enable;

    enableAll(true);
}

void WindowSgen::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/* ch1 slots */

void WindowSgen::on_spinBox_freq_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_freq->setValue(m_ui->spinBox_freq->value());
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_dial_freq_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_freq->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_doubleSpinBox_ampl_valueChanged(double)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_ampl->setValue(m_ui->doubleSpinBox_ampl->value());
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_dial_ampl_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->doubleSpinBox_ampl->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_spinBox_offset_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_offset->setValue(m_ui->spinBox_offset->value());
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_dial_offset_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_offset->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_spinBox_phase_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_phase->setValue(m_ui->spinBox_phase->value());
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_dial_phase_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_phase->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_pushButton_enable_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    m_ch_wantSwitch = true;
    sendSet(true);
}

void WindowSgen::on_pushButton_disable_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    m_ch_wantSwitch = true;
    sendSet(false);
}

void WindowSgen::on_radioButton_const_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_radioButton_sine_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_radioButton_triangle_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_radioButton_saw_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_radioButton_square_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet(m_ch1_enabled);
}

void WindowSgen::on_radioButton_noise_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet(m_ch1_enabled);
}

/* ch2 slots */

void WindowSgen::on_spinBox_freq2_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_freq2->setValue(m_ui->spinBox_freq2->value());
    m_ignoreValuesChanged = false;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_dial_freq2_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_freq2->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_doubleSpinBox_ampl2_valueChanged(double)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_ampl2->setValue(m_ui->doubleSpinBox_ampl2->value());
    m_ignoreValuesChanged = false;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_dial_ampl2_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->doubleSpinBox_ampl2->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_spinBox_offset2_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_offset2->setValue(m_ui->spinBox_offset2->value());
    m_ignoreValuesChanged = false;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_dial_offset2_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_offset2->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_spinBox_phase2_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_phase2->setValue(m_ui->spinBox_phase2->value());
    m_ignoreValuesChanged = false;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_dial_phase2_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_phase2->setValue(value);
    m_ignoreValuesChanged = false;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_pushButton_enable2_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    m_ch_wantSwitch2 = true;
    sendSet2(true);
}

void WindowSgen::on_pushButton_disable2_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    m_ch_wantSwitch2 = true;
    sendSet2(false);
}

void WindowSgen::on_radioButton_const2_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_radioButton_sine2_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_radioButton_triangle2_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_radioButton_saw2_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_radioButton_square2_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet2(m_ch2_enabled);
}

void WindowSgen::on_radioButton_noise2_clicked()
{
    if (m_ignoreValuesChanged)
        return;

    sendSet2(m_ch2_enabled);
}

/* private */

void WindowSgen::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();
    emit closing(WindowSgen::staticMetaObject.className());
}

void WindowSgen::showEvent(QShowEvent*)
{
    m_ignoreValuesChanged = true;

    auto info = Core::getInstance()->getDevInfo();

    m_ui->pushButton_enable->show();
    m_ui->pushButton_disable->hide();

    m_ui->pushButton_enable2->show();
    m_ui->pushButton_disable2->hide();

    if (info->dac == 1)
    {
        m_ui->pushButton_enable2->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_SGEN_ON);
        m_ui->pushButton_disable2->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_SGEN_ON);

        m_ui->spinBox_freq2->setStyleSheet(CSS_SPINBOX);
        m_ui->doubleSpinBox_ampl2->setStyleSheet(CSS_DSPINBOX2);
        m_ui->spinBox_offset2->setStyleSheet(CSS_SPINBOX);
        m_ui->spinBox_phase2->setStyleSheet(CSS_SPINBOX);

        m_ui->radioButton_const2->setStyleSheet(CSS_RADIOBUTTON);
        m_ui->radioButton_sine2->setStyleSheet(CSS_RADIOBUTTON);
        m_ui->radioButton_triangle2->setStyleSheet(CSS_RADIOBUTTON);
        m_ui->radioButton_saw2->setStyleSheet(CSS_RADIOBUTTON);
        m_ui->radioButton_square2->setStyleSheet(CSS_RADIOBUTTON);
        m_ui->radioButton_noise2->setStyleSheet(CSS_RADIOBUTTON);

        m_ui->groupBox_ch2->setEnabled(false);

        m_ui->pushButton_enable2->setEnabled(false);
        m_ui->pushButton_disable2->setEnabled(false);

        m_ui->dial_freq2->hide();
        m_ui->dial_ampl2->hide();
        m_ui->dial_offset2->hide();
        m_ui->dial_phase2->hide();
    }

    enableAll(false);

    m_ignoreValuesChanged = false;

    Core::getInstance()->msgAdd(m_msg_set, true, "1");
    if (info->dac == 2)
        Core::getInstance()->msgAdd(m_msg_set2, true, "2");
}

void WindowSgen::enableAll(bool enable)
{
    auto info = Core::getInstance()->getDevInfo();

    m_ui->pushButton_enable->setEnabled(enable);
    m_ui->pushButton_disable->setEnabled(enable);

    m_ui->spinBox_freq->setEnabled(enable);
    m_ui->doubleSpinBox_ampl->setEnabled(enable);
    m_ui->spinBox_offset->setEnabled(enable);
    m_ui->spinBox_phase->setEnabled(enable);

    m_ui->dial_freq->setEnabled(enable);
    m_ui->dial_ampl->setEnabled(enable);
    m_ui->dial_offset->setEnabled(enable);
    m_ui->dial_phase->setEnabled(enable);

    m_ui->radioButton_const->setEnabled(enable);
    m_ui->radioButton_sine->setEnabled(enable);
    m_ui->radioButton_triangle->setEnabled(enable);
    m_ui->radioButton_saw->setEnabled(enable);
    m_ui->radioButton_square->setEnabled(enable);
    m_ui->radioButton_noise->setEnabled(enable);

    m_ui->textBrowser_realFs->setText(m_real_freq + " Hz");
    m_ui->textBrowser_N->setText(m_N);
    m_ui->textBrowser_Ampl->setText(QString::number(m_ui->doubleSpinBox_ampl->value() / 100.0 * info->ref_mv, 10, 1) + " mV");

    if (m_ui->radioButton_const->isChecked())
    {
        m_ui->dial_freq->hide();
        m_ui->dial_offset->hide();
        m_ui->dial_phase->hide();

        m_ui->textBrowser_realFs->setText("");

        m_ui->spinBox_freq->setEnabled(false);
        m_ui->spinBox_offset->setEnabled(false);
        m_ui->spinBox_phase->setEnabled(false);

        m_ui->label_freq->setEnabled(false);
        m_ui->label_offset->setEnabled(false);
        m_ui->label_phase->setEnabled(false);

        m_ui->spinBox_freq->setStyleSheet(CSS_SPINBOX);
        m_ui->spinBox_offset->setStyleSheet(CSS_SPINBOX);
        m_ui->spinBox_phase->setStyleSheet(CSS_SPINBOX);
    }
    else
    {
        m_ui->dial_freq->show();
        m_ui->dial_offset->show();
        m_ui->dial_phase->show();

        m_ui->label_freq->setEnabled(true);
        m_ui->label_offset->setEnabled(true);
        m_ui->label_phase->setEnabled(true);

        m_ui->spinBox_freq->setStyleSheet(CSS_SPINBOX_NODIS);
        m_ui->spinBox_offset->setStyleSheet(CSS_SPINBOX_NODIS);
        m_ui->spinBox_phase->setStyleSheet(CSS_SPINBOX_NODIS);
    }

    if (info->dac == 2)
    {
        m_ui->pushButton_enable2->setEnabled(enable);
        m_ui->pushButton_disable2->setEnabled(enable);

        m_ui->spinBox_freq2->setEnabled(enable);
        m_ui->doubleSpinBox_ampl2->setEnabled(enable);
        m_ui->spinBox_offset2->setEnabled(enable);
        m_ui->spinBox_phase2->setEnabled(enable);

        m_ui->dial_freq2->setEnabled(enable);
        m_ui->dial_ampl2->setEnabled(enable);
        m_ui->dial_offset2->setEnabled(enable);
        m_ui->dial_phase2->setEnabled(enable);

        m_ui->radioButton_const2->setEnabled(enable);
        m_ui->radioButton_sine2->setEnabled(enable);
        m_ui->radioButton_triangle2->setEnabled(enable);
        m_ui->radioButton_saw2->setEnabled(enable);
        m_ui->radioButton_square2->setEnabled(enable);
        m_ui->radioButton_noise2->setEnabled(enable);

        m_ui->textBrowser_realFs2->setText(m_real_freq2 + " Hz");
        m_ui->textBrowser_N2->setText(m_N2);
        m_ui->textBrowser_Ampl2->setText(QString::number(m_ui->doubleSpinBox_ampl2->value() / 100.0 * info->ref_mv, 10, 1) + " mV");

        if (m_ui->radioButton_const2->isChecked())
        {
            m_ui->dial_freq2->hide();
            m_ui->dial_offset2->hide();
            m_ui->dial_phase2->hide();

            m_ui->label_freq2->setEnabled(false);
            m_ui->label_offset2->setEnabled(false);
            m_ui->label_phase2->setEnabled(false);

            m_ui->textBrowser_realFs2->setText("");

            m_ui->spinBox_freq2->setEnabled(false);
            m_ui->spinBox_offset2->setEnabled(false);
            m_ui->spinBox_phase2->setEnabled(false);

            m_ui->spinBox_freq2->setStyleSheet(CSS_SPINBOX);
            m_ui->spinBox_offset2->setStyleSheet(CSS_SPINBOX);
            m_ui->spinBox_phase2->setStyleSheet(CSS_SPINBOX);
        }
        else
        {
            m_ui->dial_freq2->show();
            m_ui->dial_offset2->show();
            m_ui->dial_phase2->show();

            m_ui->label_freq2->setEnabled(true);
            m_ui->label_offset2->setEnabled(true);
            m_ui->label_phase2->setEnabled(true);

            m_ui->spinBox_freq2->setStyleSheet(CSS_SPINBOX_NODIS);
            m_ui->spinBox_offset2->setStyleSheet(CSS_SPINBOX_NODIS);
            m_ui->spinBox_phase2->setStyleSheet(CSS_SPINBOX_NODIS);
        }
    }

    if (enable)
    {
        if (info->dac == 1)
        {
            m_status_enabled->setText(" Ch1: " + QString(m_ch1_enabled ? "ON" : "OFF"));
        }
        else
        {
            m_status_enabled->setText(" Ch1: " + QString(m_ch1_enabled ? "ON" : "OFF") +
                                  "     Ch2: " + QString(m_ch2_enabled ? "ON" : "OFF"));
        }

        if (m_ch1_enabled)
        {
            m_ui->pushButton_enable->hide();
            m_ui->pushButton_disable->show();
        }
        else
        {
            m_ui->pushButton_enable->show();
            m_ui->pushButton_disable->hide();
        }

        if (info->dac == 2)
        {
            if (m_ch2_enabled)
            {
                m_ui->pushButton_enable2->hide();
                m_ui->pushButton_disable2->show();
            }
            else
            {
                m_ui->pushButton_enable2->show();
                m_ui->pushButton_disable2->hide();
            }
        }
    }
    else
    {
        m_status_enabled->setText(" Wait...");
    }
}

void WindowSgen::sendSet(bool enable)
{
    enableAll(false);

    int mode;

    if      (m_ui->radioButton_const->isChecked())    mode = 0;
    else if (m_ui->radioButton_sine->isChecked())     mode = 1;
    else if (m_ui->radioButton_triangle->isChecked()) mode = 2;
    else if (m_ui->radioButton_saw->isChecked())      mode = 3;
    else if (m_ui->radioButton_square->isChecked())   mode = 4;
    else                                              mode = 5;

    Core::getInstance()->msgAdd(m_msg_set, false, "1" EMBO_DELIM2 +
                                                      QString::number(m_ui->spinBox_freq->value()) + EMBO_DELIM2 +
                                                      QString::number(m_ui->doubleSpinBox_ampl->value() * 10.0) + EMBO_DELIM2 +
                                                      QString::number(m_ui->spinBox_offset->value()) + EMBO_DELIM2 +
                                                      QString::number(m_ui->spinBox_phase->value()) + EMBO_DELIM2 +
                                                      QString::number(mode) + EMBO_DELIM2 +
                                                      (enable ? "1" : "0"));
}

void WindowSgen::sendSet2(bool enable)
{
    enableAll(false);

    int mode2;

    if      (m_ui->radioButton_const2->isChecked())    mode2 = 0;
    else if (m_ui->radioButton_sine2->isChecked())     mode2 = 1;
    else if (m_ui->radioButton_triangle2->isChecked()) mode2 = 2;
    else if (m_ui->radioButton_saw2->isChecked())      mode2 = 3;
    else if (m_ui->radioButton_square2->isChecked())   mode2 = 4;
    else                                               mode2 = 5;

    Core::getInstance()->msgAdd(m_msg_set2, false, "2" EMBO_DELIM2 +
                                                       QString::number(m_ui->spinBox_freq2->value()) + EMBO_DELIM2 +
                                                       QString::number(m_ui->doubleSpinBox_ampl2->value() * 10.0) + EMBO_DELIM2 +
                                                       QString::number(m_ui->spinBox_offset2->value()) + EMBO_DELIM2 +
                                                       QString::number(m_ui->spinBox_phase2->value()) + EMBO_DELIM2 +
                                                       QString::number(mode2) + EMBO_DELIM2 +
                                                       (enable ? "1" : "0"));
}
