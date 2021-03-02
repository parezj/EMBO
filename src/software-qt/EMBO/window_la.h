/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_LA_H
#define WINDOW_LA_H

#include "interfaces.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class WindowLa; }
QT_END_NAMESPACE


class WindowLa : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowLa(QWidget *parent = nullptr);
    ~WindowLa();

    Msg* getActiveMsg() override { return m_activeMsg; };

signals:
    void closing(const char* className);

private slots:
    void on_actionHelp_triggered();

private:
    void closeEvent(QCloseEvent *event) override;

    Ui::WindowLa* m_ui;

    /* messages */
    Msg* m_activeMsg = Q_NULLPTR;

    //Msg_CNTR_Enable* m_msg_enable;
   // Msg_CNTR_Read* m_msg_read;
};

#endif // WINDOW_LA_H
