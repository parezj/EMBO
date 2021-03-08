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

#include <QDebug>
#include <QLabel>
#include <QMessageBox>


WindowVm::WindowVm(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowVm)
{
    m_ui->setupUi(this);



    // add two new graphs and set their look:
    m_ui->customPlot->addGraph();
    m_ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    m_ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    m_ui->customPlot->addGraph();
    m_ui->customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i)
    {
      x[i] = i;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
      y1[i] = qExp(-i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_ui->customPlot->xAxis2->setVisible(true);
    m_ui->customPlot->xAxis2->setTickLabels(false);
    m_ui->customPlot->yAxis2->setVisible(true);
    m_ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(m_ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    m_ui->customPlot->graph(0)->setData(x, y0);
    m_ui->customPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    m_ui->customPlot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    m_ui->customPlot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

WindowVm::~WindowVm()
{
    delete m_ui;
}

void WindowVm::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/* slots */

void WindowVm::on_msg_err(QString text, MsgBoxType type, bool needClose)
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

/* private */

void WindowVm::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
    emit closing(WindowVm::staticMetaObject.className());
}

void WindowVm::showEvent(QShowEvent*)
{
    //m_msg_enable->setIsQuery(true);
    //Core::getInstance()->msgAdd(m_msg_enable);
}
