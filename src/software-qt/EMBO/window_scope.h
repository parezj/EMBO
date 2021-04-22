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


#define TIMER_SCOPE_PLOT           33.3    // cursors refresh rate = 30 FPS

#define GRAPH_CH1       0
#define GRAPH_CH2       1
#define GRAPH_CH3       2
#define GRAPH_CH4       3

#define CURSOR_DEFAULT_H_MIN    400
#define CURSOR_DEFAULT_H_MAX    600
#define CURSOR_DEFAULT_V_MIN    400
#define CURSOR_DEFAULT_V_MAX    600


#define MAX_SCOPE_AVG     100
#define AVERAGE_DEFAULT   10



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
                    DaqTrigEdge trig_edge, DaqTrigMode trig_mode, int trig_pre, double maxZ, double fs_real_n, const QString fs_real);
    void on_msg_read(const QByteArray data);

    /* ok-err msg */
    void on_msg_err(const QString text, MsgBoxType type, bool needClose);
    void on_msg_ok_set(double maxZ, double fs_real_n, const QString fs_real);
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
    void on_actionInterpLinear_triggered(bool checked);
    void on_actionInterpSinc_triggered(bool checked);

    /* GUI slots - Menu - Export */
    void on_actionExportSave_triggered();
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
    void on_radioButton_trigCh_1_clicked(bool checked);
    void on_radioButton_trigCh_2_clicked(bool checked);
    void on_radioButton_trigCh_3_clicked(bool checked);
    void on_radioButton_trigCh_4_clicked(bool checked);
    void on_spinBox_trigVal_valueChanged(int arg1);
    void on_dial_trigVal_valueChanged(int value);
    void on_spinBox_trigPre_valueChanged(int arg1);
    void on_dial_trigPre_valueChanged(int value);
    void on_pushButton_trigForc_clicked();
    void on_hideTrigSliders();
    void on_dial_trigVal_sliderPressed();
    void on_dial_trigPre_sliderPressed();

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
    void on_doubleSpinBox_gain_ch1_valueChanged(double arg1);
    void on_doubleSpinBox_gain_ch2_valueChanged(double arg1);
    void on_doubleSpinBox_gain_ch3_valueChanged(double arg1);
    void on_doubleSpinBox_gain_ch4_valueChanged(double arg1);
    void on_dial_Vpos_ch1_valueChanged(int value);
    void on_dial_Vpos_ch2_valueChanged(int value);
    void on_dial_Vpos_ch3_valueChanged(int value);
    void on_dial_Vpos_ch4_valueChanged(int value);

    /* GUI slots - right pannel - utils */
    void on_pushButton_average_off_clicked();
    void on_pushButton_average_on_clicked();
    void on_spinBox_average_valueChanged(int arg1);
    void on_pushButton_bit8_off_clicked();
    void on_pushButton_bit8_on_clicked();
    void on_pushButton_bit12_off_clicked();
    void on_pushButton_bit12_on_clicked();
    void on_pushButton_fft_off_clicked();
    void on_pushButton_fft_on_clicked();

    void on_actionMath_XY_X_1_Y_2_triggered(bool checked);

    void on_actionMath_XY_X_3_Y_4_triggered(bool checked);

private:
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
    Ui::WindowScope* m_ui;

    /* timers */
    QTimer* m_timer_plot;
    QTimer* m_timer_trigSliders;

    /* async ready data */
    int m_firstPos;
    Ready m_ready;

    /* X time axis */
    QSharedPointer<QCPAxisTickerTime> m_timeTicker;
    QSharedPointer<QCPAxisTickerFixed> m_timeTicker2;
    QVector<double> m_t;

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

    /* pos */
    double m_offset1 = 0;
    double m_offset2 = 0;
    double m_offset3 = 0;
    double m_offset4 = 0;

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
    bool m_math_2minus1 = false;
    bool m_math_4minus3 = false;
    bool m_math_xy_12 = false;
    bool m_math_xy_34 = false;
    bool m_fft = false;
    bool m_single = false;

    /* average */
    bool m_average = false;
    int m_average_num = AVERAGE_DEFAULT;
    int m_average_cnt = 0;
    int m_average_it = 0;
    QVector<QVector<double>> m_average_buff_ch1;
    QVector<QVector<double>> m_average_buff_ch2;
    QVector<QVector<double>> m_average_buff_ch3;
    QVector<QVector<double>> m_average_buff_ch4;

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

    /* DAQ data */
    DaqSettings m_daqSet;

    /* helpers */
    int m_seq_num = 0;
    bool m_zoomed = false;
    bool m_rescale_needed = true;
    bool m_msgPending = false;
    bool m_ignoreValuesChanged = false;

    /* button groups */
    QButtonGroup m_trigMode;
    QButtonGroup m_trigSlope;
    QButtonGroup m_trigCh;
    QButtonGroup m_fsMem;

    /* messages */
    Msg_SCOP_Set* m_msg_set;
    Msg_SCOP_Read* m_msg_read;
    Msg_SCOP_ForceTrig* m_msg_forceTrig;
};

#endif // WINDOW_SCOPE_H
