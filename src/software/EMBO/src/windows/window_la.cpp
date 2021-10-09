/*
 * CTU/EMBO - EMBedded OscilloLAe <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_la.h"
#include "ui_window_la.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>

#define Y_LIM                   0.20
#define TRIG_VAL_PRE_TIMEOUT    3000


WindowLa::WindowLa(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowLa), m_rec(0)
{
    m_ui->setupUi(this);

    m_timer_plot = new QTimer(this);
    m_timer_plot->setTimerType(Qt::PreciseTimer);

    m_timer_trigSliders = new QTimer(this);
    m_timer_trigSliders->setSingleShot(true);

    m_msg_set = new Msg_LA_Set(this);
    m_msg_read = new Msg_LA_Read(this);
    m_msg_forceTrig = new Msg_LA_ForceTrig(this);

    connect(m_msg_set, &Msg_LA_Set::ok2, this, &WindowLa::on_msg_ok_set, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_LA_Set::err, this, &WindowLa::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_LA_Set::result, this, &WindowLa::on_msg_set, Qt::QueuedConnection);

    connect(m_msg_read, &Msg_LA_Read::err, this, &WindowLa::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read, &Msg_LA_Read::result, this, &WindowLa::on_msg_read, Qt::QueuedConnection);

    connect(m_msg_forceTrig, &Msg_LA_ForceTrig::ok, this, &WindowLa::on_msg_ok_forceTrig, Qt::QueuedConnection);
    //connect(m_msg_forceTrig, &Msg_LA_ForceTrig::err, this, &WindowLa::on_msg_err, Qt::QueuedConnection);

    connect(Core::getInstance(), &Core::daqReady, this, &WindowLa::on_msg_daqReady, Qt::QueuedConnection);

    connect(m_timer_plot, &QTimer::timeout, this, &WindowLa::on_timer_plot);
    connect(m_timer_trigSliders, &QTimer::timeout, this, &WindowLa::on_hideTrigSliders);

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
    m_trigSlope.addButton(m_ui->radioButton_trigSlope_Both);

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

    /* event filter */

    m_ui->dial_trigPre->installEventFilter(this);

    m_instrEnabled = true;
}

bool WindowLa::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_ui->dial_trigPre)
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

void WindowLa::statusBarLoad()
{
    m_status_vcc = new QLabel(" ", this);
    m_status_seq = new QLabel("Sequence Number: 0", this);
    QWidget* widget = new QWidget(this);
    QLabel* status_zoom = new QLabel("<span>Zoom with Scroll Wheel, Move with Mouse Drag&nbsp;&nbsp;<span>", this);

    QFont font1("Roboto", 11, QFont::Normal);
    m_status_vcc->setFont(font1);
    m_status_seq->setFont(font1);
    status_zoom->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/img/la.png");

    status_img->setPixmap(status_img_icon);
    status_img->setFixedWidth(17);
    status_img->setFixedHeight(17);
    status_img->setScaledContents(true);

    m_status_line1 = new QFrame(this);
    m_status_line1->setFrameShape(QFrame::VLine);
    m_status_line1->setFrameShadow(QFrame::Plain);
    m_status_line1->setStyleSheet("color:gray;");
    m_status_line1->setFixedHeight(18);

    QLabel* status_spacer2 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer3 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);

    QSpacerItem* status_spacer0 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(status_img,     0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_vcc,   0,1,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer2, 0,2,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_line1, 0,3,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer3, 0,4,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_seq,   0,5,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->addItem(status_spacer0,   0,6,1,1,Qt::AlignVCenter);
    layout->addWidget(status_zoom,    0,7,1,1,Qt::AlignVCenter);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);
}

void WindowLa::initQcp()
{
    m_ui->customPlot->plotLayout()->clear();

    m_axis_ch1 = new QCPAxisRect(m_ui->customPlot);
    m_axis_ch2 = new QCPAxisRect(m_ui->customPlot);
    m_axis_ch3 = new QCPAxisRect(m_ui->customPlot);
    m_axis_ch4 = new QCPAxisRect(m_ui->customPlot);

    m_axis_ch1->setupFullAxesBox();
    m_axis_ch2->setupFullAxesBox();
    m_axis_ch3->setupFullAxesBox();
    m_axis_ch4->setupFullAxesBox();

    m_axis_ch1->setMinimumMargins(QMargins(25,15,15,0));
    m_axis_ch2->setMinimumMargins(QMargins(25,1,15,0));
    m_axis_ch3->setMinimumMargins(QMargins(25,1,15,0));
    m_axis_ch4->setMinimumMargins(QMargins(25,1,15,30));

    m_timeTicker = QSharedPointer<QCPAxisTickerTime>(new QCPAxisTickerTime);
    m_timeTicker->setTimeFormat("%z ms");
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuSeconds, 1);
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuMilliseconds, 1);
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuMicroseconds, 1);

    m_axis_ch1->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);
    m_axis_ch2->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);
    m_axis_ch3->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);
    m_axis_ch4->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);

    m_axis_ch1->axis(QCPAxis::atLeft)->ticker()->setTickCount(1);
    m_axis_ch2->axis(QCPAxis::atLeft)->ticker()->setTickCount(1);
    m_axis_ch3->axis(QCPAxis::atLeft)->ticker()->setTickCount(1);
    m_axis_ch4->axis(QCPAxis::atLeft)->ticker()->setTickCount(1);

    m_axis_ch1->axis(QCPAxis::atRight)->ticker()->setTickCount(1);
    m_axis_ch2->axis(QCPAxis::atRight)->ticker()->setTickCount(1);
    m_axis_ch3->axis(QCPAxis::atRight)->ticker()->setTickCount(1);
    m_axis_ch4->axis(QCPAxis::atRight)->ticker()->setTickCount(1);

    QFont font2("Roboto", 12, QFont::Normal);
    m_axis_ch1->axis(QCPAxis::atBottom)->setTickLabelFont(font2);
    m_axis_ch2->axis(QCPAxis::atBottom)->setTickLabelFont(font2);
    m_axis_ch3->axis(QCPAxis::atBottom)->setTickLabelFont(font2);
    m_axis_ch4->axis(QCPAxis::atBottom)->setTickLabelFont(font2);

    m_axis_ch1->axis(QCPAxis::atLeft)->setTickLabelFont(font2);
    m_axis_ch2->axis(QCPAxis::atLeft)->setTickLabelFont(font2);
    m_axis_ch3->axis(QCPAxis::atLeft)->setTickLabelFont(font2);
    m_axis_ch4->axis(QCPAxis::atLeft)->setTickLabelFont(font2);

    m_axis_ch1->setRangeDrag(Qt::Horizontal);
    m_axis_ch2->setRangeDrag(Qt::Horizontal);
    m_axis_ch3->setRangeDrag(Qt::Horizontal);
    m_axis_ch4->setRangeDrag(Qt::Horizontal);

    m_axis_ch1->setRangeZoom(Qt::Horizontal);
    m_axis_ch2->setRangeZoom(Qt::Horizontal);
    m_axis_ch3->setRangeZoom(Qt::Horizontal);
    m_axis_ch4->setRangeZoom(Qt::Horizontal);

    m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_ch1);
    m_ui->customPlot->plotLayout()->addElement(1, 0, m_axis_ch2);
    m_ui->customPlot->plotLayout()->addElement(2, 0, m_axis_ch3);
    m_ui->customPlot->plotLayout()->addElement(3, 0, m_axis_ch4);

    foreach (QCPAxisRect *rect, m_ui->customPlot->axisRects())
    {
        foreach (QCPAxis *axis, rect->axes())
        {
            axis->setLayer("axes");
            axis->grid()->setLayer("grid");
        }
    }

    m_ui->customPlot->addGraph(m_axis_ch1->axis(QCPAxis::atBottom), m_axis_ch1->axis(QCPAxis::atLeft));  // ch1
    m_ui->customPlot->addGraph(m_axis_ch2->axis(QCPAxis::atBottom), m_axis_ch2->axis(QCPAxis::atLeft));  // ch2
    m_ui->customPlot->addGraph(m_axis_ch3->axis(QCPAxis::atBottom), m_axis_ch3->axis(QCPAxis::atLeft));  // ch3
    m_ui->customPlot->addGraph(m_axis_ch4->axis(QCPAxis::atBottom), m_axis_ch4->axis(QCPAxis::atLeft));  // ch4

    m_ui->customPlot->graph(GRAPH_CH1)->setPen(QPen(QColor(COLOR1)));
    m_ui->customPlot->graph(GRAPH_CH2)->setPen(QPen(QColor(COLOR2)));
    m_ui->customPlot->graph(GRAPH_CH3)->setPen(QPen(QColor(COLOR5)));
    m_ui->customPlot->graph(GRAPH_CH4)->setPen(QPen(QColor(COLOR4)));

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(false);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(false);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(false);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(false);

    //m_ui->customPlot->setOpenGl(true);

    //m_ui->customPlot->setInteractions(0);
    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    connect(m_ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(on_qcpMouseWheel(QWheelEvent*)));
    connect(m_ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(on_qcpMousePress(QMouseEvent*)));

    connect(m_axis_ch1->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch1->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch1->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));

    connect(m_axis_ch2->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch2->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch2->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));

    connect(m_axis_ch3->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch3->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch3->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));

    connect(m_axis_ch4->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch4->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch4->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));

    connect(m_axis_ch1->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
    connect(m_axis_ch2->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
    connect(m_axis_ch3->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
    connect(m_axis_ch4->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));

    connect(m_axis_ch1->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));
    connect(m_axis_ch2->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));
    connect(m_axis_ch3->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));
    connect(m_axis_ch4->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));

    /* cursors */

    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorV->setValues(m_cursorV_min, m_cursorV_max);

    m_ui->horizontalSlider_cursorH->hide();
    m_ui->horizontalSlider_cursorV->hide();

    connect(m_ui->horizontalSlider_cursorH, &ctkRangeSlider::valuesChanged, this, &WindowLa::on_cursorH_valuesChanged);

    m_cursors1 = new QCPCursors(this, m_ui->customPlot, m_axis_ch1, true, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursors2 = new QCPCursors(this, m_ui->customPlot, m_axis_ch2, true, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursors3 = new QCPCursors(this, m_ui->customPlot, m_axis_ch3, true, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursors4 = new QCPCursors(this, m_ui->customPlot, m_axis_ch4, true, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));

    m_cursorTrigPre1 = new QCPCursor(this, m_ui->customPlot, m_axis_ch1, false, false, QColor(COLOR9));
    m_cursorTrigPre2 = new QCPCursor(this, m_ui->customPlot, m_axis_ch2, false, false, QColor(COLOR9));
    m_cursorTrigPre3 = new QCPCursor(this, m_ui->customPlot, m_axis_ch3, false, false, QColor(COLOR9));
    m_cursorTrigPre4 = new QCPCursor(this, m_ui->customPlot, m_axis_ch4, false, false, QColor(COLOR9));

    m_cursorTrigPre1->showText(false);
    m_cursorTrigPre2->showText(false);
    m_cursorTrigPre3->showText(false);
    m_cursorTrigPre4->showText(false);
}

WindowLa::~WindowLa()
{
    delete m_ui;
}

void WindowLa::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/********************************* timer slots *********************************/

void WindowLa::on_timer_plot() // 60 FPS
{
    if (m_cursorsV_en || m_cursorsH_en)
    {
        auto rngV = m_ui->customPlot->yAxis->range();
        auto rngH = m_ui->customPlot->xAxis->range();

        m_cursors1->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false); // true
        m_cursors2->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false); // true
        m_cursors3->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false); // true
        m_cursors4->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false); // true
    }

    m_ui->customPlot->replot();
}

/********************************* MSG slots *********************************/

void WindowLa::on_msg_err(const QString text, MsgBoxType type, bool needClose)
{
    m_activeMsgs.clear();

    if (needClose)
        this->close();

    msgBox(this, text, type);
}

void WindowLa::on_msg_ok_set(double fs_real_n, const QString fs_real)
{
    m_daqSet.fs_real = fs_real;
    m_daqSet.fs_real_n = fs_real_n;

    updatePanel();
    m_msgPending = false;
}

void WindowLa::on_msg_set(int mem, int fs, int trig_ch, DaqTrigEdge trig_edge, DaqTrigMode trig_mode, int trig_pre, double fs_real_n, const QString fs_real)
{
    auto info = Core::getInstance()->getDevInfo();

    m_daqSet.bits = B1;
    m_daqSet.mem = mem;
    m_daqSet.fs = fs;
    m_daqSet.ch1_en = true;
    m_daqSet.ch2_en = true;
    m_daqSet.ch3_en = info->daq_ch == 4 ? true : false;
    m_daqSet.ch4_en = info->daq_ch == 4 ? true : false;
    m_daqSet.trig_ch = trig_ch;
    m_daqSet.trig_val = 0;
    m_daqSet.trig_edge = trig_edge;
    m_daqSet.trig_mode = trig_mode;
    m_daqSet.trig_pre = trig_pre;
    m_daqSet.maxZ_ohm = 0;
    m_daqSet.fs_real = fs_real;
    m_daqSet.fs_real_n = fs_real_n;

    updatePanel();
    m_msgPending = false;
}

void WindowLa::on_msg_read(const QByteArray data)
{
    if (m_msgPending)
        return;

    auto info = Core::getInstance()->getDevInfo();
    int data_sz = data.size();

    int data_sz_wanted = m_daqSet.mem + (info->daq_reserve * 1);
    if (data_sz != data_sz_wanted) // wrong data size
    {
        m_err_cntr++;
        if (m_err_cntr > READ_ERROR_CNT)
        {
            on_msg_err(QString(INVALID_MSG) + " (data size wrong -> " + QString::number(data_sz) + "!=" +
                       QString::number(data_sz_wanted) + ")", CRITICAL, true);
            m_err_cntr = 0;
        }

        return;
    }

    std::vector<qreal> buff(data_sz);

    QVector<double> y1(m_daqSet.mem);
    QVector<double> y2(m_daqSet.mem);
    QVector<double> y3(m_daqSet.mem);
    QVector<double> y4(m_daqSet.mem);

    for (int k = 0, i = m_firstPos; k < m_daqSet.mem; k++, i++)
    {
        if (i >= data_sz)
            i = 0;

        bool ch1 = (data[i] & (1 << info->la_ch1_pin)) != 0;
        bool ch2 = (data[i] & (1 << info->la_ch2_pin)) != 0;
        bool ch3 = false;
        bool ch4 = false;

        if (info->daq_ch == 4)
        {
            ch3 = (data[i] & (1 << info->la_ch3_pin)) != 0;
            ch4 = (data[i] & (1 << info->la_ch4_pin)) != 0;
        }

        y1[k] = ch1 ? 1.0 : 0.0;
        y2[k] = ch2 ? 1.0 : 0.0;
        if (info->daq_ch == 4)
        {
            y3[k] = ch3 ? 1.0 : 0.0;
            y4[k] = ch4 ? 1.0 : 0.0;
        }
    }

    assert(!m_t.isEmpty());

    m_ui->customPlot->graph(GRAPH_CH1)->setData(m_t, y1);
    m_ui->customPlot->graph(GRAPH_CH2)->setData(m_t, y2);

    if (info->daq_ch == 4)
    {
        m_ui->customPlot->graph(GRAPH_CH3)->setData(m_t, y3);
        m_ui->customPlot->graph(GRAPH_CH4)->setData(m_t, y4);
    }

    m_seq_num++;
    m_status_seq->setText("Sequence Number: " + QString::number(m_seq_num));

    //m_ui->customPlot->replot();
}

void WindowLa::on_msg_daqReady(Ready ready, int firstPos)
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

void WindowLa::on_msg_ok_forceTrig(const QString, const QString)
{
    updatePanel();
}

/******************************** GUI slots ********************************/

/********** Plot **********/

void WindowLa::on_actionViewPoints_triggered(bool checked)
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

void WindowLa::on_actionViewLines_triggered(bool checked)
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

/********** Export **********/

void WindowLa::on_actionExportSave_triggered()
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
        {"Common.Mode",     "LA"},
        {"LA.SampleRate",  m_daqSet.fs_real},
        {"LA.Memory",      QString::number(m_daqSet.mem)},
        {"LA.Ch1",         m_daqSet.ch1_en ? "True" : "False"},
        {"LA.Ch2",         m_daqSet.ch2_en ? "True" : "False"},
        {"LA.Ch3",         m_daqSet.ch3_en ? "True" : "False"},
        {"LA.Ch4",         m_daqSet.ch4_en ? "True" : "False"},
        {"LA.Trig.Ch",     QString::number(m_daqSet.trig_ch)},
        {"LA.Trig.Mode",   m_daqSet.trig_mode == AUTO ? "AUTO" : (m_daqSet.trig_mode == NORMAL ? "NORMAL" : (m_daqSet.trig_mode == SINGLE ? "SINGLE" : "DISABLED"))},
        {"LA.Trig.Slope",  m_daqSet.trig_edge == RISING ? "RISING" : "FALLING"},
        {"LA.Trig.Pre",    QString::number(m_daqSet.trig_pre)}
    };
    bool ret = m_rec.createFile("LA", header);

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
                m_rec << (int)(data_1->at(i)->value);
            if (m_daqSet.ch2_en)
                m_rec << (int)(data_2->at(i)->value);
            if (m_daqSet.ch3_en)
                m_rec << (int)(data_3->at(i)->value);
            if (m_daqSet.ch4_en)
                m_rec << (int)(data_4->at(i)->value);
            m_rec << ENDL;
        }

        auto f = m_rec.closeFile();
        msgBox(this, "File saved at: " + f, INFO);
    }
}

void WindowLa::on_actionExportPNG_triggered()
{
     //QString ret = m_rec.takeScreenshot("LA", m_ui->customPlot);

     QString path = m_rec.generateFilePath("LA", ".png");
     bool ret = m_ui->customPlot->savePng(path);

     if (ret)
         msgBox(this, "File saved at: " + path, INFO);
     else
         msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
}

void WindowLa::on_actionExportPDF_triggered()
{
    QString path = m_rec.generateFilePath("LA", ".pdf");
    bool ret = m_ui->customPlot->savePdf(path);

    if (ret)
        msgBox(this, "File saved at: " + path, INFO);
    else
        msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
}

void WindowLa::on_actionExportFolder_triggered()
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

void WindowLa::on_actionExportCSV_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(CSV);

        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowLa::on_actionExportTXT_Tabs_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(TAB);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowLa::on_actionExportTXT_Semicolon_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(SEMICOLON);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowLa::on_actionExportMAT_triggered(bool checked)
{
    if (checked)
    {
        //rec.setDelim(MAT); // not implemented yet

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
    }
}

/********** Cursors **********/

void WindowLa::on_pushButton_cursorsHoff_clicked()
{
    m_ui->horizontalSlider_cursorH->hide();

    m_ui->pushButton_cursorsHon->show();
    m_ui->pushButton_cursorsHoff->hide();

    m_cursors1->showH(false);
    m_cursors2->showH(false);
    m_cursors3->showH(false);
    m_cursors4->showH(false);

    m_cursorsH_en = false;
}

void WindowLa::on_pushButton_cursorsHon_clicked()
{
    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorH->show();

    m_ui->pushButton_cursorsHon->hide();
    m_ui->pushButton_cursorsHoff->show();

    auto rngH = m_ui->customPlot->xAxis->range();
    auto rngV = m_ui->customPlot->yAxis->range();

    m_cursors1->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursors2->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursors3->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursors4->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);

    m_cursors1->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors1->setH_max(m_cursorH_max, rngH.lower, rngH.upper);
    m_cursors2->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors2->setH_max(m_cursorH_max, rngH.lower, rngH.upper);
    m_cursors3->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors3->setH_max(m_cursorH_max, rngH.lower, rngH.upper);
    m_cursors4->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors4->setH_max(m_cursorH_max, rngH.lower, rngH.upper);

    m_cursors1->showH(true);
    m_cursors2->showH(true);
    m_cursors3->showH(true);
    m_cursors4->showH(true);

    m_cursorsH_en = true;
}

void WindowLa::on_cursorH_valuesChanged(int min, int max)
{
    m_cursorH_min = min;
    m_cursorH_max = max;

    auto rng = m_ui->customPlot->axisRect()->rangeZoomAxis(Qt::Horizontal)->range();
    //auto rng = m_ui->customPlot->xAxis->range();

    m_cursors1->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors1->setH_max(m_cursorH_max, rng.lower, rng.upper);
    m_cursors2->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors2->setH_max(m_cursorH_max, rng.lower, rng.upper);
    m_cursors3->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors3->setH_max(m_cursorH_max, rng.lower, rng.upper);
    m_cursors4->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors4->setH_max(m_cursorH_max, rng.lower, rng.upper);
}

/********** QCP **********/

void WindowLa::on_qcpMouseWheel(QWheelEvent*)
{
    m_ui->pushButton_reset->hide();
    m_ui->pushButton_resetZoom->show();

    auto rngH = m_ui->customPlot->axisRect()->rangeZoomAxis(Qt::Horizontal)->range();
    double d = rngH.upper - rngH.lower;

    if (d >= 1)
        m_timeTicker->setTimeFormat("%s s");
    else if (d >= 0.001)
        m_timeTicker->setTimeFormat("%z ms");
    else
        m_timeTicker->setTimeFormat("%u μs");

    m_ui->horizontalSlider_trigPre->setStyleSheet(CSS_LA_TRIG_PRE_OFF);
}

void WindowLa::on_qcpMousePress(QMouseEvent*)
{
    m_ui->pushButton_reset->hide();
    m_ui->pushButton_resetZoom->show();

    m_ui->horizontalSlider_trigPre->setStyleSheet(CSS_LA_TRIG_PRE_OFF);
}

/********** right pannel - main **********/

void WindowLa::on_radioButton_zoomH_clicked(bool checked)
{
    if (checked)
    {
        m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

        m_axis_ch1->setRangeDrag(Qt::Horizontal);
        m_axis_ch2->setRangeDrag(Qt::Horizontal);
        m_axis_ch3->setRangeDrag(Qt::Horizontal);
        m_axis_ch4->setRangeDrag(Qt::Horizontal);
    }
    else
    {
        m_ui->customPlot->setInteractions(0);
    }
}

void WindowLa::on_radioButton_zoomV_clicked(bool)
{
}

void WindowLa::on_pushButton_reset_clicked()
{
    m_msgPending = true;
    m_rescale_needed = true;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    /* cursors */
    on_pushButton_cursorsHoff_clicked();

    /* plot style */
    on_actionViewLines_triggered(true);
    m_ui->actionViewLines->setChecked(true);

    on_actionViewPoints_triggered(false);
    m_ui->actionViewPoints->setChecked(false);

    Settings::setValue(CFG_REC_DIR, m_rec.getDir());

    on_actionExportCSV_triggered(true);
    m_ui->actionExportCSV->setChecked(true);

    on_pushButton_resetZoom_clicked();

    Core::getInstance()->sendRst(LA);

    showEvent(NULL);
}

void WindowLa::on_pushButton_resetZoom_clicked()
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

    m_ui->horizontalSlider_trigPre->setStyleSheet(CSS_LA_TRIG_PRE);

    m_ui->customPlot->replot();
}

void WindowLa::on_pushButton_single_off_clicked()
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

    sendSet();
}

void WindowLa::on_pushButton_single_on_clicked()
{
    m_single = true;
    m_instrEnabled = true;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    sendSet();
}

void WindowLa::on_pushButton_run_off_clicked()
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

    sendSet();
}

void WindowLa::on_pushButton_run_clicked()
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

void WindowLa::on_pushButton_stop_clicked()
{
    m_ui->pushButton_run->show();
    m_ui->pushButton_stop->hide();
    m_ui->pushButton_run_off->hide();

    m_instrEnabled = true;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    sendSet();
}

/********** right pannel - trigger **********/

void WindowLa::on_radioButton_trigMode_Auto_clicked(bool checked)
{
    if (checked)
    {
        m_ui->pushButton_single_off->show();
        m_ui->pushButton_single_on->hide();
        m_single = false;

        sendSet();
    }
}

void WindowLa::on_radioButton_trigMode_Normal_clicked(bool checked)
{
    if (checked)
    {
        m_ui->pushButton_single_off->show();
        m_ui->pushButton_single_on->hide();
        m_single = false;

        sendSet();
    }
}

void WindowLa::on_radioButton_trigMode_Disabled_clicked(bool checked)
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
        m_ui->radioButton_trigSlope_Both->setEnabled(false);

        m_ui->groupBox_t_19->setEnabled(false);

        sendSet();
    }
}

void WindowLa::on_radioButton_trigSlope_Rising_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowLa::on_radioButton_trigSlope_Falling_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowLa::on_radioButton_trigSlope_Both_toggled(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}


void WindowLa::on_radioButton_trigCh_1_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowLa::on_radioButton_trigCh_2_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowLa::on_radioButton_trigCh_3_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowLa::on_radioButton_trigCh_4_clicked(bool checked)
{
    if (checked)
    {
        sendSet();
    }
}

void WindowLa::on_spinBox_trigPre_valueChanged(int arg1)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->dial_trigPre->setValue(arg1);

    if (!m_t.isEmpty())
    {
        m_cursorTrigPre1->setValue(arg1, 0, 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigPre2->setValue(arg1, 0, 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigPre3->setValue(arg1, 0, 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigPre4->setValue(arg1, 0, 1, 0, m_t[m_t.size()-1]);
    }

    m_cursorTrigPre1->show(true);
    m_cursorTrigPre2->show(true);
    m_cursorTrigPre3->show(true);
    m_cursorTrigPre4->show(true);

    m_timer_trigSliders->start(TRIG_VAL_PRE_TIMEOUT);

    m_ui->horizontalSlider_trigPre->setValue(arg1 * 10.0);

    m_ignoreValuesChanged = false;

    sendSet();
}

void WindowLa::on_dial_trigPre_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    m_ignoreValuesChanged = true;
    m_ui->spinBox_trigPre->setValue(value);

    if (!m_t.isEmpty())
    {
        m_cursorTrigPre1->setValue(value, 0, 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigPre2->setValue(value, 0, 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigPre3->setValue(value, 0, 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigPre4->setValue(value, 0, 1, 0, m_t[m_t.size()-1]);
    }

    m_cursorTrigPre1->show(true);
    m_cursorTrigPre2->show(true);
    m_cursorTrigPre3->show(true);
    m_cursorTrigPre4->show(true);

    m_timer_trigSliders->start(TRIG_VAL_PRE_TIMEOUT);

    m_ui->horizontalSlider_trigPre->setValue(value * 10.0);

    m_ignoreValuesChanged = false;

    //if (!m_trigDialPressed)
    //    sendSet();
}

void WindowLa::on_pushButton_trigForc_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    m_ui->radioButton_trigLed->setChecked(false);
    enablePanel(false);

    Core::getInstance()->msgAdd(m_msg_forceTrig, false, "");
}

void WindowLa::on_dial_trigPre_sliderPressed()
{
    m_cursorTrigPre1->show(true);
    m_cursorTrigPre2->show(true);
    m_cursorTrigPre3->show(true);
    m_cursorTrigPre4->show(true);

    m_trigDialPressed = true;
    m_timer_trigSliders->start(TRIG_VAL_PRE_TIMEOUT);
}

void WindowLa::on_hideTrigSliders()
{
    m_cursorTrigPre1->show(false);
    m_cursorTrigPre2->show(false);
    m_cursorTrigPre3->show(false);
    m_cursorTrigPre4->show(false);
}

void WindowLa::on_dial_trigPre_sliderReleased()
{
    m_trigDialPressed = false;

    if (m_daqSet.trig_pre != m_ui->dial_trigPre->value())
        sendSet();
}

/********** right pannel - horizontal **********/

void WindowLa::on_radioButton_fsMem_clicked(bool checked)
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

void WindowLa::on_radioButton_div_clicked(bool checked)
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

void WindowLa::on_spinBox_mem_valueChanged(int arg1)
{
    if (m_ignoreValuesChanged)
        return;

    if (arg1 > m_daqSet.fs)
    {
        m_ui->spinBox_mem->setValue(m_daqSet.fs);
        return;
    }

    m_ignoreValuesChanged = true;
    m_ui->dial_mem->setValue(arg1);
    m_ignoreValuesChanged = false;

    m_rescale_needed = true;

    sendSet();
}

void WindowLa::on_dial_mem_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    if (value > m_daqSet.fs)
    {
        m_ui->dial_mem->setValue(m_daqSet.fs);
        return;
    }

    m_ignoreValuesChanged = true;
    m_ui->spinBox_mem->setValue(value);
    m_ignoreValuesChanged = false;

    m_rescale_needed = true;

    sendSet();
}

void WindowLa::on_spinBox_fs_valueChanged(int arg1)
{
    if (m_ignoreValuesChanged)
        return;

    if (arg1 < m_daqSet.mem)
    {
        m_ui->spinBox_fs->setValue(m_daqSet.mem);
        return;
    }

    m_ignoreValuesChanged = true;
    m_ui->dial_fs->setValue(arg1);
    m_ignoreValuesChanged = false;

    m_rescale_needed = true;

    sendSet();
}

void WindowLa::on_dial_fs_valueChanged(int value)
{
    if (m_ignoreValuesChanged)
        return;

    if (value < m_daqSet.mem)
    {
        m_ui->dial_fs->setValue(m_daqSet.mem);
        return;
    }

    m_ignoreValuesChanged = true;
    m_ui->spinBox_fs->setValue(value);
    m_ignoreValuesChanged = false;

    m_rescale_needed = true;

    sendSet();
}

void WindowLa::on_spinBox_div_valueChanged(int)
{
    if (m_ignoreValuesChanged)
        return;
}

void WindowLa::on_dial_div_valueChanged(int value)
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

void WindowLa::on_pushButton_disable1_clicked()
{
    if ((m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en) == 1)
        return;

    m_ui->pushButton_enable1->show();
    m_ui->pushButton_disable1->hide();

    m_daqSet.ch1_en = false;
    m_rescale_needed = true;

    if (m_daqSet.trig_ch == 1)
        sendSet();
    else
        updatePanel();

    m_ui->customPlot->replot();
}

void WindowLa::on_pushButton_disable2_clicked()
{
    if ((m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en) == 1)
        return;

    m_ui->pushButton_enable2->show();
    m_ui->pushButton_disable2->hide();

    m_daqSet.ch2_en = false;
    m_rescale_needed = true;

    if (m_daqSet.trig_ch == 2)
        sendSet();
    else
        updatePanel();

    m_ui->customPlot->replot();
}

void WindowLa::on_pushButton_disable3_clicked()
{
    auto info = Core::getInstance()->getDevInfo();
    if (info->daq_ch == 4)
    {
        if ((m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en) == 1)
            return;

        m_ui->pushButton_enable3->show();
        m_ui->pushButton_disable3->hide();

        m_daqSet.ch3_en = false;
        m_rescale_needed = true;

        if (m_daqSet.trig_ch == 3)
            sendSet();
        else
            updatePanel();

        m_ui->customPlot->replot();
    }
}

void WindowLa::on_pushButton_disable4_clicked()
{
    auto info = Core::getInstance()->getDevInfo();
    if (info->daq_ch == 4)
    {
        if ((m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en) == 1)
            return;

        m_ui->pushButton_enable4->show();
        m_ui->pushButton_disable4->hide();

        m_daqSet.ch4_en = false;
        m_rescale_needed = true;

        if (m_daqSet.trig_ch == 4)
            sendSet();
        else
            updatePanel();

        m_ui->customPlot->replot();
    }
}

void WindowLa::on_pushButton_enable1_clicked()
{
    m_ui->pushButton_enable1->hide();
    m_ui->pushButton_disable1->show();

    m_daqSet.ch1_en = true;
    m_rescale_needed = true;

    updatePanel();

    m_ui->customPlot->replot();
}

void WindowLa::on_pushButton_enable2_clicked()
{
    m_ui->pushButton_enable2->hide();
    m_ui->pushButton_disable2->show();

    m_daqSet.ch2_en = true;
    m_rescale_needed = true;

    updatePanel();

    m_ui->customPlot->replot();
}

void WindowLa::on_pushButton_enable3_clicked()
{
    auto info = Core::getInstance()->getDevInfo();
    if (info->daq_ch == 4)
    {
        m_ui->pushButton_enable3->hide();
        m_ui->pushButton_disable3->show();

        m_daqSet.ch3_en = true;
        m_rescale_needed = true;

        updatePanel();

        m_ui->customPlot->replot();
    }
}

void WindowLa::on_pushButton_enable4_clicked()
{
    auto info = Core::getInstance()->getDevInfo();
    if (info->daq_ch == 4)
    {
        m_ui->pushButton_enable4->hide();
        m_ui->pushButton_disable4->show();

        m_daqSet.ch4_en = true;
        m_rescale_needed = true;

        updatePanel();

        m_ui->customPlot->replot();
    }
}

/********** right pannel - utils **********/


/******************************** private ********************************/


void WindowLa::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();
    m_instrEnabled = false;

    Core::getInstance()->setMode(NO_MODE);
    emit closing(WindowLa::staticMetaObject.className());

     m_timer_plot->stop();
}

void WindowLa::showEvent(QShowEvent*)
{
    m_ignoreValuesChanged = true;

    m_seq_num = 0;

    enablePanel(false);

    Core::getInstance()->setMode(LA);
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
    }

    m_ui->radioButton_trigLed->setChecked(false);

    on_pushButton_resetZoom_clicked();

    m_ui->dial_mem->setRange(2, info->mem);
    m_ui->spinBox_mem->setRange(2, info->mem);

    m_ui->dial_fs->setRange(1, info->la_fs);
    m_ui->spinBox_fs->setRange(1, info->la_fs);

    m_ui->dial_div->setRange(((1.0 / info->la_fs) * 2.0 * 1000000.0), 1000000);

    m_timer_plot->start((int)TIMER_LA_PLOT);

    m_ignoreValuesChanged = false;

    m_ui->pushButton_disable1->setStyleSheet(CSS_BUTTON_CH1_NODIS CSS_BUTTON_CH);
    m_ui->pushButton_disable2->setStyleSheet(CSS_BUTTON_CH2_NODIS CSS_BUTTON_CH);
    m_ui->pushButton_enable1->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_CH);
    m_ui->pushButton_enable2->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_CH);
    if (info->daq_ch == 4)
    {
        m_ui->pushButton_enable3->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_CH);
        m_ui->pushButton_enable4->setStyleSheet(CSS_BUTTON_ON_NODIS CSS_BUTTON_CH);
        m_ui->pushButton_disable3->setStyleSheet(CSS_BUTTON_CH3_NODIS CSS_BUTTON_CH);
        m_ui->pushButton_disable4->setStyleSheet(CSS_BUTTON_CH4_NODIS CSS_BUTTON_CH);

        m_ui->pushButton_enable3->show();
        m_ui->pushButton_enable4->show();
        m_ui->pushButton_disable3->show();
        m_ui->pushButton_disable4->show();

        m_ui->line_4->show();
        m_ui->line_5->show();

        m_ui->radioButton_trigCh_3->show();
        m_ui->radioButton_trigCh_4->show();
    }
    else
    {
        m_ui->pushButton_enable3->hide();
        m_ui->pushButton_enable4->hide();
        m_ui->pushButton_disable3->hide();
        m_ui->pushButton_disable4->hide();

        m_ui->line_4->hide();
        m_ui->line_5->hide();

        m_ui->radioButton_trigCh_3->hide();
        m_ui->radioButton_trigCh_4->hide();
    }

    m_ui->actionMeasChannel_3->setEnabled(info->daq_ch == 4);
    m_ui->actionMeasChannel_4->setEnabled(info->daq_ch == 4);

    m_ui->actionMath_3_4->setEnabled(info->daq_ch == 4);

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
    m_ui->radioButton_trigSlope_Both->setStyleSheet(trigEnabled ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);

    m_ui->spinBox_trigPre->setStyleSheet(trigEnabled ? CSS_SPINBOX_NODIS : CSS_SPINBOX);

    bool forc = (m_daqSet.trig_mode != DaqTrigMode::DISABLED && m_daqSet.trig_mode != DaqTrigMode::AUTO);
    m_ui->pushButton_trigForc->setStyleSheet(forc ? (CSS_BUTTON_ON_NODIS CSS_BUTTON_FORC) : (CSS_BUTTON_ON CSS_BUTTON_FORC));

    m_ui->radioButton_trigCh_1->setStyleSheet(m_ui->radioButton_trigCh_1->isEnabled() ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    m_ui->radioButton_trigCh_2->setStyleSheet(m_ui->radioButton_trigCh_2->isEnabled() ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    m_ui->radioButton_trigCh_3->setStyleSheet(m_ui->radioButton_trigCh_3->isEnabled() ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
    m_ui->radioButton_trigCh_4->setStyleSheet(m_ui->radioButton_trigCh_4->isEnabled() ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);

    m_refresh = true;
}

void WindowLa::rescaleYAxis()
{
    m_axis_ch1->axis(QCPAxis::atLeft)->setRange(0 - Y_LIM , 1 + Y_LIM);
    m_axis_ch2->axis(QCPAxis::atLeft)->setRange(0 - Y_LIM , 1 + Y_LIM);
    m_axis_ch3->axis(QCPAxis::atLeft)->setRange(0 - Y_LIM , 1 + Y_LIM);
    m_axis_ch4->axis(QCPAxis::atLeft)->setRange(0 - Y_LIM , 1 + Y_LIM);

    auto rngV = m_ui->customPlot->yAxis->range();
    auto rngH = m_ui->customPlot->xAxis->range();

    m_cursorTrigPre1->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursorTrigPre2->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursorTrigPre3->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursorTrigPre4->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
}

void WindowLa::rescaleXAxis()
{
    if (m_t.isEmpty())
        return;

    m_axis_ch1->axis(QCPAxis::atBottom)->setRange(0, m_t[m_t.size()-1]);
    //m_axis_ch2->axis(QCPAxis::atBottom)->setRange(0, m_t_last);
    //m_axis_ch3->axis(QCPAxis::atBottom)->setRange(0, m_t_last);
    //m_axis_ch4->axis(QCPAxis::atBottom)->setRange(0, m_t_last);

    auto rngV = m_ui->customPlot->yAxis->range();
    auto rngH = m_ui->customPlot->xAxis->range();

    m_cursorTrigPre1->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursorTrigPre2->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursorTrigPre3->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursorTrigPre4->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
}

void WindowLa::createX()
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

void WindowLa::updatePanel()
{
    auto info = Core::getInstance()->getDevInfo();

    m_ignoreValuesChanged = true;

    createX();

    enablePanel(true);

    if (m_rescale_needed)
    {
        rescaleXAxis();
        rescaleYAxis();

        m_rescale_needed = false;
    }

    if (m_axis_ch1->visible()) {
        m_axis_ch1->setVisible(false);
        m_axis_ch1->layout()->take(m_axis_ch1);
    }
    if (m_axis_ch2->visible()) {
        m_axis_ch2->setVisible(false);
        m_axis_ch2->layout()->take(m_axis_ch2);
    }
    if (m_axis_ch3->visible()) {
        m_axis_ch3->setVisible(false);
        m_axis_ch3->layout()->take(m_axis_ch3);
    }
    if (m_axis_ch4->visible()) {
        m_axis_ch4->setVisible(false);
        m_axis_ch4->layout()->take(m_axis_ch4);
    }

    m_ui->customPlot->plotLayout()->simplify();

    if (m_daqSet.ch4_en) {
        m_ui->customPlot->plotLayout()->insertRow(0);
        m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_ch4);
        m_axis_ch4->setVisible(true);
    }
    if (m_daqSet.ch3_en) {
        m_ui->customPlot->plotLayout()->insertRow(0);
        m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_ch3);
        m_axis_ch3->setVisible(true);
    }
    if (m_daqSet.ch2_en) {
        m_ui->customPlot->plotLayout()->insertRow(0);
        m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_ch2);
        m_axis_ch2->setVisible(true);
    }
    if (m_daqSet.ch1_en) {
        m_ui->customPlot->plotLayout()->insertRow(0);
        m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_ch1);
        m_axis_ch1->setVisible(true);
    }

    m_axis_ch1->axis(QCPAxis::atBottom)->setTickLabels(false);
    m_axis_ch2->axis(QCPAxis::atBottom)->setTickLabels(false);
    m_axis_ch3->axis(QCPAxis::atBottom)->setTickLabels(false);
    m_axis_ch4->axis(QCPAxis::atBottom)->setTickLabels(false);

    m_axis_ch1->setMinimumMargins(QMargins(25,15,15,0));
    m_axis_ch2->setMinimumMargins(QMargins(25,1,15,0));
    m_axis_ch3->setMinimumMargins(QMargins(25,1,15,0));
    m_axis_ch4->setMinimumMargins(QMargins(25,1,15,30));

    m_cursors1->showText(false);
    m_cursors2->showText(false);
    m_cursors3->showText(false);
    m_cursors4->showText(false);

    QCPAxisRect* top = m_axis_ch1;
    QCPAxisRect* bot = m_axis_ch4;
    QCPCursors* bot_cursors = m_cursors4;

    if (m_daqSet.ch4_en)
    {
        bot_cursors = m_cursors4;
        bot = m_axis_ch4;
        m_axis_ch4->axis(QCPAxis::atBottom)->setTickLabels(true);
    }
    else if (m_daqSet.ch3_en)
    {
        bot_cursors = m_cursors3;
        bot = m_axis_ch3;
        m_axis_ch3->axis(QCPAxis::atBottom)->setTickLabels(true);
    }
    else if (m_daqSet.ch2_en)
    {
        bot_cursors = m_cursors2;
        bot = m_axis_ch2;
        m_axis_ch2->axis(QCPAxis::atBottom)->setTickLabels(true);
    }
    else if (m_daqSet.ch1_en)
    {
        bot_cursors = m_cursors1;
        bot = m_axis_ch1;
        m_axis_ch1->axis(QCPAxis::atBottom)->setTickLabels(true);
    }

    if (m_daqSet.ch1_en)
        top = m_axis_ch1;
    else if (m_daqSet.ch2_en)
        top = m_axis_ch2;
    else if (m_daqSet.ch3_en)
        top = m_axis_ch3;
    else if (m_daqSet.ch4_en)
        top = m_axis_ch4;

    top->setMinimumMargins(QMargins(25,15,15,0));
    bot->setMinimumMargins(QMargins(25,1,15,30));

    bot_cursors->showText(true);

    QStringList tokens = m_daqSet.fs_real.split('.', QString::SkipEmptyParts);

    if (tokens.size() > 1 && tokens[0].length() > 4)
        m_ui->textBrowser_realFs->setHtml("<p align=\"center\">" + tokens[0] + ". " + tokens[1] + "</p>");
    else
        m_ui->textBrowser_realFs->setHtml("<p align=\"center\">" + m_daqSet.fs_real + "</p>");

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

    m_ui->spinBox_mem->setValue(m_daqSet.mem);
    m_ui->dial_mem->setValue(m_daqSet.mem);

    m_ui->spinBox_fs->setValue(m_daqSet.fs);
    m_ui->dial_fs->setValue(m_daqSet.fs);

    m_ui->dial_trigPre->setValue(m_daqSet.trig_pre);
    m_ui->spinBox_trigPre->setValue(m_daqSet.trig_pre);

    if (!m_t.isEmpty())
    {
        m_cursorTrigPre1->setValue(m_daqSet.trig_pre, 0, 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigPre2->setValue(m_daqSet.trig_pre, 0, 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigPre3->setValue(m_daqSet.trig_pre, 0, 1, 0, m_t[m_t.size()-1]);
        m_cursorTrigPre4->setValue(m_daqSet.trig_pre, 0, 1, 0, m_t[m_t.size()-1]);
    }

    m_ui->horizontalSlider_trigPre->setValue(m_daqSet.trig_pre * 10.0);

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
    m_ui->radioButton_trigSlope_Both->setEnabled(trigEnabled);

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
    else if (m_daqSet.trig_edge == DaqTrigEdge::BOTH)
        m_ui->radioButton_trigSlope_Both->setChecked(true);
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

    on_radioButton_fsMem_clicked(m_ui->radioButton_fsMem->isChecked());

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
    //m_ui->dial_div->setRange(((1.0 / info->la_fs) * 2.0 * 1000000.0), 1000000);
    m_ui->dial_div->setValue(lin_to_exp_1to1M(div_sec * 1000000.0, true));
    m_ui->radioButton_div->setEnabled(true);

    bool trigCh1_en = m_ui->radioButton_trigCh_1->isEnabled();
    bool trigCh2_en = m_ui->radioButton_trigCh_2->isEnabled();
    bool trigCh3_en = m_ui->radioButton_trigCh_3->isEnabled();
    bool trigCh4_en = m_ui->radioButton_trigCh_4->isEnabled();

    if (m_refresh || m_last_trigEnabled != trigEnabled)
    {
        m_ui->radioButton_trigSlope_Rising->setStyleSheet(trigEnabled ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
        m_ui->radioButton_trigSlope_Falling->setStyleSheet(trigEnabled ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);
        m_ui->radioButton_trigSlope_Both->setStyleSheet(trigEnabled ? CSS_RADIOBUTTON_NODIS : CSS_RADIOBUTTON);

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

void WindowLa::enablePanel(bool en)
{
    m_ui->groupBox_main->setEnabled(en);
    m_ui->groupBox_trigger->setEnabled(en);
    m_ui->groupBox_horizontal->setEnabled(en);
    m_ui->groupBox_vertical->setEnabled(en);
}

void WindowLa::sendSet()
{
    auto info = Core::getInstance()->getDevInfo();

    m_msgPending = true;
    enablePanel(false);

    m_ui->radioButton_trigLed->setChecked(false);

    m_daqSet.bits = B1;
    m_daqSet.mem = m_ui->spinBox_mem->value();
    m_daqSet.fs = m_ui->spinBox_fs->value();
    m_daqSet.ch1_en = m_ui->pushButton_disable1->isVisible();
    m_daqSet.ch2_en = m_ui->pushButton_disable2->isVisible();
    m_daqSet.ch3_en = m_ui->pushButton_disable3->isVisible();
    m_daqSet.ch4_en = m_ui->pushButton_disable4->isVisible();

    if (m_ui->radioButton_trigCh_1->isChecked()) m_daqSet.trig_ch = 1;
    else if (m_ui->radioButton_trigCh_2->isChecked()) m_daqSet.trig_ch = 2;
    else if (m_ui->radioButton_trigCh_3->isChecked()) m_daqSet.trig_ch = 3;
    else m_daqSet.trig_ch = 4;

    m_daqSet.trig_val = 0;
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
    else if (m_ui->radioButton_trigSlope_Both->isChecked())
    {
        m_daqSet.trig_edge = BOTH;
        trigEdge = "B";
    }
    else
    {
        m_daqSet.trig_edge = FALLING;
        trigEdge = "F";
    }

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

    Core::getInstance()->msgAdd(m_msg_set, false, QString::number(m_daqSet.mem) + "," +       // mem
                                                  QString::number(m_daqSet.fs) + "," +        // fs
                                                  QString::number(m_daqSet.trig_ch) + "," +   // trig ch
                                                  trigEdge + "," +                            // trig edge
                                                  trigMode + "," +                            // trig mode
                                                  QString::number(m_daqSet.trig_pre));        // trig pre
}
