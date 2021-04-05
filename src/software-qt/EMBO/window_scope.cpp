/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_scope.h"
#include "ui_window_scope.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>


WindowScope::WindowScope(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowScope)
{
    m_ui->setupUi(this);

    m_msg_set = new Msg_SCOP_Set(this);
    m_msg_read = new Msg_SCOP_Read(this);
    m_msg_forceTrig = new Msg_SCOP_ForceTrig(this);

    connect(m_msg_set, &Msg_SCOP_Set::ok, this, &WindowScope::on_msg_ok_set, Qt::DirectConnection);
    connect(m_msg_set, &Msg_SCOP_Set::err, this, &WindowScope::on_msg_err, Qt::DirectConnection);
    connect(m_msg_set, &Msg_SCOP_Set::result, this, &WindowScope::on_msg_set, Qt::DirectConnection);

    connect(m_msg_read, &Msg_SCOP_Read::err, this, &WindowScope::on_msg_err, Qt::DirectConnection);
    connect(m_msg_read, &Msg_SCOP_Read::result, this, &WindowScope::on_msg_read, Qt::DirectConnection);

    connect(m_msg_forceTrig, &Msg_SCOP_ForceTrig::ok, this, &WindowScope::on_msg_ok_forceTrig, Qt::DirectConnection);
    connect(m_msg_forceTrig, &Msg_SCOP_ForceTrig::err, this, &WindowScope::on_msg_err, Qt::DirectConnection);

    connect(Core::getInstance(), &Core::daqReady, this, &WindowScope::on_msg_daqReady, Qt::QueuedConnection);

    /* QCP */

    initQcp();

    /* statusbar */

    /* styles */
}
void WindowScope::initQcp()
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

WindowScope::~WindowScope()
{
    delete m_ui;
}

void WindowScope::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/* slots */

void WindowScope::on_msg_err(const QString text, MsgBoxType type, bool needClose)
{
    m_activeMsgs.clear();

    if (needClose)
        this->close();

    msgBox(this, text, type);
}

void WindowScope::on_msg_ok_set(const QString maxZ, const QString fs_real)
{
    m_daqSet.maxZ_kohm = maxZ.toDouble();
    m_daqSet.fs_real = fs_real.toDouble();
}

void WindowScope::on_msg_set(DaqBits bits, int mem, int fs, bool ch1, bool ch2, bool ch3, bool ch4, int trig_ch, int trig_val,
                             DaqTrigEdge trig_edge, DaqTrigMode trig_mode, int trig_pre, double maxZ, double fs_real)
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
    m_daqSet.maxZ_kohm = maxZ;
    m_daqSet.fs_real = fs_real;
}

void WindowScope::on_msg_read(const QByteArray data)
{
    int ch_num = m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en;
    const unsigned char *dataU8 = reinterpret_cast<const unsigned char*>(data.constData());

    int data_sz = data.size();
    int real_sz = data_sz;

    std::vector<qreal> buff(data_sz);

    if (m_daqSet.bits == B8)
    {
        for (int i = 0; i < data_sz; i++)
            buff[i] = (((qreal)(dataU8[i]) / 100.0));
    }
    else
    {
        real_sz = data_sz / 2;
        buff.resize(real_sz);
        for (int i = 0, j = 0; i < data_sz; i += 2, j++)
            buff[j] = (((qreal)(dataU8[i + 1] << 8 | dataU8[i]) / 10000.0));
    }
    int ch_sz = real_sz / ch_num;

    if (ch_sz != m_daqSet.mem) // wrong data size
    {
        on_msg_err(INVALID_MSG, CRITICAL, true);
        return;
    }

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    for (int i = 0, k = 0; k < ch_num; k++)
    {
        for (int j = 1; j <= ch_sz; j++, i++) // plot from 1 to ch_sz
        {
            if (k == 0 && m_daqSet.ch1_en)
                m_ui->customPlot->graph(GRAPH_CH1)->addData(j, buff[i]);
            else if (k == 1 && m_daqSet.ch2_en)
                m_ui->customPlot->graph(GRAPH_CH2)->addData(j, buff[i]);
            else if (k == 2 && m_daqSet.ch3_en)
                m_ui->customPlot->graph(GRAPH_CH3)->addData(j, buff[i]);
            else if (k == 3 && m_daqSet.ch4_en)
                m_ui->customPlot->graph(GRAPH_CH4)->addData(j, buff[i]);
        }
    }

    m_old_range = m_ui->customPlot->yAxis->range();
    m_ui->customPlot->xAxis->setRange(1, ch_sz);
    m_ui->customPlot->yAxis->setRange(-0.1, 3.4);

    /*
    m_ui->customPlot->yAxis->rescale();

    if (m_old_range != m_ui->customPlot->yAxis->range())
    {
        auto low_range = m_ui->customPlot->yAxis->range().lower;
        auto up_range = m_ui->customPlot->yAxis->range().upper;
        auto hysteris = (up_range - low_range) * 0.05;

        m_ui->customPlot->yAxis->setRange(low_range - hysteris,up_range + hysteris);
    }
    */

    /*
    if (m_cursorsV_en || m_cursorsH_en)
    {
        auto rngV = m_ui->customPlot->yAxis->range();
        auto rngH = m_ui->customPlot->xAxis->range();

        m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, true);
    }
    */

    m_ui->customPlot->replot();
}

void WindowScope::on_msg_ok_forceTrig(const QString, const QString)
{

}

void WindowScope::on_msg_daqReady(Ready ready)
{
    if (m_instrEnabled)
        Core::getInstance()->msgAdd(m_msg_read, true);
}

/* private */

void WindowScope::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();
    m_instrEnabled = false;

    Core::getInstance()->setMode(NO_MODE);
    emit closing(WindowScope::staticMetaObject.className());
}

void WindowScope::showEvent(QShowEvent*)
{
    Core::getInstance()->setMode(SCOPE);
    m_instrEnabled = true;

    Core::getInstance()->msgAdd(m_msg_set, true, "");
}
