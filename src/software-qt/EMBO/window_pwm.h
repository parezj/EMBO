/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_PWM_H
#define WINDOW_PWM_H

#include "interfaces.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class WindowPwm; }
QT_END_NAMESPACE


class WindowPwm : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowPwm(QWidget *parent = nullptr);
    ~WindowPwm();

    Msg* getActiveMsg() override { return m_activeMsg; };

signals:
    void closing(const char* className);

private slots:
    void on_actionHelp_triggered();

private:
    void closeEvent(QCloseEvent *event) override;

    Ui::WindowPwm* m_ui;

    /* messages */
    Msg* m_activeMsg = Q_NULLPTR;

    //Msg_CNTR_Enable* m_msg_enable;
   // Msg_CNTR_Read* m_msg_read;
};

#endif // WINDOW_PWM_H
