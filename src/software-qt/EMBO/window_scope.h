/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_SCOPE_H
#define WINDOW_SCOPE_H

#include "interfaces.h"
#include "messages.h"

#include <QMainWindow>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class WindowScope; }
QT_END_NAMESPACE


class WindowScope : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowScope(QWidget *parent = nullptr);
    ~WindowScope();

    bool getInstrEnabled() override { return m_instrEnabled; };
    Msg* getActiveMsg() override { return m_activeMsg; };

signals:
    void closing(const char* className);

private slots:
    void on_msg_err(QString text, MsgBoxType type, bool needClose);

    void on_actionAbout_triggered();

private:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

    Ui::WindowScope* m_ui;

    /* messages */
    //Msg_CNTR_Enable* m_msg_enable;
   // Msg_CNTR_Read* m_msg_read;
};

#endif // WINDOW_SCOPE_H
