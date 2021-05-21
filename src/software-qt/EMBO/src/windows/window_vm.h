/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_VM_H
#define WINDOW_VM_H

#include "interfaces.h"
#include "messages.h"
#include "qcpcursors.h"
#include "movemean.h"
#include "recorder.h"

#include "lib/qcustomplot.h"

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QElapsedTimer>


#define TIMER_VM_PLOT           33.0    // graph refresh rate = 16.6 ms = 60 FPS
#define TIMER_VM_DIGITS         250.0   // values refresh rate = 250 ms = 4 FPS
//#define MOVEMEAN_VM           1       // values moving average 20 * 10 ms = 200 ms

#define GRAPH_CH1               0
#define GRAPH_CH2               1
#define GRAPH_CH3               2
#define GRAPH_CH4               3

#define CURSOR_DEFAULT_H_MIN    400
#define CURSOR_DEFAULT_H_MAX    600
#define CURSOR_DEFAULT_V_MIN    400
#define CURSOR_DEFAULT_V_MAX    600

#define DISPLAY_VM_DEFAULT      1000.0


QT_BEGIN_NAMESPACE
namespace Ui { class WindowVm; }
QT_END_NAMESPACE


class VmSample
{
public:
    double t;

    double ch1;
    double ch2;
    double ch3;
    double ch4;
};


class WindowVm : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowVm(QWidget *parent = nullptr);
    ~WindowVm();

    bool getInstrEnabled() override { return m_instrEnabled; };
    std::vector<Msg*>& getActiveMsgs() override { return m_activeMsgs; };

signals:
    void closing(const char* className);

private slots:
    /* msg slots */
    void on_msg_err(const QString text, MsgBoxType type, bool needClose);
    void on_msg_read(const QString ch1, const QString ch2, const QString ch3, const QString ch4, const QString vcc);

    /* timer slots */
    void on_timer_plot();
    void on_timer_digits();

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
    void on_actionExportPNG_triggered();
    void on_actionExportPDF_triggered();
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

    /* GUI slots - right panel - on/off */
    void on_pushButton_disable1_clicked();
    void on_pushButton_enable1_clicked();
    void on_pushButton_disable2_clicked();
    void on_pushButton_enable2_clicked();
    void on_pushButton_disable3_clicked();
    void on_pushButton_enable3_clicked();
    void on_pushButton_disable4_clicked();
    void on_pushButton_enable4_clicked();

    /* GUI slots - right panel - gain */
    void on_doubleSpinBox_gain1_valueChanged(double arg1);
    void on_doubleSpinBox_gain2_valueChanged(double arg1);
    void on_doubleSpinBox_gain3_valueChanged(double arg1);
    void on_doubleSpinBox_gain4_valueChanged(double arg1);

    /* GUI slots - right panel - main buttons */
    void on_pushButton_disable_clicked();
    void on_pushButton_enable_clicked();
    void on_pushButton_reset_clicked();
    void on_pushButton_resetZoom_clicked();

    /* GUI slots - right panel - main settings */
    void on_spinBox_average_valueChanged(int arg1);
    void on_dial_average_valueChanged(int value);
    void on_spinBox_display_valueChanged(int arg1);
    void on_dial_display_valueChanged(int value);

private:
    void statusBarLoad();
    void initQcp();

    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

    bool updatePlotData();
    void rescaleYAxis();
    void rescaleXAxis();

    /* main window */
    Ui::WindowVm* m_ui;

    /* timers */
    double m_timer_elapsed = 0;
    QTimer* m_timer_plot;
    QTimer* m_timer_digits;

    /* status bar */
    QLabel* m_status_vcc;
    QLabel* m_status_rec;
    QFrame* m_status_line1;

    /* raw sample buffer */
    std::vector<VmSample> m_smplBuff;

    /* recorder */
    Recorder m_rec;

    /* last raw data values */
    double m_data_ch1;
    double m_data_ch2;
    double m_data_ch3;
    double m_data_ch4;
    double m_data_vcc;

    /* data helpers */
    bool m_data_fresh = false;
    double m_key_last = 0;

    /* average vars */
    double m_avg1_val = 0;
    double m_avg2_val = 0;
    double m_avg3_val = 0;
    double m_avg4_val = 0;
    double m_avgVcc_val = 0;
    int m_avg_it = 0;

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

    /* status bar */
    QLabel* status_zoom;

    /* cursors */
    QCPCursors* m_cursors;
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
    bool m_plot = true;

    /* stm32 pins */
    QString m_pin1 = "?";
    QString m_pin2 = "?";
    QString m_pin3 = "?";
    QString m_pin4 = "?";

    QCPRange m_old_range;

    /* measure helpers */
    bool m_meas_en = true;
    int m_meas_ch = GRAPH_CH1;
    //double m_meas_max = -1000;
    //double m_meas_min = 1000;

    /* elapsed helpers */
    int m_elapsed_saved = 0;
    int m_elapsed_diff = 0;
    double m_display = DISPLAY_VM_DEFAULT / (1000.0 / TIMER_VM_PLOT);
    double m_display_pts = DISPLAY_VM_DEFAULT;
    int m_average = 1;

    /* messages */
    Msg_VM_Read* m_msg_read1;
    Msg_VM_Read* m_msg_read2;
    Msg_VM_Read* m_msg_read3;
    Msg_VM_Read* m_msg_read4;
    Msg_VM_Read* m_msg_read5;
};

#endif // WINDOW_VM_H
