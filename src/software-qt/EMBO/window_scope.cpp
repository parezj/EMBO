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
#include <QMap>
#include <QDateTime>
#include <QMessageBox>


#define Y_LIM           0.20


WindowScope::WindowScope(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowScope)
{
    m_ui->setupUi(this);

    m_timer_plot = new QTimer(this);
    m_timer_plot->setTimerType(Qt::PreciseTimer);

    m_msg_set = new Msg_SCOP_Set(this);
    m_msg_read = new Msg_SCOP_Read(this);
    m_msg_forceTrig = new Msg_SCOP_ForceTrig(this);

    connect(m_msg_set, &Msg_SCOP_Set::ok, this, &WindowScope::on_msg_ok_set, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_SCOP_Set::err, this, &WindowScope::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_set, &Msg_SCOP_Set::result, this, &WindowScope::on_msg_set, Qt::QueuedConnection);

    connect(m_msg_read, &Msg_SCOP_Read::err, this, &WindowScope::on_msg_err, Qt::QueuedConnection);
    connect(m_msg_read, &Msg_SCOP_Read::result, this, &WindowScope::on_msg_read, Qt::QueuedConnection);

    connect(m_msg_forceTrig, &Msg_SCOP_ForceTrig::ok, this, &WindowScope::on_msg_ok_forceTrig, Qt::QueuedConnection);
    connect(m_msg_forceTrig, &Msg_SCOP_ForceTrig::err, this, &WindowScope::on_msg_err, Qt::QueuedConnection);

    connect(Core::getInstance(), &Core::daqReady, this, &WindowScope::on_msg_daqReady, Qt::QueuedConnection);

    connect(m_timer_plot, &QTimer::timeout, this, &WindowScope::on_timer_plot);

    /* QCP */

    initQcp();

    /* statusbar */

    m_status_vcc = new QLabel(" ", this);
    m_status_rec = new QLabel(" ", this);
    QWidget* widget = new QWidget(this);
    QFont font1("Roboto", 11, QFont::Normal);
    m_status_vcc->setFont(font1);
    m_status_rec->setFont(font1);

    QLabel* status_img = new QLabel(this);
    QPixmap status_img_icon = QPixmap(":/main/resources/img/scope.svg");

    status_img->setPixmap(status_img_icon);
    status_img->setFixedWidth(17);
    status_img->setFixedHeight(17);
    status_img->setScaledContents(true);

    m_status_line1 = new QFrame(this);
    m_status_line1->setFrameShape(QFrame::VLine);
    m_status_line1->setFrameShadow(QFrame::Plain);
    m_status_line1->setStyleSheet("color:gray;");
    m_status_line1->setFixedHeight(18);
    m_status_line1->setVisible(false);

    QLabel* status_spacer2 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer3 = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);

    QSpacerItem* status_spacer0 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(status_img,     0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_vcc,   0,1,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer2, 0,2,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_line1, 0,3,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer3, 0,4,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_rec,   0,5,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->addItem(status_spacer0,   0,6,1,1,Qt::AlignVCenter);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);

    /* styles */

    m_instrEnabled = true;
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

    m_ui->customPlot->axisRect()->setMinimumMargins(QMargins(45,15,15,30));

    m_timeTicker = QSharedPointer<QCPAxisTickerTime>(new QCPAxisTickerTime);
    m_timeTicker->setTimeFormat("%z ms");
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuSeconds, 1);
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuMilliseconds, 1);
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuMicroseconds, 1);
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

    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorV->setValues(m_cursorV_min, m_cursorV_max);

    m_ui->horizontalSlider_cursorH->hide();
    m_ui->horizontalSlider_cursorV->hide();

    connect(m_ui->horizontalSlider_cursorH, &ctkRangeSlider::valuesChanged, this, &WindowScope::on_cursorH_valuesChanged);
    connect(m_ui->horizontalSlider_cursorV, &ctkRangeSlider::valuesChanged, this, &WindowScope::on_cursorV_valuesChanged);

    m_cursors = new QCPCursors(this, m_ui->customPlot, NULL, false, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursorTrigVal = new QCPCursor(this, m_ui->customPlot, NULL, true, false);
    m_cursorTrigPre = new QCPCursor(this, m_ui->customPlot, NULL, false, false);
}

WindowScope::~WindowScope()
{
    delete m_ui;
}

void WindowScope::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/********************************* timer slots *********************************/

void WindowScope::on_timer_plot() // 60 FPS
{
    if (m_cursorsV_en || m_cursorsH_en)
    {
        auto rngV = m_ui->customPlot->yAxis->range();
        auto rngH = m_ui->customPlot->xAxis->range();

        m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    }

    m_ui->customPlot->replot();
}

/******************************** MSG slots ********************************/

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

    updatePanel();
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

    updatePanel();
}

void WindowScope::on_msg_read(const QByteArray data)
{
    auto info = Core::getInstance()->getDevInfo();
    int ch_num = m_daqSet.ch1_en + m_daqSet.ch2_en + m_daqSet.ch3_en + m_daqSet.ch4_en;

    const uint8_t* dataU8 = reinterpret_cast<const uint8_t*>(data.constData());

    QVector<double> y1(m_daqSet.mem);
    QVector<double> y2(m_daqSet.mem);
    QVector<double> y3(m_daqSet.mem);
    QVector<double> y4(m_daqSet.mem);

    QVector<double>* _y1 = (m_daqSet.ch1_en ? &y1 : NULL);
    QVector<double>* _y2 = (m_daqSet.ch2_en ? &y2 : NULL);
    QVector<double>* _y3 = (m_daqSet.ch3_en ? &y3 : NULL);
    QVector<double>* _y4 = (m_daqSet.ch4_en ? &y4 : NULL);

    double vcc = info->ref_mv / 1000.0;
    int found = 0;

    if (info->adc_num == 1)
    {
        uint8_t* buff1 = (uint8_t*)dataU8;
        int buff1_len = data.size();

        if (m_daqSet.bits == B12)
            buff1_len /= 2;

        int buff1_mem = buff1_len - (info->daq_reserve * ch_num);

        found += get_vals_from_circ(m_firstPos, buff1_mem, buff1_len, m_daqSet.bits, vcc, buff1, _y1, _y2, _y3, _y4);

    }
    else if (info->adc_num == 2)
    {
        int buff_part = data.size();
        if (m_daqSet.bits == B12)
            buff_part /= 2;
        buff_part /= ch_num;

        uint8_t* buff_it = (uint8_t*)dataU8;

        uint8_t* buff1 = NULL;
        int buff1_len = 0;
        int buff1_mem;

        uint8_t* buff2 = NULL;
        int buff2_len = 0;
        int buff2_mem;

        if (m_daqSet.ch1_en)
        {
            buff1 = buff_it;
            buff_it += buff_part;
            buff1_len += buff_part;
        }
        if (m_daqSet.ch2_en)
        {
            if (!m_daqSet.ch1_en)
                buff1 = buff_it;
            buff_it += buff_part;
            buff1_len += buff_part;
        }
        if (m_daqSet.ch3_en)
        {
            buff2 = buff_it;
            buff_it += buff_part;
            buff2_len += buff_part;
        }
        if (m_daqSet.ch4_en)
        {
            if (!m_daqSet.ch3_en)
                buff2 = buff_it;
            //buff_it += buff_part;
            buff2_len += buff_part;
        }

        buff1_mem = buff1_len - (info->daq_reserve * (m_daqSet.ch1_en + m_daqSet.ch2_en));
        buff2_mem = buff2_len - (info->daq_reserve * (m_daqSet.ch3_en + m_daqSet.ch4_en));

        if (m_daqSet.ch1_en || m_daqSet.ch2_en)
            found += get_vals_from_circ(m_firstPos, buff1_mem, buff1_len, m_daqSet.bits, vcc, buff1, _y1, _y2, NULL, NULL);
        if (m_daqSet.ch3_en || m_daqSet.ch4_en)
            found += get_vals_from_circ(m_firstPos, buff2_mem, buff2_len, m_daqSet.bits, vcc, buff2, _y3, _y4, NULL, NULL); // todo trigger problem

    }
    else if (info->adc_num == 4)
    {
        int buff_part = data.size();
        if (m_daqSet.bits == B12)
            buff_part /= 2;
        buff_part /= ch_num;

        uint8_t* buff_it = (uint8_t*)dataU8;

        uint8_t* buff1 = NULL;
        int buff1_len = buff_part;
        int buff1_mem = buff1_len - (info->daq_reserve);

        uint8_t* buff2 = NULL;
        int buff2_len = buff_part;
        int buff2_mem = buff1_len - (info->daq_reserve);

        uint8_t* buff3 = NULL;
        int buff3_len = buff_part;
        int buff3_mem = buff1_len - (info->daq_reserve);

        uint8_t* buff4 = NULL;
        int buff4_len = buff_part;
        int buff4_mem = buff1_len - (info->daq_reserve);

        if (m_daqSet.ch1_en)
        {
            buff1 = buff_it;
            buff_it += buff_part;
        }
        if (m_daqSet.ch2_en)
        {
            buff2 = buff_it;
            buff_it += buff_part;
        }
        if (m_daqSet.ch3_en)
        {
            buff3 = buff_it;
            buff_it += buff_part;
        }
        if (m_daqSet.ch4_en)
        {
            buff4 = buff_it;
            buff_it += buff_part;
        }

        if (m_daqSet.ch1_en)
            found += get_vals_from_circ(m_firstPos, buff1_mem, buff1_len, m_daqSet.bits, vcc, buff1, _y1, NULL, NULL, NULL);
        if (m_daqSet.ch2_en)
            found += get_vals_from_circ(m_firstPos, buff2_mem, buff2_len, m_daqSet.bits, vcc, buff2, _y2, NULL, NULL, NULL);
        if (m_daqSet.ch3_en)
            found += get_vals_from_circ(m_firstPos, buff3_mem, buff3_len, m_daqSet.bits, vcc, buff3, _y3, NULL, NULL, NULL);
        if (m_daqSet.ch4_en)
            found += get_vals_from_circ(m_firstPos, buff4_mem, buff4_len, m_daqSet.bits, vcc, buff4, _y4, NULL, NULL, NULL);

    }
    else assert(0);

    if (found / ch_num != m_daqSet.mem) // wrong data size
    {
        on_msg_err(INVALID_MSG, CRITICAL, true);
        return;
    }

    assert(!m_t.isEmpty());

    if (m_daqSet.ch1_en)
        m_ui->customPlot->graph(GRAPH_CH1)->setData(m_t, y1);
    if (m_daqSet.ch2_en)
        m_ui->customPlot->graph(GRAPH_CH2)->setData(m_t, y2);
    if (m_daqSet.ch3_en)
        m_ui->customPlot->graph(GRAPH_CH3)->setData(m_t, y3);
    if (m_daqSet.ch4_en)
        m_ui->customPlot->graph(GRAPH_CH4)->setData(m_t, y4);
}

void WindowScope::on_msg_daqReady(Ready ready, int firstPos)
{
    m_firstPos = firstPos;
    m_ready = ready;

    if (m_instrEnabled)
        Core::getInstance()->msgAdd(m_msg_read, true);
}

void WindowScope::on_msg_ok_forceTrig(const QString, const QString)
{

}

/******************************** GUI slots ********************************/

/********** Plot **********/

void WindowScope::on_actionViewPoints_triggered(bool checked)
{
    QCPScatterStyle style = QCPScatterStyle(QCPScatterStyle::ssNone);

    if (checked)
        style = QCPScatterStyle(QCPScatterStyle::ssDisc, 5);

    m_points = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setScatterStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setScatterStyle(style);

    //if (!m_instrEnabled)
    //    m_ui->customPlot->replot();
}

void WindowScope::on_actionViewLines_triggered(bool checked)
{
    QCPGraph::LineStyle style = QCPGraph::lsNone;

    if (checked)
        style = QCPGraph::lsLine;

    m_lines = checked;

    m_ui->customPlot->graph(GRAPH_CH1)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH2)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH3)->setLineStyle(style);
    m_ui->customPlot->graph(GRAPH_CH4)->setLineStyle(style);

    //if (!m_instrEnabled)
    //    m_ui->customPlot->replot();
}

void WindowScope::on_actionInterpLinear_triggered(bool checked) // exclusive with - actionSinc
{
    m_ui->actionInterpSinc->setChecked(!checked);
    on_actionInterpSinc_triggered(!checked);
}


void WindowScope::on_actionInterpSinc_triggered(bool checked) // exclusive with - actionLinear
{
    m_spline = checked;

    m_ui->actionInterpLinear->setChecked(!checked);

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(checked);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(checked);

    //if (!m_instrEnabled)
    //    m_ui->customPlot->replot();
}

/********** Export **********/

void WindowScope::on_actionExportSave_triggered()
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
        {"Common.Mode",     "SCOPE"},
        {"SCOPE.SampleRate",   "TODO Hz"}, // TODO
        {"SCOPE.Resolution",   "TODO bit"}, // TODO
    };
    bool ret = m_rec.createFile("SCOPE", header);

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
                m_rec << data_1->at(i)->value;
            if (m_daqSet.ch2_en)
                m_rec << data_2->at(i)->value;
            if (m_daqSet.ch3_en)
                m_rec << data_3->at(i)->value;
            if (m_daqSet.ch4_en)
                m_rec << data_4->at(i)->value;
            m_rec << ENDL;
        }

        auto f = m_rec.closeFile();
        msgBox(this, "File saved at: " + f, INFO);
    }
}

void WindowScope::on_actionExportScreenshot_triggered()
{
     QString ret = m_rec.takeScreenshot("VM", m_ui->customPlot);

     if (ret.isEmpty())
         msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
     else
         msgBox(this, "File saved at: " + ret, INFO);
}

void WindowScope::on_actionExportFolder_triggered()
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

void WindowScope::on_actionExportCSV_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(CSV);

        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowScope::on_actionExportTXT_Tabs_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(CSV);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowScope::on_actionExportTXT_Semicolon_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(CSV);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowScope::on_actionExportMAT_triggered(bool checked)
{
    if (checked)
    {
        //rec.setDelim(MAT); // not implemented yet

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
    }
}

/********** Meas **********/

void WindowScope::on_actionMeasEnabled_triggered(bool checked)
{
    m_meas_en = checked;
    on_actionMeasReset_triggered();

    m_ui->textBrowser_measVpp->setEnabled(checked);
    m_ui->textBrowser_measAvg->setEnabled(checked);
    m_ui->textBrowser_measMin->setEnabled(checked);
    m_ui->textBrowser_measMax->setEnabled(checked);
}

void WindowScope::on_actionMeasReset_triggered()
{
    //m_meas_max = -1000;
    //m_meas_min = 1000;

    m_ui->textBrowser_measVpp->setText("");
    m_ui->textBrowser_measAvg->setText("");
    m_ui->textBrowser_measMin->setText("");
    m_ui->textBrowser_measMax->setText("");
}

void WindowScope::on_actionMeasChannel_1_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH1;

        m_ui->actionMeasChannel_2->setChecked(false);
        m_ui->actionMeasChannel_3->setChecked(false);
        m_ui->actionMeasChannel_4->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 1)");
    }
}

void WindowScope::on_actionMeasChannel_2_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH2;

        m_ui->actionMeasChannel_1->setChecked(false);
        m_ui->actionMeasChannel_3->setChecked(false);
        m_ui->actionMeasChannel_4->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 2)");
    }
}

void WindowScope::on_actionMeasChannel_3_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH3;

        m_ui->actionMeasChannel_1->setChecked(false);
        m_ui->actionMeasChannel_2->setChecked(false);
        m_ui->actionMeasChannel_4->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 3)");
    }
}

void WindowScope::on_actionMeasChannel_4_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH4;

        m_ui->actionMeasChannel_1->setChecked(false);
        m_ui->actionMeasChannel_2->setChecked(false);
        m_ui->actionMeasChannel_3->setChecked(false);

        m_ui->label_meas->setText("Measure (Channel 4)");
    }
}

/********** Math **********/

void WindowScope::on_actionMath_1_2_triggered(bool checked)
{
    m_math_2minus1 = checked;

    /*
    if (checked)
    {
        m_ui->label_ch3->setText("Channel 2—1 (" + m_pin2 + "—" + m_pin1 + ")");
        m_ui->label_ch3->setStyleSheet("color:red");

        m_ui->pushButton_enable3->setText("2—1 ON  ");
        m_ui->pushButton_disable3->setText("2—1 OFF");
    }
    else
    {
        m_ui->label_ch3->setText("Channel 3 (" + m_pin3 + ")");
        m_ui->label_ch3->setStyleSheet("color:black");

        m_ui->pushButton_enable3->setText("CH3 ON  ");
        m_ui->pushButton_disable3->setText("CH3 OFF");
    }
    */
}

void WindowScope::on_actionMath_3_4_triggered(bool checked)
{
    m_math_4minus3 = checked;

    /*
    if (checked)
    {
        m_ui->label_ch4->setText("Channel 4—3 (" + m_pin4 + "—" + m_pin3 + ")");
        m_ui->label_ch4->setStyleSheet("color:red");

        m_ui->pushButton_enable4->setText("4—3 ON  ");
        m_ui->pushButton_disable4->setText("4—3 OFF");
    }
    else
    {
        m_ui->label_ch4->setText("Channel 4 (" + m_pin4 + ")");
        m_ui->label_ch4->setStyleSheet("color:black");

        m_ui->pushButton_enable4->setText("CH4 ON  ");
        m_ui->pushButton_disable4->setText("CH4 OFF");
    }
    */
}

/********** Cursors **********/

void WindowScope::on_pushButton_cursorsHoff_clicked()
{
    m_ui->horizontalSlider_cursorH->hide();

    m_ui->pushButton_cursorsHon->show();
    m_ui->pushButton_cursorsHoff->hide();

    m_cursors->showH(false);
    m_cursorsH_en = false;
}

void WindowScope::on_pushButton_cursorsHon_clicked()
{
    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorH->show();

    m_ui->pushButton_cursorsHon->hide();
    m_ui->pushButton_cursorsHoff->show();

    auto rngH = m_ui->customPlot->xAxis->range();
    auto rngV = m_ui->customPlot->yAxis->range();

    m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);

    m_cursors->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors->setH_max(m_cursorH_max, rngH.lower, rngH.upper);

    m_cursors->showH(true);
    m_cursorsH_en = true;
}

void WindowScope::on_pushButton_cursorsVoff_clicked()
{
    m_ui->horizontalSlider_cursorV->hide();

    m_ui->pushButton_cursorsVon->show();
    m_ui->pushButton_cursorsVoff->hide();

    m_cursors->showV(false);
    m_cursorsV_en = false;
}

void WindowScope::on_pushButton_cursorsVon_clicked()
{
    m_ui->horizontalSlider_cursorV->setValues(m_cursorV_min, m_cursorV_max);
    m_ui->horizontalSlider_cursorV->show();

    m_ui->pushButton_cursorsVon->hide();
    m_ui->pushButton_cursorsVoff->show();

    auto rngH = m_ui->customPlot->xAxis->range();
    auto rngV = m_ui->customPlot->yAxis->range();

    m_cursors->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);

    m_cursors->setV_min(m_cursorV_min, rngV.lower, rngV.upper);
    m_cursors->setV_max(m_cursorV_max, rngV.lower, rngV.upper);

    m_cursors->showV(true);
    m_cursorsV_en = true;
}

void WindowScope::on_cursorH_valuesChanged(int min, int max)
{
    m_cursorH_min = min;
    m_cursorH_max = max;

    auto rng = m_ui->customPlot->axisRect()->rangeZoomAxis(Qt::Horizontal)->range();
    //auto rng = m_ui->customPlot->xAxis->range();

    m_cursors->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors->setH_max(m_cursorH_max, rng.lower, rng.upper);
}

void WindowScope::on_cursorV_valuesChanged(int min, int max)
{
    m_cursorV_min = min;
    m_cursorV_max = max;

    auto rng = m_ui->customPlot->axisRect()->rangeZoomAxis(Qt::Vertical)->range();
    //auto rng = m_ui->customPlot->yAxis->range();

    m_cursors->setV_min(m_cursorV_min, rng.lower, rng.upper);
    m_cursors->setV_max(m_cursorV_max, rng.lower, rng.upper);
}

/********** QCP **********/

void WindowScope::on_qcpMouseWheel(QWheelEvent*)
{
    //m_ui->pushButton_reset->hide();
    //m_ui->pushButton_resetZoom->show();
}

void WindowScope::on_qcpMousePress(QMouseEvent*)
{
    //m_ui->pushButton_reset->hide();
    //m_ui->pushButton_resetZoom->show();
}

/********** right pannel - on/off **********/

/********** right pannel - on/off **********/

/********** right pannel - on/off **********/

/********** right pannel - on/off **********/

/******************************** private ********************************/

void WindowScope::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();
    m_instrEnabled = false;

    Core::getInstance()->setMode(NO_MODE);
    emit closing(WindowScope::staticMetaObject.className());

     m_timer_plot->stop();
}

void WindowScope::showEvent(QShowEvent*)
{
    Core::getInstance()->setMode(SCOPE);
    m_instrEnabled = true;

    auto info = Core::getInstance()->getDevInfo();

    m_ref_v = info->ref_mv / 1000.0;
    m_status_vcc->setText(" Vcc: " + QString::number(info->ref_mv) + " mV");

    QStringList pins = info->pins_scope_vm.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (pins.size() == 4)
    {
        m_pin1 = pins[0].trimmed();
        m_pin2 = pins[1].trimmed();
        m_pin3 = pins[2].trimmed();
        m_pin4 = pins[3].trimmed();

        //m_ui->label_pins->setText("Vertical (" + m_pin1 + ", " + m_pin2 + ", " + m_pin3 + ", " + m_pin4 + ")");
    }

    Core::getInstance()->msgAdd(m_msg_set, true, "");

    m_ui->customPlot->graph(GRAPH_CH1)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH2)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH3)->data()->clear();
    m_ui->customPlot->graph(GRAPH_CH4)->data()->clear();

    on_actionMeasReset_triggered();

    m_timer_plot->start((int)TIMER_SCOPE_PLOT);
}

void WindowScope::rescaleYAxis()
{
    double max_scale = 0;
    double min_scale = 0;
    if (m_daqSet.ch1_en && m_gain1 > max_scale) max_scale = m_gain1;
    else if (m_daqSet.ch1_en && m_gain1 < min_scale) min_scale = m_gain1;
    if (m_daqSet.ch2_en && m_gain2 > max_scale) max_scale = m_gain2;
    else if (m_daqSet.ch2_en && m_gain2 < min_scale) min_scale = m_gain2;
    if (m_daqSet.ch3_en && m_gain3 > max_scale) max_scale = m_gain3;
    else if (m_daqSet.ch3_en && m_gain3 < min_scale) min_scale = m_gain3;
    if (m_daqSet.ch4_en && m_gain4 > max_scale) max_scale = m_gain4;
    else if (m_daqSet.ch4_en && m_gain4 < min_scale) min_scale = m_gain4;

    m_ui->customPlot->yAxis->setRange((min_scale * m_ref_v) - Y_LIM , (max_scale * m_ref_v) + Y_LIM);
}

void WindowScope::rescaleXAxis()
{
    assert(!m_t.isEmpty());
    m_ui->customPlot->xAxis->setRange(0, m_t[m_t.size()-1]);
}

void WindowScope::createX()
{
    double x = 0;
    double dt = 1.0 / m_daqSet.fs_real;
    m_t.resize(m_daqSet.mem);

    for (int i = 0; i < m_daqSet.mem; i++)
    {
        m_t[i] = x;
        x += dt;
    }

    if (x >= 1)
        m_timeTicker->setTimeFormat("%s s");
    else if (x >= 0.001)
        m_timeTicker->setTimeFormat("%z ms");
    else
        m_timeTicker->setTimeFormat("%u μs");
}

void WindowScope::updatePanel()
{
    createX();
    rescaleXAxis();
    rescaleYAxis();

    m_ui->customPlot->graph(GRAPH_CH1)->setVisible(m_daqSet.ch1_en);
    m_ui->customPlot->graph(GRAPH_CH2)->setVisible(m_daqSet.ch2_en);
    m_ui->customPlot->graph(GRAPH_CH3)->setVisible(m_daqSet.ch3_en);
    m_ui->customPlot->graph(GRAPH_CH4)->setVisible(m_daqSet.ch4_en);

    enablePanel(true);
}

void WindowScope::enablePanel(bool en)
{

}
