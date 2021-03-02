/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_VM_H
#define WINDOW_VM_H

#include "interfaces.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class WindowVm; }
QT_END_NAMESPACE


class WindowVm : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowVm(QWidget *parent = nullptr);
    ~WindowVm();

    Msg* getActiveMsg() override { return m_activeMsg; };

signals:
    void closing(const char* className);

private slots:
    void on_actionAbout_triggered();

private:
    void closeEvent(QCloseEvent *event) override;

    Ui::WindowVm* m_ui;

    /* messages */
    Msg* m_activeMsg = Q_NULLPTR;

    //Msg_CNTR_Enable* m_msg_enable;
   // Msg_CNTR_Read* m_msg_read;
};

#endif // WINDOW_VM_H
