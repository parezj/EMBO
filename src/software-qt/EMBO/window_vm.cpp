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
#include "lib/ctkrangeslider.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>


WindowVm::WindowVm(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowVm)
{
    m_ui->setupUi(this);

    m_timer_render = new QTimer(this);
    m_timer_render->setTimerType(Qt::PreciseTimer);

    m_msg_read = new Msg_VM_Read(this);

    connect(m_msg_read, &Msg_VM_Read::err, this, &WindowVm::on_msg_err, Qt::DirectConnection);
    connect(m_msg_read, &Msg_VM_Read::result, this, &WindowVm::on_msg_read, Qt::DirectConnection);

    connect(m_timer_render, &QTimer::timeout, this, &WindowVm::on_timer_render);

    m_ui->dial_display->setValue(DISPLAY_DEFAULT);
    m_ui->horizontalSlider_trigPre->setVisible(false);
    m_ui->horizontalSlider_trigVal->setVisible(false);

    /* QCP */

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

    m_ui->customPlot->axisRect()->setMinimumMargins(QMargins(45,15,15,15));

    m_spline = true;

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    m_ui->customPlot->xAxis->setTicker(timeTicker);
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

    m_ui->customPlot->setInteractions(0);

    connect(m_ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    /* cursors */

    m_ui->horizontalSlider_cursorH->hide();
    m_ui->horizontalSlider_cursorV->hide();

    connect(m_ui->horizontalSlider_cursorH, &ctkRangeSlider::valuesChanged, this, &WindowVm::on_cursorH_valuesChanged);
    connect(m_ui->horizontalSlider_cursorV, &ctkRangeSlider::valuesChanged, this, &WindowVm::on_cursorV_valuesChanged);

    m_cursors = new QCPCursors(this, m_ui->customPlot, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));

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

    /* styles */

    QString style1(CSS_BUTTON_ONOFF);

    m_ui->pushButton_enable->setStyleSheet(style1);
    m_ui->pushButton_disable->setStyleSheet(style1);
    m_ui->pushButton_enable1->setStyleSheet(style1);
    m_ui->pushButton_disable1->setStyleSheet(style1);
    m_ui->pushButton_enable2->setStyleSheet(style1);
    m_ui->pushButton_disable2->setStyleSheet(style1);
    m_ui->pushButton_enable3->setStyleSheet(style1);
    m_ui->pushButton_disable3->setStyleSheet(style1);
    m_ui->pushButton_enable4->setStyleSheet(style1);
    m_ui->pushButton_disable4->setStyleSheet(style1);

    QString style2(CSS_SPINBOX);

    m_ui->spinBox_average->setStyleSheet(style2);
    m_ui->spinBox_display->setStyleSheet(style2);

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
    if (m_instrEnabled && m_activeMsg != Q_NULLPTR)
    {
        double t = (m_timer_elapsed.elapsed() - m_elapsed_diff) / 1000.0;

        m_data_ch1 = ch1.toDouble() * m_gain1;
        m_data_ch2 = ch2.toDouble() * m_gain2;
        m_data_ch3 = ch3.toDouble() * m_gain3;
        m_data_ch4 = ch4.toDouble() * m_gain4;

        m_data_vcc = vcc;
        m_data_vcc = m_data_vcc.replace(".", "").left(4);

        int vcc_n = m_data_vcc.toInt();
        m_vref = (double)vcc_n / 1000.0;
        Core::getInstance()->getDevInfo()->ref_mv = vcc_n;

        m_smplBuff.push_back(VmSample {t, m_data_ch1, m_data_ch2, m_data_ch3, m_data_ch4});

        m_data_fresh = true;

        if (m_meas_ch == GRAPH_CH1)
        {
            if (m_data_ch1 > m_meas_max) m_meas_max = m_data_ch1;
            if (m_data_ch1 < m_meas_min) m_meas_min = m_data_ch1;
        }
        if (m_meas_ch == GRAPH_CH2)
        {
            if (m_data_ch2 > m_meas_max) m_meas_max = m_data_ch2;
            if (m_data_ch2 < m_meas_min) m_meas_min = m_data_ch2;
        }
        if (m_meas_ch == GRAPH_CH3)
        {
            if (m_data_ch3 > m_meas_max) m_meas_max = m_data_ch3;
            if (m_data_ch3 < m_meas_min) m_meas_min = m_data_ch3;
        }
        if (m_meas_ch == GRAPH_CH4)
        {
            if (m_data_ch4 > m_meas_max) m_meas_max = m_data_ch4;
            if (m_data_ch4 < m_meas_min) m_meas_min = m_data_ch4;
        }
    }
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
        QString ch1_s;
        QString ch2_s;
        QString ch3_s;
        QString ch4_s;

        ch1_s = ch1_s.asprintf(ch1 >= 100 ? "%.2f" : (ch1 >= 10 ? "%.3f" : "%.4f"), ch1);
        ch2_s = ch1_s.asprintf(ch2 >= 100 ? "%.2f" : (ch2 >= 10 ? "%.3f" : "%.4f"), ch2);
        ch3_s = ch1_s.asprintf(ch3 >= 100 ? "%.2f" : (ch3 >= 10 ? "%.3f" : "%.4f"), ch3);
        ch4_s = ch1_s.asprintf(ch4 >= 100 ? "%.2f" : (ch4 >= 10 ? "%.3f" : "%.4f"), ch4);

        if (m_en1)
        {
            m_ui->textBrowser_ch1->setHtml("<p align=\"center\">" + ch1_s + " V</p>");
            m_ui->progressBar_ch1->setValue((ch1 / (m_vref * m_gain1)) * 100.0);
        }
        if (m_en2)
        {
            m_ui->textBrowser_ch2->setHtml("<p align=\"center\">" + ch2_s + " V</p>");
            m_ui->progressBar_ch2->setValue((ch2 / (m_vref * m_gain2)) * 100.0);
        }
        if (m_en3)
        {
            m_ui->textBrowser_ch3->setHtml("<p align=\"center\">" + ch3_s + " V</p>");
            m_ui->progressBar_ch3->setValue((ch3 / (m_vref * m_gain3)) * 100.0);
        }
        if (m_en4)
        {
            m_ui->textBrowser_ch4->setHtml("<p align=\"center\">" + ch4_s + " V</p>");
            m_ui->progressBar_ch4->setValue((ch4 / (m_vref * m_gain4)) * 100.0);
        }

        m_status_vcc->setText(" Vcc: " + vcc + " mV");

        double maxRng = 0;
        double key = 0;

        for (auto smpl : m_smplBuff)
        {
            key = smpl.t;

            m_ui->customPlot->graph(GRAPH_CH1)->addData(key, smpl.ch1);
            m_ui->customPlot->graph(GRAPH_CH2)->addData(key, smpl.ch2);
            m_ui->customPlot->graph(GRAPH_CH3)->addData(key, smpl.ch3);
            m_ui->customPlot->graph(GRAPH_CH4)->addData(key, smpl.ch4);

            if (m_gain1 > maxRng) maxRng = m_gain1;
            if (m_gain2 > maxRng) maxRng = m_gain2;
            if (m_gain3 > maxRng) maxRng = m_gain3;
            if (m_gain4 > maxRng) maxRng = m_gain4;
        }

        m_smplBuff.clear();

        old_range = m_ui->customPlot->yAxis->range();
        m_ui->customPlot->yAxis->rescale();
        m_ui->customPlot->xAxis->setRange(key, m_display, Qt::AlignRight);

        if (old_range != m_ui->customPlot->yAxis->range())
        {
            auto low_range = m_ui->customPlot->yAxis->range().lower;
            auto up_range = m_ui->customPlot->yAxis->range().upper;
            auto hysteris = (up_range - low_range) * 0.05;

            m_ui->customPlot->yAxis->setRange(low_range - hysteris,up_range + hysteris);
        }

        if (m_cursorsV_en || m_cursorsH_en)
        {
            auto rngV = m_ui->customPlot->yAxis->range();
            auto rngH = m_ui->customPlot->xAxis->range();

            m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, true);
        }

        m_ui->customPlot->graph(GRAPH_CH1)->data()->removeBefore(key - m_display);
        m_ui->customPlot->graph(GRAPH_CH2)->data()->removeBefore(key - m_display);
        m_ui->customPlot->graph(GRAPH_CH3)->data()->removeBefore(key - m_display);
        m_ui->customPlot->graph(GRAPH_CH4)->data()->removeBefore(key - m_display);

        m_ui->customPlot->replot();

        m_data_fresh = false;

        if (m_meas_en && m_meas_max > -1000 && m_meas_min < 1000)
        {
            QString meas_vpp_s;
            QString meas_avg_s;
            QString meas_min_s;
            QString meas_max_s;

            auto data_begin = m_ui->customPlot->graph(m_meas_ch)->data()->begin();
            auto data_end = m_ui->customPlot->graph(m_meas_ch)->data()->end();

            double vpp = m_meas_max - m_meas_min;
            double avg = std::accumulate(data_begin, data_end, .0, [](double a, QCPGraphData b) { return a + b.value;}) / std::distance(data_begin, data_end);
            double min = m_meas_min;
            double max = m_meas_max;

            meas_vpp_s = meas_vpp_s.asprintf(vpp >= 100 ? "%.2f" : (vpp >= 10 ? "%.3f" : "%.4f"), vpp);
            meas_avg_s = meas_avg_s.asprintf(avg >= 100 ? "%.2f" : (avg >= 10 ? "%.3f" : "%.4f"), avg);
            meas_min_s = meas_min_s.asprintf(min >= 100 ? "%.2f" : (min >= 10 ? "%.3f" : "%.4f"), min);
            meas_max_s = meas_max_s.asprintf(max >= 100 ? "%.2f" : (max >= 10 ? "%.3f" : "%.4f"), max);

            m_ui->textBrowser_measVpp->setHtml("<p align=\"right\">" + meas_vpp_s + " </p>");
            m_ui->textBrowser_measAvg->setHtml("<p align=\"right\">" + meas_avg_s + " </p>");
            m_ui->textBrowser_measMin->setHtml("<p align=\"right\">" + meas_min_s + " </p>");
            m_ui->textBrowser_measMax->setHtml("<p align=\"right\">" + meas_max_s + " </p>");
        }
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

    m_lines = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setLineStyle(style);

    if (!m_instrEnabled)
        m_ui->customPlot->replot();
}

void WindowVm::on_actionPoints_triggered(bool checked)
{
    QCPScatterStyle style = QCPScatterStyle(QCPScatterStyle::ssNone);

    if (checked)
        style = QCPScatterStyle(QCPScatterStyle::ssDisc, 5);

    m_points = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setScatterStyle(style);

    if (!m_instrEnabled)
        m_ui->customPlot->replot();
}

void WindowVm::on_actionSinc_triggered(bool checked) // exclusive with - actionLinear
{
    m_spline = checked;

    m_ui->actionLinear->setChecked(!checked);

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(checked);

    if (!m_instrEnabled)
        m_ui->customPlot->replot();
}

void WindowVm::on_actionLinear_triggered(bool checked) // exclusive with - actionSinc
{
    m_ui->actionSinc->setChecked(!checked);
    on_actionSinc_triggered(!checked);
}

void WindowVm::on_pushButton_disable1_clicked()
{
    m_en1 = false;
    m_ui->customPlot->graph(GRAPH_CH1)->setVisible(false);
    m_ui->textBrowser_ch1->setText("");
    m_ui->progressBar_ch1->setValue(0);

    m_ui->pushButton_enable1->show();
    m_ui->pushButton_disable1->hide();
}

void WindowVm::on_pushButton_enable1_clicked()
{
    m_en1 = true;
    m_ui->customPlot->graph(GRAPH_CH1)->setVisible(true);

    m_ui->pushButton_enable1->hide();
    m_ui->pushButton_disable1->show();
}

void WindowVm::on_pushButton_disable2_clicked()
{
    m_en2 = false;
    m_ui->customPlot->graph(GRAPH_CH2)->setVisible(false);
    m_ui->textBrowser_ch2->setText("");
    m_ui->progressBar_ch2->setValue(0);

    m_ui->pushButton_enable2->show();
    m_ui->pushButton_disable2->hide();
}

void WindowVm::on_pushButton_enable2_clicked()
{
    m_en2 = true;
    m_ui->customPlot->graph(GRAPH_CH2)->setVisible(true);

    m_ui->pushButton_enable2->hide();
    m_ui->pushButton_disable2->show();
}

void WindowVm::on_pushButton_disable3_clicked()
{
    m_en3 = false;
    m_ui->customPlot->graph(GRAPH_CH3)->setVisible(false);
    m_ui->textBrowser_ch3->setText("");
    m_ui->progressBar_ch3->setValue(0);

    m_ui->pushButton_enable3->show();
    m_ui->pushButton_disable3->hide();
}

void WindowVm::on_pushButton_enable3_clicked()
{
    m_en3 = true;
    m_ui->customPlot->graph(GRAPH_CH3)->setVisible(true);

    m_ui->pushButton_enable3->hide();
    m_ui->pushButton_disable3->show();
}

void WindowVm::on_pushButton_disable4_clicked()
{
    m_en4 = false;
    m_ui->customPlot->graph(GRAPH_CH4)->setVisible(false);
    m_ui->textBrowser_ch4->setText("");
    m_ui->progressBar_ch4->setValue(0);

    m_ui->pushButton_enable4->show();
    m_ui->pushButton_disable4->hide();
}

void WindowVm::on_pushButton_enable4_clicked()
{
    m_en4 = true;
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

    m_ui->textBrowser_ch1->setEnabled(false);
    m_ui->textBrowser_ch2->setEnabled(false);
    m_ui->textBrowser_ch3->setEnabled(false);
    m_ui->textBrowser_ch4->setEnabled(false);

    m_ui->pushButton_disable1->setEnabled(false);
    m_ui->pushButton_enable1->setEnabled(false);
    m_ui->pushButton_disable2->setEnabled(false);
    m_ui->pushButton_enable2->setEnabled(false);
    m_ui->pushButton_disable3->setEnabled(false);
    m_ui->pushButton_enable3->setEnabled(false);
    m_ui->pushButton_disable4->setEnabled(false);
    m_ui->pushButton_enable4->setEnabled(false);

    m_ui->doubleSpinBox_gain1->setEnabled(false);
    m_ui->doubleSpinBox_gain2->setEnabled(false);
    m_ui->doubleSpinBox_gain3->setEnabled(false);
    m_ui->doubleSpinBox_gain4->setEnabled(false);

    m_ui->progressBar_ch1->setEnabled(false);
    m_ui->progressBar_ch2->setEnabled(false);
    m_ui->progressBar_ch3->setEnabled(false);
    m_ui->progressBar_ch4->setEnabled(false);

    m_ui->spinBox_average->setEnabled(false);
    m_ui->dial_average->setEnabled(false);

    m_ui->spinBox_display->setEnabled(false);
    m_ui->dial_display->setEnabled(false);

    m_ui->textBrowser_measVpp->setEnabled(false);
    m_ui->textBrowser_measAvg->setEnabled(false);
    m_ui->textBrowser_measMax->setEnabled(false);
    m_ui->textBrowser_measMin->setEnabled(false);

    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void WindowVm::on_pushButton_enable_clicked()
{
    m_smplBuff.clear();

    m_instrEnabled = true;
    m_elapsed_diff += m_timer_elapsed.elapsed() - m_elapsed_saved;

    m_ui->pushButton_enable->hide();
    m_ui->pushButton_disable->show();

    m_ui->textBrowser_ch1->setEnabled(true);
    m_ui->textBrowser_ch2->setEnabled(true);
    m_ui->textBrowser_ch3->setEnabled(true);
    m_ui->textBrowser_ch4->setEnabled(true);

    m_ui->pushButton_disable1->setEnabled(true);
    m_ui->pushButton_enable1->setEnabled(true);
    m_ui->pushButton_disable2->setEnabled(true);
    m_ui->pushButton_enable2->setEnabled(true);
    m_ui->pushButton_disable3->setEnabled(true);
    m_ui->pushButton_enable3->setEnabled(true);
    m_ui->pushButton_disable4->setEnabled(true);
    m_ui->pushButton_enable4->setEnabled(true);

    m_ui->doubleSpinBox_gain1->setEnabled(true);
    m_ui->doubleSpinBox_gain2->setEnabled(true);
    m_ui->doubleSpinBox_gain3->setEnabled(true);
    m_ui->doubleSpinBox_gain4->setEnabled(true);

    m_ui->progressBar_ch1->setEnabled(true);
    m_ui->progressBar_ch2->setEnabled(true);
    m_ui->progressBar_ch3->setEnabled(true);
    m_ui->progressBar_ch4->setEnabled(true);

    m_ui->spinBox_average->setEnabled(true);
    m_ui->dial_average->setEnabled(true);

    m_ui->spinBox_display->setEnabled(true);
    m_ui->dial_display->setEnabled(true);

    m_ui->textBrowser_measVpp->setEnabled(true);
    m_ui->textBrowser_measAvg->setEnabled(true);
    m_ui->textBrowser_measMax->setEnabled(true);
    m_ui->textBrowser_measMin->setEnabled(true);

    m_ui->customPlot->setInteractions(0);
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

    m_display = (double)arg1 / ((double)TIMER_VM_RENDER);
}

void WindowVm::on_dial_display_valueChanged(int value)
{
    m_ui->spinBox_display->setValue(value);
}

void WindowVm::on_actionEnabled_triggered(bool checked)
{
    m_meas_en = checked;
    on_actionReset_triggered();

    m_ui->textBrowser_measVpp->setEnabled(checked);
    m_ui->textBrowser_measAvg->setEnabled(checked);
    m_ui->textBrowser_measMin->setEnabled(checked);
    m_ui->textBrowser_measMax->setEnabled(checked);
}

void WindowVm::on_actionReset_triggered()
{
    m_meas_max = -1000;
    m_meas_min = 1000;

    m_ui->textBrowser_measVpp->setText("");
    m_ui->textBrowser_measAvg->setText("");
    m_ui->textBrowser_measMin->setText("");
    m_ui->textBrowser_measMax->setText("");
}

void WindowVm::on_actionChannel_1_triggered(bool checked)
{
    if (checked)
    {
        on_actionReset_triggered();
        m_meas_ch = GRAPH_CH1;

        m_ui->actionChannel_2->setChecked(false);
        m_ui->actionChannel_3->setChecked(false);
        m_ui->actionChannel_4->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 1)");
    }
}

void WindowVm::on_actionChannel_2_triggered(bool checked)
{
    if (checked)
    {
        on_actionReset_triggered();
        m_meas_ch = GRAPH_CH2;

        m_ui->actionChannel_1->setChecked(false);
        m_ui->actionChannel_3->setChecked(false);
        m_ui->actionChannel_4->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 2)");
    }
}

void WindowVm::on_actionChannel_3_triggered(bool checked)
{
    if (checked)
    {
        on_actionReset_triggered();
        m_meas_ch = GRAPH_CH3;

        m_ui->actionChannel_1->setChecked(false);
        m_ui->actionChannel_2->setChecked(false);
        m_ui->actionChannel_4->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 3)");
    }
}

void WindowVm::on_actionChannel_4_triggered(bool checked)
{
    if (checked)
    {
        on_actionReset_triggered();
        m_meas_ch = GRAPH_CH4;

        m_ui->actionChannel_1->setChecked(false);
        m_ui->actionChannel_2->setChecked(false);
        m_ui->actionChannel_3->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 4)");
    }
}

void WindowVm::on_pushButton_cursorsHoff_clicked()
{
    m_ui->horizontalSlider_cursorH->hide();

    m_ui->pushButton_cursorsHon->show();
    m_ui->pushButton_cursorsHoff->hide();

    m_cursors->showH(false);
    m_cursorsH_en = false;
}

void WindowVm::on_pushButton_cursorsHon_clicked()
{
    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorH->show();

    m_ui->pushButton_cursorsHon->hide();
    m_ui->pushButton_cursorsHoff->show();

    auto rngH = m_ui->customPlot->xAxis->range();
    auto rngV = m_ui->customPlot->yAxis->range();

    m_cursors->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors->setH_max(m_cursorH_max, rngH.lower, rngH.upper);

    m_cursors->setV_min(m_cursorV_min, rngV.lower, rngV.upper);
    m_cursors->setV_max(m_cursorV_max, rngV.lower, rngV.upper);

    m_cursors->showH(true);
    m_cursorsH_en = true;
}

void WindowVm::on_pushButton_cursorsVoff_clicked()
{
    m_ui->horizontalSlider_cursorV->hide();

    m_ui->pushButton_cursorsVon->show();
    m_ui->pushButton_cursorsVoff->hide();

    m_cursors->showV(false);
    m_cursorsV_en = false;
}

void WindowVm::on_pushButton_cursorsVon_clicked()
{
    m_ui->horizontalSlider_cursorV->setValues(m_cursorV_min, m_cursorV_max);
    m_ui->horizontalSlider_cursorV->show();

    m_ui->pushButton_cursorsVon->hide();
    m_ui->pushButton_cursorsVoff->show();

    auto rngH = m_ui->customPlot->xAxis->range();
    auto rngV = m_ui->customPlot->yAxis->range();

    m_cursors->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors->setH_max(m_cursorH_max, rngH.lower, rngH.upper);

    m_cursors->setV_min(m_cursorV_min, rngV.lower, rngV.upper);
    m_cursors->setV_max(m_cursorV_max, rngV.lower, rngV.upper);

    m_cursors->showV(true);
    m_cursorsV_en = true;
}

void WindowVm::on_cursorH_valuesChanged(int min, int max)
{
    m_cursorH_min = min;
    m_cursorH_max = max;

    auto rng = m_ui->customPlot->xAxis->range();

    m_cursors->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors->setH_max(m_cursorH_max, rng.lower, rng.upper);
}

void WindowVm::on_cursorV_valuesChanged(int min, int max)
{
    m_cursorV_min = min;
    m_cursorV_max = max;

    auto rng = m_ui->customPlot->yAxis->range();

    m_cursors->setV_min(m_cursorV_min, rng.lower, rng.upper);
    m_cursors->setV_max(m_cursorV_max, rng.lower, rng.upper);
}

/* private */

void WindowVm::closeEvent(QCloseEvent*)
{
    m_activeMsg = Q_NULLPTR;

    Core::getInstance()->setMode(NO_MODE);
    emit closing(WindowVm::staticMetaObject.className());

    m_timer_render->stop();
}

void WindowVm::showEvent(QShowEvent*)
{
    auto info = Core::getInstance()->getDevInfo();
    QStringList pins = info->pins_scope_vm.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (pins.size() == 4)
    {
        m_ui->label_ch1->setText("Channel 1 (" + pins[0].trimmed() + ")");
        m_ui->label_ch2->setText("Channel 2 (" + pins[1].trimmed() + ")");
        m_ui->label_ch3->setText("Channel 3 (" + pins[2].trimmed() + ")");
        m_ui->label_ch4->setText("Channel 4 (" + pins[3].trimmed() + ")");
    }

    m_ui->dial_average->setMaximum(info->vm_mem);
    m_ui->spinBox_average->setMaximum(info->vm_mem);

    m_vref = info->ref_mv / 1000;

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    m_ui->customPlot->replot();

    Core::getInstance()->setMode(VM);

    m_activeMsg = m_msg_read;

    m_smplBuff.clear();
    m_data_fresh = false;
    on_actionReset_triggered();

    m_timer_elapsed.restart();
    m_timer_render->start(TIMER_VM_RENDER);
}
