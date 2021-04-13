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

#define Y_LIM           0.20

WindowLa::WindowLa(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowLa)
{
    m_ui->setupUi(this);

    m_msg_set = new Msg_LA_Set(this);
    m_msg_read = new Msg_LA_Read(this);
    m_msg_forceTrig = new Msg_LA_ForceTrig(this);

    connect(m_msg_set, &Msg_LA_Set::ok, this, &WindowLa::on_msg_ok_set, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_LA_Set::err, this, &WindowLa::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_LA_Set::result, this, &WindowLa::on_msg_set, Qt::QueuedConnection);

    connect(m_msg_read, &Msg_LA_Read::err, this, &WindowLa::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read, &Msg_LA_Read::result, this, &WindowLa::on_msg_read, Qt::QueuedConnection);

    connect(m_msg_forceTrig, &Msg_LA_ForceTrig::ok, this, &WindowLa::on_msg_ok_forceTrig, Qt::QueuedConnection);
    connect(m_msg_forceTrig, &Msg_LA_ForceTrig::err, this, &WindowLa::on_msg_err, Qt::QueuedConnection);

    connect(Core::getInstance(), &Core::daqReady, this, &WindowLa::on_msg_daqReady, Qt::QueuedConnection);

    /* QCP */

    initQcp();

    /* statusbar */

    /* styles */
}

void WindowLa::initQcp()
{
    m_ui->customPlot->addGraph();  // ch1
    m_ui->customPlot->addGraph();  // ch2
    m_ui->customPlot->addGraph();  // ch3
    m_ui->customPlot->addGraph();  // ch4

    m_ui->customPlot->graph(GRAPH_CH1)->setPen(QPen(QColor(COLOR1)));
    m_ui->customPlot->graph(GRAPH_CH2)->setPen(QPen(QColor(COLOR2)));
    m_ui->customPlot->graph(GRAPH_CH3)->setPen(QPen(QColor(COLOR5)));
    m_ui->customPlot->graph(GRAPH_CH4)->setPen(QPen(QColor(COLOR4)));

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(false);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(false);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(false);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(false);

    m_ui->customPlot->axisRect()->setMinimumMargins(QMargins(45,15,15,30));

    m_timeTicker = QSharedPointer<QCPAxisTickerTime>(new QCPAxisTickerTime);
    m_timeTicker->setTimeFormat("%s s");
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuSeconds, 1);
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuMilliseconds, 1);
    m_ui->customPlot->xAxis->setTicker(m_timeTicker);
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

    //m_ui->customPlot->setInteractions(0);
    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    connect(m_ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(on_qcpMouseWheel(QWheelEvent*)));
    connect(m_ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(on_qcpMousePress(QMouseEvent*)));

    /* cursors */

    /*
    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorV->setValues(m_cursorV_min, m_cursorV_max);

    m_ui->horizontalSlider_cursorH->hide();
    m_ui->horizontalSlider_cursorV->hide();

    connect(this, &WindowVm::on_cursorH_valuesChanged, m_ui->horizontalSlider_cursorH, &ctkRangeSlider::valuesChanged);
    connect(this, &WindowVm::on_cursorV_valuesChanged, m_ui->horizontalSlider_cursorV, &ctkRangeSlider::valuesChanged);
    */

    m_cursors = new QCPCursors(this, m_ui->customPlot, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursorTrigVal = new QCPCursor(this, m_ui->customPlot, true);
    m_cursorTrigPre = new QCPCursor(this, m_ui->customPlot, false);
}

WindowLa::~WindowLa()
{
    delete m_ui;
}

void WindowLa::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/* slots */

void WindowLa::on_msg_err(const QString text, MsgBoxType type, bool needClose)
{
    m_activeMsgs.clear();

    if (needClose)
        this->close();

    msgBox(this, text, type);
}

void WindowLa::on_msg_ok_set(const QString fs_real, const QString)
{
    m_daqSet.fs_real = fs_real.toDouble();
}

void WindowLa::on_msg_set(int mem, int fs, int trig_ch, DaqTrigEdge trig_edge, DaqTrigMode trig_mode, int trig_pre, double fs_real)
{
    m_daqSet.bits = B1;
    m_daqSet.mem = mem;
    m_daqSet.fs = fs;
    m_daqSet.ch1_en = true;
    m_daqSet.ch2_en = true;
    m_daqSet.ch3_en = true;
    m_daqSet.ch4_en = true;
    m_daqSet.trig_ch = trig_ch;
    m_daqSet.trig_val = 0;
    m_daqSet.trig_edge = trig_edge;
    m_daqSet.trig_mode = trig_mode;
    m_daqSet.trig_pre = trig_pre;
    m_daqSet.maxZ_kohm = 0;
    m_daqSet.fs_real = fs_real;
}

void WindowLa::on_msg_read(const QByteArray data)
{
    bool ch1_en = true;
    bool ch2_en = true;
    bool ch3_en = true;
    bool ch4_en = true;

    m_ui->customPlot->graph(GRAPH_CH1)->setVisible(ch2_en);
    m_ui->customPlot->graph(GRAPH_CH2)->setVisible(ch2_en);
    m_ui->customPlot->graph(GRAPH_CH3)->setVisible(ch3_en);
    m_ui->customPlot->graph(GRAPH_CH4)->setVisible(ch4_en);

    auto info = Core::getInstance()->getDevInfo();
    int data_sz = data.size();

    if (data_sz != m_daqSet.mem + (info->daq_reserve * 1)) // wrong data size
    {
        on_msg_err(INVALID_MSG, CRITICAL, true);
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
        bool ch3 = (data[i] & (1 << info->la_ch3_pin)) != 0;
        bool ch4 = (data[i] & (1 << info->la_ch4_pin)) != 0;

        if (ch1_en) y1[k] = ch1 ? 1.0 : 0.0;
        if (ch2_en) y2[k] = ch2 ? 1.0 : 0.0;
        if (ch3_en) y3[k] = ch3 ? 1.0 : 0.0;
        if (ch4_en) y4[k] = ch4 ? 1.0 : 0.0;
    }

    double x = 0;
    double dt = 1.0 / m_daqSet.fs_real;
    QVector<double> t(m_daqSet.mem); // TODO move somewhere ELSE !
    for (int i = 0; i < m_daqSet.mem; i++)
    {
        t[i] = x;
        x += dt;
    }

    m_t_last = t[t.size()-1];

    if (m_t_last < 1)
        m_timeTicker->setTimeFormat("%z ms");

    if (m_daqSet.ch1_en)
        m_ui->customPlot->graph(GRAPH_CH1)->setData(t, y1);
    if (m_daqSet.ch2_en)
        m_ui->customPlot->graph(GRAPH_CH2)->setData(t, y2);
    if (m_daqSet.ch3_en)
        m_ui->customPlot->graph(GRAPH_CH3)->setData(t, y3);
    if (m_daqSet.ch4_en)
        m_ui->customPlot->graph(GRAPH_CH4)->setData(t, y4);

    rescaleXAxis();
    rescaleYAxis();

    m_ui->customPlot->replot();
}

void WindowLa::on_msg_ok_forceTrig(const QString, const QString)
{

}

void WindowLa::on_msg_daqReady(Ready ready, int firstPos)
{
    m_firstPos = firstPos;

    if (m_instrEnabled)
        Core::getInstance()->msgAdd(m_msg_read, true);
}

void WindowLa::on_qcpMouseWheel(QWheelEvent*)
{
    //m_ui->pushButton_reset->hide();
    //m_ui->pushButton_resetZoom->show();
}

void WindowLa::on_qcpMousePress(QMouseEvent*)
{
    //m_ui->pushButton_reset->hide();
    //m_ui->pushButton_resetZoom->show();
}

/* private */

void WindowLa::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();
    m_instrEnabled = false;

    Core::getInstance()->setMode(NO_MODE);
    emit closing(WindowLa::staticMetaObject.className());
}

void WindowLa::showEvent(QShowEvent*)
{
    Core::getInstance()->setMode(LA);
    m_instrEnabled = true;

    Core::getInstance()->msgAdd(m_msg_set, true, "");
}

void WindowLa::rescaleYAxis()
{
    m_ui->customPlot->yAxis->setRange(0 - Y_LIM , 1 + Y_LIM);
}

void WindowLa::rescaleXAxis()
{
    m_ui->customPlot->xAxis->setRange(0, m_t_last);
}
