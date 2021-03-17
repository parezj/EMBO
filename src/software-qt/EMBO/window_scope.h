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

#define GRAPH_CH1   0
#define GRAPH_CH2   1
#define GRAPH_CH3   2
#define GRAPH_CH4   3

#define GRAPH_CH1_SPLINE   4
#define GRAPH_CH2_SPLINE   5
#define GRAPH_CH3_SPLINE   6
#define GRAPH_CH4_SPLINE   7


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
    void on_msg_ok(const QString val1, const QString val2);
    void on_msg_err(const QString text, MsgBoxType type, bool needClose);
    void on_msg_set();
    void on_msg_read(const QString data);
    void on_msg_daqReady(Ready ready);

    void on_actionAbout_triggered();

private:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

    Ui::WindowScope* m_ui;

    bool m_spline = false;

    /* messages */
    Msg_SCOP_Set* m_msg_set;
    Msg_SCOP_Read* m_msg_read;
    Msg_SCOP_Average* m_msg_average;
    Msg_SCOP_ForceTrig* m_msg_forceTrig;
};

#endif // WINDOW_SCOPE_H
