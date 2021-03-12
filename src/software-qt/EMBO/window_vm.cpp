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

    m_timer_render = new QTimer(this);
    m_msg_read = new Msg_VM_Read(this);

    connect(m_msg_read, &Msg_VM_Read::err, this, &WindowVm::on_msg_err, Qt::DirectConnection);
    connect(m_msg_read, &Msg_VM_Read::result, this, &WindowVm::on_msg_read, Qt::DirectConnection);

    connect(m_timer_render, &QTimer::timeout, this, &WindowVm::on_timer_render);

    m_ui->customPlot->addGraph();
    m_ui->customPlot->addGraph();
    m_ui->customPlot->addGraph();
    m_ui->customPlot->addGraph();

    m_ui->customPlot->graph(0)->setPen(QPen(QColor(COLOR1)));
    m_ui->customPlot->graph(1)->setPen(QPen(QColor(COLOR2)));
    m_ui->customPlot->graph(2)->setPen(QPen(QColor(COLOR3)));
    m_ui->customPlot->graph(3)->setPen(QPen(QColor(COLOR4)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s.%z");
    m_ui->customPlot->xAxis->setTicker(timeTicker);
    m_ui->customPlot->axisRect()->setupFullAxesBox();

    m_ui->customPlot->xAxis->setVisible(true);
    m_ui->customPlot->xAxis->setTickLabels(true);
    m_ui->customPlot->yAxis->setVisible(true);
    m_ui->customPlot->yAxis->setTickLabels(true);

    m_ui->customPlot->xAxis2->setVisible(true);
    m_ui->customPlot->xAxis2->setTickLabels(true);
    m_ui->customPlot->yAxis2->setVisible(true);
    m_ui->customPlot->yAxis2->setTickLabels(true);

    m_ui->customPlot->yAxis->setRange(0, 3.4);
    m_ui->customPlot->yAxis->setLabel("Voltage [V]");
    m_ui->customPlot->xAxis->setLabel("Time [s]");

    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(m_ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
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

void WindowVm::on_msg_err(const QString text, MsgBoxType type, bool needClose)
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

void WindowVm::on_msg_read(const QString ch1, const QString ch2, const QString ch3, const QString ch4, const QString vcc)
{
    m_data_ch1 = ch1;
    m_data_ch2 = ch2;
    m_data_ch3 = ch3;
    m_data_ch4 = ch4;
    m_data_vcc = vcc;

    m_data_fresh = true;
}

void WindowVm::on_timer_render()
{
    if (!m_data_fresh)
        return;

    QString ch1 = m_data_ch1;
    QString ch2 = m_data_ch2;
    QString ch3 = m_data_ch3;
    QString ch4 = m_data_ch4;
    QString vcc = m_data_vcc;

    double key = m_timer_elapsed.elapsed() / 1000.0;

    m_ui->textBrowser_ch1->setText(ch1 + " V");
    m_ui->textBrowser_ch2->setText(ch2 + " V");
    m_ui->textBrowser_ch3->setText(ch3 + " V");
    m_ui->textBrowser_ch4->setText(ch4 + " V");

    m_ui->customPlot->graph(0)->addData(key, ch1.toDouble());
    m_ui->customPlot->graph(1)->addData(key, ch2.toDouble());
    m_ui->customPlot->graph(2)->addData(key, ch3.toDouble());
    m_ui->customPlot->graph(3)->addData(key, ch4.toDouble());

    //m_ui->customPlot->graph(0)->rescaleAxes();
    //m_ui->customPlot->graph(1)->rescaleAxes();
    //m_ui->customPlot->graph(2)->rescaleAxes();
    //m_ui->customPlot->graph(3)->rescaleAxes();

    m_ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    m_ui->customPlot->replot();

    //m_ui->customPlot->graph(0)->data()->size();

    m_data_fresh = false;
}

/* private */

void WindowVm::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;
    emit closing(WindowVm::staticMetaObject.className());

    m_timer_render->stop();
}

void WindowVm::showEvent(QShowEvent*)
{
    auto core = Core::getInstance()->getDevInfo();
    QStringList pins = core->pins_scope_vm.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (pins.size() == 4)
    {
        m_ui->groupBox_ch1->setTitle("Channel 1 (pin " + pins[0].trimmed() + ")");
        m_ui->groupBox_ch2->setTitle("Channel 2 (pin " + pins[1].trimmed() + ")");
        m_ui->groupBox_ch3->setTitle("Channel 3 (pin " + pins[2].trimmed() + ")");
        m_ui->groupBox_ch4->setTitle("Channel 4 (pin " + pins[3].trimmed() + ")");
    }

    m_ui->customPlot->graph(0)->data()->clear();
    m_ui->customPlot->graph(1)->data()->clear();
    m_ui->customPlot->graph(2)->data()->clear();
    m_ui->customPlot->graph(3)->data()->clear();

    m_activeMsg = m_msg_read;

    m_timer_elapsed.restart();
    m_timer_render->start(TIMER_VM_RENDER);
}

