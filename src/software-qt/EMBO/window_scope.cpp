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

    m_ui->customPlot->addGraph();
    m_ui->customPlot->addGraph();
    m_ui->customPlot->addGraph();
    m_ui->customPlot->addGraph();

    m_ui->customPlot->addGraph();
    m_ui->customPlot->addGraph();
    m_ui->customPlot->addGraph();
    m_ui->customPlot->addGraph();

    m_ui->customPlot->graph(GRAPH_CH1)->setPen(QPen(QColor(COLOR1)));
    m_ui->customPlot->graph(GRAPH_CH2)->setPen(QPen(QColor(COLOR2)));
    m_ui->customPlot->graph(GRAPH_CH3)->setPen(QPen(QColor(COLOR3)));
    m_ui->customPlot->graph(GRAPH_CH4)->setPen(QPen(QColor(COLOR4)));

    m_ui->customPlot->graph(GRAPH_CH1_SPLINE)->setPen(QPen(QColor(COLOR1)));
    m_ui->customPlot->graph(GRAPH_CH2_SPLINE)->setPen(QPen(QColor(COLOR2)));
    m_ui->customPlot->graph(GRAPH_CH3_SPLINE)->setPen(QPen(QColor(COLOR3)));
    m_ui->customPlot->graph(GRAPH_CH4_SPLINE)->setPen(QPen(QColor(COLOR4)));

    m_ui->customPlot->graph(GRAPH_CH1_SPLINE)->setVisible(false);
    m_ui->customPlot->graph(GRAPH_CH2_SPLINE)->setVisible(false);
    m_ui->customPlot->graph(GRAPH_CH3_SPLINE)->setVisible(false);
    m_ui->customPlot->graph(GRAPH_CH4_SPLINE)->setVisible(false);

    m_ui->customPlot->xAxis->setVisible(true);
    m_ui->customPlot->xAxis->setTickLabels(true);
    m_ui->customPlot->yAxis->setVisible(true);
    m_ui->customPlot->yAxis->setTickLabels(true);

    //m_ui->customPlot->xAxis2->setVisible(true);
    //m_ui->customPlot->xAxis2->setTickLabels(true);
    //m_ui->customPlot->yAxis2->setVisible(true);
    //m_ui->customPlot->yAxis2->setTickLabels(true);

    m_ui->customPlot->yAxis->setLabel("Voltage [V]");
    m_ui->customPlot->xAxis->setLabel("Time [s]");

    QFont font2("Roboto", 12, QFont::Normal);
    m_ui->customPlot->xAxis->setTickLabelFont(font2);
    m_ui->customPlot->yAxis->setTickLabelFont(font2);
    m_ui->customPlot->xAxis->setLabelFont(font2);
    m_ui->customPlot->yAxis->setLabelFont(font2);

    //m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(m_ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    /* statusbar */

    /* styles */
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

void WindowScope::on_msg_read(const QString data)
{
    // PLOT DATA
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
