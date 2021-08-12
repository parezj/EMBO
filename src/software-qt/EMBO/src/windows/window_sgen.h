/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_SGEN_H
#define WINDOW_SGEN_H

#include "interfaces.h"
#include "messages.h"

#include <QMainWindow>
#include <QLabel>
#include <QButtonGroup>


QT_BEGIN_NAMESPACE
namespace Ui { class WindowSgen; }
QT_END_NAMESPACE


class WindowSgen : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowSgen(QWidget *parent = nullptr);
    ~WindowSgen();

    bool getInstrEnabled() override { return m_instrEnabled; };
    std::vector<Msg*>& getActiveMsgs() override { return m_activeMsgs; };

signals:
    void closing(const char* className);

private slots:
    void on_msg_ok(const QString real_freq, const QString N);
    void on_msg_err(const QString text, MsgBoxType type, bool needClose);
    void on_msg_set(double freq, int ampl, int offset, int phase, SgenMode mode, bool enable, const QString real_freq, const QString N);

    void on_msg_ok2(const QString real_freq, const QString N);
    void on_msg_set2(double freq, int ampl, int offset, int phase, SgenMode mode, bool enable, const QString real_freq, const QString N);

    void on_actionAbout_triggered();

    void on_spinBox_freq_valueChanged(int arg1);
    void on_dial_freq_valueChanged(int value);
    void on_doubleSpinBox_ampl_valueChanged(double arg1);
    void on_dial_ampl_valueChanged(int value);
    void on_spinBox_offset_valueChanged(int arg1);
    void on_dial_offset_valueChanged(int value);
    void on_spinBox_phase_valueChanged(int arg1);
    void on_dial_phase_valueChanged(int value);
    void on_pushButton_enable_clicked();
    void on_pushButton_disable_clicked();

    void on_radioButton_saw_clicked();
    void on_radioButton_const_clicked();
    void on_radioButton_sine_clicked();
    void on_radioButton_triangle_clicked();
    void on_radioButton_square_clicked();
    void on_radioButton_noise_clicked();

    void on_spinBox_freq2_valueChanged(int arg1);
    void on_dial_freq2_valueChanged(int value);
    void on_doubleSpinBox_ampl2_valueChanged(double arg1);
    void on_dial_ampl2_valueChanged(int value);
    void on_spinBox_offset2_valueChanged(int arg1);
    void on_dial_offset2_valueChanged(int value);
    void on_spinBox_phase2_valueChanged(int arg1);
    void on_dial_phase2_valueChanged(int value);
    void on_pushButton_enable2_clicked();
    void on_pushButton_disable2_clicked();

    void on_radioButton_saw2_clicked();
    void on_radioButton_const2_clicked();
    void on_radioButton_sine2_clicked();
    void on_radioButton_triangle2_clicked();
    void on_radioButton_square2_clicked();
    void on_radioButton_noise2_clicked();

private:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

    void enableAll(bool enable);
    void sendSet(bool enable);
    void sendSet2(bool enable);

    /* main window */
    Ui::WindowSgen* m_ui;

    /* messages */
    Msg_SGEN_Set* m_msg_set;
    Msg_SGEN_Set* m_msg_set2;

    /* helpers */
    bool m_ch1_enabled = false;
    bool m_ch2_enabled = false;
    bool m_ignoreValuesChanged = false;
    bool m_ch_wantSwitch = false;
    bool m_ch_wantSwitch2 = false;
    QButtonGroup m_mode;
    QButtonGroup m_mode2;

    /* data */
    QString m_real_freq;
    QString m_N;
    QString m_real_freq2;
    QString m_N2;

    /* status bar */
    QLabel* m_status_enabled;
};

#endif // WINDOW_SGEN_H
