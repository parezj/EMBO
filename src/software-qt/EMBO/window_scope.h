/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_SCOPE_H
#define WINDOW_SCOPE_H

#include "interfaces.h"
#include "messages.h"
#include "qcpcursors.h"
#include "containers.h"
#include "recorder.h"

#include <QMainWindow>
#include <QLabel>

#define GRAPH_CH1       0
#define GRAPH_CH2       1
#define GRAPH_CH3       2
#define GRAPH_CH4       3


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
    std::vector<Msg*>& getActiveMsgs() override { return m_activeMsgs; };

signals:
    void closing(const char* className);

private slots:
    /* data msg */
    void on_msg_set(DaqBits bits, int mem, int fs, bool ch1, bool ch2, bool ch3, bool ch4, int trig_ch, int trig_val,
                    DaqTrigEdge trig_edge, DaqTrigMode trig_mode, int trig_pre, double maxZ, double fs_real);
    void on_msg_read(const QByteArray data);

    /* ok-err msg */
    void on_msg_err(const QString text, MsgBoxType type, bool needClose);
    void on_msg_ok_set(const QString maxZ, const QString fs_real);
    void on_msg_ok_forceTrig(const QString, const QString);

     /* async ready msg */
    void on_msg_daqReady(Ready ready, int firstPos);

    void on_actionAbout_triggered();
    void on_actionRec1_triggered(); // DEBUG
    void on_qcpMouseWheel(QWheelEvent*);
    void on_qcpMousePress(QMouseEvent*);

private:
    void initQcp();
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;
    void rescaleXAxis();
    void rescaleYAxis();

    Ui::WindowScope* m_ui;

    QCPRange m_old_range;

    QCPCursors* m_cursors;
    QCPCursor* m_cursorTrigVal;
    QCPCursor* m_cursorTrigPre;

    bool m_spline = true;

    bool m_export = false;

    int m_firstPos;

    double m_t_last = 0;

    QSharedPointer<QCPAxisTickerTime> m_timeTicker;

    /* gain */
    double m_gain1 = 1;
    double m_gain2 = 1;
    double m_gain3 = 1;
    double m_gain4 = 1;
    double m_ref_v = 3.3;

    /* recorder */
    Recorder m_rec;

    /* data */
    DaqSettings m_daqSet;

    /* messages */
    Msg_SCOP_Set* m_msg_set;
    Msg_SCOP_Read* m_msg_read;
    Msg_SCOP_ForceTrig* m_msg_forceTrig;
};

#endif // WINDOW_SCOPE_H
