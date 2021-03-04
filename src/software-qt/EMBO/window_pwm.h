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
    Msg* getActiveMsg() override { return m_activeMsg; };

signals:
    void closing(const char* className);

private slots:
    void on_msg_err(QString text, MsgBoxType type, bool needClose);
    void on_msg_set(double freq, int duty, int duty2, int offset, bool en1, bool en2);

    void on_actionAbout_triggered();
    void on_spinBox_duty1_valueChanged(int arg1);
    void on_spinBox_freq_valueChanged(int arg1);
    void on_horizontalSlider_freq_sliderMoved(int position);
    void on_dial_freq_sliderMoved(int position);
    void on_dial_duty1_valueChanged(int value);
    void on_spinBox_duty2_valueChanged(int arg1);
    void on_dial_duty2_valueChanged(int value);
    void on_spinBox_offset_valueChanged(int arg1);
    void on_dial_offset_valueChanged(int value);
    void on_pushButton_ch2disable_clicked();
    void on_pushButton_ch2enable_clicked();
    void on_pushButton_ch1disable_clicked();
    void on_pushButton_ch1enable_clicked();

private:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

    QLabel* m_status_enabled;

    Ui::WindowPwm* m_ui;

    /* messages */
    Msg_PWM_Set* m_msg_set;
};

#endif // WINDOW_PWM_H
