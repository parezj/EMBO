/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_LA_H
#define WINDOW_LA_H

#include "interfaces.h"
#include "messages.h"
#include "qcpcursors.h"
#include "containers.h"

#include <QMainWindow>
#include <QLabel>


#define GRAPH_CH1       0
#define GRAPH_CH2       1
#define GRAPH_CH3       2
#define GRAPH_CH4       3


QT_BEGIN_NAMESPACE
namespace Ui { class WindowLa; }
QT_END_NAMESPACE


class WindowLa : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowLa(QWidget *parent = nullptr);
    ~WindowLa();

    bool getInstrEnabled() override { return m_instrEnabled; };
    std::vector<Msg*>& getActiveMsgs() override { return m_activeMsgs; };

signals:
    void closing(const char* className);

private slots:
    /* data msg */
    void on_msg_set(int mem, int fs, int trig_ch, DaqTrigEdge trig_edge, DaqTrigMode trig_mode, int trig_pre, double fs_real);
    void on_msg_read(const QByteArray data);

    /* ok-err msg */
    void on_msg_err(const QString text, MsgBoxType type, bool needClose);
    void on_msg_ok_set(const QString fs_real, const QString);
    void on_msg_ok_forceTrig(const QString, const QString);

     /* async ready msg */
    void on_msg_daqReady(Ready ready, int firstPos);

    void on_actionAbout_triggered();
    void on_qcpMouseWheel(QWheelEvent*);
    void on_qcpMousePress(QMouseEvent*);

private:
    void initQcp();
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;
    void rescaleXAxis();
    void rescaleYAxis();

    Ui::WindowLa* m_ui;

    int m_firstPos;

    QCPCursors* m_cursors;
    QCPCursor* m_cursorTrigVal;
    QCPCursor* m_cursorTrigPre;

    QSharedPointer<QCPAxisTickerTime> m_timeTicker;

    double m_t_last = 0;

    /* data */
    DaqSettings m_daqSet;

    /* messages */
    Msg_LA_Set* m_msg_set;
    Msg_LA_Read* m_msg_read;
    Msg_LA_ForceTrig* m_msg_forceTrig;
};

#endif // WINDOW_LA_H
