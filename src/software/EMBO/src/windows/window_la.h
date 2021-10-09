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
#include "recorder.h"

#include <QMainWindow>
#include <QLabel>


#define TIMER_LA_PLOT           33.0    // cursors refresh rate = 30 FPS

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

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

signals:
    void closing(const char* className);

private slots:
    /* data msg */
    void on_msg_set(int mem, int fs, int trig_ch, DaqTrigEdge trig_edge, DaqTrigMode trig_mode, int trig_pre, double fs_real_n, const QString fs_real);
    void on_msg_read(const QByteArray data);

    /* ok-err msg */
    void on_msg_err(const QString text, MsgBoxType type, bool needClose);
    void on_msg_ok_set(double fs_real_n, const QString fs_real);
    void on_msg_ok_forceTrig(const QString, const QString);

     /* async ready msg */
    void on_msg_daqReady(Ready ready, int firstPos);

    /* timer slots */
    void on_timer_plot();

    /* GUI slots - Menu - Help */
    void on_actionAbout_triggered();

    /* GUI slots - Menu - Plot */
    void on_actionViewPoints_triggered(bool checked);
    void on_actionViewLines_triggered(bool checked);

    /* GUI slots - Menu - Export */
    void on_actionExportSave_triggered();
    void on_actionExportPNG_triggered();
    void on_actionExportPDF_triggered();
    void on_actionExportFolder_triggered();
    void on_actionExportCSV_triggered(bool checked);
    void on_actionExportTXT_Tabs_triggered(bool checked);
    void on_actionExportTXT_Semicolon_triggered(bool checked);
    void on_actionExportMAT_triggered(bool checked);

    /* GUI slots - Cursors */
    void on_cursorH_valuesChanged(int min, int max);
    void on_pushButton_cursorsHoff_clicked();
    void on_pushButton_cursorsHon_clicked();

    /* GUI slots - QCP */
    void on_qcpMouseWheel(QWheelEvent*);
    void on_qcpMousePress(QMouseEvent*);

    /* GUI slots - right pannel - main */
    void on_radioButton_zoomH_clicked(bool checked);
    void on_radioButton_zoomV_clicked(bool checked);
    void on_pushButton_reset_clicked();
    void on_pushButton_resetZoom_clicked();
    void on_pushButton_single_off_clicked();
    void on_pushButton_single_on_clicked();
    void on_pushButton_run_off_clicked();
    void on_pushButton_run_clicked();
    void on_pushButton_stop_clicked();

    /* GUI slots - right pannel - trigger */
    void on_radioButton_trigMode_Auto_clicked(bool checked);
    void on_radioButton_trigMode_Normal_clicked(bool checked);
    void on_radioButton_trigMode_Disabled_clicked(bool checked);
    void on_radioButton_trigSlope_Rising_clicked(bool checked);
    void on_radioButton_trigSlope_Falling_clicked(bool checked);
    void on_radioButton_trigSlope_Both_toggled(bool checked);
    void on_radioButton_trigCh_1_clicked(bool checked);
    void on_radioButton_trigCh_2_clicked(bool checked);
    void on_radioButton_trigCh_3_clicked(bool checked);
    void on_radioButton_trigCh_4_clicked(bool checked);
    void on_spinBox_trigPre_valueChanged(int arg1);
    void on_dial_trigPre_valueChanged(int value);
    void on_pushButton_trigForc_clicked();
    void on_hideTrigSliders();
    void on_dial_trigPre_sliderPressed();
    void on_dial_trigPre_sliderReleased();

    /* GUI slots - right pannel - horizontal */
    void on_radioButton_fsMem_clicked(bool checked);
    void on_radioButton_div_clicked(bool checked);
    void on_spinBox_mem_valueChanged(int arg1);
    void on_dial_mem_valueChanged(int value);
    void on_spinBox_fs_valueChanged(int arg1);
    void on_dial_fs_valueChanged(int value);
    void on_spinBox_div_valueChanged(int arg1);
    void on_dial_div_valueChanged(int value);

    /* GUI slots - right pannel - vertical */
    void on_pushButton_disable1_clicked();
    void on_pushButton_disable2_clicked();
    void on_pushButton_disable3_clicked();
    void on_pushButton_disable4_clicked();
    void on_pushButton_enable1_clicked();
    void on_pushButton_enable2_clicked();
    void on_pushButton_enable3_clicked();
    void on_pushButton_enable4_clicked();

    /* GUI slots - right pannel - utils */

private:
    void statusBarLoad();
    void initQcp();

    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

    void rescaleXAxis();
    void rescaleYAxis();
    void createX();

    void updatePanel();
    void enablePanel(bool en);

    void sendSet();

    /* main window */
    Ui::WindowLa* m_ui;

    /* timers */
    QTimer* m_timer_plot;
    QTimer* m_timer_trigSliders;

    /* async ready data */
    int m_firstPos;
    Ready m_ready;

    /* X time axis vars */
    QSharedPointer<QCPAxisTickerTime> m_timeTicker;
    QVector<double> m_t;

    /* QCP axis */
    QCPAxisRect* m_axis_ch1;
    QCPAxisRect* m_axis_ch2;
    QCPAxisRect* m_axis_ch3;
    QCPAxisRect* m_axis_ch4;

    /* status bar */
    QLabel* m_status_vcc;
    QLabel* m_status_seq;
    QFrame* m_status_line1;

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
    QCPCursors* m_cursors1;
    QCPCursors* m_cursors2;
    QCPCursors* m_cursors3;
    QCPCursors* m_cursors4;

    QCPCursor* m_cursorTrigPre1;
    QCPCursor* m_cursorTrigPre2;
    QCPCursor* m_cursorTrigPre3;
    QCPCursor* m_cursorTrigPre4;

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
    bool m_math_2minus1 = false;
    bool m_math_4minus3 = false;
    bool m_export = false;
    bool m_single = false;

    /* helpers */
    int m_seq_num = 0;
    bool m_zoomed = false;
    bool m_rescale_needed = true;
    bool m_msgPending = false;
    bool m_ignoreValuesChanged = false;
    bool m_trigDialPressed = false;
    bool m_trig_led = false;
    int m_last_fs = 0;
    int m_last_mem = 0;
    int m_err_cntr = 0;
    bool m_refresh = true;

    /* last widget enabled values */
    bool m_last_trigEnabled = true;
    bool m_last_trigCh1_en = true;
    bool m_last_trigCh2_en = true;
    bool m_last_trigCh3_en = true;
    bool m_last_trigCh4_en = true;
    bool m_last_forc = true;
    bool m_last_single = false;

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

    /* recorder */
    Recorder m_rec;

    /* button groups */
    QButtonGroup m_trigMode;
    QButtonGroup m_trigSlope;
    QButtonGroup m_trigCh;
    QButtonGroup m_fsMem;

    /* DAQ data */
    DaqSettings m_daqSet;

    /* messages */
    Msg_LA_Set* m_msg_set;
    Msg_LA_Read* m_msg_read;
    Msg_LA_ForceTrig* m_msg_forceTrig;
};

#endif // WINDOW_LA_H
