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


#define TIMER_VM_PLOT           16.6    // graph refresh rate = 16.6 ms = 60 FPS
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
    void on_msg_err(const QString text, MsgBoxType type, bool needClose);
    void on_msg_read(const QString ch1, const QString ch2, const QString ch3, const QString ch4, const QString vcc);

    void on_timer_plot();
    void on_timer_digits();

    void on_actionAbout_triggered();
    void on_actionPoints_triggered(bool checked);
    void on_actionLinear_triggered(bool checked);
    void on_actionLines_triggered(bool checked);
    void on_actionSinc_triggered(bool checked);
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_actionScreenshot_triggered();
    void on_actionFolder_triggered();
    void on_actionCSV_triggered(bool checked);
    void on_actionTXT_Tabs_triggered(bool checked);
    void on_actionTXT_Semicolon_triggered(bool checked);
    void on_actionMAT_triggered(bool checked);
    void on_pushButton_disable1_clicked();
    void on_pushButton_enable1_clicked();
    void on_pushButton_disable2_clicked();
    void on_pushButton_enable2_clicked();
    void on_pushButton_disable3_clicked();
    void on_pushButton_enable3_clicked();
    void on_pushButton_disable4_clicked();
    void on_pushButton_enable4_clicked();
    void on_doubleSpinBox_gain1_valueChanged(double arg1);
    void on_doubleSpinBox_gain2_valueChanged(double arg1);
    void on_doubleSpinBox_gain3_valueChanged(double arg1);
    void on_doubleSpinBox_gain4_valueChanged(double arg1);
    void on_pushButton_disable_clicked();
    void on_pushButton_enable_clicked();
    void on_spinBox_average_valueChanged(int arg1);
    void on_dial_average_valueChanged(int value);
    void on_spinBox_display_valueChanged(int arg1);
    void on_dial_display_valueChanged(int value);
    void on_actionEnabled_triggered(bool checked);
    void on_actionReset_triggered();
    void on_actionChannel_1_triggered(bool checked);
    void on_actionChannel_2_triggered(bool checked);
    void on_actionChannel_3_triggered(bool checked);
    void on_actionChannel_4_triggered(bool checked);
    void on_cursorH_valuesChanged(int min, int max);
    void on_cursorV_valuesChanged(int min, int max);
    void on_pushButton_cursorsHoff_clicked();
    void on_pushButton_cursorsHon_clicked();
    void on_pushButton_cursorsVoff_clicked();
    void on_pushButton_cursorsVon_clicked();
    void on_actionMath_1_2_triggered(bool checked);
    void on_actionMath_3_4_triggered(bool checked);
    void on_pushButton_reset_clicked();
    void on_pushButton_resetZoom_clicked();
    void on_qcpMouseWheel(QWheelEvent*);
    void on_qcpMousePress(QMouseEvent*);
    void on_actionShow_Plot_triggered(bool checked);

private:
    void initQcp();
    bool updatePlotData();
    void rescaleYAxis();
    void rescaleXAxis();

    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

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

    /* mean buffers */
    /*
    MoveMean<double> m_meanCh1;
    MoveMean<double> m_meanCh2;
    MoveMean<double> m_meanCh3;
    MoveMean<double> m_meanCh4;
    MoveMean<double> m_meanVcc;
    MoveMean<double> m_meanAvg;
    */

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
    bool m_math_1minus2 = false;
    bool m_math_3minus4 = false;
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
    double m_meas_max = -1000;
    double m_meas_min = 1000;

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
