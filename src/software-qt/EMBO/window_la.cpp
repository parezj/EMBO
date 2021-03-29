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


WindowLa::WindowLa(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowLa)
{
    m_ui->setupUi(this);

    m_msg_set = new Msg_LA_Set(this);
    m_msg_read = new Msg_LA_Read(this);
    m_msg_forceTrig = new Msg_LA_ForceTrig(this);

    connect(m_msg_set, &Msg_LA_Set::ok, this, &WindowLa::on_msg_ok_set, Qt::DirectConnection);
    connect(m_msg_set, &Msg_LA_Set::err, this, &WindowLa::on_msg_err, Qt::DirectConnection);
    connect(m_msg_set, &Msg_LA_Set::result, this, &WindowLa::on_msg_set, Qt::DirectConnection);

    connect(m_msg_read, &Msg_LA_Read::err, this, &WindowLa::on_msg_err, Qt::DirectConnection);
    connect(m_msg_read, &Msg_LA_Read::result, this, &WindowLa::on_msg_read, Qt::DirectConnection);

    connect(m_msg_forceTrig, &Msg_LA_ForceTrig::ok, this, &WindowLa::on_msg_ok_forceTrig, Qt::DirectConnection);
    connect(m_msg_forceTrig, &Msg_LA_ForceTrig::err, this, &WindowLa::on_msg_err, Qt::DirectConnection);

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

    m_ui->customPlot->xAxis->setVisible(true);
    m_ui->customPlot->xAxis->setTickLabels(true);
    m_ui->customPlot->yAxis->setVisible(true);
    m_ui->customPlot->yAxis->setTickLabels(true);

    QFont font2("Roboto", 12, QFont::Normal);
    m_ui->customPlot->xAxis->setTickLabelFont(font2);
    m_ui->customPlot->yAxis->setTickLabelFont(font2);
    m_ui->customPlot->xAxis->setLabelFont(font2);
    m_ui->customPlot->yAxis->setLabelFont(font2);

    m_ui->customPlot->setInteractions(0);
    //m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(m_ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

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
    m_activeMsg = Q_NULLPTR;

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

    int data_sz = data.size();

    if (data_sz != m_daqSet.mem) // wrong data size
    {
        on_msg_err(INVALID_MSG, CRITICAL, true);
        return;
    }

    std::vector<qreal> buff(data_sz);

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    for (int i = 0; i < data_sz; i++)
    {
        bool ch1 = (data[i] & 2) != 0;
        bool ch2 = (data[i] & 4) != 0;
        bool ch3 = (data[i] & 8) != 0;
        bool ch4 = (data[i] & 16) != 0;

        if (ch1_en)
            m_ui->customPlot->graph(GRAPH_CH1)->addData(i, (qreal)ch1);
        if (ch2_en)
            m_ui->customPlot->graph(GRAPH_CH2)->addData(i, (qreal)ch2);
        if (ch3_en)
            m_ui->customPlot->graph(GRAPH_CH3)->addData(i, (qreal)ch3);
        if (ch4_en)
            m_ui->customPlot->graph(GRAPH_CH4)->addData(i, (qreal)ch4);
    }

    //m_ui->customPlot->graph(GRAPH_CH1)->rescaleValueAxis(false);
    //m_ui->customPlot->graph(GRAPH_CH2)->rescaleValueAxis(false);
    //m_ui->customPlot->graph(GRAPH_CH3)->rescaleValueAxis(false);
    //m_ui->customPlot->graph(GRAPH_CH4)->rescaleValueAxis(false);

    //m_ui->customPlot->yAxis->setRange(-LIM_OFFSET, (maxRng * 3.3) + LIM_OFFSET);
    m_ui->customPlot->yAxis->setRange(-0.1, 1.1);
    m_ui->customPlot->xAxis->setRange(0, data_sz);

    m_ui->customPlot->replot();
}

void WindowLa::on_msg_ok_forceTrig(const QString, const QString)
{

}

void WindowLa::on_msg_daqReady(Ready ready)
{
    if (m_instrEnabled)
        Core::getInstance()->msgAdd(m_msg_read, true);
}

/* private */

void WindowLa::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
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
