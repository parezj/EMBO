/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_scope.h"
#include "ui_window_scope.h"
#include "window_pwm.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#include <QDebug>
#include <QLabel>
#include <QMap>
#include <QDateTime>
#include <QMessageBox>


#define Y_LIM1                  0.50    // spline on
#define Y_LIM2                  0.15    // spline off
#define TRIG_VAL_PRE_TIMEOUT    3000    // trig cursors visible time

#define FFT_MAX_SIZE            131072  // 1048576 //65536
#define FFT_DB_MIN              -100
#define FFT_DB_MAX              0


WindowScope::WindowScope(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowScope), m_rec(4)
{
    m_ui->setupUi(this);

    m_timer_plot = new QTimer(this);
    m_timer_plot->setTimerType(Qt::PreciseTimer);

    m_timer_trigSliders = new QTimer(this);
    m_timer_trigSliders->setSingleShot(true);

    m_msg_set = new Msg_SCOP_Set(this);
    m_msg_read = new Msg_SCOP_Read(this);
    m_msg_forceTrig = new Msg_SCOP_ForceTrig(this);

    connect(m_msg_set, &Msg_SCOP_Set::ok2, this, &WindowScope::on_msg_ok_set, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_SCOP_Set::err, this, &WindowScope::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_SCOP_Set::result, this, &WindowScope::on_msg_set, Qt::QueuedConnection);

    connect(m_msg_read, &Msg_SCOP_Read::err, this, &WindowScope::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read, &Msg_SCOP_Read::result, this, &WindowScope::on_msg_read, Qt::QueuedConnection);

    connect(m_msg_forceTrig, &Msg_SCOP_ForceTrig::ok, this, &WindowScope::on_msg_ok_forceTrig, Qt::QueuedConnection);
    //connect(m_msg_forceTrig, &Msg_SCOP_ForceTrig::err, this, &WindowScope::on_msg_err, Qt::QueuedConnection);

    connect(Core::getInstance(), &Core::daqReady, this, &WindowScope::on_msg_daqReady, Qt::QueuedConnection);

    connect(m_timer_plot, &QTimer::timeout, this, &WindowScope::on_timer_plot);
    connect(m_timer_trigSliders, &QTimer::timeout, this, &WindowScope::on_hideTrigSliders);

    connect(m_ui->actionEMBO_Help, SIGNAL(triggered()), Core::getInstance(), SLOT(on_actionEMBO_Help()));

    /* QCP */

    initQcp();

    /* statusbar */

    statusBarLoad();

    /* button groups */

    m_trigMode.addButton(m_ui->radioButton_trigMode_Auto);
    m_trigMode.addButton(m_ui->radioButton_trigMode_Normal);
    m_trigMode.addButton(m_ui->radioButton_trigMode_Disabled);

    m_trigSlope.addButton(m_ui->radioButton_trigSlope_Rising);
    m_trigSlope.addButton(m_ui->radioButton_trigSlope_Falling);

    m_trigCh.addButton(m_ui->radioButton_trigCh_1);
    m_trigCh.addButton(m_ui->radioButton_trigCh_2);
    m_trigCh.addButton(m_ui->radioButton_trigCh_3);
    m_trigCh.addButton(m_ui->radioButton_trigCh_4);

    m_fsMem.addButton(m_ui->radioButton_fsMem);
    m_fsMem.addButton(m_ui->radioButton_div);

    m_trigMode.setExclusive(true);
    m_trigSlope.setExclusive(true);
    m_trigCh.setExclusive(true);
    m_fsMem.setExclusive(true);

    /* avg */

    m_ui->spinBox_average->setRange(1, MAX_SCOPE_AVG);
    m_ui->spinBox_average->setValue(AVERAGE_DEFAULT);

    m_average_buff_ch1 = QVector<QVector<double>>(MAX_SCOPE_AVG);
    m_average_buff_ch2 = QVector<QVector<double>>(MAX_SCOPE_AVG);
    m_average_buff_ch3 = QVector<QVector<double>>(MAX_SCOPE_AVG);
    m_average_buff_ch4 = QVector<QVector<double>>(MAX_SCOPE_AVG);

    /* styles */

    m_ui->label_FFT->setVisible(false);
    m_ui->label_Vpos1->setVisible(false);
    m_ui->label_Vpos2->setVisible(false);
    m_ui->label_Vpos3->setVisible(false);
    m_ui->label_Vpos4->setVisible(false);

    /* settings */

    m_ui->actionInterpSinc->setChecked(Settings::getValue(CFG_SCOPE_SPLINE, true).toBool());
    on_actionInterpSinc_triggered(m_ui->actionInterpSinc->isChecked());

    /* event filter */

    m_ui->dial_trigPre->installEventFilter(this);
    m_ui->dial_trigVal->installEventFilter(this);

    m_instrEnabled = true;
}

bool WindowScope::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_ui->dial_trigPre || obj == m_ui->dial_trigVal)
    {
        if (event->type() == QEvent::Wheel)
        {
            return true; // handled
        }
        return false; // pass the event to the widget
    }
    else
    {
        return QMainWindow::eventFilter(obj, event); // pass the event on to the parent class
    }
}

void WindowScope::statusBarLoad()
{
    m_status_vcc = new QLabel(" ", this);
    m_status_seq = new QLabel("Sequence Number: 0", this);
    m_status_smpl = new QLabel("Sampling Time: 1.5", this);
    m_status_ets = new QLabel("", this);

    QWidget* widget = new QWidget(this);
    QLabel* status_zoom = new QLabel("<span>Zoom with Scroll Wheel, Move with Mouse Drag&nbsp;&nbsp;<span>", this);

    QFont font1("Roboto", 11, QFont::Normal);
    m_status_vcc->setFont(font1);
    m_status_seq->setFont(font1);
    m_status_smpl->setFont(font1);
    m_status_ets->setFont(font1);
    status_zoom->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/img/scope.svg");

    status_img->setPixmap(status_img_icon);
    status_img->setFixedWidth(17);
    status_img->setFixedHeight(17);
    status_img->setScaledContents(true);

    m_status_line1 = new QFrame(this);
    m_status_line1->setFrameShape(QFrame::VLine);
    m_status_line1->setFrameShadow(QFrame::Plain);
    m_status_line1->setStyleSheet("color:gray;");
    m_status_line1->setFixedHeight(18);

    m_status_line2 = new QFrame(this);
    m_status_line2->setFrameShape(QFrame::VLine);
    m_status_line2->setFrameShadow(QFrame::Plain);
    m_status_line2->setStyleSheet("color:gray;");
    m_status_line2->setFixedHeight(18);

    m_status_line3 = new QFrame(this);
    m_status_line3->setFrameShape(QFrame::VLine);
    m_status_line3->setFrameShadow(QFrame::Plain);
    m_status_line3->setStyleSheet("color:gray;");
    m_status_line3->setFixedHeight(18);
    m_status_line3->setVisible(false);

    QLabel* status_spacer2 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer3 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer4 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer5 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer6 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer7 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);

    QSpacerItem* status_spacer0 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(status_img,     0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_vcc,   0,1,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer2, 0,2,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_line1, 0,3,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer3, 0,4,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_smpl,  0,5,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer4, 0,6,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_line2, 0,7,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer5, 0,8,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_seq,   0,9,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer6, 0,10,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_line3, 0,11,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer7, 0,12,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_ets,   0,13,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->addItem(status_spacer0,   0,14,1,1,Qt::AlignVCenter);
    layout->addWidget(status_zoom,    0,15,1,1,Qt::AlignVCenter);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);
}

void WindowScope::initQcp()
{
    m_ui->customPlot->plotLayout()->clear();

    m_axis_scope = new QCPAxisRect(m_ui->customPlot);
    m_axis_fft = new QCPAxisRect(m_ui->customPlot);

    m_axis_scope->setupFullAxesBox();
    m_axis_fft->setupFullAxesBox();

    QFont font2("Roboto", 12, QFont::Normal);
    m_axis_scope->axis(QCPAxis::atBottom)->setTickLabelFont(font2);
    m_axis_fft->axis(QCPAxis::atBottom)->setTickLabelFont(font2);
    m_axis_scope->axis(QCPAxis::atLeft)->setTickLabelFont(font2);
    m_axis_fft->axis(QCPAxis::atLeft)->setTickLabelFont(font2);

    //m_axis_fft->axis(QCPAxis::atBottom)->setScaleType(QCPAxis::stLogarithmic);
    //m_axis_fft->axis(QCPAxis::atTop)->setScaleType(QCPAxis::stLogarithmic);

    m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_scope);
    m_ui->customPlot->plotLayout()->addElement(1, 0, m_axis_fft);

    foreach (QCPAxisRect *rect, m_ui->customPlot->axisRects())
    {
        foreach (QCPAxis *axis, rect->axes())
        {
            axis->setLayer("axes");
            axis->grid()->setLayer("grid");
        }
    }

    m_ui->customPlot->addGraph(m_axis_scope->axis(QCPAxis::atBottom), m_axis_scope->axis(QCPAxis::atLeft));
    m_ui->customPlot->addGraph(m_axis_scope->axis(QCPAxis::atBottom), m_axis_scope->axis(QCPAxis::atLeft));
    m_ui->customPlot->addGraph(m_axis_scope->axis(QCPAxis::atBottom), m_axis_scope->axis(QCPAxis::atLeft));
    m_ui->customPlot->addGraph(m_axis_scope->axis(QCPAxis::atBottom), m_axis_scope->axis(QCPAxis::atLeft));
    m_ui->customPlot->addGraph(m_axis_fft->axis(QCPAxis::atBottom), m_axis_fft->axis(QCPAxis::atLeft));

    m_ui->customPlot->graph(GRAPH_CH1)->setPen(QPen(QColor(COLOR1)));
    m_ui->customPlot->graph(GRAPH_CH2)->setPen(QPen(QColor(COLOR2)));
    m_ui->customPlot->graph(GRAPH_CH3)->setPen(QPen(QColor(COLOR5)));
    m_ui->customPlot->graph(GRAPH_CH4)->setPen(QPen(QColor(COLOR4)));
    m_ui->customPlot->graph(GRAPH_FFT)->setPen(QPen(QColor(COLOR1)));

    m_spline = true;

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(m_spline);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(m_spline);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(m_spline);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(m_spline);
    m_ui->customPlot->graph(GRAPH_FFT)->setSpline(false);

    m_timeTicker = QSharedPointer<QCPAxisTickerTime>(new QCPAxisTickerTime);
    m_timeTicker2 = QSharedPointer<QCPAxisTickerFixed>(new QCPAxisTickerFixed);
    m_timeTicker->setTimeFormat("%z ms");
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuSeconds, 1);
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuMilliseconds, 1);
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuMicroseconds, 1);

    auto ticker_fft = QSharedPointer<QCPAxisTickerPi>(new QCPAxisTickerPi);
    ticker_fft->setPiValue(1);
    ticker_fft->setPiSymbol("Hz");

    m_axis_scope->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);
    m_axis_fft->axis(QCPAxis::atBottom)->setTicker(ticker_fft);

    /*
    m_ui->customPlot->xAxis->setVisible(true);
    m_ui->customPlot->xAxis->setTickLabels(true);
    m_ui->customPlot->yAxis->setVisible(true);
    m_ui->customPlot->yAxis->setTickLabels(true);
    */

    //m_ui->customPlot->setInteractions(0);
    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    m_axis_scope->setRangeDrag(Qt::Horizontal);
    m_axis_scope->setRangeZoom(Qt::Horizontal);
    m_axis_fft->setRangeDrag(Qt::Horizontal);
    m_axis_fft->setRangeZoom(Qt::Horizontal);

    //m_ui->customPlot->setOpenGl(true);

    connect(m_axis_scope->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_scope->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
    connect(m_axis_fft->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_fft->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
    connect(m_axis_scope->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_scope->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));
    connect(m_axis_fft->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_fft->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));

    connect(m_ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(on_qcpMouseWheel(QWheelEvent*)));
    connect(m_ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(on_qcpMousePress(QMouseEvent*)));

    if (m_axis_scope->visible())
    {
        m_axis_scope->setVisible(false);
        m_axis_scope->layout()->take(m_axis_scope);
    }
    if (m_axis_fft->visible())
    {
        m_axis_fft->setVisible(false);
        m_axis_fft->layout()->take(m_axis_fft);
    }

    m_ui->customPlot->plotLayout()->simplify();

    m_ui->customPlot->plotLayout()->insertRow(0);
    m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_scope);
    m_axis_scope->setVisible(true);

    /* cursors */

    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorV->setValues(m_cursorV_min, m_cursorV_max);

    m_ui->horizontalSlider_cursorH->hide();
    m_ui->horizontalSlider_cursorV->hide();

    connect(m_ui->horizontalSlider_cursorH, &ctkRangeSlider::valuesChanged, this, &WindowScope::on_cursorH_valuesChanged);
    connect(m_ui->horizontalSlider_cursorV, &ctkRangeSlider::valuesChanged, this, &WindowScope::on_cursorV_valuesChanged);

    m_cursors = new QCPCursors(this, m_ui->customPlot, m_axis_scope, false, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursorTrigVal = new QCPCursor(this, m_ui->customPlot, NULL, true, false, QColor(COLOR9));
    m_cursorTrigPre = new QCPCursor(this, m_ui->customPlot, NULL, false, false, QColor(COLOR9));
}

WindowScope::~WindowScope()
{
    delete m_ui;

    if (m_fft_in != NULL)
        fftw_free(m_fft_in);
    if (m_fft_out != NULL)
        fftw_free(m_fft_out);
    if (m_fft_plan != NULL)
        fftw_destroy_plan(m_fft_plan);
}

void WindowScope::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/********************************* timer slots *********************************/

void WindowScope::on_timer_plot() // 60 FPS
{
    if (m_cursorsV_en || m_cursorsH_en)
    {
        auto rngV = m_axis_scope->axis(QCPAxis::atLeft)->range();
        auto rngH = m_axis_scope->axis(QCPAxis::atBottom)->range();

        m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false); // true
    }

    m_ui->customPlot->replot();
}

/******************************** MSG slots ********************************/

void WindowScope::on_msg_err(const QString text, MsgBoxType type, bool needClose)
{
    m_activeMsgs.clear();

    if (needClose)
        this->close();

    msgBox(this, text, type);
}

void WindowScope::on_msg_ok_set(double maxZ, double smpl_time, double fs_real_n, const QString fs_real)
{
    m_daqSet.maxZ_ohm = maxZ;
    m_daqSet.smpl_time = smpl_time;
    m_daqSet.fs_real = fs_real;
    m_daqSet.fs_real_n = fs_real_n;

    updatePanel();
    m_msgPending = false;
}

void WindowScope::on_msg_set(DaqBits bits, int mem, int fs, bool ch1, bool ch2, bool ch3, bool ch4, int trig_ch, int trig_val,
                             DaqTrigEdge trig_edge, DaqTrigMode trig_mode, int trig_pre, double maxZ,
                             double smpl_time, double fs_real_n, const QString fs_real)
{
    m_daqSet.bits = bits;
    m_daqSet.mem = mem;
    m_daqSet.fs = fs;
    m_daqSet.ch1_en = ch1;
    m_daqSet.ch2_en = ch2;
    m_daqSet.ch3_en = ch3;
    m_daqSet.ch4_en = ch4;
    m_daqSet.trig_ch = trig_ch;
    m_daqSet.trig_val = trig_val;
    m_daqSet.trig_edge = trig_edge;
    m_daqSet.trig_mode = trig_mode;
    m_daqSet.trig_pre = trig_pre;
    m_daqSet.maxZ_ohm = maxZ;
    m_daqSet.smpl_time = smpl_time;
    m_daqSet.fs_real = fs_real;
    m_daqSet.fs_real_n = fs_real_n;

    updatePanel();
    m_msgPending = false;
}

void WindowScope::on_msg_read(const QByteArray data)
{
    if (m_msgPending)
        return;

    /************* parse circular buffer(s) *************/

    auto info = Core::getInstance()->getDevInfo();
    int ch_num = m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en;

    const uint8_t* dataU8 = reinterpret_cast<const uint8_t*>(data.constData());

    QVector<double> y1(m_daqSet.mem);
    QVector<double> y2(m_daqSet.mem);
    QVector<double> y3(m_daqSet.mem);
    QVector<double> y4(m_daqSet.mem);

    QVector<double>* _y1 = (m_daqSet.ch1_en ? &y1 : NULL);
    QVector<double>* _y2 = (m_daqSet.ch2_en ? &y2 : NULL);
    QVector<double>* _y3 = (m_daqSet.ch3_en ? &y3 : NULL);
    QVector<double>* _y4 = (m_daqSet.ch4_en ? &y4 : NULL);

    double vcc = info->ref_mv / 1000.0;
    int found = 0;

    if (info->adc_num == 1)
    {
        uint8_t* buff1 = (uint8_t*)dataU8;
        int buff1_len = data.size();

        if (m_daqSet.bits == B12)
            buff1_len /= 2;

        int buff1_mem = buff1_len - (info->daq_reserve * ch_num);

        found += get_vals_from_circ(m_firstPos, buff1_mem, buff1_len, m_daqSet.bits, vcc, buff1, _y1, _y2, _y3, _y4,
                                    m_gain1, m_gain2, m_gain3, m_gain4, m_offset1, m_offset2, m_offset3, m_offset4);

    }
    else if (info->adc_num == 2)
    {
        int buff_part = data.size();
        int buff_part_raw = buff_part;

        if (m_daqSet.bits == B12)
            buff_part /= 2;
        buff_part /= ch_num;
        buff_part_raw /= ch_num;

        uint8_t* buff_it = (uint8_t*)dataU8;

        uint8_t* buff1 = NULL;
        int buff1_len = 0;
        int buff1_mem;

        uint8_t* buff2 = NULL;
        int buff2_len = 0;
        int buff2_mem;

        if (m_daqSet.ch1_en)
        {
            buff1 = buff_it;
            buff_it += buff_part_raw;
            buff1_len += buff_part;
        }
        if (m_daqSet.ch2_en)
        {
            if (!m_daqSet.ch1_en)
                buff1 = buff_it;
            buff_it += buff_part_raw;
            buff1_len += buff_part;
        }
        if (m_daqSet.ch3_en)
        {
            buff2 = buff_it;
            buff_it += buff_part_raw;
            buff2_len += buff_part;
        }
        if (m_daqSet.ch4_en)
        {
            if (!m_daqSet.ch3_en)
                buff2 = buff_it;
            //buff_it += buff_part_raw;
            buff2_len += buff_part;
        }

        buff1_mem = buff1_len - (info->daq_reserve * (m_daqSet.ch1_en + m_daqSet.ch2_en));
        buff2_mem = buff2_len - (info->daq_reserve * (m_daqSet.ch3_en + m_daqSet.ch4_en));

        if (m_daqSet.ch1_en || m_daqSet.ch2_en)
            found += get_vals_from_circ(m_firstPos, buff1_mem, buff1_len, m_daqSet.bits, vcc, buff1, _y1, _y2, NULL, NULL,
                                        m_gain1, m_gain2, 0, 0, m_offset1, m_offset2, 0, 0);
        if (m_daqSet.ch3_en || m_daqSet.ch4_en)
            found += get_vals_from_circ(m_firstPos, buff2_mem, buff2_len, m_daqSet.bits, vcc, buff2, _y3, _y4, NULL, NULL,
                                        m_gain3, m_gain4, 0, 0, m_offset3, m_offset4, 0, 0);

    }
    else if (info->adc_num == 4)
    {
        int buff_part = data.size();
        int buff_part_raw = buff_part;

        if (m_daqSet.bits == B12)
            buff_part /= 2;
        buff_part /= ch_num;
        buff_part_raw /= ch_num;

        uint8_t* buff_it = (uint8_t*)dataU8;

        uint8_t* buff1 = NULL;
        int buff1_len = buff_part;
        int buff1_mem = buff1_len - (info->daq_reserve);

        uint8_t* buff2 = NULL;
        int buff2_len = buff_part;
        int buff2_mem = buff2_len - (info->daq_reserve);

        uint8_t* buff3 = NULL;
        int buff3_len = buff_part;
        int buff3_mem = buff3_len - (info->daq_reserve);

        uint8_t* buff4 = NULL;
        int buff4_len = buff_part;
        int buff4_mem = buff4_len - (info->daq_reserve);

        if (m_daqSet.ch1_en)
        {
            buff1 = buff_it;
            buff_it += buff_part_raw;
        }
        if (m_daqSet.ch2_en)
        {
            buff2 = buff_it;
            buff_it += buff_part_raw;
        }
        if (m_daqSet.ch3_en)
        {
            buff3 = buff_it;
            buff_it += buff_part_raw;
        }
        if (m_daqSet.ch4_en)
        {
            buff4 = buff_it;
            buff_it += buff_part_raw;
        }

        if (m_daqSet.ch1_en)
            found += get_vals_from_circ(m_firstPos, buff1_mem, buff1_len, m_daqSet.bits, vcc, buff1, _y1, NULL, NULL, NULL,
                                        m_gain1, 0, 0, 0, m_offset1, 0, 0, 0);
        if (m_daqSet.ch2_en)
            found += get_vals_from_circ(m_firstPos, buff2_mem, buff2_len, m_daqSet.bits, vcc, buff2, _y2, NULL, NULL, NULL,
                                        m_gain2, 0, 0, 0, m_offset2, 0, 0, 0);
        if (m_daqSet.ch3_en)
            found += get_vals_from_circ(m_firstPos, buff3_mem, buff3_len, m_daqSet.bits, vcc, buff3, _y3, NULL, NULL, NULL,
                                        m_gain3, 0, 0, 0, m_offset3, 0, 0, 0);
        if (m_daqSet.ch4_en)
            found += get_vals_from_circ(m_firstPos, buff4_mem, buff4_len, m_daqSet.bits, vcc, buff4, _y4, NULL, NULL, NULL,
                                        m_gain4, 0, 0, 0, m_offset4, 0, 0, 0);

    }
    else assert(0);

    if (found / ch_num != m_daqSet.mem) // wrong data size
    {
        m_err_cntr++;
        if (m_err_cntr > READ_ERROR_CNT)
        {
            on_msg_err(QString(INVALID_MSG) + " (data size wrong -> " + QString::number(found) + "!=" +
                       QString::number((m_daqSet.mem * ch_num)) + ")", CRITICAL, true);
            m_err_cntr = 0;
        }

        return;
    }

    /************* math *************/

    if (m_math_2minus1 || m_math_4minus3)
    {
        for (int i = 0; i < m_daqSet.mem; i++)
        {
            if (m_math_2minus1 && m_daqSet.ch1_en && m_daqSet.ch2_en)
                y1[i] = y2[i] - y1[i];

            if (m_math_4minus3 && m_daqSet.ch3_en && m_daqSet.ch4_en)
                y3[i] = y4[i] - y3[i];
        }
    }

    /************* average *************/

    if (m_average)
    {
        if (m_average_cnt < m_average_num)
            m_average_cnt++;

        for (int i = 0; i < m_daqSet.mem; i++)
        {
            double acc1 = 0;
            double acc2 = 0;
            double acc3 = 0;
            double acc4 = 0;

            if (m_daqSet.ch1_en) m_average_buff_ch1[m_average_it][i] = y1[i];
            if (m_daqSet.ch2_en) m_average_buff_ch2[m_average_it][i] = y2[i];
            if (m_daqSet.ch3_en) m_average_buff_ch3[m_average_it][i] = y3[i];
            if (m_daqSet.ch4_en) m_average_buff_ch4[m_average_it][i] = y4[i];

            for (int j = 0; j < m_average_cnt; j++)
            {
                if (m_daqSet.ch1_en) acc1 += m_average_buff_ch1[j][i];
                if (m_daqSet.ch2_en) acc2 += m_average_buff_ch2[j][i];
                if (m_daqSet.ch3_en) acc3 += m_average_buff_ch3[j][i];
                if (m_daqSet.ch4_en) acc4 += m_average_buff_ch4[j][i];
            }

            if (m_daqSet.ch1_en) y1[i] = acc1 / m_average_cnt;
            if (m_daqSet.ch2_en) y2[i] = acc2 / m_average_cnt;
            if (m_daqSet.ch3_en) y3[i] = acc3 / m_average_cnt;
            if (m_daqSet.ch4_en) y4[i] = acc4 / m_average_cnt;
        }

        m_average_it++;

        if (m_average_it == m_average_num)
            m_average_it = 0;
    }

    /************* plot data *************/

    assert(!m_t.isEmpty());

    if (m_math_xy_12 || m_math_xy_34)
    {
        if (m_math_xy_12)
        {
            if (m_daqSet.ch1_en && m_daqSet.ch2_en)
                m_ui->customPlot->graph(GRAPH_CH1)->setData(y1, y2);
        }

        if (m_math_xy_34)
        {
            if (m_daqSet.ch3_en && m_daqSet.ch4_en)
                m_ui->customPlot->graph(GRAPH_CH3)->setData(y3, y4);
        }
    }
    else
    {
        if (m_daqSet.ch1_en)
            m_ui->customPlot->graph(GRAPH_CH1)->setData(m_t, y1);

        if (!m_math_2minus1 && m_daqSet.ch2_en)
            m_ui->customPlot->graph(GRAPH_CH2)->setData(m_t, y2);

        if (m_daqSet.ch3_en)
            m_ui->customPlot->graph(GRAPH_CH3)->setData(m_t, y3);

        if (!m_math_4minus3 && m_daqSet.ch4_en)
            m_ui->customPlot->graph(GRAPH_CH4)->setData(m_t, y4);
    }

    /************* meas *************/

    if (m_meas_en)
    {
        QString meas_vpp_s;
        QString meas_rms_s;
        QString meas_avg_s;
        QString meas_min_s;
        QString meas_max_s;

        auto data_begin = m_ui->customPlot->graph(m_meas_ch)->data()->constBegin();
        auto data_end = m_ui->customPlot->graph(m_meas_ch)->data()->constEnd();

        double avg = std::accumulate(data_begin, data_end, .0, [](double a, QCPGraphData b) { return a + b.value;}) / std::distance(data_begin, data_end);
        double rms = sqrt((std::accumulate(data_begin, data_end, .0, [](double a, QCPGraphData b) { return a + (b.value * b.value);}) / std::distance(data_begin, data_end)));
        double min = std::min_element(data_begin, data_end, [](QCPGraphData a, QCPGraphData b) { return a.value < b.value; })->value; // m_meas_min;
        double max = std::max_element(data_begin, data_end, [](QCPGraphData a, QCPGraphData b) { return a.value < b.value; })->value; // m_meas_max;
        double vpp = max - min;

        meas_vpp_s = meas_vpp_s.asprintf(vpp >= 100 || vpp <= -10  ? "%.2f" : (vpp >= 10 || vpp < 0 ? "%.3f" : "%.4f"), vpp);
        meas_rms_s = meas_rms_s.asprintf(rms >= 100 || rms <= -10  ? "%.2f" : (rms >= 10 || rms < 0 ? "%.3f" : "%.4f"), rms);
        meas_avg_s = meas_avg_s.asprintf(avg >= 100 || avg <= -10  ? "%.2f" : (avg >= 10 || avg < 0 ? "%.3f" : "%.4f"), avg);
        meas_min_s = meas_min_s.asprintf(min >= 100 || min <= -10  ? "%.2f" : (min >= 10 || min < 0 ? "%.3f" : "%.4f"), min);
        meas_max_s = meas_max_s.asprintf(max >= 100 || max <= -10  ? "%.2f" : (max >= 10 || max < 0 ? "%.3f" : "%.4f"), max);

        m_ui->textBrowser_measVpp->setHtml("<p align=\"right\">" + meas_vpp_s + " </p>");
        m_ui->textBrowser_measRms->setHtml("<p align=\"right\">" + meas_rms_s + " </p>");
        m_ui->textBrowser_measAvg->setHtml("<p align=\"right\">" + meas_avg_s + " </p>");
        m_ui->textBrowser_measMin->setHtml("<p align=\"right\">" + meas_min_s + " </p>");
        m_ui->textBrowser_measMax->setHtml("<p align=\"right\">" + meas_max_s + " </p>");
    }

    /************* FFT *************/

    if (m_fft)
    {
        QVector<double>* y = NULL;

        if (m_fft_ch == 1 && m_daqSet.ch1_en)
            y = &y1;
        else if (m_fft_ch == 2 && m_daqSet.ch2_en)
            y = &y2;
        else if (m_fft_ch == 3 && m_daqSet.ch3_en)
            y = &y3;
        else if (m_fft_ch == 4 && m_daqSet.ch4_en)
            y = &y4;

        if (y != NULL && m_fft_in != NULL)
        {
            memset(m_fft_in, 0, m_fft_size); // zero pad
            memcpy(m_fft_in, (*y).data(), m_daqSet.mem * sizeof(double));

            for (int i = 0; i < m_daqSet.mem; i++)
            {
                double multiplier = 0.5 * (1 - cos(2*M_PI*i/(m_daqSet.mem - 1))); // hanning window
                m_fft_in[i] = multiplier * m_fft_in[i];
            }

            fftw_execute(m_fft_plan);

            double scale = 1.0 / (double)m_daqSet.mem;
            QVector<double> fft_db;

            for (int re = 0, im = m_fft_size - 1; re < m_fft_size / 2; re++, im--)
            {
                m_fft_out[re] *= scale; // normalize
                m_fft_out[im] *= scale;

                double db = 20 * log10(sqrt((m_fft_out[re] * m_fft_out[re]) + (m_fft_out[im] * m_fft_out[im]))); // complex to dB
                fft_db.append(db);
            }

            m_ui->customPlot->graph(GRAPH_FFT)->setData(m_fft_x, fft_db);

            if (m_rescale_fft_needed)
            {
                m_axis_fft->axis(QCPAxis::atLeft)->setRange(FFT_DB_MIN, FFT_DB_MAX);
                //m_axis_fft->axis(QCPAxis::atLeft)->rescale();
                m_axis_fft->axis(QCPAxis::atBottom)->setRange(0, m_daqSet.fs_real_n / 2);
                m_rescale_fft_needed = false;
            }
        }
    }

    /************* seq num *************/

    m_seq_num++;
    m_status_seq->setText("Sequence Number: " + QString::number(m_seq_num));

    /************** ETS ****************/

    if (m_ets)
    {
        double fin = m_ets_freq;
        if (m_ets_pwm)
            fin = WindowPwm::getFreqReal().toDouble();

        if (m_fin_last != fin)
        {
            m_last_fs = 0;
            m_rescale_needed = true;
            updatePanel();
        }

        m_fin_last = fin;
    }

    /************* finally replot *************/

    //m_ui->customPlot->replot();
}

void WindowScope::on_msg_daqReady(Ready ready, int firstPos)
{
    if (m_msgPending)
    {
        m_msgPending = false;
        return;
    }

    m_firstPos = firstPos;
    m_ready = ready;

    if (ready == Ready::READY_NORMAL || ready == Ready::READY_SINGLE)
    {
        if (m_trig_led)
            m_ui->radioButton_trigLed->setStyleSheet(CSS_TRIG_LED1);
        else
            m_ui->radioButton_trigLed->setStyleSheet(CSS_TRIG_LED2);

        m_trig_led = !m_trig_led;
        m_ui->radioButton_trigLed->setChecked(true);
    }
    else
        m_ui->radioButton_trigLed->setChecked(false);

    if (m_instrEnabled)
        Core::getInstance()->msgAdd(m_msg_read, true);
}

void WindowScope::on_msg_ok_forceTrig(const QString, const QString)
{
    updatePanel();
}

/******************************** GUI slots ********************************/

/********** Plot **********/

void WindowScope::on_actionViewPoints_triggered(bool checked)
{
    QCPScatterStyle style = QCPScatterStyle(QCPScatterStyle::ssNone);

    if (checked)
        style = QCPScatterStyle(QCPScatterStyle::ssDisc, 5);

    m_points = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setScatterStyle(style);

    m_ui->customPlot->replot();
}

void WindowScope::on_actionViewLines_triggered(bool checked)
{
    QCPGraph::LineStyle style = QCPGraph::lsNone;

    if (checked)
        style = QCPGraph::lsLine;

    m_lines = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setLineStyle(style);

    m_ui->customPlot->replot();
}

void WindowScope::on_actionInterpLinear_triggered(bool checked) // exclusive with - actionSinc
{
    m_ui->actionInterpSinc->setChecked(!checked);
    on_actionInterpSinc_triggered(!checked);
}


void WindowScope::on_actionInterpSinc_triggered(bool checked) // exclusive with - actionLinear
{
    m_spline = checked;

    Settings::setValue(CFG_SCOPE_SPLINE, m_spline);

    m_ui->actionInterpLinear->setChecked(!checked);

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(checked);

    rescaleYAxis();
    m_ui->customPlot->replot();
}

/********** Export **********/

void WindowScope::on_actionExportSave_triggered()
{
    auto info = Core::getInstance()->getDevInfo();
    auto sys = QSysInfo();

    QMap<QString, QString> header {
        {"Common.Created",    {QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss.zzz")}},
        {"Common.Version",    "EMBO " + QString(APP_VERSION)},
        {"Common.System",     {sys.prettyProductName() + " [" + sys.currentCpuArchitecture() + "]"}},
        {"Common.Device",     info->name},
        {"Common.Firmware",   info->fw},
        {"Common.Vcc",        QString::number(info->ref_mv) + " mV"},
        {"Common.Mode",       "SCOPE"},
        {"SCOPE.SampleRate",  m_daqSet.fs_real},
        {"SCOPE.Resolution",  QString::number(m_daqSet.bits)},
        {"SCOPE.Memory",      QString::number(m_daqSet.mem)},
        {"SCOPE.Ch1",         m_daqSet.ch1_en ? "True" : "False"},
        {"SCOPE.Ch2",         m_daqSet.ch2_en ? "True" : "False"},
        {"SCOPE.Ch3",         m_daqSet.ch3_en ? "True" : "False"},
        {"SCOPE.Ch4",         m_daqSet.ch4_en ? "True" : "False"},
        {"SCOPE.Trig.Ch",     QString::number(m_daqSet.trig_ch)},
        {"SCOPE.Trig.Level",  QString::number(m_daqSet.trig_val)},
        {"SCOPE.Trig.Mode",   m_daqSet.trig_mode == AUTO ? "AUTO" : (m_daqSet.trig_mode == NORMAL ? "NORMAL" : (m_daqSet.trig_mode == SINGLE ? "SINGLE" : "DISABLED"))},
        {"SCOPE.Trig.Slope",  m_daqSet.trig_edge == RISING ? "RISING" : "FALLING"},
        {"SCOPE.Trig.Pre",    QString::number(m_daqSet.trig_pre)},
        {"SCOPE.MaxZ_ohm",    QString::number(m_daqSet.maxZ_ohm)},
    };
    bool ret = m_rec.createFile("SCOPE", header);

    if (!ret)
    {
        msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
    }
    else
    {
        auto data_1 = m_ui->customPlot->graph(GRAPH_CH1)->data();
        auto data_2 = m_ui->customPlot->graph(GRAPH_CH2)->data();
        auto data_3 = m_ui->customPlot->graph(GRAPH_CH3)->data();
        auto data_4 = m_ui->customPlot->graph(GRAPH_CH4)->data();

        for (int i = 0; i < data_1->size(); i++)
        {
            if (m_daqSet.ch1_en)
                m_rec << data_1->at(i)->value;
            if (m_daqSet.ch2_en)
                m_rec << data_2->at(i)->value;
            if (m_daqSet.ch3_en)
                m_rec << data_3->at(i)->value;
            if (m_daqSet.ch4_en)
                m_rec << data_4->at(i)->value;
            m_rec << ENDL;
        }

        auto f = m_rec.closeFile();
        msgBox(this, "File saved at: " + f, INFO);
    }
}

void WindowScope::on_actionExportPNG_triggered()
{
     //QString ret = m_rec.takeScreenshot("SCOPE", m_ui->customPlot);

     QString path = m_rec.generateFilePath("SCOPE", ".png");
     bool ret = m_ui->customPlot->savePng(path);

     if (ret)
         msgBox(this, "File saved at: " + path, INFO);
     else
         msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
}

void WindowScope::on_actionExportPDF_triggered()
{
    QString path = m_rec.generateFilePath("SCOPE", ".pdf");
    bool ret = m_ui->customPlot->savePdf(path);

    if (ret)
        msgBox(this, "File saved at: " + path, INFO);
    else
        msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
}

void WindowScope::on_actionExportFolder_triggered()
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

void WindowScope::on_actionExportCSV_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(CSV);

        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowScope::on_actionExportTXT_Tabs_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(TAB);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowScope::on_actionExportTXT_Semicolon_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(SEMICOLON);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowScope::on_actionExportMAT_triggered(bool checked)
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

void WindowScope::on_actionMeasEnabled_triggered(bool checked)
{
    m_meas_en = checked;
    on_actionMeasReset_triggered();

    m_ui->textBrowser_measVpp->setEnabled(checked);
    m_ui->textBrowser_measRms->setEnabled(checked);
    m_ui->textBrowser_measAvg->setEnabled(checked);
    m_ui->textBrowser_measMin->setEnabled(checked);
    m_ui->textBrowser_measMax->setEnabled(checked);
}

void WindowScope::on_actionMeasReset_triggered()
{
    //m_meas_max = -1000;
    //m_meas_min = 1000;

    m_ui->textBrowser_measVpp->setText("");
    m_ui->textBrowser_measRms->setText("");
    m_ui->textBrowser_measAvg->setText("");
    m_ui->textBrowser_measMin->setText("");
    m_ui->textBrowser_measMax->setText("");
}

void WindowScope::on_actionMeasChannel_1_triggered(bool checked)
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

void WindowScope::on_actionMeasChannel_2_triggered(bool checked)
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

void WindowScope::on_actionMeasChannel_3_triggered(bool checked)
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

void WindowScope::on_actionMeasChannel_4_triggered(bool checked)
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

void WindowScope::on_actionMath_1_2_triggered(bool checked)
{
    if (checked)
    {
        on_actionMath_3_4_triggered(false);
        on_actionMath_XY_X_1_Y_2_triggered(false);
        on_actionMath_XY_X_3_Y_4_triggered(false);

        m_ui->pushButton_enable1->setText(" 2—1  ");
        m_ui->pushButton_disable1->setText(" 2—1  ");

        m_ui->pushButton_enable2->setText(" 2—1  ");
        m_ui->pushButton_disable2->setText(" 2—1  ");

        m_ui->actionMath_3_4->setChecked(false);
        m_ui->actionMath_XY_X_1_Y_2->setChecked(false);
        m_ui->actionMath_XY_X_3_Y_4->setChecked(false);
    }
    else
    {
        m_ui->pushButton_enable1->setText(" CH1  ");
        m_ui->pushButton_disable1->setText(" CH1  ");

        m_ui->pushButton_enable2->setText(" CH2  ");
        m_ui->pushButton_disable2->setText(" CH2  ");
    }

    m_math_2minus1 = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();
}

void WindowScope::on_actionMath_3_4_triggered(bool checked)
{
    if (checked)
    {
        on_actionMath_1_2_triggered(false);
        on_actionMath_XY_X_1_Y_2_triggered(false);
        on_actionMath_XY_X_3_Y_4_triggered(false);

        m_ui->pushButton_enable3->setText(" 4—3  ");
        m_ui->pushButton_disable3->setText(" 4—3  ");

        m_ui->pushButton_enable4->setText(" 4—3  ");
        m_ui->pushButton_disable4->setText(" 4—3  ");

        m_ui->actionMath_1_2->setChecked(false);
        m_ui->actionMath_XY_X_1_Y_2->setChecked(false);
        m_ui->actionMath_XY_X_3_Y_4->setChecked(false);
    }
    else
    {
        m_ui->pushButton_enable3->setText(" CH3  ");
        m_ui->pushButton_disable3->setText(" CH3  ");

        m_ui->pushButton_enable4->setText(" CH4  ");
        m_ui->pushButton_disable4->setText(" CH4  ");
    }

    m_math_4minus3 = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();
}

void WindowScope::on_actionMath_XY_X_1_Y_2_triggered(bool checked)
{
    m_math_xy_12 = checked;

    if (checked)
    {
        on_actionMath_1_2_triggered(false);
        on_actionMath_3_4_triggered(false);
        on_actionMath_XY_X_3_Y_4_triggered(false);

        m_ui->pushButton_enable1->setText(" XY12");
        m_ui->pushButton_disable1->setText(" XY12");

        m_ui->pushButton_enable2->setText(" XY12");
        m_ui->pushButton_disable2->setText(" XY12");

        m_ui->actionMath_1_2->setChecked(false);
        m_ui->actionMath_3_4->setChecked(false);
        m_ui->actionMath_XY_X_3_Y_4->setChecked(false);

        m_ui->actionViewLines->setChecked(false);
        m_ui->actionViewPoints->setChecked(true);

        on_actionViewLines_triggered(false);
        on_actionViewPoints_triggered(true);

        m_axis_scope->axis(QCPAxis::atBottom)->setTicker(m_timeTicker2);
        rescaleXAxis();
    }
    else
    {
        m_ui->pushButton_enable1->setText(" CH1  ");
        m_ui->pushButton_disable1->setText( "CH1  ");

        m_ui->pushButton_enable2->setText(" CH2  ");
        m_ui->pushButton_disable2->setText(" CH2  ");

        m_ui->actionViewLines->setChecked(true);
        m_ui->actionViewPoints->setChecked(false);

        on_actionViewLines_triggered(true);
        on_actionViewPoints_triggered(false);

        m_axis_scope->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);
        rescaleXAxis();
    }

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();
}

void WindowScope::on_actionMath_XY_X_3_Y_4_triggered(bool checked)
{
    m_math_xy_34 = checked;

    if (checked)
    {
        on_actionMath_1_2_triggered(false);
        on_actionMath_3_4_triggered(false);
        on_actionMath_XY_X_1_Y_2_triggered(false);

        m_ui->pushButton_enable1->setText(" XY34");
        m_ui->pushButton_disable1->setText( "XY34");

        m_ui->pushButton_enable2->setText(" XY34");
        m_ui->pushButton_disable2->setText(" XY34");

        m_ui->actionMath_1_2->setChecked(false);
        m_ui->actionMath_3_4->setChecked(false);
        m_ui->actionMath_XY_X_1_Y_2->setChecked(false);

        m_ui->actionViewLines->setChecked(false);
        m_ui->actionViewPoints->setChecked(true);

        on_actionViewLines_triggered(false);
        on_actionViewPoints_triggered(true);

        m_axis_scope->axis(QCPAxis::atBottom)->setTicker(m_timeTicker2);
        rescaleXAxis();
    }
    else
    {
        m_ui->pushButton_enable1->setText(" CH3  ");
        m_ui->pushButton_disable1->setText(" CH3  ");

        m_ui->pushButton_enable2->setText(" CH4  ");
        m_ui->pushButton_disable2->setText(" CH4  ");

        m_ui->actionViewLines->setChecked(true);
        m_ui->actionViewPoints->setChecked(false);

        on_actionViewLines_triggered(true);
        on_actionViewPoints_triggered(false);

        m_axis_scope->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);
        rescaleXAxis();
    }

    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();
}

/********** FFT **********/

void WindowScope::on_actionFFTChannel_1_triggered(bool checked)
{
    if (checked)
    {
        m_fft_ch = 1;
        m_ui->label_FFT->setText("CH1");

        m_ui->actionFFTChannel_2->setChecked(false);
        m_ui->actionFFTChannel_3->setChecked(false);
        m_ui->actionFFTChannel_4->setChecked(false);

        m_ui->customPlot->graph(GRAPH_FFT)->setPen(QPen(QColor(COLOR1)));
        m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

        m_ui->customPlot->replot();
    }
}

void WindowScope::on_actionFFTChannel_2_triggered(bool checked)
{
    if (checked)
    {
        m_fft_ch = 2;
        m_ui->label_FFT->setText("CH2");

        m_ui->actionFFTChannel_1->setChecked(false);
        m_ui->actionFFTChannel_3->setChecked(false);
        m_ui->actionFFTChannel_4->setChecked(false);

        m_ui->customPlot->graph(GRAPH_FFT)->setPen(QPen(QColor(COLOR2)));
        m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

        m_ui->customPlot->replot();
    }
}

void WindowScope::on_actionFFTChannel_3_triggered(bool checked)
{
    if (checked)
    {
        m_fft_ch = 3;
        m_ui->label_FFT->setText("CH3");

        m_ui->actionFFTChannel_1->setChecked(false);
        m_ui->actionFFTChannel_2->setChecked(false);
        m_ui->actionFFTChannel_4->setChecked(false);

        m_ui->customPlot->graph(GRAPH_FFT)->setPen(QPen(QColor(COLOR5)));
        m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

        m_ui->customPlot->replot();
    }
}

void WindowScope::on_actionFFTChannel_4_triggered(bool checked)
{
    if (checked)
    {
        m_fft_ch = 4;
        m_ui->label_FFT->setText("CH4");

        m_ui->actionFFTChannel_1->setChecked(false);
        m_ui->actionFFTChannel_2->setChecked(false);
        m_ui->actionFFTChannel_3->setChecked(false);

        m_ui->customPlot->graph(GRAPH_FFT)->setPen(QPen(QColor(COLOR4)));
        m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

        m_ui->customPlot->replot();
    }
}

void WindowScope::on_actionFFTSplit_Screen_triggered(bool checked)
{
    m_fft_split = checked;

    m_axis_scope->setMinimumMargins(QMargins(45,15,15,0));

    if (m_fft_split)
        m_axis_fft->setMinimumMargins(QMargins(45,0,15,30));
    else
        m_axis_fft->setMinimumMargins(QMargins(45,15,15,30));

    if (m_fft)
    {
        if (checked)
        {
            if (m_axis_scope->visible())
            {
                m_axis_scope->setVisible(false);
                m_axis_scope->layout()->take(m_axis_scope);
            }
            if (m_axis_fft->visible())
            {
                m_axis_fft->setVisible(false);
                m_axis_fft->layout()->take(m_axis_fft);
            }

            m_ui->customPlot->plotLayout()->simplify();

            m_ui->customPlot->plotLayout()->insertRow(0);
            m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_fft);
            m_axis_fft->setVisible(true);

            m_ui->customPlot->plotLayout()->insertRow(0);
            m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_scope);
            m_axis_scope->setVisible(true);
        }
        else
        {
            if (m_axis_scope->visible())
            {
                m_axis_scope->setVisible(false);
                m_axis_scope->layout()->take(m_axis_scope);
            }
            if (m_axis_fft->visible())
            {
                m_axis_fft->setVisible(false);
                m_axis_fft->layout()->take(m_axis_fft);
            }

            m_ui->customPlot->plotLayout()->simplify();

            m_ui->customPlot->plotLayout()->insertRow(0);
            m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_fft);
            m_axis_fft->setVisible(true);
        }
    }
    m_ui->customPlot->replot();
}

void WindowScope::on_actionFFT_8192_triggered(bool checked)
{
    if (checked)
    {
        bool en = m_fft;

        if (en)
            on_pushButton_fft_on_clicked();

        m_fft_size = 8192;

        m_ui->actionFFT_32768->setChecked(false);
        m_ui->actionFFT_131072->setChecked(false);
        m_ui->actionFFT_524288->setChecked(false);
        m_ui->actionFFT_1048576->setChecked(false);

        if (en)
            on_pushButton_fft_off_clicked();
    }
}

void WindowScope::on_actionFFT_32768_triggered(bool checked)
{
    if (checked)
    {
        bool en = m_fft;

        if (en)
            on_pushButton_fft_on_clicked();

        m_fft_size = 32768;

        m_ui->actionFFT_8192->setChecked(false);
        m_ui->actionFFT_131072->setChecked(false);
        m_ui->actionFFT_524288->setChecked(false);
        m_ui->actionFFT_1048576->setChecked(false);

        if (en)
            on_pushButton_fft_off_clicked();
    }
}

void WindowScope::on_actionFFT_131072_triggered(bool checked)
{
    if (checked)
    {
        bool en = m_fft;

        if (en)
            on_pushButton_fft_on_clicked();

        m_fft_size = 131072;

        m_ui->actionFFT_8192->setChecked(false);
        m_ui->actionFFT_32768->setChecked(false);
        m_ui->actionFFT_524288->setChecked(false);
        m_ui->actionFFT_1048576->setChecked(false);

        if (en)
            on_pushButton_fft_off_clicked();
    }
}

void WindowScope::on_actionFFT_524288_triggered(bool checked)
{
    if (checked)
    {
        bool en = m_fft;

        if (en)
            on_pushButton_fft_on_clicked();

        m_fft_size = 524288;

        m_ui->actionFFT_8192->setChecked(false);
        m_ui->actionFFT_32768->setChecked(false);
        m_ui->actionFFT_131072->setChecked(false);
        m_ui->actionFFT_1048576->setChecked(false);

        if (en)
            on_pushButton_fft_off_clicked();
    }
}

void WindowScope::on_actionFFT_1048576_triggered(bool checked)
{
    if (checked)
    {
        bool en = m_fft;

        if (en)
            on_pushButton_fft_on_clicked();

        m_fft_size = 1048576;

        m_ui->actionFFT_8192->setChecked(false);
        m_ui->actionFFT_32768->setChecked(false);
        m_ui->actionFFT_131072->setChecked(false);
        m_ui->actionFFT_524288->setChecked(false);

        if (en)
            on_pushButton_fft_off_clicked();
    }
}

/********** ETS **********/

void WindowScope::on_actionETS_Custom_triggered(bool checked)
{
    if (checked)
    {
        bool ok;
        double value = QInputDialog::getDouble(this, "EMBO - ETS (Equivalent Time Sampling - Stroboscopic)", "Signal frequency:", m_ets_freq, 0.00001, 1000000000, 6, &ok);

        if (ok)
        {
            m_ets_freq = value;
            m_ets_pwm = false;

            m_ui->actionETS_PWM_Generator->setChecked(false);

            if (m_ets)
                on_actionETS_Enabled_triggered(true);
        }
        else
        {
            m_ui->actionETS_Custom->setChecked(false);
        }
    }
}

void WindowScope::on_actionETS_PWM_Generator_triggered(bool checked)
{
    if (checked)
    {
        m_ets_pwm = true;

        m_ui->actionETS_Custom->setChecked(false);

        if (m_ets)
            on_actionETS_Enabled_triggered(true);
    }
}

void WindowScope::on_actionETS_Enabled_triggered(bool checked)
{
    m_ets = checked;
    m_last_fs = 0;
    m_rescale_needed = true;
    updatePanel();

    if (checked)
    {
        if (m_ets_pwm && !m_ets_pwm_shown)
        {
            emit showPwm();
            m_ets_pwm_shown = true;
        }

        m_status_line3->setVisible(true);
    }
    else
    {
        m_status_ets->setText("");
        m_status_line3->setVisible(false);
        m_ui->actionETS_fSEQ->setText("fSEQ: ?");
        m_ui->actionETS_coef->setText("coef:  ?");
    }

}

/********** Cursors **********/

void WindowScope::on_pushButton_cursorsHoff_clicked()
{
    m_ui->horizontalSlider_cursorH->hide();

    m_ui->pushButton_cursorsHon->show();
    m_ui->pushButton_cursorsHoff->hide();

    m_cursors->showH(false);
    m_cursorsH_en = false;
}

void WindowScope::on_pushButton_cursorsHon_clicked()
{
    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorH->show();

    m_ui->pushButton_cursorsHon->hide();
    m_ui->pushButton_cursorsHoff->show();

    auto rngH = m_axis_scope->axis(QCPAxis::atBottom)->range();
    auto rngV = m_axis_scope->axis(QCPAxis::atLeft)->range();

    m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);

    m_cursors->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors->setH_max(m_cursorH_max, rngH.lower, rngH.upper);

    m_cursors->showH(true);
    m_cursorsH_en = true;
}

void WindowScope::on_pushButton_cursorsVoff_clicked()
{
    m_ui->horizontalSlider_cursorV->hide();

    m_ui->pushButton_cursorsVon->show();
    m_ui->pushButton_cursorsVoff->hide();

    m_cursors->showV(false);
    m_cursorsV_en = false;
}

void WindowScope::on_pushButton_cursorsVon_clicked()
{
    m_ui->horizontalSlider_cursorV->setValues(m_cursorV_min, m_cursorV_max);
    m_ui->horizontalSlider_cursorV->show();

    m_ui->pushButton_cursorsVon->hide();
    m_ui->pushButton_cursorsVoff->show();

    auto rngH = m_axis_scope->axis(QCPAxis::atBottom)->range();
    auto rngV = m_axis_scope->axis(QCPAxis::atLeft)->range();

    m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);

    m_cursors->setV_min(m_cursorV_min, rngV.lower, rngV.upper);
    m_cursors->setV_max(m_cursorV_max, rngV.lower, rngV.upper);

    m_cursors->showV(true);
    m_cursorsV_en = true;
}

void WindowScope::on_cursorH_valuesChanged(int min, int max)
{
    m_cursorH_min = min;
    m_cursorH_max = max;

    auto rng = m_axis_scope->axis(QCPAxis::atBottom)->range();

    m_cursors->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors->setH_max(m_cursorH_max, rng.lower, rng.upper);
}

void WindowScope::on_cursorV_valuesChanged(int min, int max)
{
    m_cursorV_min = min;
    m_cursorV_max = max;

    auto rng = m_axis_scope->rangeZoomAxis(Qt::Vertical)->range();

    m_cursors->setV_min(m_cursorV_min, rng.lower, rng.upper);
    m_cursors->setV_max(m_cursorV_max, rng.lower, rng.upper);
}

/********** QCP **********/

void WindowScope::on_qcpMouseWheel(QWheelEvent*)
{
    m_ui->pushButton_reset->hide();
    m_ui->pushButton_resetZoom->show();

    auto rngH = m_axis_scope->rangeZoomAxis(Qt::Horizontal)->range();
    double d = rngH.upper - rngH.lower;

    if (d >= 1)
        m_timeTicker->setTimeFormat("%s s");
    else if (d >= 0.001)
        m_timeTicker->setTimeFormat("%z ms");
    else
        m_timeTicker->setTimeFormat("%u μs");

    m_ui->horizontalSlider_trigPre->setStyleSheet(CSS_SCOPE_TRIG_PRE_OFF);
    m_ui->horizontalSlider_trigVal->setStyleSheet(CSS_SCOPE_TRIG_VAL_OFF);
}

void WindowScope::on_qcpMousePress(QMouseEvent*)
{
    m_ui->pushButton_reset->hide();
    m_ui->pushButton_resetZoom->show();

    m_ui->horizontalSlider_trigPre->setStyleSheet(CSS_SCOPE_TRIG_PRE_OFF);
    m_ui->horizontalSlider_trigVal->setStyleSheet(CSS_SCOPE_TRIG_VAL_OFF);
}

/********** right pannel - main **********/

void WindowScope::on_radioButton_zoomH_clicked(bool checked)
{
    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    if (checked)
    {
        if (m_ui->radioButton_zoomV->isChecked())
        {
            m_axis_scope->setRangeDrag(Qt::Vertical | Qt::Horizontal);
            m_axis_scope->setRangeZoom(Qt::Vertical | Qt::Horizontal);
            m_axis_fft->setRangeDrag(Qt::Vertical | Qt::Horizontal);
            m_axis_fft->setRangeZoom(Qt::Vertical | Qt::Horizontal);
        }
        else
        {
            m_axis_scope->setRangeDrag(Qt::Horizontal);
            m_axis_scope->setRangeZoom(Qt::Horizontal);
            m_axis_fft->setRangeDrag(Qt::Horizontal);
            m_axis_fft->setRangeZoom(Qt::Horizontal);
        }
    }
    else
    {
        if (m_ui->radioButton_zoomV->isChecked())
        {
            m_axis_scope->setRangeDrag(Qt::Vertical);
            m_axis_scope->setRangeZoom(Qt::Vertical);
            m_axis_fft->setRangeDrag(Qt::Vertical);
            m_axis_fft->setRangeZoom(Qt::Vertical);
        }
        else
        {
            m_ui->customPlot->setInteractions(0);
        }
    }
}

void WindowScope::on_radioButton_zoomV_clicked(bool checked)
{
    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    if (checked)
    {
        if (m_ui->radioButton_zoomH->isChecked())
        {
            m_axis_scope->setRangeDrag(Qt::Vertical | Qt::Horizontal);
            m_axis_scope->setRangeZoom(Qt::Vertical | Qt::Horizontal);
            m_axis_fft->setRangeDrag(Qt::Vertical | Qt::Horizontal);
            m_axis_fft->setRangeZoom(Qt::Vertical | Qt::Horizontal);
        }
        else
        {
            m_axis_scope->setRangeDrag(Qt::Vertical);
            m_axis_scope->setRangeZoom(Qt::Vertical);
            m_axis_fft->setRangeDrag(Qt::Vertical);
            m_axis_fft->setRangeZoom(Qt::Vertical);
        }
    }
    else
    {
        if (m_ui->radioButton_zoomH->isChecked())
        {
            m_axis_scope->setRangeDrag(Qt::Horizontal);
            m_axis_scope->setRangeZoom(Qt::Horizontal);
            m_axis_fft->setRangeDrag(Qt::Horizontal);
            m_axis_fft->setRangeZoom(Qt::Horizontal);
        }
        else
        {
            m_ui->customPlot->setInteractions(0);
        }
    }
}

void WindowScope::on_pushButton_reset_clicked()
{
    m_msgPending = true;
    m_rescale_needed = true;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

    m_ui->doubleSpinBox_gain_ch1->setValue(1.0);
    m_ui->doubleSpinBox_gain_ch2->setValue(1.0);
    m_ui->doubleSpinBox_gain_ch3->setValue(1.0);
    m_ui->doubleSpinBox_gain_ch4->setValue(1.0);

    m_ui->dial_Vpos_ch1->setValue(0);
    m_ui->dial_Vpos_ch2->setValue(0);
    m_ui->dial_Vpos_ch3->setValue(0);
    m_ui->dial_Vpos_ch4->setValue(0);

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
    */

    Settings::setValue(CFG_REC_DIR, m_rec.getDir());

    on_actionExportCSV_triggered(true);
    m_ui->actionExportCSV->setChecked(true);

    on_pushButton_resetZoom_clicked();
    on_pushButton_average_on_clicked();

    Core::getInstance()->sendRst(SCOPE);

    showEvent(NULL);
}

void WindowScope::on_pushButton_resetZoom_clicked()
{
    rescaleYAxis();
    rescaleXAxis();

    m_ui->pushButton_reset->show();
    m_ui->pushButton_resetZoom->hide();

    if (m_t.isEmpty())
        return;

    double x = m_t[m_t.size()-1];

    if (x >= 2)
        m_timeTicker->setTimeFormat("%s s");
    else if (x >= 0.002)
        m_timeTicker->setTimeFormat("%z ms");
    else
        m_timeTicker->setTimeFormat("%u μs");

    m_ui->horizontalSlider_trigPre->setStyleSheet(CSS_SCOPE_TRIG_PRE);

    if (!m_fft)
        m_ui->horizontalSlider_trigVal->setStyleSheet(CSS_SCOPE_TRIG_VAL);

    m_ui->customPlot->replot();
}

void WindowScope::on_pushButton_single_off_clicked()
{
    m_ui->radioButton_trigMode_Auto->setEnabled(false);
    m_ui->radioButton_trigMode_Normal->setEnabled(false);
    m_ui->radioButton_trigMode_Disabled->setEnabled(false);

    m_ui->pushButton_single_on->show();
    m_ui->pushButton_single_off->hide();

    m_ui->pushButton_run->hide();
    m_ui->pushButton_stop->hide();
    m_ui->pushButton_run_off->show();

    m_single = true;
    m_instrEnabled = true;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

    sendSet();
}

void WindowScope::on_pushButton_single_on_clicked()
{
    m_single = true;
    m_instrEnabled = true;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

    sendSet();
}

void WindowScope::on_pushButton_run_off_clicked()
{
    m_ui->radioButton_trigMode_Auto->setEnabled(true);
    m_ui->radioButton_trigMode_Normal->setEnabled(true);
    m_ui->radioButton_trigMode_Disabled->setEnabled(true);

    m_ui->pushButton_single_off->show();
    m_ui->pushButton_single_on->hide();

    m_ui->pushButton_run->show();
    m_ui->pushButton_stop->hide();
    m_ui->pushButton_run_off->hide();

    m_single = false;
    m_instrEnabled = true;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

    sendSet();
}

void WindowScope::on_pushButton_run_clicked()
{
    m_ui->pushButton_run->hide();
    m_ui->pushButton_stop->show();
    m_ui->pushButton_run_off->hide();

    m_instrEnabled = false;

    m_ui->radioButton_trigLed->setChecked(false);

    m_ui->groupBox_trigger->setEnabled(false);
    m_ui->groupBox_horizontal->setEnabled(false);
    m_ui->groupBox_vertical->setEnabled(false);
}

void WindowScope::on_pushButton_stop_clicked()
{
    m_ui->pushButton_run->show();
    m_ui->pushButton_stop->hide();
    m_ui->pushButton_run_off->hide();

    m_instrEnabled = true;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

    sendSet();
}

/********** right pannel - trigger **********/

void WindowScope::on_radioButton_trigMode_Auto_clicked(bool checked)
{
    if (checked)
    {
        m_ui->pushButton_single_off->show();
        m_ui->pushButton_single_on->hide();
        m_single = false;

        sendSet();
    }
}

void WindowScope::on_radioButton_trigMode_Normal_clicked(bool checked)
{
    if (checked)
    {
        m_ui->pushButton_single_off->show();
        m_ui->pushButton_single_on->hide();
        m_single = false;

        sendSet();
    }
}

void WindowScope::on_radioButton_trigMode_Disabled_clicked(bool checked)
{
    if (checked)
    {
        m_ui->pushButton_single_off->show();
        m_ui->pushButton_single_on->hide();
        m_single = false;

        m_ui->radioButton_trigCh_1->setEnabled(false);
        m_ui->radioButton_trigCh_2->setEnabled(false);
        m_ui->radioButton_trigCh_3->setEnabled(false);
        m_ui->radioButton_trigCh_4->setEnabled(false);

        m_ui->radioButton_trigSlope_Rising->setEnabled(false);
        m_ui->radioButton_trigSlope_Falling->setEnabled(false);

        m_ui->groupBox_t_19->setEnabled(false);

        sendSet();
    }
}

void WindowScope::on_radioButton_trigSlope_Rising_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowScope::on_radioButton_trigSlope_Falling_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowScope::on_radioButton_trigCh_1_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowScope::on_radioButton_trigCh_2_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowScope::on_radioButton_trigCh_3_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowScope::on_radioButton_trigCh_4_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowScope::on_spinBox_trigVal_valueChanged(int arg1)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_trigVal->setValue(arg1);

    if (!m_t.isEmpty())
        m_cursorTrigVal->setValue(arg1, 0, m_ref_v * 1, 0, m_t[m_t.size()-1]);

    m_cursorTrigVal->show(true);
    m_cursorTrigPre->show(true);
    m_timer_trigSliders->start(TRIG_VAL_PRE_TIMEOUT);

    double yLim = (m_spline ? Y_LIM1 : Y_LIM2);
    double p = yLim / (m_ref_v + (2.0 * yLim));
    m_ui->horizontalSlider_trigVal->setValue(((arg1 * (1.0 - (2.0 * p))) + (p * 100.0)) * 10.0);

     m_ignoreValuesChanged = false;

    sendSet();
}

void WindowScope::on_dial_trigVal_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_trigVal->setValue(value);

    if (!m_t.isEmpty())
        m_cursorTrigVal->setValue(value, 0, m_ref_v * 1, 0, m_t[m_t.size()-1]);

    m_cursorTrigVal->show(true);
    m_cursorTrigPre->show(true);
    m_timer_trigSliders->start(TRIG_VAL_PRE_TIMEOUT);

    double yLim = (m_spline ? Y_LIM1 : Y_LIM2);
    double p = yLim / (m_ref_v + (2.0 * yLim));
    m_ui->horizontalSlider_trigVal->setValue(((value * (1.0 - (2.0 * p))) + (p * 100.0)) * 10.0);

    m_ignoreValuesChanged = false;

    //if (!m_trigDialPressed)
    //    sendSet();
}

void WindowScope::on_spinBox_trigPre_valueChanged(int arg1)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_trigPre->setValue(arg1);

    if (!m_t.isEmpty())
        m_cursorTrigPre->setValue(arg1, 0, m_ref_v * 1, 0, m_t[m_t.size()-1]);

    m_cursorTrigVal->show(true);
    m_cursorTrigPre->show(true);
    m_timer_trigSliders->start(TRIG_VAL_PRE_TIMEOUT);

    m_ui->horizontalSlider_trigPre->setValue(arg1 * 10.0);

    m_ignoreValuesChanged = false;

    sendSet();
}

void WindowScope::on_dial_trigPre_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_trigPre->setValue(value);

    if (!m_t.isEmpty())
        m_cursorTrigPre->setValue(value, 0, m_ref_v * 1, 0, m_t[m_t.size()-1]);

    m_cursorTrigVal->show(true);
    m_cursorTrigPre->show(true);
    m_timer_trigSliders->start(TRIG_VAL_PRE_TIMEOUT);

    m_ui->horizontalSlider_trigPre->setValue(value * 10.0);

    m_ignoreValuesChanged = false;

    //if (!m_trigDialPressed)
    //    sendSet();
}

void WindowScope::on_pushButton_trigForc_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
    m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();

    m_ui->radioButton_trigLed->setChecked(false);
    enablePanel(false);

    Core::getInstance()->msgAdd(m_msg_forceTrig, false, "");
}

void WindowScope::on_hideTrigSliders()
{
    m_cursorTrigVal->show(false);
    m_cursorTrigPre->show(false);
}

void WindowScope::on_dial_trigVal_sliderPressed()
{
    m_cursorTrigVal->show(true);
    m_cursorTrigPre->show(true);

    m_timer_trigSliders->start(TRIG_VAL_PRE_TIMEOUT);
    m_trigDialPressed = true;
}

void WindowScope::on_dial_trigPre_sliderPressed()
{
    m_cursorTrigVal->show(true);
    m_cursorTrigPre->show(true);

    m_timer_trigSliders->start(TRIG_VAL_PRE_TIMEOUT);
    m_trigDialPressed = true;
}

void WindowScope::on_dial_trigVal_sliderReleased()
{
    m_trigDialPressed = false;

    if (m_daqSet.trig_val != m_ui->dial_trigVal->value())
        sendSet();
}

void WindowScope::on_dial_trigPre_sliderReleased()
{
    m_trigDialPressed = false;

    if (m_daqSet.trig_pre != m_ui->dial_trigPre->value())
        sendSet();
}

/********** right pannel - horizontal **********/

void WindowScope::on_radioButton_fsMem_clicked(bool checked)
{
    if (checked)
    {
        m_ui->groupBox_h_fsMem->setEnabled(true);
        m_ui->groupBox_h_div->setEnabled(false);

        m_ui->spinBox_mem->setStyleSheet(CSS_SPINBOX_NODIS);
        m_ui->spinBox_fs->setStyleSheet(CSS_SPINBOX_NODIS);
        m_ui->doubleSpinBox_div->setStyleSheet(CSS_DSPINBOX);
    }
}

void WindowScope::on_radioButton_div_clicked(bool checked)
{
    if (checked)
    {
        m_ui->groupBox_h_fsMem->setEnabled(false);
        m_ui->groupBox_h_div->setEnabled(true);

        m_ui->spinBox_mem->setStyleSheet(CSS_SPINBOX);
        m_ui->spinBox_fs->setStyleSheet(CSS_SPINBOX);
        m_ui->doubleSpinBox_div->setStyleSheet(CSS_DSPINBOX_NODIS);
    }
}

void WindowScope::on_spinBox_mem_valueChanged(int arg1)
{
    if (arg1 > m_daqSet.fs)
    {
        m_ui->spinBox_mem->setValue(m_daqSet.fs);
        return;
    }

    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_mem->setValue(arg1);
    m_ignoreValuesChanged = false;

    m_rescale_needed = true;

    sendSet();
}

void WindowScope::on_dial_mem_valueChanged(int value)
{
    if (value > m_daqSet.fs)
    {
        m_ui->dial_mem->setValue(m_daqSet.fs);
        return;
    }

    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_mem->setValue(value);
    m_ignoreValuesChanged = false;

    m_rescale_needed = true;

    sendSet();
}

void WindowScope::on_spinBox_fs_valueChanged(int arg1)
{
    if (arg1 < m_daqSet.mem)
    {
        m_ui->spinBox_fs->setValue(m_daqSet.mem);
        return;
    }

    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_fs->setValue(arg1);
    m_ignoreValuesChanged = false;

    m_rescale_needed = true;

    sendSet();
}

void WindowScope::on_dial_fs_valueChanged(int value)
{
    if (value < m_daqSet.mem)
    {
        m_ui->dial_fs->setValue(m_daqSet.mem);
        return;
    }

    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_fs->setValue(value);
    m_ignoreValuesChanged = false;

    m_rescale_needed = true;

    sendSet();
}

void WindowScope::on_spinBox_div_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;
}

void WindowScope::on_dial_div_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    int fs_last = m_ui->spinBox_fs->value();
    int mem_last = m_ui->spinBox_mem->value();

    double sec = lin_to_exp_1to1M(value, false) / 1000000.0;
    double fs_max = m_ui->spinBox_fs->maximum();
    double fs_min = m_ui->spinBox_fs->minimum();
    double mem_max = m_ui->spinBox_mem->maximum();

    int fs = mem_max / sec;
    int mem = mem_max;

    if (fs >= fs_max)
    {
        double ratio = 1.0 - ((fs - fs_max) / fs);

        fs = fs_max;
        mem = mem_max * ratio;
    }
    else if (fs < fs_min)
        fs = fs_min;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_fs->setValue(fs);
    m_ui->dial_fs->setValue(fs);
    m_ui->spinBox_mem->setValue(mem);
    m_ui->dial_mem->setValue(mem);
    m_ignoreValuesChanged = false;

    if (fs_last != fs || mem_last != mem)
    {
        m_rescale_needed = true;
        sendSet();
    }
}

/********** right pannel - vertical **********/

void WindowScope::on_pushButton_disable1_clicked()
{
    if ((m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en) == 1)
        return;

    m_ui->pushButton_enable1->show();
    m_ui->pushButton_disable1->hide();

    m_rescale_needed = true;

    fix2ADCproblem(false);

    if (m_ui->pushButton_enable1->isVisible())
        m_ui->customPlot->graph(GRAPH_CH1)->setVisible(false);

    sendSet();
}

void WindowScope::on_pushButton_disable2_clicked()
{
    if ((m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en) == 1)
        return;

    m_ui->pushButton_enable2->show();
    m_ui->pushButton_disable2->hide();

    m_rescale_needed = true;

    fix2ADCproblem(false);

    if (m_ui->pushButton_enable2->isVisible())
        m_ui->customPlot->graph(GRAPH_CH2)->setVisible(false);

    sendSet();
}

void WindowScope::on_pushButton_disable3_clicked()
{
    auto info = Core::getInstance()->getDevInfo();
    if (info->daq_ch == 4)
    {
        if ((m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en) == 1)
            return;

        m_ui->pushButton_enable3->show();
        m_ui->pushButton_disable3->hide();

        fix2ADCproblem(false);

        m_rescale_needed = true;

        if (m_ui->pushButton_enable3->isVisible())
            m_ui->customPlot->graph(GRAPH_CH3)->setVisible(false);

        sendSet();
    }
}

void WindowScope::on_pushButton_disable4_clicked()
{
    auto info = Core::getInstance()->getDevInfo();
    if (info->daq_ch == 4)
    {
        if ((m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en) == 1)
            return;

        m_ui->pushButton_enable4->show();
        m_ui->pushButton_disable4->hide();

        fix2ADCproblem(false);

        m_rescale_needed = true;

        if (m_ui->pushButton_enable4->isVisible())
            m_ui->customPlot->graph(GRAPH_CH4)->setVisible(false);

        sendSet();
    }
}

void WindowScope::on_pushButton_enable1_clicked()
{
    m_ui->pushButton_enable1->hide();
    m_ui->pushButton_disable1->show();

    fix2ADCproblem(true);

    m_rescale_needed = true;

    sendSet();
}

void WindowScope::on_pushButton_enable2_clicked()
{
    m_ui->pushButton_enable2->hide();
    m_ui->pushButton_disable2->show();

    fix2ADCproblem(true);

    m_rescale_needed = true;

    sendSet();
}

void WindowScope::on_pushButton_enable3_clicked()
{
    auto info = Core::getInstance()->getDevInfo();
    if (info->daq_ch == 4)
    {
        m_ui->pushButton_enable3->hide();
        m_ui->pushButton_disable3->show();

        fix2ADCproblem(true);

        m_rescale_needed = true;

        sendSet();
    }
}

void WindowScope::on_pushButton_enable4_clicked()
{
    auto info = Core::getInstance()->getDevInfo();
    if (info->daq_ch == 4)
    {
        m_ui->pushButton_enable4->hide();
        m_ui->pushButton_disable4->show();

        fix2ADCproblem(true);

        m_rescale_needed = true;

        sendSet();
    }
}

void WindowScope::on_doubleSpinBox_gain_ch1_valueChanged(double arg1)
{
    m_gain1 = arg1;
    m_ui->dial_Vpos_ch1->setRange(-m_ref_v * m_gain1 * 1000.0, m_ref_v * m_gain1 * 1000.0);

    rescaleYAxis();
    on_pushButton_resetZoom_clicked();
}

void WindowScope::on_doubleSpinBox_gain_ch2_valueChanged(double arg1)
{
    m_gain2 = arg1;
    m_ui->dial_Vpos_ch2->setRange(-m_ref_v * m_gain2 * 1000.0, m_ref_v * m_gain2 * 1000.0);

    rescaleYAxis();
    on_pushButton_resetZoom_clicked();
}

void WindowScope::on_doubleSpinBox_gain_ch3_valueChanged(double arg1)
{
    m_gain3 = arg1;
    m_ui->dial_Vpos_ch3->setRange(-m_ref_v * m_gain3 * 1000.0, m_ref_v * m_gain3 * 1000.0);

    rescaleYAxis();
    on_pushButton_resetZoom_clicked();
}

void WindowScope::on_doubleSpinBox_gain_ch4_valueChanged(double arg1)
{
    m_gain4 = arg1;
    m_ui->dial_Vpos_ch4->setRange(-m_ref_v * m_gain4 * 1000.0, m_ref_v * m_gain4 * 1000.0);

    rescaleYAxis();
    on_pushButton_resetZoom_clicked();
}

void WindowScope::on_dial_Vpos_ch1_valueChanged(int value)
{
    m_offset1 = value / 1000.0;

    rescaleYAxis();
    on_pushButton_resetZoom_clicked();

    if (m_ignoreValuesChanged)
        return;

    m_ui->label_Vpos1->setText(QString::number(m_offset1, 10, 1));
    m_ui->label_Vpos1->setVisible(true);
}

void WindowScope::on_dial_Vpos_ch2_valueChanged(int value)
{
    m_offset2 = value / 1000.0;

    rescaleYAxis();
    on_pushButton_resetZoom_clicked();

    if (m_ignoreValuesChanged)
        return;

    m_ui->label_Vpos2->setText(QString::number(m_offset2, 10, 1));
    m_ui->label_Vpos2->setVisible(true);
}

void WindowScope::on_dial_Vpos_ch3_valueChanged(int value)
{
    m_offset3 = value / 1000.0;

    rescaleYAxis();
    on_pushButton_resetZoom_clicked();

    if (m_ignoreValuesChanged)
        return;

    m_ui->label_Vpos3->setText(QString::number(m_offset3, 10, 1));
    m_ui->label_Vpos3->setVisible(true);
}

void WindowScope::on_dial_Vpos_ch4_valueChanged(int value)
{
    m_offset4 = value / 1000.0;

    rescaleYAxis();
    on_pushButton_resetZoom_clicked();

    if (m_ignoreValuesChanged)
        return;

    m_ui->label_Vpos4->setText(QString::number(m_offset4, 10, 1));
    m_ui->label_Vpos4->setVisible(true);
}

/********** right pannel - utils **********/

void WindowScope::on_pushButton_average_off_clicked()
{
    m_ui->pushButton_average_on->show();
    m_ui->pushButton_average_off->hide();

    for (int i = 0 ; i < MAX_SCOPE_AVG ; i++)
    {
        if (m_daqSet.ch1_en) m_average_buff_ch1[i].resize(m_daqSet.mem);
        if (m_daqSet.ch2_en) m_average_buff_ch2[i].resize(m_daqSet.mem);
        if (m_daqSet.ch3_en) m_average_buff_ch3[i].resize(m_daqSet.mem);
        if (m_daqSet.ch4_en) m_average_buff_ch4[i].resize(m_daqSet.mem);
    }

    m_average_cnt = 0;
    m_average_it = 0;
    m_average_num = m_ui->spinBox_average->value();

    m_ui->spinBox_average->setEnabled(false);
    m_ui->spinBox_average->setStyleSheet(CSS_SPINBOX);

    m_average = true;
}

void WindowScope::on_pushButton_average_on_clicked()
{
    m_average = false;

    m_ui->pushButton_average_off->show();
    m_ui->pushButton_average_on->hide();

    for (int i = 0 ; i < MAX_SCOPE_AVG ; i++)
    {
        m_average_buff_ch1[i].clear();
        m_average_buff_ch2[i].clear();
        m_average_buff_ch3[i].clear();
        m_average_buff_ch4[i].clear();
    }

    m_ui->spinBox_average->setEnabled(true);
    m_ui->spinBox_average->setStyleSheet(CSS_SPINBOX_NODIS);
}

void WindowScope::on_spinBox_average_valueChanged(int)
{
}

void WindowScope::on_pushButton_bit8_off_clicked()
{
    m_ui->pushButton_bit12_on->hide();
    m_ui->pushButton_bit12_off->show();
    m_ui->pushButton_bit8_off->hide();
    m_ui->pushButton_bit8_on->show();

    m_rescale_needed = true;

    sendSet();
}

void WindowScope::on_pushButton_bit8_on_clicked()
{
}

void WindowScope::on_pushButton_bit12_off_clicked()
{
    if (m_ui->pushButton_bit8_on->isEnabled())
    {
        m_ui->pushButton_bit12_off->hide();
        m_ui->pushButton_bit12_on->show();
        m_ui->pushButton_bit8_on->hide();
        m_ui->pushButton_bit8_off->show();

        m_rescale_needed = true;

        sendSet();
    }
}

void WindowScope::on_pushButton_bit12_on_clicked()
{
}

void WindowScope::on_pushButton_fft_off_clicked()
{
    m_ui->pushButton_fft_on->show();
    m_ui->pushButton_fft_off->hide();

    m_axis_scope->setMinimumMargins(QMargins(45,15,15,0));

    if (m_fft_split)
        m_axis_fft->setMinimumMargins(QMargins(45,0,15,30));
    else
        m_axis_fft->setMinimumMargins(QMargins(45,15,15,30));

    m_ui->horizontalSlider_trigVal->setStyleSheet(CSS_SCOPE_TRIG_VAL_OFF);

    m_ui->pushButton_cursorsVon->setEnabled(false);
    on_pushButton_cursorsVoff_clicked();

    if (m_axis_scope->visible())
    {
        m_axis_scope->setVisible(false);
        m_axis_scope->layout()->take(m_axis_scope);
    }
    if (m_axis_fft->visible())
    {
        m_axis_fft->setVisible(false);
        m_axis_fft->layout()->take(m_axis_fft);
    }

    m_ui->customPlot->plotLayout()->simplify();

    m_ui->customPlot->plotLayout()->insertRow(0);
    m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_fft);
    m_axis_fft->setVisible(true);

    m_ui->label_FFT->setVisible(true);

    if (m_fft_split)
    {
        m_ui->customPlot->plotLayout()->insertRow(0);
        m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_scope);
        m_axis_scope->setVisible(true);
    }

    /*
    m_ui->radioButton_zoomH->setChecked(true);
    m_ui->radioButton_zoomV->setChecked(true);
    on_radioButton_zoomH_clicked(true);
    on_radioButton_zoomV_clicked(true);
    */

    m_ui->customPlot->replot();

    m_axis_fft->axis(QCPAxis::atLeft)->setRange(FFT_DB_MIN, FFT_DB_MAX);
    //m_axis_fft->axis(QCPAxis::atLeft)->rescale();
    m_axis_fft->axis(QCPAxis::atBottom)->setRange(0, m_daqSet.fs_real_n / 2);

    m_rescale_fft_needed = true;
    m_fft = true;
    m_last_fs = 0;

    createX();

    m_ui->horizontalSlider_cursorH->setStyleSheet(CSS_CURSOR_H2);
}

void WindowScope::on_pushButton_fft_on_clicked()
{
    m_fft = false;

    m_ui->pushButton_fft_off->show();
    m_ui->pushButton_fft_on->hide();

    m_axis_scope->setMinimumMargins(QMargins(45,15,15,30));

    m_ui->horizontalSlider_trigVal->setStyleSheet(CSS_SCOPE_TRIG_VAL);

    m_ui->pushButton_cursorsVon->setEnabled(true);

    if (m_axis_scope->visible())
    {
        m_axis_scope->setVisible(false);
        m_axis_scope->layout()->take(m_axis_scope);
    }
    if (m_axis_fft->visible())
    {
        m_axis_fft->setVisible(false);
        m_axis_fft->layout()->take(m_axis_fft);
    }

    m_ui->customPlot->plotLayout()->simplify();

    m_ui->customPlot->plotLayout()->insertRow(0);
    m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_scope);
    m_axis_scope->setVisible(true);

    m_ui->label_FFT->setVisible(false);

    /*
    m_ui->radioButton_zoomH->setChecked(true);
    m_ui->radioButton_zoomV->setChecked(false);
    on_radioButton_zoomH_clicked(true);
    on_radioButton_zoomV_clicked(false);
    */

    m_ui->customPlot->replot();

    if (m_fft_in != NULL)
        fftw_free(m_fft_in);
    if (m_fft_out != NULL)
        fftw_free(m_fft_out);
    if (m_fft_plan != NULL)
        fftw_destroy_plan(m_fft_plan);

    fftw_cleanup();

    m_fft_in = NULL;
    m_fft_out = NULL;
    m_fft_plan = NULL;

    //m_ui->horizontalSlider_cursorH->setStyleSheet(CSS_CURSOR_H);
}

/******************************** private ********************************/

void WindowScope::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();
    m_instrEnabled = false;

    on_pushButton_average_on_clicked();

    Core::getInstance()->setMode(NO_MODE);
    emit closing(WindowScope::staticMetaObject.className());

     m_timer_plot->stop();
}

void WindowScope::showEvent(QShowEvent*)
{
    m_ignoreValuesChanged = true;

    m_seq_num = 0;

    enablePanel(false);

    Core::getInstance()->setMode(SCOPE);
    if (m_ui->pushButton_run->isVisible())
        m_instrEnabled = true;

    auto info = Core::getInstance()->getDevInfo();

    m_err_cntr = 0;
    m_ref_v = info->ref_mv / 1000.0;
    m_status_vcc->setText(" Vcc: " + QString::number(info->ref_mv) + " mV");

    QStringList pins = info->pins_scope_vm.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (pins.size() == 4)
    {
        m_pin1 = pins[0].trimmed();
        m_pin2 = pins[1].trimmed();
        m_pin3 = pins[2].trimmed();
        m_pin4 = pins[3].trimmed();

        //m_ui->label_pins->setText("Vertical (" + m_pin1 + ", " + m_pin2 + ", " + m_pin3 + ", " + m_pin4 + ")");
    }

    Core::getInstance()->msgAdd(m_msg_set, true, "");

    if (m_instrEnabled)
    {
        m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
        m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
        m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
        m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();
        m_ui->customPlot->graph(GRAPH_FFT)->data()->clear();
    }

    on_actionMeasReset_triggered();
    on_pushButton_resetZoom_clicked();

    m_ui->radioButton_trigLed->setChecked(false);

    m_ui->pushButton_bit8_on->setEnabled(info->adc_bit8);
    m_ui->pushButton_bit8_off->setEnabled(info->adc_bit8);
    m_ui->pushButton_bit12_off->hide();
    m_ui->pushButton_bit12_on->show();

    m_ui->dial_mem->setRange(2, info->mem);
    m_ui->spinBox_mem->setRange(2, info->mem);

    m_ui->dial_fs->setRange(1, info->adc_fs_12b); // TODO
    m_ui->spinBox_fs->setRange(1, info->adc_fs_12b); // TODO

    m_ui->dial_div->setRange(((1.0 / info->adc_fs_12b) * 2.0 * 1000000.0), 1000000);

    m_timer_plot->start((int)TIMER_SCOPE_PLOT);

    m_ui->dial_Vpos_ch1->setRange(-m_ref_v * m_gain1 * 1000.0, m_ref_v * m_gain1 * 1000.0);
    m_ui->dial_Vpos_ch2->setRange(-m_ref_v * m_gain2 * 1000.0, m_ref_v * m_gain2 * 1000.0);
    m_ui->dial_Vpos_ch3->setRange(-m_ref_v * m_gain3 * 1000.0, m_ref_v * m_gain3 * 1000.0);
    m_ui->dial_Vpos_ch4->setRange(-m_ref_v * m_gain4 * 1000.0, m_ref_v * m_gain4 * 1000.0);

    m_ignoreValuesChanged = false;

    m_ui->pushButton_average_off->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_AVG);
    m_ui->pushButton_average_on->setStyleSheet(CSS_BUTTON_OFF_NODIS CSS_BUTTON_AVG);
    if (info->adc_bit8)
    {
        m_ui->pushButton_bit8_off->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_BIT);
        m_ui->pushButton_bit8_on->setStyleSheet(CSS_BUTTON_OFF_NODIS CSS_BUTTON_BIT);
    }
    else
    {
        m_ui->pushButton_bit8_off->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_BIT);
        m_ui->pushButton_bit8_on->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_BIT);
    }
    m_ui->pushButton_bit12_off->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_BIT);
    m_ui->pushButton_bit12_on->setStyleSheet(CSS_BUTTON_OFF_NODIS CSS_BUTTON_BIT);
    m_ui->pushButton_fft_off->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_FFT);
    m_ui->pushButton_fft_on->setStyleSheet(CSS_BUTTON_OFF_NODIS CSS_BUTTON_FFT);
    m_ui->spinBox_average->setStyleSheet(m_ui->pushButton_average_on->isVisible() ? CSS_SPINBOX : CSS_SPINBOX_NODIS);

    m_ui->pushButton_disable1->setStyleSheet(CSS_BUTTON_CH1_NODIS CSS_BUTTON_CH);
    m_ui->pushButton_disable2->setStyleSheet(CSS_BUTTON_CH2_NODIS CSS_BUTTON_CH);
    m_ui->pushButton_enable1->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_CH);
    m_ui->pushButton_enable2->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_CH);
    m_ui->doubleSpinBox_gain_ch1->setStyleSheet(CSS_DSPINBOX_NODIS);
    m_ui->doubleSpinBox_gain_ch2->setStyleSheet(CSS_DSPINBOX_NODIS);
    if (info->daq_ch == 4)
    {
        m_ui->pushButton_enable3->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_CH);
        m_ui->pushButton_enable4->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_CH);
        m_ui->pushButton_disable3->setStyleSheet(CSS_BUTTON_CH3_NODIS CSS_BUTTON_CH);
        m_ui->pushButton_disable4->setStyleSheet(CSS_BUTTON_CH4_NODIS CSS_BUTTON_CH);
        m_ui->doubleSpinBox_gain_ch3->setStyleSheet(CSS_DSPINBOX_NODIS);
        m_ui->doubleSpinBox_gain_ch4->setStyleSheet(CSS_DSPINBOX_NODIS);

        m_ui->groupBox_v_5->show();
        m_ui->groupBox_v_6->show();

        m_ui->pushButton_enable3->show();
        m_ui->pushButton_enable4->show();
        m_ui->pushButton_disable3->show();
        m_ui->pushButton_disable4->show();
        m_ui->doubleSpinBox_gain_ch3->show();
        m_ui->doubleSpinBox_gain_ch4->show();

        m_ui->dial_Vpos_ch3->show();
        m_ui->dial_Vpos_ch4->show();
        m_ui->label_dial3->show();
        m_ui->label_dial4->show();

        m_ui->radioButton_trigCh_3->show();
        m_ui->radioButton_trigCh_4->show();
    }
    else
    {
        m_ui->groupBox_v_5->hide();
        m_ui->groupBox_v_6->hide();

        m_ui->pushButton_enable3->hide();
        m_ui->pushButton_enable4->hide();
        m_ui->pushButton_disable3->hide();
        m_ui->pushButton_disable4->hide();
        m_ui->doubleSpinBox_gain_ch3->hide();
        m_ui->doubleSpinBox_gain_ch4->hide();

        m_ui->dial_Vpos_ch3->hide();
        m_ui->dial_Vpos_ch4->hide();
        m_ui->label_dial3->hide();
        m_ui->label_dial4->hide();

        m_ui->radioButton_trigCh_3->hide();
        m_ui->radioButton_trigCh_4->hide();
    }

    m_ui->actionMeasChannel_3->setEnabled(info->daq_ch == 4);
    m_ui->actionMeasChannel_4->setEnabled(info->daq_ch == 4);

    m_ui->actionFFTChannel_3->setEnabled(info->daq_ch == 4);
    m_ui->actionFFTChannel_4->setEnabled(info->daq_ch == 4);

    m_ui->actionMath_3_4->setEnabled(info->daq_ch == 4);
    m_ui->actionMath_XY_X_3_Y_4->setEnabled(info->daq_ch == 4);

    bool fsMem = m_ui->radioButton_fsMem->isChecked();

    m_ui->spinBox_mem->setStyleSheet(fsMem ? CSS_SPINBOX_NODIS : CSS_SPINBOX);
    m_ui->spinBox_fs->setStyleSheet(fsMem ? CSS_SPINBOX_NODIS : CSS_SPINBOX);
    m_ui->doubleSpinBox_div->setStyleSheet(fsMem ? CSS_DSPINBOX : CSS_DSPINBOX_NODIS);
    m_ui->radioButton_fsMem->setStyleSheet(CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_div->setStyleSheet(CSS_RADIOBUTTON_NODIS);

    m_ui->radioButton_trigMode_Auto->setStyleSheet(m_single ? CSS_RADIOBUTTON : CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_trigMode_Normal->setStyleSheet(m_single ? CSS_RADIOBUTTON : CSS_RADIOBUTTON_NODIS);
    m_ui->radioButton_trigMode_Disabled->setStyleSheet(m_single ? CSS_RADIOBUTTON : CSS_RADIOBUTTON_NODIS);

    bool trigEnabled = !(m_daqSet.trig_mode == DaqTrigMode::DISABLED);

    m_ui->radioButton_trigSlope_Rising->setStyleSheet(trigEnabled ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    m_ui->radioButton_trigSlope_Falling->setStyleSheet(trigEnabled ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);

    m_ui->spinBox_trigVal->setStyleSheet(trigEnabled ? CSS_SPINBOX_NODIS : CSS_SPINBOX);
    m_ui->spinBox_trigPre->setStyleSheet(trigEnabled ? CSS_SPINBOX_NODIS : CSS_SPINBOX);

    bool forc = (m_daqSet.trig_mode != DaqTrigMode::DISABLED && m_daqSet.trig_mode != DaqTrigMode::AUTO);
    m_ui->pushButton_trigForc->setStyleSheet(forc ? (CSS_BUTTON_ON_NODIS CSS_BUTTON_FORC) : (CSS_BUTTON_ON CSS_BUTTON_FORC));

    m_ui->radioButton_trigCh_1->setStyleSheet(m_ui->radioButton_trigCh_1->isEnabled() ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    m_ui->radioButton_trigCh_2->setStyleSheet(m_ui->radioButton_trigCh_2->isEnabled() ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    m_ui->radioButton_trigCh_3->setStyleSheet(m_ui->radioButton_trigCh_3->isEnabled() ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    m_ui->radioButton_trigCh_4->setStyleSheet(m_ui->radioButton_trigCh_4->isEnabled() ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);

    m_refresh = true;
}

void WindowScope::rescaleYAxis()
{
    double max_scale = 0;
    double min_scale = 0;
    if (m_daqSet.ch1_en && m_gain1 > max_scale) max_scale = m_gain1;
    else if (m_daqSet.ch1_en && m_gain1 < min_scale) min_scale = m_gain1;
    if (m_daqSet.ch2_en && m_gain2 > max_scale) max_scale = m_gain2;
    else if (m_daqSet.ch2_en && m_gain2 < min_scale) min_scale = m_gain2;
    if (m_daqSet.ch3_en && m_gain3 > max_scale) max_scale = m_gain3;
    else if (m_daqSet.ch3_en && m_gain3 < min_scale) min_scale = m_gain3;
    if (m_daqSet.ch4_en && m_gain4 > max_scale) max_scale = m_gain4;
    else if (m_daqSet.ch4_en && m_gain4 < min_scale) min_scale = m_gain4;

    double yLim = (m_spline ? Y_LIM1 : Y_LIM2);
    m_axis_scope->axis(QCPAxis::atLeft)->setRange((min_scale * m_ref_v) - yLim , (max_scale * m_ref_v) + yLim);

    //if (m_fft)
    //    m_axis_fft->axis(QCPAxis::atLeft)->rescale();
    if (m_fft)
        m_axis_fft->axis(QCPAxis::atLeft)->setRange(FFT_DB_MIN, FFT_DB_MAX);

    auto rngV = m_axis_scope->axis(QCPAxis::atLeft)->range();
    auto rngH = m_axis_scope->axis(QCPAxis::atBottom)->range();

    m_cursorTrigVal->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursorTrigPre->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
}

void WindowScope::rescaleXAxis()
{
    if (m_t.isEmpty())
        return;

    if (m_math_xy_12 || m_math_xy_34)
        m_axis_scope->axis(QCPAxis::atBottom)->setRange(0, m_axis_scope->axis(QCPAxis::atLeft)->range().upper);
    else
        m_axis_scope->axis(QCPAxis::atBottom)->setRange(0, m_t[m_t.size()-1]);

    if (m_fft)
        m_axis_fft->axis(QCPAxis::atBottom)->setRange(0, m_daqSet.fs_real_n / 2);

    auto rngV = m_axis_scope->axis(QCPAxis::atLeft)->range();
    auto rngH = m_axis_scope->axis(QCPAxis::atBottom)->range();

    m_cursorTrigVal->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursorTrigPre->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
}

void WindowScope::createX()
{
    if (m_last_fs != m_daqSet.fs || m_last_mem != m_daqSet.mem)
    {
        double x = 0;
        double dt = 1.0 / m_daqSet.fs_real_n;
        m_t.resize(m_daqSet.mem);

        for (int i = 0; i < m_daqSet.mem; i++)
        {
            m_t[i] = x;
            x += dt;
        }

        /* FFT */

        if (m_fft)
        {
            /*
            m_fft_size = 2;
            while (m_fft_size < m_daqSet.fs_real_n)
            {
                m_fft_size *= 2;

                if (m_fft_size >= FFT_MAX_SIZE)
                {
                    m_fft_size = FFT_MAX_SIZE;
                    break;
                }
            }
            */
            //m_fft_size = FFT_MAX_SIZE;

            double fft_x = 0;
            double fft_dt = m_daqSet.fs_real_n / (double)m_fft_size;
            double fft_dt_real = m_daqSet.fs_real_n / (double)m_daqSet.mem;

            m_fft_x.resize(m_fft_size / 2);

            for (int i = 0; i < m_fft_size / 2; i++)
            {
                m_fft_x[i] = fft_x;
                fft_x += fft_dt;
            }

            m_ui->actionFFTwindow->setText("wind:   Hanning");
            //m_ui->menuFFTsamples->setText("size:    " + QString::number(m_fft_size));
            m_ui->actionFFTresolution->setText("res:      " + QString::number(fft_dt_real, 10, 2) + " Hz");

            if (m_fft_in != NULL)
                fftw_free(m_fft_in);
            if (m_fft_out != NULL)
                fftw_free(m_fft_out);
            if (m_fft_plan != NULL)
                fftw_destroy_plan(m_fft_plan);

            fftw_cleanup();

            m_fft_in = NULL;
            m_fft_out = NULL;
            m_fft_plan = NULL;

            m_fft_in  = fftw_alloc_real(m_fft_size);
            m_fft_out = fftw_alloc_real(m_fft_size);
            m_fft_plan = fftw_plan_r2r_1d(m_fft_size, m_fft_in, m_fft_out, FFTW_R2HC, FFTW_ESTIMATE);

            if (m_fft_in == NULL || m_fft_out == NULL || m_fft_plan == NULL)
            {
                msgBox(this, "FFTW alloc memory failed!", CRITICAL);
                on_pushButton_fft_on_clicked();
            }
        }

        /* ETS */
        if (m_ets)
        {
            double fin = m_ets_freq;
            if (m_ets_pwm)
                fin = WindowPwm::getFreqReal().toDouble();

            qInfo() << "ETS: " << fin;
            double ets_coef = abs(fin - m_daqSet.fs_real_n) / fin;
            double f_seq = (1.0 / ets_coef) * m_daqSet.fs_real_n;

            for (int i = 0; i < m_daqSet.mem; i++)
                m_t[i] *= ets_coef;

            m_ui->actionETS_fIN->setText("fIN:    " + QString::number(fin, 10, 6) +  "Hz");
            m_ui->actionETS_coef->setText("coef:  " + QString::number(ets_coef, 10, 9));
            m_ui->actionETS_fSEQ->setText("fSEQ: " + QString::number(f_seq, 10, 2) + " Hz");
            m_status_ets->setText("ETS: " + QString::number(f_seq, 10, 2) + " Hz");
        }
    }

    m_last_fs = m_daqSet.fs;
    m_last_mem = m_daqSet.mem;

    if (m_zoomed)
    {
        if (m_t.isEmpty())
            return;

        double x = m_t[m_t.size()-1];

        if (x >= 2)
            m_timeTicker->setTimeFormat("%s s");
        else if (x >= 0.002)
            m_timeTicker->setTimeFormat("%z ms");
        else
            m_timeTicker->setTimeFormat("%u μs");
    }
}

void WindowScope::updatePanel()
{
    auto info = Core::getInstance()->getDevInfo();

    m_ignoreValuesChanged = true;

    on_pushButton_average_on_clicked();

    createX();

    enablePanel(true);

    if (m_rescale_needed)
    {
        rescaleXAxis();
        rescaleYAxis();

        m_rescale_needed = false;
    }

    m_ui->customPlot->graph(GRAPH_CH1)->setVisible(m_daqSet.ch1_en);
    m_ui->customPlot->graph(GRAPH_CH2)->setVisible(m_daqSet.ch2_en);
    m_ui->customPlot->graph(GRAPH_CH3)->setVisible(m_daqSet.ch3_en);
    m_ui->customPlot->graph(GRAPH_CH4)->setVisible(m_daqSet.ch4_en);

    QStringList tokens = m_daqSet.fs_real.split('.', QString::SkipEmptyParts);

    if (tokens.size() > 1 && tokens[0].length() > 4)
        m_ui->textBrowser_realFs->setHtml("<p align=\"center\">" + tokens[0] + ". " + tokens[1] + "</p>");
    else
        m_ui->textBrowser_realFs->setHtml("<p align=\"center\">" + m_daqSet.fs_real + "</p>");

    m_ui->textBrowser_maxZ->setHtml("<p align=\"center\">" + format_unit(m_daqSet.maxZ_ohm, "Ω", 2) + "</p>");

    m_ui->pushButton_enable1->setVisible(!m_daqSet.ch1_en);
    m_ui->pushButton_enable2->setVisible(!m_daqSet.ch2_en);
    m_ui->pushButton_disable1->setVisible(m_daqSet.ch1_en);
    m_ui->pushButton_disable2->setVisible(m_daqSet.ch2_en);

    if (info->daq_ch == 4)
    {
        m_ui->pushButton_enable3->setVisible(!m_daqSet.ch3_en);
        m_ui->pushButton_enable4->setVisible(!m_daqSet.ch4_en);
        m_ui->pushButton_disable3->setVisible(m_daqSet.ch3_en);
        m_ui->pushButton_disable4->setVisible(m_daqSet.ch4_en);
    }

    m_ui->pushButton_bit12_on->setVisible(m_daqSet.bits == B12);
    m_ui->pushButton_bit12_off->setVisible(!(m_daqSet.bits == B12));
    m_ui->pushButton_bit8_off->setVisible(m_daqSet.bits == B12);
    m_ui->pushButton_bit8_on->setVisible(!(m_daqSet.bits == B12));

    m_ui->spinBox_mem->setValue(m_daqSet.mem);
    m_ui->dial_mem->setValue(m_daqSet.mem);

    m_ui->spinBox_fs->setValue(m_daqSet.fs);
    m_ui->dial_fs->setValue(m_daqSet.fs);

    m_ui->dial_trigPre->setValue(m_daqSet.trig_pre);
    m_ui->dial_trigVal->setValue(m_daqSet.trig_val);

    m_ui->spinBox_trigPre->setValue(m_daqSet.trig_pre);
    m_ui->spinBox_trigVal->setValue(m_daqSet.trig_val);

    if (!m_t.isEmpty())
    {
        m_cursorTrigPre->setValue(m_daqSet.trig_pre, 0, m_ref_v * 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigVal->setValue(m_daqSet.trig_val, 0, m_ref_v * 1, 0, m_t[m_t.size()-1]);
    }

    double yLim = (m_spline ? Y_LIM1 : Y_LIM2);
    double p = yLim / (m_ref_v + (2.0 * yLim));
    m_ui->horizontalSlider_trigPre->setValue(m_daqSet.trig_pre * 10.0);
    m_ui->horizontalSlider_trigVal->setValue(((m_daqSet.trig_val * (1.0 - (2.0 * p))) + (p * 100.0)) * 10.0);

    m_ui->pushButton_single_off->show();
    m_ui->pushButton_single_on->hide();
    m_single = false;

    bool trigEnabled = !(m_daqSet.trig_mode == DaqTrigMode::DISABLED);

    m_ui->radioButton_trigCh_1->setEnabled(trigEnabled);
    m_ui->radioButton_trigCh_2->setEnabled(trigEnabled);
    m_ui->radioButton_trigCh_3->setEnabled(trigEnabled);
    m_ui->radioButton_trigCh_4->setEnabled(trigEnabled);

    m_ui->groupBox_t_19->setEnabled(trigEnabled);

    m_ui->radioButton_trigSlope_Rising->setEnabled(trigEnabled);
    m_ui->radioButton_trigSlope_Falling->setEnabled(trigEnabled);

    if (m_daqSet.trig_mode == DaqTrigMode::AUTO)
        m_ui->radioButton_trigMode_Auto->setChecked(true);
    else if (m_daqSet.trig_mode == DaqTrigMode::NORMAL)
        m_ui->radioButton_trigMode_Normal->setChecked(true);
    else if (m_daqSet.trig_mode == DaqTrigMode::DISABLED)
        m_ui->radioButton_trigMode_Disabled->setChecked(true);
    else // SINGLE
    {
        m_ui->radioButton_trigMode_Auto->setEnabled(false);
        m_ui->radioButton_trigMode_Normal->setEnabled(false);
        m_ui->radioButton_trigMode_Disabled->setEnabled(false);

        m_ui->pushButton_single_on->show();
        m_ui->pushButton_single_off->hide();

        m_ui->pushButton_run->hide();
        m_ui->pushButton_stop->hide();
        m_ui->pushButton_run_off->show();

        m_single = true;
    }

    if (m_daqSet.trig_edge == DaqTrigEdge::RISING)
        m_ui->radioButton_trigSlope_Rising->setChecked(true);
    else // FALLING
        m_ui->radioButton_trigSlope_Falling->setChecked(true);

    if (m_daqSet.trig_ch == 1)
        m_ui->radioButton_trigCh_1->setChecked(true);
    else if (m_daqSet.trig_ch == 2)
        m_ui->radioButton_trigCh_2->setChecked(true);
    else if (m_daqSet.trig_ch == 3)
        m_ui->radioButton_trigCh_3->setChecked(true);
    else // 4
        m_ui->radioButton_trigCh_4->setChecked(true);

    bool forc = (m_daqSet.trig_mode != DaqTrigMode::DISABLED && m_daqSet.trig_mode != DaqTrigMode::AUTO);
    m_ui->pushButton_trigForc->setEnabled(forc);
    m_ui->spinBox_average->setEnabled(!m_average);

    on_radioButton_fsMem_clicked(m_ui->radioButton_fsMem->isChecked());

    /* MAX FS AND MEM */

    int max_mem = info->mem;
    if (m_daqSet.bits == B12)
        max_mem /= 2;
    max_mem /= (m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en);

    m_ui->spinBox_mem->setRange(2,max_mem);
    m_ui->dial_mem->setRange(2,max_mem);

    int max_fs = info->adc_fs_12b; // TODO

    if (info->adc_num == 1)
        max_fs /= (m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en);
    else if (info->adc_num == 2)
    {
        int cnt1 = m_daqSet.ch1_en + m_daqSet.ch2_en;
        int cnt2 = m_daqSet.ch3_en + m_daqSet.ch4_en;
        max_fs /= (cnt1 > cnt2) ? cnt1 : cnt2;
    }

    m_ui->spinBox_fs->setRange(1,max_fs);
    m_ui->dial_fs->setRange(1,max_fs);

    /************ */

    if (trigEnabled)
    {
        m_ui->radioButton_trigCh_1->setEnabled(m_daqSet.ch1_en);
        m_ui->radioButton_trigCh_2->setEnabled(m_daqSet.ch2_en);
        m_ui->radioButton_trigCh_3->setEnabled(m_daqSet.ch3_en);
        m_ui->radioButton_trigCh_4->setEnabled(m_daqSet.ch4_en);
    }

    double div_format;
    double div_sec;
    const QString suffix = h_manual_to_auto(m_daqSet.fs_real_n, m_daqSet.mem, div_format, div_sec);

    m_ui->doubleSpinBox_div->setValue(div_format);
    m_ui->doubleSpinBox_div->setSuffix(suffix);
    //m_ui->dial_div->setRange(((1.0 / info->adc_fs_12b) * 2.0 * 1000000.0), 1000000);
    m_ui->dial_div->setValue(lin_to_exp_1to1M(div_sec * 1000000.0, true));
    m_ui->radioButton_div->setEnabled(true);

    m_status_smpl->setText("Sampling Time: " + format_unit(m_daqSet.smpl_time, "s", 2));

    bool trigCh1_en = m_ui->radioButton_trigCh_1->isEnabled();
    bool trigCh2_en = m_ui->radioButton_trigCh_2->isEnabled();
    bool trigCh3_en = m_ui->radioButton_trigCh_3->isEnabled();
    bool trigCh4_en = m_ui->radioButton_trigCh_4->isEnabled();

    if (m_refresh || m_last_trigEnabled != trigEnabled)
    {
        m_ui->radioButton_trigSlope_Rising->setStyleSheet(trigEnabled ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
        m_ui->radioButton_trigSlope_Falling->setStyleSheet(trigEnabled ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);

        m_ui->spinBox_trigVal->setStyleSheet(trigEnabled ? CSS_SPINBOX_NODIS : CSS_SPINBOX);
        m_ui->spinBox_trigPre->setStyleSheet(trigEnabled ? CSS_SPINBOX_NODIS : CSS_SPINBOX);
    }

    if (m_refresh || m_last_forc != forc)
        m_ui->pushButton_trigForc->setStyleSheet(forc ? (CSS_BUTTON_ON_NODIS CSS_BUTTON_FORC) : (CSS_BUTTON_ON CSS_BUTTON_FORC));

    if (m_refresh || m_last_trigCh1_en != trigCh1_en)
        m_ui->radioButton_trigCh_1->setStyleSheet(trigCh1_en ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    if (m_refresh || m_last_trigCh2_en != trigCh2_en)
        m_ui->radioButton_trigCh_2->setStyleSheet(trigCh2_en ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    if (m_refresh || m_last_trigCh3_en != trigCh3_en)
        m_ui->radioButton_trigCh_3->setStyleSheet(trigCh3_en ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    if (m_refresh || m_last_trigCh4_en != trigCh4_en)
        m_ui->radioButton_trigCh_4->setStyleSheet(trigCh4_en ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);

    if (m_refresh || m_last_single != m_single)
    {
        m_ui->radioButton_trigMode_Auto->setStyleSheet(m_single ? CSS_RADIOBUTTON : CSS_RADIOBUTTON_NODIS);
        m_ui->radioButton_trigMode_Normal->setStyleSheet(m_single ? CSS_RADIOBUTTON : CSS_RADIOBUTTON_NODIS);
        m_ui->radioButton_trigMode_Disabled->setStyleSheet(m_single ? CSS_RADIOBUTTON : CSS_RADIOBUTTON_NODIS);
    }

    m_last_forc = forc;
    m_last_single = m_single;
    m_last_trigEnabled = trigEnabled;
    m_last_trigCh1_en = trigCh1_en;
    m_last_trigCh2_en = trigCh2_en;
    m_last_trigCh3_en = trigCh3_en;
    m_last_trigCh4_en = trigCh4_en;

    m_ignoreValuesChanged = false;
    m_refresh = false;
}

void WindowScope::enablePanel(bool en)
{
    m_ui->groupBox_main->setEnabled(en);
    m_ui->groupBox_trigger->setEnabled(en);
    m_ui->groupBox_horizontal->setEnabled(en);
    m_ui->groupBox_vertical->setEnabled(en);
    m_ui->groupBox_utils->setEnabled(en);
}

void WindowScope::fix2ADCproblem(bool add)
{
    if (Core::getInstance()->getDevInfo()->adc_num == 2)
    {
        int count = 0;

        if (m_ui->pushButton_disable1->isVisible()) count++;
        if (m_ui->pushButton_disable2->isVisible()) count++;
        if (m_ui->pushButton_disable3->isVisible()) count++;
        if (m_ui->pushButton_disable4->isVisible()) count++;

        if (count == 3)
        {
            if (add)
            {
                m_ui->pushButton_enable1->hide();
                m_ui->pushButton_disable1->show();

                m_ui->pushButton_enable2->hide();
                m_ui->pushButton_disable2->show();

                m_ui->pushButton_enable3->hide();
                m_ui->pushButton_disable3->show();

                m_ui->pushButton_enable4->hide();
                m_ui->pushButton_disable4->show();
            }
            else
            {
                if (m_ui->pushButton_disable1->isVisible() && m_ui->pushButton_disable2->isVisible())
                {
                    m_ui->pushButton_enable3->show();
                    m_ui->pushButton_disable3->hide();

                    m_ui->pushButton_enable4->show();
                    m_ui->pushButton_disable4->hide();
                }
                else
                {
                    m_ui->pushButton_enable1->show();
                    m_ui->pushButton_disable1->hide();

                    m_ui->pushButton_enable2->show();
                    m_ui->pushButton_disable2->hide();
                }
            }
        }
    }
}

void WindowScope::sendSet()
{
    auto info = Core::getInstance()->getDevInfo();

    m_msgPending = true;
    enablePanel(false);

    /************ */

    m_ui->radioButton_trigLed->setChecked(false);

    m_daqSet.bits = m_ui->pushButton_bit12_on->isVisible() ? B12 : B8;
    m_daqSet.mem = m_ui->spinBox_mem->value();
    m_daqSet.fs = m_ui->spinBox_fs->value();
    m_daqSet.ch1_en = m_ui->pushButton_disable1->isVisible();
    m_daqSet.ch2_en = m_ui->pushButton_disable2->isVisible();
    m_daqSet.ch3_en = m_ui->pushButton_disable3->isVisible();
    m_daqSet.ch4_en = m_ui->pushButton_disable4->isVisible();

    QString channs = "0000";
    channs[0] = m_daqSet.ch1_en ? '1' : '0';
    channs[1] = m_daqSet.ch2_en ? '1' : '0';
    channs[2] = m_daqSet.ch3_en ? '1' : '0';
    channs[3] = m_daqSet.ch4_en ? '1' : '0';

    if (m_ui->radioButton_trigCh_1->isChecked()) m_daqSet.trig_ch = 1;
    else if (m_ui->radioButton_trigCh_2->isChecked()) m_daqSet.trig_ch = 2;
    else if (m_ui->radioButton_trigCh_3->isChecked()) m_daqSet.trig_ch = 3;
    else m_daqSet.trig_ch = 4;

    m_daqSet.trig_val = m_ui->spinBox_trigVal->value();
    m_daqSet.trig_pre = m_ui->spinBox_trigPre->value();

    QString trigMode = "0";

    if (m_single)
    {
        m_daqSet.trig_mode = SINGLE;
        trigMode = "S";
    }
    else if (m_ui->radioButton_trigMode_Auto->isChecked())
    {
        m_daqSet.trig_mode = AUTO;
        trigMode = "A";
    }
    else if (m_ui->radioButton_trigMode_Normal->isChecked())
    {
        m_daqSet.trig_mode = NORMAL;
        trigMode = "N";
    }
    else if (m_ui->radioButton_trigMode_Disabled->isChecked())
    {
        m_daqSet.trig_mode = DISABLED;
        trigMode = "D";
    }
    else assert(0);

    QString trigEdge = "0";

    if (m_ui->radioButton_trigSlope_Rising->isChecked())
    {
        m_daqSet.trig_edge = RISING;
        trigEdge = "R";
    }
    else
    {
        m_daqSet.trig_edge = FALLING;
        trigEdge = "F";
    }

    /* fs, mem, trig ch -> trimm */

    int max_mem = info->mem;
    if (m_daqSet.bits == B12)
        max_mem /= 2;
    max_mem /= (m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en);

    m_ui->spinBox_mem->setRange(2,max_mem);
    m_ui->dial_mem->setRange(2,max_mem);

    int max_fs = info->adc_fs_12b; // TODO

    if (info->adc_num == 1)
        max_fs /= (m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en);
    else if (info->adc_num == 2)
    {
        int cnt1 = m_daqSet.ch1_en + m_daqSet.ch2_en;
        int cnt2 = m_daqSet.ch3_en + m_daqSet.ch4_en;
        max_fs /= (cnt1 > cnt2) ? cnt1 : cnt2;
    }

    m_ui->spinBox_fs->setRange(1,max_fs);
    m_ui->dial_fs->setRange(1,max_fs);

    int trig_cnt = info->daq_ch;
    for (int i = 0, j = m_daqSet.trig_ch; i < trig_cnt; i++) // optimize trigger channel according to enabled channels
    {
        if ((m_daqSet.trig_ch == 1 && m_ui->pushButton_enable1->isVisible()) ||
            (m_daqSet.trig_ch == 2 && m_ui->pushButton_enable2->isVisible()) ||
            (m_daqSet.trig_ch == 3 && m_ui->pushButton_enable3->isVisible()) ||
            (m_daqSet.trig_ch == 4 && m_ui->pushButton_enable4->isVisible()))
        {
            j++;
            if (j == trig_cnt + 1)
                j = 1;

            m_daqSet.trig_ch = j;
        }
        else break;
    }

    Core::getInstance()->msgAdd(m_msg_set, false, (m_daqSet.bits == B12 ? "12," : "8," ) +     // bits
                                                   QString::number(m_daqSet.mem) + "," +       // mem
                                                   QString::number(m_daqSet.fs) + "," +        // fs
                                                   channs + "," +                              // channs
                                                   QString::number(m_daqSet.trig_ch) + "," +   // trig ch
                                                   QString::number(m_daqSet.trig_val) + "," +  // trig val
                                                   trigEdge + "," +                            // trig edge
                                                   trigMode + "," +                            // trig mode
                                                   QString::number(m_daqSet.trig_pre));        // trig pre
}
