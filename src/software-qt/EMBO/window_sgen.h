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
    Msg* getActiveMsg() override { return m_activeMsg; };

signals:
    void closing(const char* className);

private slots:
    void on_msg_err(QString text, MsgBoxType type, bool needClose);
    void on_msg_set(SgenMode mode, double freq, int ampl, int offset);

    void on_actionAbout_triggered();
    void on_spinBox_freq_valueChanged(int arg1);
    void on_dial_freq_valueChanged(int value);
    void on_spinBox_ampl_valueChanged(int arg1);
    void on_dial_ampl_valueChanged(int value);
    void on_spinBox_offset_valueChanged(int arg1);
    void on_dial_offset_valueChanged(int value);
    void on_pushButton_enable_clicked();
    void on_pushButton_disable_clicked();

    void on_radioButton_saw_clicked();
    void on_radioButton_const_clicked();
    void on_radioButton_sine_clicked();
    void on_radioButton_triangle_clicked();
    void on_radioButton_square_clicked();
    void on_radioButton_noise_clicked();

private:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

    QLabel* m_status_enabled;

    QButtonGroup m_mode;

    Ui::WindowSgen* m_ui;

    /* messages */
    Msg_SGEN_Set* m_msg_set;
};

#endif // WINDOW_SGEN_H
