/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_vm.h"
#include "ui_window_vm.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#include "lib/qcustomplot.h"
#include "lib/ctkrangeslider.h"

#include <QDebug>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>

#include <algorithm>


#define Y_LIM1          0.50 // spline on
#define Y_LIM2          0.15 // spline off
#define DEFAULT_PLT     DISPLAY_VM_DEFAULT
#define DEFAULT_AVG     1


WindowVm::WindowVm(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowVm), m_rec(4)
{
    m_ui->setupUi(this);

    m_timer_plot = new QTimer(this);
    m_timer_digits = new QTimer(this);

    m_timer_plot->setTimerType(Qt::PreciseTimer);
    m_timer_digits->setTimerType(Qt::PreciseTimer);

    m_msg_read1 = new Msg_VM_Read(this);
    m_msg_read2 = new Msg_VM_Read(this);
    m_msg_read3 = new Msg_VM_Read(this);
    m_msg_read4 = new Msg_VM_Read(this);
    m_msg_read5 = new Msg_VM_Read(this);

    m_msg_read1->setParams("1");
    m_msg_read2->setParams("1");
    m_msg_read3->setParams("1");
    m_msg_read4->setParams("1");
    m_msg_read5->setParams("1");

    connect(m_msg_read1, &Msg_VM_Read::err, this, &WindowVm::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read1, &Msg_VM_Read::result, this, &WindowVm::on_msg_read, Qt::QueuedConnection);

    connect(m_msg_read2, &Msg_VM_Read::err, this, &WindowVm::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read2, &Msg_VM_Read::result, this, &WindowVm::on_msg_read, Qt::QueuedConnection);

    connect(m_msg_read3, &Msg_VM_Read::err, this, &WindowVm::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read3, &Msg_VM_Read::result, this, &WindowVm::on_msg_read, Qt::QueuedConnection);

    connect(m_msg_read4, &Msg_VM_Read::err, this, &WindowVm::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read4, &Msg_VM_Read::result, this, &WindowVm::on_msg_read, Qt::QueuedConnection);

    connect(m_msg_read5, &Msg_VM_Read::err, this, &WindowVm::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read5, &Msg_VM_Read::result, this, &WindowVm::on_msg_read, Qt::QueuedConnection);

    connect(m_timer_plot, &QTimer::timeout, this, &WindowVm::on_timer_plot);
    connect(m_timer_digits, &QTimer::timeout, this, &WindowVm::on_timer_digits);

    connect(m_ui->actionEMBO_Help, SIGNAL(triggered()), Core::getInstance(), SLOT(on_actionEMBO_Help()));

    m_ui->dial_display->setValue(DISPLAY_VM_DEFAULT);

    /* QCP */

    initQcp();

    /* statusbar */

    statusBarLoad();

    /* styles */

    //m_ui->pushButton_enable->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM_MAIN);
    m_ui->pushButton_disable->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_VM_MAIN);

    /*
    m_ui->pushButton_enable1->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM_ON);
    m_ui->pushButton_enable2->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM_ON);
    m_ui->pushButton_enable3->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM_ON);
    m_ui->pushButton_enable4->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM_ON);

    m_ui->pushButton_disable1->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_VM_ON);
    m_ui->pushButton_disable2->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_VM_ON);
    m_ui->pushButton_disable3->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_VM_ON);
    m_ui->pushButton_disable4->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_VM_ON);
    */

    m_ui->pushButton_cursorsHon->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM_ON);
    m_ui->pushButton_cursorsVon->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM_ON);

    m_ui->pushButton_cursorsHoff->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_VM_ON);
    m_ui->pushButton_cursorsVoff->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_VM_ON);

    //m_ui->pushButton_reset->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM_RESET);
    //m_ui->pushButton_resetZoom->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM_RESETZ);

    m_ui->spinBox_average->setStyleSheet(CSS_SPINBOX);
    m_ui->spinBox_display->setStyleSheet(CSS_SPINBOX);

    /* settings */

    Settings::getValue(CFG_VM_CH1_EN, true).toBool() ? on_pushButton_enable1_clicked() : on_pushButton_disable1_clicked();
    Settings::getValue(CFG_VM_CH2_EN, true).toBool() ? on_pushButton_enable2_clicked() : on_pushButton_disable2_clicked();
    Settings::getValue(CFG_VM_CH3_EN, false).toBool() ? on_pushButton_enable3_clicked() : on_pushButton_disable3_clicked();
    Settings::getValue(CFG_VM_CH4_EN, false).toBool() ? on_pushButton_enable4_clicked() : on_pushButton_disable4_clicked();

    m_ui->spinBox_average->setValue(DEFAULT_AVG); //Settings::getValue(CFG_VM_AVG, DEFAULT_AVG).toInt());
    m_ui->spinBox_display->setValue(DEFAULT_PLT); //Settings::getValue(CFG_VM_PLT, DEFAULT_PLT).toInt());
    m_ui->actionShowPlot->setChecked(Settings::getValue(CFG_VM_SHOW_PLOT, true).toBool());
    m_ui->actionInterpSinc->setChecked(Settings::getValue(CFG_VM_SPLINE, true).toBool());

    on_spinBox_average_valueChanged(m_ui->spinBox_average->value());
    on_spinBox_display_valueChanged(m_ui->spinBox_display->value());
    on_actionShowPlot_triggered(m_ui->actionShowPlot->isChecked());
    on_actionInterpSinc_triggered(m_ui->actionInterpSinc->isChecked());

    m_instrEnabled = true;
}

void WindowVm::statusBarLoad()
{
    m_status_vcc = new QLabel(" ", this);
    m_status_rec = new QLabel(" ", this);
    status_zoom = new QLabel("<span>Zoom with Scroll Wheel, Move with Mouse Drag&nbsp;&nbsp;<span>", this);
    QWidget* widget = new QWidget(this);

    QFont font1("Roboto", 11, QFont::Normal);
    m_status_vcc->setFont(font1);
    m_status_rec->setFont(font1);
    status_zoom->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/img/vm.png");

    status_img->setPixmap(status_img_icon);
    status_img->setFixedWidth(17);
    status_img->setFixedHeight(17);
    status_img->setScaledContents(true);

    m_status_line1 = new QFrame(this);
    m_status_line1->setFrameShape(QFrame::VLine);
    m_status_line1->setFrameShadow(QFrame::Plain);
    m_status_line1->setStyleSheet("color:gray;");
    m_status_line1->setFixedHeight(18);
    m_status_line1->setVisible(false);

    QLabel* status_spacer2 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer3 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);

    QSpacerItem* status_spacer0 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(status_img,     0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_vcc,   0,1,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer2, 0,2,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_line1, 0,3,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer3, 0,4,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_rec,   0,5,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->addItem(status_spacer0,   0,6,1,1,Qt::AlignVCenter);
    layout->addWidget(status_zoom,    0,7,1,1,Qt::AlignVCenter);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);
}

void WindowVm::initQcp()
{
    m_ui->customPlot->addGraph();  // ch1
    m_ui->customPlot->addGraph();  // ch2
    m_ui->customPlot->addGraph();  // ch3
    m_ui->customPlot->addGraph();  // ch4

    m_ui->customPlot->graph(GRAPH_CH1)->setPen(QPen(QColor(COLOR1)));
    m_ui->customPlot->graph(GRAPH_CH2)->setPen(QPen(QColor(COLOR2)));
    m_ui->customPlot->graph(GRAPH_CH3)->setPen(QPen(QColor(COLOR5)));
    m_ui->customPlot->graph(GRAPH_CH4)->setPen(QPen(QColor(COLOR4)));

    m_spline = true;

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(m_spline);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(m_spline);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(m_spline);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(m_spline);

    m_ui->customPlot->axisRect()->setMinimumMargins(QMargins(45,15,15,30));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    m_ui->customPlot->xAxis->setTicker(timeTicker);
    //m_ui->customPlot->xAxis2->setTicker(timeTicker);
    m_ui->customPlot->axisRect()->setupFullAxesBox();

    m_ui->customPlot->xAxis->setVisible(true);
    m_ui->customPlot->xAxis->setTickLabels(true);
    m_ui->customPlot->yAxis->setVisible(true);
    m_ui->customPlot->yAxis->setTickLabels(true);

    QFont font2("Roboto", 12, QFont::Normal);
    m_ui->customPlot->xAxis->setTickLabelFont(font2);
    m_ui->customPlot->yAxis->setTickLabelFont(font2);
    m_ui->customPlot->xAxis->setLabelFont(font2);
    m_ui->customPlot->yAxis->setLabelFont(font2);

    //m_ui->customPlot->setOpenGl(true);

    //m_ui->customPlot->setInteractions(0);
    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    connect(m_ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(on_qcpMouseWheel(QWheelEvent*)));
    connect(m_ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(on_qcpMousePress(QMouseEvent*)));

    /* cursors */

    m_ui->horizontalSlider_cursorH->hide();
    m_ui->horizontalSlider_cursorV->hide();

    connect(m_ui->horizontalSlider_cursorH, &ctkRangeSlider::valuesChanged, this, &WindowVm::on_cursorH_valuesChanged);
    connect(m_ui->horizontalSlider_cursorV, &ctkRangeSlider::valuesChanged, this, &WindowVm::on_cursorV_valuesChanged);

    m_cursors = new QCPCursors(this, m_ui->customPlot, NULL, false, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
}

WindowVm::~WindowVm()
{
    delete m_ui;
}

void WindowVm::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/********************************* MSG slots *********************************/

void WindowVm::on_msg_err(const QString text, MsgBoxType type, bool needClose)
{
    m_activeMsgs.clear();

    if (needClose)
        this->close();

    msgBox(this, text, type);
}

void WindowVm::on_msg_read(const QString ch1, const QString ch2, const QString ch3, const QString ch4, const QString vcc) // 100 Hz idealy
{
    if (m_instrEnabled && !m_activeMsgs.empty())
    {
        double t_ms = m_timer_elapsed;
        m_timer_elapsed += 10;
        double t = t_ms / 1000.0;

        double _ch1 = ch1.toDouble() * m_gain1;
        double _ch2 = ch2.toDouble() * m_gain2;
        double _ch3 = ch3.toDouble() * m_gain3;
        double _ch4 = ch4.toDouble() * m_gain4;

        double data_ch1 = _ch1;
        double data_ch2 = _ch2;
        double data_ch3 = _ch3;
        double data_ch4 = _ch4;
        double data_vcc = vcc.toDouble();

        if (m_math_2minus1)
            data_ch3 = _ch2 - _ch1;

        if (m_math_4minus3)
            data_ch4 = _ch4 - _ch3;

        if (m_recording)
        {
            m_rec << t_ms;
            if (m_en1)
                m_rec << data_ch1;
            if (m_en2)
                m_rec << data_ch2;
            if (m_en3)
                m_rec << data_ch3;
            if (m_en4)
                m_rec << data_ch4;
            if (m_en1 + m_en2 + m_en3 + m_en4 > 0)
                m_rec << ENDL;
        }

        bool data_fresh = false;

        if (m_average > 1) // average enabled
        {
            m_avg_it++;

            m_avg1_val += data_ch1;
            m_avg2_val += data_ch2;
            m_avg3_val += data_ch3;
            m_avg4_val += data_ch4;
            m_avgVcc_val += data_vcc;

            if (m_avg_it == m_average) // average is ready
            {
                m_data_ch1 = m_avg1_val / m_average;
                m_data_ch2 = m_avg2_val / m_average;
                m_data_ch3 = m_avg3_val / m_average;
                m_data_ch4 = m_avg4_val / m_average;
                m_data_vcc = m_avgVcc_val / m_average;

                m_avg1_val = 0;
                m_avg2_val = 0;
                m_avg3_val = 0;
                m_avg4_val = 0;
                m_avgVcc_val = 0;

                m_avg_it = 0;

                data_fresh = true;
                m_data_fresh = true;
            }
        }
        else // average disabled
        {
            data_fresh = true;
            m_data_fresh = true;

            m_data_ch1 = data_ch1;
            m_data_ch2 = data_ch2;
            m_data_ch3 = data_ch3;
            m_data_ch4 = data_ch4;
            m_data_vcc = data_vcc;
        }

        if (data_fresh)
        {
            data_fresh = false;

            m_smplBuff.push_back(VmSample {t, m_data_ch1, m_data_ch2, m_data_ch3, m_data_ch4});
        }
    }
}

/********************************* timer slots *********************************/

void WindowVm::on_timer_plot() // 60 FPS
{
    if (m_instrEnabled)
    {
        if (updatePlotData()) // add values to graph
        {
            if (m_en1)
                m_ui->progressBar_ch1->setValue((m_data_ch1 / (m_ref_v * m_gain1)) * 100.0);
            if (m_en2)
                m_ui->progressBar_ch2->setValue((m_data_ch2 / (m_ref_v * m_gain2)) * 100.0);
            if (m_en3)
                m_ui->progressBar_ch3->setValue((m_data_ch3 / (m_ref_v * m_gain3)) * 100.0);
            if (m_en4)
                m_ui->progressBar_ch4->setValue((m_data_ch4 / (m_ref_v * m_gain4)) * 100.0);
        }
    }

    if (m_plot)
    {
        if (m_cursorsV_en || m_cursorsH_en)
        {
            auto rngV = m_ui->customPlot->yAxis->range();
            auto rngH = m_ui->customPlot->xAxis->range();

            m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
        }

        m_ui->customPlot->replot();
    }
}

void WindowVm::on_timer_digits() // 4 FPS
{
    if (m_instrEnabled && m_data_fresh)
    {
        m_data_fresh = false;

        double ch1 = m_data_ch1; //m_meanCh1.getMean();
        double ch2 = m_data_ch2; //m_meanCh2.getMean();
        double ch3 = m_data_ch3; //m_meanCh3.getMean();
        double ch4 = m_data_ch4; //m_meanCh4.getMean();
        double vcc = m_data_vcc; //m_meanVcc.getMean();
        int vcc_mv = (int)(vcc * 1000);

        QString ch1_s;
        QString ch2_s;
        QString ch3_s;
        QString ch4_s;
        QString vcc_mv_s;

        ch1_s = ch1_s.asprintf(ch1 >= 100 || ch1 <= -10 ? "%.2f" : (ch1 >= 10 || ch1 < 0 ? "%.3f" : "%.4f"), ch1);
        ch2_s = ch1_s.asprintf(ch2 >= 100 || ch2 <= -10 ? "%.2f" : (ch2 >= 10 || ch2 < 0 ? "%.3f" : "%.4f"), ch2);
        ch3_s = ch1_s.asprintf(ch3 >= 100 || ch3 <= -10 ? "%.2f" : (ch3 >= 10 || ch3 < 0 ? "%.3f" : "%.4f"), ch3);
        ch4_s = ch1_s.asprintf(ch4 >= 100 || ch4 <= -10 ? "%.2f" : (ch4 >= 10 || ch4 < 0 ? "%.3f" : "%.4f"), ch4);
        vcc_mv_s = vcc_mv_s.asprintf("%d", vcc_mv);

        if (m_en1)
            m_ui->textBrowser_ch1->setHtml("<p align=\"center\">" + ch1_s + " V</p>");
        if (m_en2)
            m_ui->textBrowser_ch2->setHtml("<p align=\"center\">" + ch2_s + " V</p>");
        if (m_en3)
            m_ui->textBrowser_ch3->setHtml("<p align=\"center\">" + ch3_s + " V</p>");
        if (m_en4)
            m_ui->textBrowser_ch4->setHtml("<p align=\"center\">" + ch4_s + " V</p>");

        m_ref_v = vcc;
        Core::getInstance()->getDevInfo()->ref_mv = vcc_mv;
        m_status_vcc->setText(" Vcc: " + vcc_mv_s + " mV");

        if (m_meas_en) //&& m_meas_max > -1000 && m_meas_min < 1000)
        {
            QString meas_vpp_s;
            QString meas_avg_s;
            QString meas_min_s;
            QString meas_max_s;

            auto data_begin = m_ui->customPlot->graph(m_meas_ch)->data()->constBegin();
            auto data_end = m_ui->customPlot->graph(m_meas_ch)->data()->constEnd();

            double avg = std::accumulate(data_begin, data_end, .0, [](double a, QCPGraphData b) { return a + b.value;}) / std::distance(data_begin, data_end);
            double min = std::min_element(data_begin, data_end, [](QCPGraphData a, QCPGraphData b) { return a.value < b.value; })->value; // m_meas_min;
            double max = std::max_element(data_begin, data_end, [](QCPGraphData a, QCPGraphData b) { return a.value < b.value; })->value; // m_meas_max;
            double vpp = max - min;

            meas_vpp_s = meas_vpp_s.asprintf(vpp >= 100 || vpp <= -10  ? "%.2f" : (vpp >= 10 || vpp < 0 ? "%.3f" : "%.4f"), vpp);
            meas_avg_s = meas_avg_s.asprintf(avg >= 100 || avg <= -10  ? "%.2f" : (avg >= 10 || avg < 0 ? "%.3f" : "%.4f"), avg);
            meas_min_s = meas_min_s.asprintf(min >= 100 || min <= -10  ? "%.2f" : (min >= 10 || min < 0 ? "%.3f" : "%.4f"), min);
            meas_max_s = meas_max_s.asprintf(max >= 100 || max <= -10  ? "%.2f" : (max >= 10 || max < 0 ? "%.3f" : "%.4f"), max);

            m_ui->textBrowser_measVpp->setHtml("<p align=\"right\">" + meas_vpp_s + " </p>");
            m_ui->textBrowser_measAvg->setHtml("<p align=\"right\">" + meas_avg_s + " </p>");
            m_ui->textBrowser_measMin->setHtml("<p align=\"right\">" + meas_min_s + " </p>");
            m_ui->textBrowser_measMax->setHtml("<p align=\"right\">" + meas_max_s + " </p>");
        }
    }
}

bool WindowVm::updatePlotData()
{
    if (m_smplBuff.empty())
        return false;

    for (auto smpl : m_smplBuff)
    {
        m_key_last = smpl.t;

        m_ui->customPlot->graph(GRAPH_CH1)->addData(m_key_last, smpl.ch1);
        m_ui->customPlot->graph(GRAPH_CH2)->addData(m_key_last, smpl.ch2);
        m_ui->customPlot->graph(GRAPH_CH3)->addData(m_key_last, smpl.ch3);
        m_ui->customPlot->graph(GRAPH_CH4)->addData(m_key_last, smpl.ch4);
    }

    m_smplBuff.clear();

    rescaleXAxis();

    m_ui->customPlot->graph(GRAPH_CH1)->data()->removeBefore(m_key_last - m_display);
    m_ui->customPlot->graph(GRAPH_CH2)->data()->removeBefore(m_key_last - m_display);
    m_ui->customPlot->graph(GRAPH_CH3)->data()->removeBefore(m_key_last - m_display);
    m_ui->customPlot->graph(GRAPH_CH4)->data()->removeBefore(m_key_last - m_display);

    return true;
}

/********************************* GUI slots *********************************/

/********** Plot **********/

void WindowVm::on_actionViewPoints_triggered(bool checked)
{
    QCPScatterStyle style = QCPScatterStyle(QCPScatterStyle::ssNone);

    if (checked)
        style = QCPScatterStyle(QCPScatterStyle::ssDisc, 5);

    m_points = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setScatterStyle(style);
}

void WindowVm::on_actionViewLines_triggered(bool checked)
{
    QCPGraph::LineStyle style = QCPGraph::lsNone;

    if (checked)
        style = QCPGraph::lsLine;

    m_lines = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setLineStyle(style);
}

void WindowVm::on_actionInterpLinear_triggered(bool checked) // exclusive with - actionSinc
{
    m_ui->actionInterpSinc->setChecked(!checked);
    on_actionInterpSinc_triggered(!checked);
}

void WindowVm::on_actionInterpSinc_triggered(bool checked) // exclusive with - actionLinear
{
    m_spline = checked;

    Settings::setValue(CFG_VM_SPLINE, m_spline);

    m_ui->actionInterpLinear->setChecked(!checked);

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(checked);

    rescaleYAxis();
}

void WindowVm::on_actionShowPlot_triggered(bool checked)
{
    Settings::setValue(CFG_VM_SHOW_PLOT, checked);
    m_plot = checked;

    if (checked)
    {
        this->setMinimumWidth(1244);
        this->setMinimumHeight(606);

        this->setMaximumWidth(QWIDGETSIZE_MAX);
        this->setMaximumHeight(QWIDGETSIZE_MAX);

        status_zoom->show();
        m_ui->groupBox_screen->show();

        this->setMinimumWidth(947);
        this->setMinimumHeight(261);
    }
    else
    {
        this->setFixedWidth(426);
        this->setFixedHeight(606);

        status_zoom->hide();
        m_ui->groupBox_screen->hide();
    }

    m_ui->spinBox_display->setEnabled(checked);
    m_ui->dial_display->setEnabled(checked);
}

/********** Export **********/

void WindowVm::on_actionExportStart_triggered()
{
    auto info = Core::getInstance()->getDevInfo();
    auto sys = QSysInfo();

    QMap<QString, QString> header {
        {"Common.Created",  {QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss.zzz")}},
        {"Common.Version",  "EMBO " + QString(APP_VERSION)},
        {"Common.System",   {sys.prettyProductName() + " [" + sys.currentCpuArchitecture() + "]"}},
        {"Common.Device",   info->name},
        {"Common.Firmware", info->fw},
        {"Common.Vcc",      QString::number(info->ref_mv) + " mV"},
        {"Common.Mode",     "VM"},
        {"VM.SampleRate",   "100 Hz"},
        {"VM.Resolution",   "12 bit"},
    };
    bool ret = m_rec.createFile("VM", header);

    if (!ret)
    {
        msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
    }
    else
    {
        m_rec << "t(ms)";
        if (m_en1) m_rec << "CH1(V)";
        if (m_en2) m_rec << "CH2(V)";
        if (m_en3) m_rec << "CH3(V)";
        if (m_en4) m_rec << "CH4(V)";
        m_rec << ENDL;

        m_recording = true;

        m_ui->actionExportStart->setEnabled(false);
        m_ui->actionExportStop->setEnabled(true);

        m_ui->actionFormat->setEnabled(false);
        m_ui->actionExportFolder->setEnabled(false);

        m_status_rec->setText("Recording to: " + m_rec.getFilePath());

        m_status_rec->setVisible(true);
        m_status_line1->setVisible(true);
    }
}

void WindowVm::on_actionExportStop_triggered()
{
    m_recording = false;

    m_ui->actionExportStart->setEnabled(true);
    m_ui->actionExportStop->setEnabled(false);

    m_ui->actionFormat->setEnabled(true);
    m_ui->actionExportFolder->setEnabled(true);

    m_status_rec->setVisible(false);
    m_status_line1->setVisible(false);

    QString ret = m_rec.closeFile();

    msgBox(this, "File saved at: " + ret, INFO);
}

void WindowVm::on_actionExportPNG_triggered()
{
     //QString ret = m_rec.takeScreenshot("VM", m_ui->customPlot);

     QString path = m_rec.generateFilePath("VM", ".png");
     bool ret = m_ui->customPlot->savePng(path);

     if (ret)
         msgBox(this, "File saved at: " + path, INFO);
     else
         msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
}

void WindowVm::on_actionExportPDF_triggered()
{
    QString path = m_rec.generateFilePath("VM", ".pdf");
    bool ret = m_ui->customPlot->savePdf(path);

    if (ret)
        msgBox(this, "File saved at: " + path, INFO);
    else
        msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
}

void WindowVm::on_actionExportFolder_triggered()
{
    bool ok;
    QString dir_saved = Settings::getValue(CFG_REC_DIR, m_rec.getDir()).toString();
    QString dir = QInputDialog::getText(this, "EMBO - Recordings", "Directory path:", QLineEdit::Normal, dir_saved, &ok);

    if (ok && !dir.isEmpty())
    {
        if (!m_rec.setDir(dir))
            msgBox(this, "Directory create failed!", CRITICAL);
        else
            Settings::setValue(CFG_REC_DIR, dir);
    }
}

void WindowVm::on_actionExportCSV_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(CSV);

        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowVm::on_actionExportTXT_Tabs_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(TAB);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowVm::on_actionExportTXT_Semicolon_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(SEMICOLON);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowVm::on_actionExportMAT_triggered(bool checked)
{
    if (checked)
    {
        //rec.setDelim(MAT); // not implemented yet

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
    }
}

/********** Meas **********/

void WindowVm::on_actionMeasEnabled_triggered(bool checked)
{
    m_meas_en = checked;
    on_actionMeasReset_triggered();

    m_ui->textBrowser_measVpp->setEnabled(checked);
    m_ui->textBrowser_measAvg->setEnabled(checked);
    m_ui->textBrowser_measMin->setEnabled(checked);
    m_ui->textBrowser_measMax->setEnabled(checked);
}

void WindowVm::on_actionMeasReset_triggered()
{
    //m_meas_max = -1000;
    //m_meas_min = 1000;

    m_ui->textBrowser_measVpp->setText("");
    m_ui->textBrowser_measAvg->setText("");
    m_ui->textBrowser_measMin->setText("");
    m_ui->textBrowser_measMax->setText("");
}

void WindowVm::on_actionMeasChannel_1_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH1;

        m_ui->actionMeasChannel_2->setChecked(false);
        m_ui->actionMeasChannel_3->setChecked(false);
        m_ui->actionMeasChannel_4->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 1)");
    }
}

void WindowVm::on_actionMeasChannel_2_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH2;

        m_ui->actionMeasChannel_1->setChecked(false);
        m_ui->actionMeasChannel_3->setChecked(false);
        m_ui->actionMeasChannel_4->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 2)");
    }
}

void WindowVm::on_actionMeasChannel_3_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH3;

        m_ui->actionMeasChannel_1->setChecked(false);
        m_ui->actionMeasChannel_2->setChecked(false);
        m_ui->actionMeasChannel_4->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 3)");
    }
}

void WindowVm::on_actionMeasChannel_4_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH4;

        m_ui->actionMeasChannel_1->setChecked(false);
        m_ui->actionMeasChannel_2->setChecked(false);
        m_ui->actionMeasChannel_3->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 4)");
    }
}

/********** Math **********/

void WindowVm::on_actionMath_1_2_triggered(bool checked)
{
    if (checked)
    {
        m_ui->label_ch3->setText("Channel 2—1 (" + m_pin2 + "—" + m_pin1 + ")");
        m_ui->label_ch3->setStyleSheet("color:red");

        m_ui->pushButton_enable3->setText("2—1 ON  ");
        m_ui->pushButton_disable3->setText("2—1 OFF");

        m_ui->actionMath_3_4->setChecked(false);
        on_actionMath_3_4_triggered(false);
    }
    else
    {
        m_ui->label_ch3->setText("Channel 3 (" + m_pin3 + ")");
        m_ui->label_ch3->setStyleSheet("color:black");

        m_ui->pushButton_enable3->setText("CH3 ON  ");
        m_ui->pushButton_disable3->setText("CH3 OFF");
    }

    m_math_2minus1 = checked;
}

void WindowVm::on_actionMath_3_4_triggered(bool checked)
{
    if (checked)
    {
        m_ui->label_ch4->setText("Channel 4—3 (" + m_pin4 + "—" + m_pin3 + ")");
        m_ui->label_ch4->setStyleSheet("color:red");

        m_ui->pushButton_enable4->setText("4—3 ON  ");
        m_ui->pushButton_disable4->setText("4—3 OFF");

        m_ui->actionMath_1_2->setChecked(false);
        on_actionMath_1_2_triggered(false);
    }
    else
    {
        m_ui->label_ch4->setText("Channel 4 (" + m_pin4 + ")");
        m_ui->label_ch4->setStyleSheet("color:black");

        m_ui->pushButton_enable4->setText("CH4 ON  ");
        m_ui->pushButton_disable4->setText("CH4 OFF");
    }

    m_math_4minus3 = checked;
}

/********** Cursors **********/

void WindowVm::on_pushButton_cursorsHoff_clicked()
{
    m_ui->horizontalSlider_cursorH->hide();

    m_ui->pushButton_cursorsHon->show();
    m_ui->pushButton_cursorsHoff->hide();

    m_cursors->showH(false);
    m_cursorsH_en = false;
}

void WindowVm::on_pushButton_cursorsHon_clicked()
{
    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorH->show();

    m_ui->pushButton_cursorsHon->hide();
    m_ui->pushButton_cursorsHoff->show();

    auto rngH = m_ui->customPlot->xAxis->range();
    auto rngV = m_ui->customPlot->yAxis->range();

    m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);

    m_cursors->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors->setH_max(m_cursorH_max, rngH.lower, rngH.upper);

    m_cursors->showH(true);
    m_cursorsH_en = true;
}

void WindowVm::on_pushButton_cursorsVoff_clicked()
{
    m_ui->horizontalSlider_cursorV->hide();

    m_ui->pushButton_cursorsVon->show();
    m_ui->pushButton_cursorsVoff->hide();

    m_cursors->showV(false);
    m_cursorsV_en = false;
}

void WindowVm::on_pushButton_cursorsVon_clicked()
{
    m_ui->horizontalSlider_cursorV->setValues(m_cursorV_min, m_cursorV_max);
    m_ui->horizontalSlider_cursorV->show();

    m_ui->pushButton_cursorsVon->hide();
    m_ui->pushButton_cursorsVoff->show();

    auto rngH = m_ui->customPlot->xAxis->range();
    auto rngV = m_ui->customPlot->yAxis->range();

    m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);

    m_cursors->setV_min(m_cursorV_min, rngV.lower, rngV.upper);
    m_cursors->setV_max(m_cursorV_max, rngV.lower, rngV.upper);

    m_cursors->showV(true);
    m_cursorsV_en = true;
}

void WindowVm::on_cursorH_valuesChanged(int min, int max)
{
    m_cursorH_min = min;
    m_cursorH_max = max;

    auto rng = m_ui->customPlot->axisRect()->rangeZoomAxis(Qt::Horizontal)->range();
    //auto rng = m_ui->customPlot->xAxis->range();

    m_cursors->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors->setH_max(m_cursorH_max, rng.lower, rng.upper);
}

void WindowVm::on_cursorV_valuesChanged(int min, int max)
{
    m_cursorV_min = min;
    m_cursorV_max = max;

    auto rng = m_ui->customPlot->axisRect()->rangeZoomAxis(Qt::Vertical)->range();
    //auto rng = m_ui->customPlot->yAxis->range();

    m_cursors->setV_min(m_cursorV_min, rng.lower, rng.upper);
    m_cursors->setV_max(m_cursorV_max, rng.lower, rng.upper);
}

/********** QCP **********/


void WindowVm::on_qcpMouseWheel(QWheelEvent*)
{
    m_ui->pushButton_reset->hide();
    m_ui->pushButton_resetZoom->show();
}

void WindowVm::on_qcpMousePress(QMouseEvent*)
{
    m_ui->pushButton_reset->hide();
    m_ui->pushButton_resetZoom->show();
}

/********** right pannel - on/off **********/

void WindowVm::on_pushButton_disable1_clicked()
{
    m_en1 = false;
    m_ui->customPlot->graph(GRAPH_CH1)->setVisible(false);
    m_ui->textBrowser_ch1->setText("");
    m_ui->progressBar_ch1->setValue(0);

    m_ui->pushButton_enable1->show();
    m_ui->pushButton_disable1->hide();
    m_ui->doubleSpinBox_gain1->setEnabled(false);

    Settings::setValue(CFG_VM_CH1_EN, false);

    rescaleYAxis();
}

void WindowVm::on_pushButton_enable1_clicked()
{
    m_en1 = true;
    m_ui->customPlot->graph(GRAPH_CH1)->setVisible(true);

    m_ui->pushButton_enable1->hide();
    m_ui->pushButton_disable1->show();
    m_ui->doubleSpinBox_gain1->setEnabled(true);

    Settings::setValue(CFG_VM_CH1_EN, true);

    rescaleYAxis();
}

void WindowVm::on_pushButton_disable2_clicked()
{
    m_en2 = false;
    m_ui->customPlot->graph(GRAPH_CH2)->setVisible(false);
    m_ui->textBrowser_ch2->setText("");
    m_ui->progressBar_ch2->setValue(0);

    m_ui->pushButton_enable2->show();
    m_ui->pushButton_disable2->hide();
    m_ui->doubleSpinBox_gain2->setEnabled(false);

    Settings::setValue(CFG_VM_CH2_EN, false);

    rescaleYAxis();
}

void WindowVm::on_pushButton_enable2_clicked()
{
    m_en2 = true;
    m_ui->customPlot->graph(GRAPH_CH2)->setVisible(true);

    m_ui->pushButton_enable2->hide();
    m_ui->pushButton_disable2->show();
    m_ui->doubleSpinBox_gain2->setEnabled(true);

    Settings::setValue(CFG_VM_CH2_EN, true);

    rescaleYAxis();
}

void WindowVm::on_pushButton_disable3_clicked()
{
    m_en3 = false;
    m_ui->customPlot->graph(GRAPH_CH3)->setVisible(false);
    m_ui->textBrowser_ch3->setText("");
    m_ui->progressBar_ch3->setValue(0);

    m_ui->pushButton_enable3->show();
    m_ui->pushButton_disable3->hide();
    m_ui->doubleSpinBox_gain3->setEnabled(false);

    Settings::setValue(CFG_VM_CH3_EN, false);

    rescaleYAxis();
}

void WindowVm::on_pushButton_enable3_clicked()
{
    m_en3 = true;
    m_ui->customPlot->graph(GRAPH_CH3)->setVisible(true);

    m_ui->pushButton_enable3->hide();
    m_ui->pushButton_disable3->show();
    m_ui->doubleSpinBox_gain3->setEnabled(true);

    Settings::setValue(CFG_VM_CH3_EN, true);

    rescaleYAxis();
}

void WindowVm::on_pushButton_disable4_clicked()
{
    m_en4 = false;
    m_ui->customPlot->graph(GRAPH_CH4)->setVisible(false);
    m_ui->textBrowser_ch4->setText("");
    m_ui->progressBar_ch4->setValue(0);

    m_ui->pushButton_enable4->show();
    m_ui->pushButton_disable4->hide();
    m_ui->doubleSpinBox_gain4->setEnabled(false);

    Settings::setValue(CFG_VM_CH4_EN, false);

    rescaleYAxis();
}

void WindowVm::on_pushButton_enable4_clicked()
{
    m_en4 = true;
    m_ui->customPlot->graph(GRAPH_CH4)->setVisible(true);

    m_ui->pushButton_enable4->hide();
    m_ui->pushButton_disable4->show();
    m_ui->doubleSpinBox_gain4->setEnabled(true);

    Settings::setValue(CFG_VM_CH4_EN, true);

    rescaleYAxis();
}

/********** right pannel - gain **********/

void WindowVm::on_doubleSpinBox_gain1_valueChanged(double arg1)
{
    m_gain1 = arg1;

    rescaleYAxis();
}

void WindowVm::on_doubleSpinBox_gain2_valueChanged(double arg1)
{
    m_gain2 = arg1;

    rescaleYAxis();
}

void WindowVm::on_doubleSpinBox_gain3_valueChanged(double arg1)
{
    m_gain3 = arg1;

    rescaleYAxis();
}

void WindowVm::on_doubleSpinBox_gain4_valueChanged(double arg1)
{
    m_gain4 = arg1;

    rescaleYAxis();
}

/********** right pannel - main buttons **********/

void WindowVm::on_pushButton_disable_clicked()
{
    m_instrEnabled = false;

    m_ui->pushButton_enable->show();
    m_ui->pushButton_disable->hide();

    m_ui->textBrowser_ch1->setEnabled(false);
    m_ui->textBrowser_ch2->setEnabled(false);
    m_ui->textBrowser_ch3->setEnabled(false);
    m_ui->textBrowser_ch4->setEnabled(false);

    /*
    m_ui->pushButton_disable1->setEnabled(false);
    m_ui->pushButton_enable1->setEnabled(false);
    m_ui->pushButton_disable2->setEnabled(false);
    m_ui->pushButton_enable2->setEnabled(false);
    m_ui->pushButton_disable3->setEnabled(false);
    m_ui->pushButton_enable3->setEnabled(false);
    m_ui->pushButton_disable4->setEnabled(false);
    m_ui->pushButton_enable4->setEnabled(false);
    */

    m_ui->doubleSpinBox_gain1->setEnabled(false);
    m_ui->doubleSpinBox_gain2->setEnabled(false);
    m_ui->doubleSpinBox_gain3->setEnabled(false);
    m_ui->doubleSpinBox_gain4->setEnabled(false);

    m_ui->progressBar_ch1->setEnabled(false);
    m_ui->progressBar_ch2->setEnabled(false);
    m_ui->progressBar_ch3->setEnabled(false);
    m_ui->progressBar_ch4->setEnabled(false);

    m_ui->spinBox_average->setEnabled(false);
    m_ui->dial_average->setEnabled(false);

    m_ui->spinBox_display->setEnabled(false);
    m_ui->dial_display->setEnabled(false);

    m_ui->textBrowser_measVpp->setEnabled(false);
    m_ui->textBrowser_measAvg->setEnabled(false);
    m_ui->textBrowser_measMax->setEnabled(false);
    m_ui->textBrowser_measMin->setEnabled(false);

    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void WindowVm::on_pushButton_enable_clicked()
{
    m_smplBuff.clear();

    m_avg1_val = 0;
    m_avg2_val = 0;
    m_avg3_val = 0;
    m_avg4_val = 0;
    m_avgVcc_val = 0;
    m_avg_it = 0;

    m_instrEnabled = true;
    //m_elapsed_diff += m_timer_elapsed.elapsed() - m_elapsed_saved;

    m_ui->pushButton_enable->hide();
    m_ui->pushButton_disable->show();

    m_ui->textBrowser_ch1->setEnabled(true);
    m_ui->textBrowser_ch2->setEnabled(true);
    m_ui->textBrowser_ch3->setEnabled(true);
    m_ui->textBrowser_ch4->setEnabled(true);

    /*
    m_ui->pushButton_disable1->setEnabled(true);
    m_ui->pushButton_enable1->setEnabled(true);
    m_ui->pushButton_disable2->setEnabled(true);
    m_ui->pushButton_enable2->setEnabled(true);
    m_ui->pushButton_disable3->setEnabled(true);
    m_ui->pushButton_enable3->setEnabled(true);
    m_ui->pushButton_disable4->setEnabled(true);
    m_ui->pushButton_enable4->setEnabled(true);
    */

    m_ui->doubleSpinBox_gain1->setEnabled(true);
    m_ui->doubleSpinBox_gain2->setEnabled(true);
    m_ui->doubleSpinBox_gain3->setEnabled(true);
    m_ui->doubleSpinBox_gain4->setEnabled(true);

    m_ui->progressBar_ch1->setEnabled(true);
    m_ui->progressBar_ch2->setEnabled(true);
    m_ui->progressBar_ch3->setEnabled(true);
    m_ui->progressBar_ch4->setEnabled(true);

    m_ui->spinBox_average->setEnabled(true);
    m_ui->dial_average->setEnabled(true);

    if (m_plot)
    {
        m_ui->spinBox_display->setEnabled(true);
        m_ui->dial_display->setEnabled(true);
    }

    m_ui->textBrowser_measVpp->setEnabled(true);
    m_ui->textBrowser_measAvg->setEnabled(true);
    m_ui->textBrowser_measMax->setEnabled(true);
    m_ui->textBrowser_measMin->setEnabled(true);

    //m_ui->customPlot->setInteractions(0);
    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void WindowVm::on_pushButton_reset_clicked()
{
    bool en = m_instrEnabled;

    on_pushButton_disable_clicked();

    /* meas */
    on_actionMeasChannel_1_triggered(true);
    m_ui->actionMeasChannel_1->setChecked(true);

    on_actionMeasEnabled_triggered(true);
    m_ui->actionMeasEnabled->setChecked(true);

    on_actionMeasReset_triggered();

    /* math */
    on_actionMath_1_2_triggered(false);
    m_ui->actionMath_1_2->setChecked(false);

    on_actionMath_3_4_triggered(false);
    m_ui->actionMath_3_4->setChecked(false);

    /* cursors */
    on_pushButton_cursorsVoff_clicked();
    on_pushButton_cursorsHoff_clicked();

    /* plot style */
    /*
    on_actionViewLines_triggered(true);
    m_ui->actionViewLines->setChecked(true);

    on_actionViewPoints_triggered(false);
    m_ui->actionViewPoints->setChecked(false);

    on_actionInterpSinc_triggered(true);
    m_ui->actionInterpSinc->setChecked(true);

    on_actionShowPlot_triggered(true);
    m_ui->actionShowPlot->setChecked(true);
    */

    /* channels */
    on_pushButton_disable1_clicked();
    on_pushButton_disable2_clicked();
    on_pushButton_disable3_clicked();
    on_pushButton_disable4_clicked();
    on_pushButton_enable1_clicked();
    on_pushButton_enable2_clicked();

    /* main menu */
    m_ui->spinBox_average->setValue(DEFAULT_AVG);
    m_ui->spinBox_display->setValue(DEFAULT_PLT);

    /* recording */
    if (m_recording)
        on_actionExportStop_triggered();
    m_rec.reset();
    Settings::setValue(CFG_REC_DIR, m_rec.getDir());

    on_actionExportCSV_triggered(true);
    m_ui->actionExportCSV->setChecked(true);

    /* gain */
    m_ui->doubleSpinBox_gain1->setValue(1);
    m_ui->doubleSpinBox_gain2->setValue(1);
    m_ui->doubleSpinBox_gain3->setValue(1);
    m_ui->doubleSpinBox_gain4->setValue(1);

    /* graph data */
    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    /* helper vars */
    m_smplBuff.clear();
    m_timer_elapsed = 0;

    m_elapsed_diff = 0;
    m_elapsed_saved = 0;
    m_data_fresh = false;

    on_pushButton_resetZoom_clicked();

    if (en)
        on_pushButton_enable_clicked();
    //else
    //    m_ui->customPlot->replot();
}

void WindowVm::on_pushButton_resetZoom_clicked()
{
    //m_ui->customPlot->setInteractions(0);
    //m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    rescaleYAxis();

    m_ui->pushButton_reset->show();
    m_ui->pushButton_resetZoom->hide();
}

/********** right pannel - main settings **********/

void WindowVm::on_spinBox_average_valueChanged(int arg1)
{
    m_ui->dial_average->setValue(arg1);

    m_average = arg1;

    m_smplBuff.clear();

    m_avg1_val = 0;
    m_avg2_val = 0;
    m_avg3_val = 0;
    m_avg4_val = 0;
    m_avgVcc_val = 0;
    m_avg_it = 0;

    double nplc = m_average / 2.0;
    m_ui->label_nplc->setText(QString::number(nplc, 'f', 1) + " NPLC");

    Settings::setValue(CFG_VM_AVG, arg1);

    if (m_average > 1)
        m_ui->label_avg->setText("Average:");
    else
        m_ui->label_avg->setText("Average (OFF):");

    on_spinBox_display_valueChanged(m_display_pts);
}

void WindowVm::on_dial_average_valueChanged(int value)
{
    m_ui->spinBox_average->setValue(value);
}

void WindowVm::on_spinBox_display_valueChanged(int arg1)
{
    m_ui->dial_display->setValue(arg1);

    m_display_pts = arg1;
    m_display = ((double)arg1 - 1) / (100.0 / m_average);

    Settings::setValue(CFG_VM_PLT, arg1);
}

void WindowVm::on_dial_display_valueChanged(int value)
{
    m_ui->spinBox_display->setValue(value);
}

/********************************* private *********************************/

void WindowVm::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();

    Core::getInstance()->setMode(NO_MODE);
    emit closing(WindowVm::staticMetaObject.className());

    m_timer_plot->stop();
    m_timer_digits->stop();
}

void WindowVm::showEvent(QShowEvent*)
{
    auto info = Core::getInstance()->getDevInfo();
    QStringList pins = info->pins_scope_vm.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (pins.size() == 2)
    {
        m_pin1 = pins[0].trimmed();
        m_pin2 = pins[1].trimmed();

        m_ui->label_ch1->setText("Channel 1 (" + m_pin1 + ")");
        m_ui->label_ch2->setText("Channel 2 (" + m_pin2 + ")");
    }
    if (pins.size() == 4)
    {
        m_pin3 = pins[2].trimmed();
        m_pin4 = pins[3].trimmed();

        m_ui->label_ch3->setText("Channel 3 (" + m_pin3 + ")");
        m_ui->label_ch4->setText("Channel 4 (" + m_pin4 + ")");
    }

    m_ui->dial_average->setMaximum(info->vm_mem);
    m_ui->spinBox_average->setMaximum(info->vm_mem);

    m_ref_v = info->ref_mv / 1000;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    //m_ui->customPlot->replot();

    Core::getInstance()->setMode(VM);

    m_activeMsgs.push_back(m_msg_read1);
    m_activeMsgs.push_back(m_msg_read2);
    m_activeMsgs.push_back(m_msg_read3);
    m_activeMsgs.push_back(m_msg_read4);
    //m_activeMsgs.push_back(m_msg_read5);

    m_smplBuff.clear();
    m_data_fresh = false;
    on_actionMeasReset_triggered();

    m_timer_elapsed = 0;
    m_timer_plot->start((int)TIMER_VM_PLOT);
    m_timer_digits->start(TIMER_VM_DIGITS);

    if (info->daq_ch == 2)
    {
        on_pushButton_disable3_clicked();
        on_pushButton_disable4_clicked();

        m_ui->groupBox_ch3->setEnabled(false);
        m_ui->groupBox_ch4->setEnabled(false);

        m_ui->actionMeasChannel_3->setEnabled(false);
        m_ui->actionMeasChannel_4->setEnabled(false);

        m_ui->actionMath_3_4->setEnabled(false);
    }
}

void WindowVm::rescaleYAxis()
{
    double max_scale = 0;
    double min_scale = 0;
    if (m_en1 && m_gain1 > max_scale) max_scale = m_gain1;
    else if (m_en1 && m_gain1 < min_scale) min_scale = m_gain1;
    if (m_en2 && m_gain2 > max_scale) max_scale = m_gain2;
    else if (m_en2 && m_gain2 < min_scale) min_scale = m_gain2;
    if (m_en3 && m_gain3 > max_scale) max_scale = m_gain3;
    else if (m_en3 && m_gain3 < min_scale) min_scale = m_gain3;
    if (m_en4 && m_gain4 > max_scale) max_scale = m_gain4;
    else if (m_en4 && m_gain4 < min_scale) min_scale = m_gain4;

    double yLim = (m_spline ? Y_LIM1 : Y_LIM2);
    m_ui->customPlot->yAxis->setRange((min_scale * m_ref_v) - yLim, (max_scale * m_ref_v) + yLim);
}

void WindowVm::rescaleXAxis()
{
    m_ui->customPlot->xAxis->setRange(m_key_last, m_display, Qt::AlignRight);
}

