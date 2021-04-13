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

#define CURSOR_DEFAULT_H_MIN    400
#define CURSOR_DEFAULT_H_MAX    600
#define CURSOR_DEFAULT_V_MIN    400
#define CURSOR_DEFAULT_V_MAX    600


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

    /* GUI slots - Menu - Help */
    void on_actionAbout_triggered();

    /* GUI slots - Menu - Plot */
    void on_actionViewPoints_triggered(bool checked);
    void on_actionViewLines_triggered(bool checked);
    void on_actionInterpLinear_triggered(bool checked);
    void on_actionInterpSinc_triggered(bool checked);
    void on_actionShowPlot_triggered(bool checked);

    /* GUI slots - Menu - Export */
    void on_actionExportStart_triggered();
    void on_actionExportStop_triggered();
    void on_actionExportScreenshot_triggered();
    void on_actionExportFolder_triggered();
    void on_actionExportCSV_triggered(bool checked);
    void on_actionExportTXT_Tabs_triggered(bool checked);
    void on_actionExportTXT_Semicolon_triggered(bool checked);
    void on_actionExportMAT_triggered(bool checked);

    /* GUI slots - Menu - Measure */
    void on_actionMeasEnabled_triggered(bool checked);
    void on_actionMeasReset_triggered();
    void on_actionMeasChannel_1_triggered(bool checked);
    void on_actionMeasChannel_2_triggered(bool checked);
    void on_actionMeasChannel_3_triggered(bool checked);
    void on_actionMeasChannel_4_triggered(bool checked);

    /* GUI slots - Menu - Math */
    void on_actionMath_1_2_triggered(bool checked);
    void on_actionMath_3_4_triggered(bool checked);

    /* GUI slots - Cursors */
    void on_cursorH_valuesChanged(int min, int max);
    void on_cursorV_valuesChanged(int min, int max);
    void on_pushButton_cursorsHoff_clicked();
    void on_pushButton_cursorsHon_clicked();
    void on_pushButton_cursorsVoff_clicked();
    void on_pushButton_cursorsVon_clicked();

    /* GUI slots - QCP */
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

    QSharedPointer<QCPAxisTickerTime> m_timeTicker;

    double m_t_last = 0;

    /* gain */
    double m_gain1 = 1;
    double m_gain2 = 1;
    double m_gain3 = 1;
    double m_gain4 = 1;
    double m_ref_v = 3.3;

    /* enabled channels */
    bool m_en1 = true;
    bool m_en2 = true;
    bool m_en3 = true;
    bool m_en4 = true;

    /* cursors */
    QCPCursors* m_cursors;
    QCPCursor* m_cursorTrigVal;
    QCPCursor* m_cursorTrigPre;
    double m_cursorV_min = CURSOR_DEFAULT_V_MIN;
    double m_cursorV_max = CURSOR_DEFAULT_V_MAX;
    double m_cursorH_min = CURSOR_DEFAULT_H_MIN;
    double m_cursorH_max = CURSOR_DEFAULT_H_MAX;

    /* state flags */
    bool m_spline = true;
    bool m_lines = true;
    bool m_points = false;
    bool m_recording = false;
    bool m_cursorsV_en = false;
    bool m_cursorsH_en = false;
    bool m_math_1minus2 = false;
    bool m_math_3minus4 = false;
    bool m_plot = true;
    bool m_export = false;

    /* stm32 pins */
    QString m_pin1 = "?";
    QString m_pin2 = "?";
    QString m_pin3 = "?";
    QString m_pin4 = "?";

    /* measure helpers */
    bool m_meas_en = true;
    int m_meas_ch = GRAPH_CH1;
    //double m_meas_max = -1000;
    //double m_meas_min = 1000;

    /* data */
    DaqSettings m_daqSet;

    /* messages */
    Msg_LA_Set* m_msg_set;
    Msg_LA_Read* m_msg_read;
    Msg_LA_ForceTrig* m_msg_forceTrig;
};

#endif // WINDOW_LA_H
