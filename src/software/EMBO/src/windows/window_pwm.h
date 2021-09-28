/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_PWM_H
#define WINDOW_PWM_H

#include "interfaces.h"
#include "messages.h"

#include <QMainWindow>
#include <QLabel>
#include <QButtonGroup>


QT_BEGIN_NAMESPACE
namespace Ui { class WindowPwm; }
QT_END_NAMESPACE


class WindowPwm : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowPwm(QWidget *parent = nullptr);
    ~WindowPwm();

    bool getInstrEnabled() override { return m_instrEnabled; };
    std::vector<Msg*>& getActiveMsgs() override { return m_activeMsgs; };
    static const QString getFreqReal() { return s_freq_real; }

signals:
    void closing(const char* className);

private slots:
    void on_msg_ok(const QString val1, const QString);
    void on_msg_err(const QString text, MsgBoxType type, bool needClose);
    void on_msg_set(int freq, int duty1, int duty2, int offset, bool en1, bool en2, const QString freq_real);

    void on_actionAbout_triggered();
    void on_spinBox_duty1_valueChanged(int arg1);
    void on_spinBox_freq_valueChanged(int arg1);
    void on_dial_freq_valueChanged(int value);
    void on_dial_duty1_valueChanged(int value);
    void on_spinBox_duty2_valueChanged(int arg1);
    void on_dial_duty2_valueChanged(int value);
    void on_spinBox_offset_valueChanged(int arg1);
    void on_dial_offset_valueChanged(int value);
    void on_pushButton_ch2disable_clicked();
    void on_pushButton_ch2enable_clicked();
    void on_pushButton_ch1disable_clicked();
    void on_pushButton_ch1enable_clicked();

    void on_radioButton_coarse_clicked();

    void on_radioButton_fine_clicked();

private:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

    void enableAll(bool enable);
    void sendSet(bool en1, bool en2);
    QString formatFreq(QString freq);

    /* main window */
    Ui::WindowPwm* m_ui;

    /* messages */
    Msg_PWM_Set* m_msg_set;

    /* status bar */
    QLabel* m_status_enabled;

    /* helpers */
    QButtonGroup m_mode;
    bool m_ignoreValuesChanged = false;
    bool m_ch1_wantSwitch = false;
    bool m_ch2_wantSwitch = false;

    /* data */
    bool m_ch1_enabled = false;
    bool m_ch2_enabled = false;
    static QString s_freq_real;
};

#endif // WINDOW_PWM_H
