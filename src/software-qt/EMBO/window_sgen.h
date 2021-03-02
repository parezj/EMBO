/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_SGEN_H
#define WINDOW_SGEN_H

#include "interfaces.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class WindowSgen; }
QT_END_NAMESPACE


class WindowSgen : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowSgen(QWidget *parent = nullptr);
    ~WindowSgen();

    Msg* getActiveMsg() override { return m_activeMsg; };

signals:
    void closing(const char* className);

private slots:
    void on_actionAbout_triggered();

private:
    void closeEvent(QCloseEvent *event) override;

    Ui::WindowSgen* m_ui;

    /* messages */
    Msg* m_activeMsg = Q_NULLPTR;

    //Msg_CNTR_Enable* m_msg_enable;
   // Msg_CNTR_Read* m_msg_read;
};

#endif // WINDOW_SGEN_H
