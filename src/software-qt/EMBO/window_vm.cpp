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

    m_ui->customPlot->graph(GRAPH_CH1)->setPen(QPen(QColor(COLOR1)));
    m_ui->customPlot->graph(GRAPH_CH2)->setPen(QPen(QColor(COLOR2)));
    m_ui->customPlot->graph(GRAPH_CH3)->setPen(QPen(QColor(COLOR3)));
    m_ui->customPlot->graph(GRAPH_CH4)->setPen(QPen(QColor(COLOR4)));

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

    m_ui->customPlot->yAxis->setLabel("Voltage [V]");
    m_ui->customPlot->xAxis->setLabel("Time [s]");

    //m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(m_ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    /* statusbar */

    m_status_vcc = new QLabel(" ", this);
    QWidget* widget = new QWidget(this);
    QFont font1("Roboto", 11, QFont::Normal);
    m_status_vcc->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/resources/img/vm.png");

    status_img->setPixmap(status_img_icon);
    status_img->setFixedWidth(17);
    status_img->setFixedHeight(17);
    status_img->setScaledContents(true);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(status_img,0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_vcc,0,1,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);

    m_instrEnabled = true;
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
    m_data_ch1 = ch1.toDouble() * m_gain1;
    m_data_ch2 = ch2.toDouble() * m_gain2;
    m_data_ch3 = ch3.toDouble() * m_gain3;
    m_data_ch4 = ch4.toDouble() * m_gain4;
    m_data_vcc = vcc;

    m_data_fresh = true;
}

void WindowVm::on_timer_render()
{
    if (m_data_fresh && m_instrEnabled)
    {
        double ch1 = m_data_ch1;
        double ch2 = m_data_ch2;
        double ch3 = m_data_ch3;
        double ch4 = m_data_ch4;
        QString vcc = m_data_vcc;

        double key = (m_timer_elapsed.elapsed() - m_elapsed_diff) / 1000.0;

        QString ch1_s;
        QString ch2_s;
        QString ch3_s;
        QString ch4_s;
        ch1_s = ch1_s.asprintf(ch1 >= 100 ? "%.2f" : (ch1 >= 10 ? "%.3f" : "%.4f"), ch1);
        ch2_s = ch1_s.asprintf(ch2 >= 100 ? "%.2f" : (ch2 >= 10 ? "%.3f" : "%.4f"), ch2);
        ch3_s = ch1_s.asprintf(ch3 >= 100 ? "%.2f" : (ch3 >= 10 ? "%.3f" : "%.4f"), ch3);
        ch4_s = ch1_s.asprintf(ch4 >= 100 ? "%.2f" : (ch4 >= 10 ? "%.3f" : "%.4f"), ch4);

        m_ui->textBrowser_ch1->setHtml("<p align=\"center\">" + ch1_s + " V</p>");
        m_ui->textBrowser_ch2->setHtml("<p align=\"center\">" + ch2_s + " V</p>");
        m_ui->textBrowser_ch3->setHtml("<p align=\"center\">" + ch3_s + " V</p>");
        m_ui->textBrowser_ch4->setHtml("<p align=\"center\">" + ch4_s + " V</p>");
        m_status_vcc->setText(" Vcc: " + vcc + " V");

        m_ui->customPlot->graph(0)->addData(key, ch1);
        m_ui->customPlot->graph(1)->addData(key, ch2);
        m_ui->customPlot->graph(2)->addData(key, ch3);
        m_ui->customPlot->graph(3)->addData(key, ch4);

        double maxRng = m_gain1;
        if (m_gain2 > maxRng) maxRng = m_gain2;
        if (m_gain3 > maxRng) maxRng = m_gain3;
        if (m_gain4 > maxRng) maxRng = m_gain4;

        m_ui->customPlot->yAxis->setRange(-0.1, (maxRng * 3.3) + 0.1);
        m_ui->customPlot->xAxis->setRange(key, m_display, Qt::AlignRight);

        m_ui->customPlot->replot();

        m_data_fresh = false;
    }
}

void WindowVm::on_actionStart_triggered()
{
    // REC - TODO CLASS
}

void WindowVm::on_actionStop_triggered()
{
    // REC - TODO CLASS
}

void WindowVm::on_actionFolder_triggered()
{
    // REC - TODO CLASS
}

void WindowVm::on_actionCSV_triggered(bool checked)
{
    // REC - TODO CLASS
}

void WindowVm::on_actionTXT_Tabs_triggered(bool checked)
{
    // REC - TODO CLASS
}

void WindowVm::on_actionMAT_triggered(bool checked)
{
    // REC - TODO CLASS
}

void WindowVm::on_actionLines_triggered(bool checked)
{
    QCPGraph::LineStyle style = QCPGraph::lsNone;

    if (checked)
        style = QCPGraph::lsLine;

    m_ui->customPlot->graph(GRAPH_CH1)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setLineStyle(style);
}

void WindowVm::on_actionPoints_triggered(bool checked)
{
    QCPScatterStyle style = QCPScatterStyle(QCPScatterStyle::ssNone);

    if (checked)
        style = QCPScatterStyle(QCPScatterStyle::ssDisc, 5);

    m_ui->customPlot->graph(GRAPH_CH1)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setScatterStyle(style);
}

void WindowVm::on_actionSinc_triggered(bool checked)
{
    // TODO
}

void WindowVm::on_actionLinear_triggered(bool checked)
{
    // TODO
}

void WindowVm::on_pushButton_disable1_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH1)->setVisible(false);

    m_ui->pushButton_enable1->show();
    m_ui->pushButton_disable1->hide();
}

void WindowVm::on_pushButton_enable1_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH1)->setVisible(true);

    m_ui->pushButton_enable1->hide();
    m_ui->pushButton_disable1->show();
}

void WindowVm::on_pushButton_disable2_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH2)->setVisible(false);

    m_ui->pushButton_enable2->show();
    m_ui->pushButton_disable2->hide();
}

void WindowVm::on_pushButton_enable2_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH2)->setVisible(true);

    m_ui->pushButton_enable2->hide();
    m_ui->pushButton_disable2->show();
}

void WindowVm::on_pushButton_disable3_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH3)->setVisible(false);

    m_ui->pushButton_enable3->show();
    m_ui->pushButton_disable3->hide();
}

void WindowVm::on_pushButton_enable3_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH3)->setVisible(true);

    m_ui->pushButton_enable3->hide();
    m_ui->pushButton_disable3->show();
}

void WindowVm::on_pushButton_disable4_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH4)->setVisible(false);

    m_ui->pushButton_enable4->show();
    m_ui->pushButton_disable4->hide();
}

void WindowVm::on_pushButton_enable4_clicked()
{
    m_ui->customPlot->graph(GRAPH_CH4)->setVisible(true);

    m_ui->pushButton_enable4->hide();
    m_ui->pushButton_disable4->show();
}

void WindowVm::on_doubleSpinBox_gain1_valueChanged(double arg1)
{
    m_gain1 = arg1;
}

void WindowVm::on_doubleSpinBox_gain2_valueChanged(double arg1)
{
    m_gain2 = arg1;
}

void WindowVm::on_doubleSpinBox_gain3_valueChanged(double arg1)
{
    m_gain3 = arg1;
}

void WindowVm::on_doubleSpinBox_gain4_valueChanged(double arg1)
{
    m_gain4 = arg1;
}

void WindowVm::on_pushButton_disable_clicked()
{
    m_instrEnabled = false;
    m_elapsed_saved = m_timer_elapsed.elapsed();

    m_ui->pushButton_enable->show();
    m_ui->pushButton_disable->hide();
}

void WindowVm::on_pushButton_enable_clicked()
{
    m_instrEnabled = true;
    m_elapsed_diff += m_timer_elapsed.elapsed() - m_elapsed_saved;

    m_ui->pushButton_enable->hide();
    m_ui->pushButton_disable->show();
}

void WindowVm::on_spinBox_average_valueChanged(int arg1)
{
    m_ui->dial_average->setValue(arg1);
    m_average = arg1;
    m_msg_read->setParams(QString::number(m_average));
}

void WindowVm::on_dial_average_valueChanged(int value)
{
    m_ui->spinBox_average->setValue(value);
}

void WindowVm::on_spinBox_display_valueChanged(int arg1)
{
    m_ui->dial_display->setValue(arg1);
    m_display = (double)arg1 / (double)TIMER_VM_RENDER;
}

void WindowVm::on_dial_display_valueChanged(int value)
{
    m_ui->spinBox_display->setValue(value);
}

void WindowVm::on_actionMax_triggered(bool checked)
{
    // TODO - measure
}

void WindowVm::on_actionMin_triggered(bool checked)
{
    // TODO - measure
}

void WindowVm::on_actionAverage_triggered(bool checked)
{
    // TODO - measure
}

void WindowVm::on_actionReset_triggered()
{
    // TODO - measure
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
        m_ui->label_ch1->setText("Channel 1 (pin " + pins[0].trimmed() + ")");
        m_ui->label_ch2->setText("Channel 2 (pin " + pins[1].trimmed() + ")");
        m_ui->label_ch3->setText("Channel 3 (pin " + pins[2].trimmed() + ")");
        m_ui->label_ch4->setText("Channel 4 (pin " + pins[3].trimmed() + ")");
    }

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    m_activeMsg = m_msg_read;

    m_timer_elapsed.restart();
    m_timer_render->start(TIMER_VM_RENDER);
}

