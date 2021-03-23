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
    m_msg_average = new Msg_SCOP_Average(this);
    m_msg_forceTrig = new Msg_SCOP_ForceTrig(this);

    connect(m_msg_set, &Msg_SCOP_Set::ok, this, &WindowScope::on_msg_ok, Qt::DirectConnection);
    connect(m_msg_set, &Msg_SCOP_Set::err, this, &WindowScope::on_msg_err, Qt::DirectConnection);
    connect(m_msg_set, &Msg_SCOP_Set::result, this, &WindowScope::on_msg_set, Qt::DirectConnection);

    connect(m_msg_read, &Msg_SCOP_Read::err, this, &WindowScope::on_msg_err, Qt::DirectConnection);
    connect(m_msg_read, &Msg_SCOP_Read::result, this, &WindowScope::on_msg_read, Qt::DirectConnection);

    connect(m_msg_average, &Msg_SCOP_Average::ok, this, &WindowScope::on_msg_ok, Qt::DirectConnection);
    connect(m_msg_average, &Msg_SCOP_Average::err, this, &WindowScope::on_msg_err, Qt::DirectConnection);

    connect(m_msg_forceTrig, &Msg_SCOP_ForceTrig::ok, this, &WindowScope::on_msg_ok, Qt::DirectConnection);
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

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(true);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(true);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(true);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(true);

    m_spline = true;

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

void WindowScope::on_msg_ok(const QString val1, const QString val2)
{

}

void WindowScope::on_msg_err(const QString text, MsgBoxType type, bool needClose)
{
    m_activeMsg = Q_NULLPTR;

    if (type == INFO)
        QMessageBox::information(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::NoButton);
    else if (type == QUESTION)
        QMessageBox::question(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::Yes | QMessageBox::No);
    else if (type == WARNING)
        QMessageBox::warning(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::NoButton);
    else if (type == CRITICAL)
        QMessageBox::critical(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::NoButton);

    if (needClose)
        this->close();
}

void WindowScope::on_msg_set()
{

}

void WindowScope::on_msg_read(const QByteArray data)
{
    int ch_num = 2;
    bool ch1_en = true;
    bool ch2_en = true;
    bool ch3_en = false;
    bool ch4_en = false;
    bool bit8 = false;

    const unsigned char *dataU8 = reinterpret_cast<const unsigned char*>(data.constData());

    int data_sz = data.size();
    int real_sz = data_sz;

    std::vector<qreal> buff(data_sz);

    if (bit8)
    {
        for (int i = 0; i < data_sz; i++)
            buff[i] = (((qreal)(dataU8[i]) / 100.0));
    }
    else
    {
        real_sz = data_sz / 2;
        buff.resize(real_sz);
        for (int i = 0, j = 0; i < data_sz; i += 2, j++)
        {
            buff[j] = (((qreal)(dataU8[i + 1] << 8 | dataU8[i]) / 10000.0));
        }

    }
    int ch_sz = real_sz / ch_num;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    for (int i = 0, k = 0; k < ch_num; k++)
    {
        for (int j = 1; j <= ch_sz; j++, i++) // plot from 1 to ch_sz
        {
            if (k == 0 && ch1_en)
                m_ui->customPlot->graph(GRAPH_CH1)->addData(j, buff[i]);
            else if (k == 1 && ch2_en)
                m_ui->customPlot->graph(GRAPH_CH2)->addData(j, buff[i]);
            else if (k == 2 && ch3_en)
                m_ui->customPlot->graph(GRAPH_CH3)->addData(j, buff[i]);
            else if (k == 3 && ch4_en)
                m_ui->customPlot->graph(GRAPH_CH4)->addData(j, buff[i]);
        }
    }

    m_old_range = m_ui->customPlot->yAxis->range();
    m_ui->customPlot->xAxis->setRange(1, ch_sz);
    m_ui->customPlot->yAxis->rescale();

    if (m_old_range != m_ui->customPlot->yAxis->range())
    {
        auto low_range = m_ui->customPlot->yAxis->range().lower;
        auto up_range = m_ui->customPlot->yAxis->range().upper;
        auto hysteris = (up_range - low_range) * 0.05;

        m_ui->customPlot->yAxis->setRange(low_range - hysteris,up_range + hysteris);
    }

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

void WindowScope::on_msg_daqReady(Ready ready)
{
    if (m_instrEnabled)
        Core::getInstance()->msgAdd(m_msg_read, true);
}

/* private */

void WindowScope::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
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
