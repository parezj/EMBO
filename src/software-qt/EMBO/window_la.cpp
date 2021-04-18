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

    m_timer_plot = new QTimer(this);
    m_timer_plot->setTimerType(Qt::PreciseTimer);

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

    connect(m_timer_plot, &QTimer::timeout, this, &WindowLa::on_timer_plot);

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
    QPixmap status_img_icon = QPixmap(":/main/resources/img/la.png");

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

void WindowLa::initQcp()
{
    m_ui->customPlot->plotLayout()->clear();

    m_axis_ch1 = new QCPAxisRect(m_ui->customPlot);
    m_axis_ch2 = new QCPAxisRect(m_ui->customPlot);
    m_axis_ch3 = new QCPAxisRect(m_ui->customPlot);
    m_axis_ch4 = new QCPAxisRect(m_ui->customPlot);

    m_axis_ch1->setupFullAxesBox();
    m_axis_ch2->setupFullAxesBox();
    m_axis_ch3->setupFullAxesBox();
    m_axis_ch4->setupFullAxesBox();

    m_axis_ch1->setMinimumMargins(QMargins(25,15,15,0)); // TODO need dynamic
    m_axis_ch2->setMinimumMargins(QMargins(25,1,15,0));
    m_axis_ch3->setMinimumMargins(QMargins(25,1,15,0));
    m_axis_ch4->setMinimumMargins(QMargins(25,1,15,30));

    m_timeTicker = QSharedPointer<QCPAxisTickerTime>(new QCPAxisTickerTime);
    m_timeTicker->setTimeFormat("%s s");
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuSeconds, 1);
    m_timeTicker->setFieldWidth(QCPAxisTickerTime::tuMilliseconds, 1);

    m_axis_ch1->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);
    m_axis_ch2->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);
    m_axis_ch3->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);
    m_axis_ch4->axis(QCPAxis::atBottom)->setTicker(m_timeTicker);

    m_axis_ch1->axis(QCPAxis::atLeft)->ticker()->setTickCount(1);
    m_axis_ch2->axis(QCPAxis::atLeft)->ticker()->setTickCount(1);
    m_axis_ch3->axis(QCPAxis::atLeft)->ticker()->setTickCount(1);
    m_axis_ch4->axis(QCPAxis::atLeft)->ticker()->setTickCount(1);

    m_axis_ch1->axis(QCPAxis::atRight)->ticker()->setTickCount(1);
    m_axis_ch2->axis(QCPAxis::atRight)->ticker()->setTickCount(1);
    m_axis_ch3->axis(QCPAxis::atRight)->ticker()->setTickCount(1);
    m_axis_ch4->axis(QCPAxis::atRight)->ticker()->setTickCount(1);

    QFont font2("Roboto", 12, QFont::Normal);
    m_axis_ch1->axis(QCPAxis::atBottom)->setTickLabelFont(font2);
    m_axis_ch2->axis(QCPAxis::atBottom)->setTickLabelFont(font2);
    m_axis_ch3->axis(QCPAxis::atBottom)->setTickLabelFont(font2);
    m_axis_ch4->axis(QCPAxis::atBottom)->setTickLabelFont(font2);

    m_axis_ch1->axis(QCPAxis::atLeft)->setTickLabelFont(font2);
    m_axis_ch2->axis(QCPAxis::atLeft)->setTickLabelFont(font2);
    m_axis_ch3->axis(QCPAxis::atLeft)->setTickLabelFont(font2);
    m_axis_ch4->axis(QCPAxis::atLeft)->setTickLabelFont(font2);

    m_axis_ch1->setRangeDrag(Qt::Horizontal);
    m_axis_ch2->setRangeDrag(Qt::Horizontal);
    m_axis_ch3->setRangeDrag(Qt::Horizontal);
    m_axis_ch4->setRangeDrag(Qt::Horizontal);

    m_axis_ch1->setRangeZoom(Qt::Horizontal);
    m_axis_ch2->setRangeZoom(Qt::Horizontal);
    m_axis_ch3->setRangeZoom(Qt::Horizontal);
    m_axis_ch4->setRangeZoom(Qt::Horizontal);

    m_ui->customPlot->plotLayout()->addElement(0, 0, m_axis_ch1);
    m_ui->customPlot->plotLayout()->addElement(1, 0, m_axis_ch2);
    m_ui->customPlot->plotLayout()->addElement(2, 0, m_axis_ch3);
    m_ui->customPlot->plotLayout()->addElement(3, 0, m_axis_ch4);

    foreach (QCPAxisRect *rect, m_ui->customPlot->axisRects())
    {
        foreach (QCPAxis *axis, rect->axes())
        {
            axis->setLayer("axes");
            axis->grid()->setLayer("grid");
        }
    }

    m_ui->customPlot->addGraph(m_axis_ch1->axis(QCPAxis::atBottom), m_axis_ch1->axis(QCPAxis::atLeft));  // ch1
    m_ui->customPlot->addGraph(m_axis_ch2->axis(QCPAxis::atBottom), m_axis_ch2->axis(QCPAxis::atLeft));  // ch2
    m_ui->customPlot->addGraph(m_axis_ch3->axis(QCPAxis::atBottom), m_axis_ch3->axis(QCPAxis::atLeft));  // ch3
    m_ui->customPlot->addGraph(m_axis_ch4->axis(QCPAxis::atBottom), m_axis_ch4->axis(QCPAxis::atLeft));  // ch4

    m_ui->customPlot->graph(GRAPH_CH1)->setPen(QPen(QColor(COLOR1)));
    m_ui->customPlot->graph(GRAPH_CH2)->setPen(QPen(QColor(COLOR2)));
    m_ui->customPlot->graph(GRAPH_CH3)->setPen(QPen(QColor(COLOR5)));
    m_ui->customPlot->graph(GRAPH_CH4)->setPen(QPen(QColor(COLOR4)));

    m_ui->customPlot->graph(GRAPH_CH1)->setSpline(false);
    m_ui->customPlot->graph(GRAPH_CH2)->setSpline(false);
    m_ui->customPlot->graph(GRAPH_CH3)->setSpline(false);
    m_ui->customPlot->graph(GRAPH_CH4)->setSpline(false);

    //m_ui->customPlot->setInteractions(0);
    m_ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    connect(m_ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(on_qcpMouseWheel(QWheelEvent*)));
    connect(m_ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(on_qcpMousePress(QMouseEvent*)));

    connect(m_axis_ch1->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch1->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch1->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));

    connect(m_axis_ch2->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch2->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch2->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));

    connect(m_axis_ch3->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch3->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch3->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));

    connect(m_axis_ch4->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch4->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(m_axis_ch4->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));

    connect(m_axis_ch1->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
    connect(m_axis_ch2->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
    connect(m_axis_ch3->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));
    connect(m_axis_ch4->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atTop), SLOT(setRange(QCPRange)));

    connect(m_axis_ch1->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_ch1->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));
    connect(m_axis_ch2->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_ch2->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));
    connect(m_axis_ch3->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_ch3->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));
    connect(m_axis_ch4->axis(QCPAxis::atLeft), SIGNAL(rangeChanged(QCPRange)), m_axis_ch4->axis(QCPAxis::atRight), SLOT(setRange(QCPRange)));

    /* cursors */

    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorV->setValues(m_cursorV_min, m_cursorV_max);

    m_ui->horizontalSlider_cursorH->hide();
    m_ui->horizontalSlider_cursorV->hide();

    connect(m_ui->horizontalSlider_cursorH, &ctkRangeSlider::valuesChanged, this, &WindowLa::on_cursorH_valuesChanged);

    m_cursors1 = new QCPCursors(this, m_ui->customPlot, m_axis_ch1, true, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursors2 = new QCPCursors(this, m_ui->customPlot, m_axis_ch2, true, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursors3 = new QCPCursors(this, m_ui->customPlot, m_axis_ch3, true, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursors4 = new QCPCursors(this, m_ui->customPlot, m_axis_ch4, true, QColor(COLOR3), QColor(COLOR3), QColor(COLOR7), QColor(Qt::black));
    m_cursorTrigPre = new QCPCursor(this, m_ui->customPlot, m_axis_ch4, false, false);
}

WindowLa::~WindowLa()
{
    delete m_ui;
}

void WindowLa::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

/********************************* timer slots *********************************/

void WindowLa::on_timer_plot() // 60 FPS
{
    if (m_cursorsV_en || m_cursorsH_en)
    {
        auto rngV = m_ui->customPlot->yAxis->range();
        auto rngH = m_ui->customPlot->xAxis->range();

        m_cursors1->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
        m_cursors2->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
        m_cursors3->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
        m_cursors4->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    }

    m_ui->customPlot->replot();
}

/********************************* MSG slots *********************************/

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

    updatePanel();
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

    updatePanel();
}

void WindowLa::on_msg_read(const QByteArray data)
{
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

        y1[k] = ch1 ? 1.0 : 0.0;
        y2[k] = ch2 ? 1.0 : 0.0;
        y3[k] = ch3 ? 1.0 : 0.0;
        y4[k] = ch4 ? 1.0 : 0.0;
    }

    assert(!m_t.isEmpty());

    m_ui->customPlot->graph(GRAPH_CH1)->setData(m_t, y1);
    m_ui->customPlot->graph(GRAPH_CH2)->setData(m_t, y2);
    m_ui->customPlot->graph(GRAPH_CH3)->setData(m_t, y3);
    m_ui->customPlot->graph(GRAPH_CH4)->setData(m_t, y4);
}

void WindowLa::on_msg_daqReady(Ready ready, int firstPos)
{
    m_firstPos = firstPos;
    m_ready = ready;

    if (m_instrEnabled)
        Core::getInstance()->msgAdd(m_msg_read, true);
}

void WindowLa::on_msg_ok_forceTrig(const QString, const QString)
{

}

/******************************** GUI slots ********************************/

/********** Plot **********/

void WindowLa::on_actionViewPoints_triggered(bool checked)
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

void WindowLa::on_actionViewLines_triggered(bool checked)
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

/********** Export **********/

void WindowLa::on_actionExportSave_triggered()
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
        {"Common.Mode",     "LA"},
        {"LA.SampleRate",   "TODO Hz"}, // TODO
        {"LA.Resolution",   "TODO bit"}, // TODO
    };
    bool ret = m_rec.createFile("LA", header);

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

void WindowLa::on_actionExportScreenshot_triggered()
{
     QString ret = m_rec.takeScreenshot("VM", m_ui->customPlot);

     if (ret.isEmpty())
         msgBox(this, "Write file at: " + m_rec.getDir() + " failed!", CRITICAL);
     else
         msgBox(this, "File saved at: " + ret, INFO);
}

void WindowLa::on_actionExportFolder_triggered()
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

void WindowLa::on_actionExportCSV_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(CSV);

        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowLa::on_actionExportTXT_Tabs_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(CSV);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Semicolon->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowLa::on_actionExportTXT_Semicolon_triggered(bool checked)
{
    if (checked)
    {
        m_rec.setDelim(CSV);

        m_ui->actionExportCSV->setChecked(false);
        m_ui->actionExportTXT_Tabs->setChecked(false);
        m_ui->actionExportMAT->setChecked(false);
    }
}

void WindowLa::on_actionExportMAT_triggered(bool checked)
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

void WindowLa::on_actionMeasEnabled_triggered(bool checked)
{
    m_meas_en = checked;
    on_actionMeasReset_triggered();

    /*
    m_ui->textBrowser_measVpp->setEnabled(checked);
    m_ui->textBrowser_measAvg->setEnabled(checked);
    m_ui->textBrowser_measMin->setEnabled(checked);
    m_ui->textBrowser_measMax->setEnabled(checked);
    */
}

void WindowLa::on_actionMeasReset_triggered()
{
    //m_meas_max = -1000;
    //m_meas_min = 1000;

    /*
    m_ui->textBrowser_measVpp->setText("");
    m_ui->textBrowser_measAvg->setText("");
    m_ui->textBrowser_measMin->setText("");
    m_ui->textBrowser_measMax->setText("");
    */
}

void WindowLa::on_actionMeasChannel_1_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH1;

        m_ui->actionMeasChannel_2->setChecked(false);
        m_ui->actionMeasChannel_3->setChecked(false);
        m_ui->actionMeasChannel_4->setChecked(false);

        //m_ui->label_meas->setText("Measure (Channel 1)");
    }
}

void WindowLa::on_actionMeasChannel_2_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH2;

        m_ui->actionMeasChannel_1->setChecked(false);
        m_ui->actionMeasChannel_3->setChecked(false);
        m_ui->actionMeasChannel_4->setChecked(false);

        //m_ui->label_meas->setText("Measure (Channel 2)");
    }
}

void WindowLa::on_actionMeasChannel_3_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH3;

        m_ui->actionMeasChannel_1->setChecked(false);
        m_ui->actionMeasChannel_2->setChecked(false);
        m_ui->actionMeasChannel_4->setChecked(false);

        //m_ui->label_meas->setText("Measure (Channel 3)");
    }
}

void WindowLa::on_actionMeasChannel_4_triggered(bool checked)
{
    if (checked)
    {
        on_actionMeasReset_triggered();
        m_meas_ch = GRAPH_CH4;

        m_ui->actionMeasChannel_1->setChecked(false);
        m_ui->actionMeasChannel_2->setChecked(false);
        m_ui->actionMeasChannel_3->setChecked(false);

        //m_ui->label_meas->setText("Measure (Channel 4)");
    }
}

/********** Math **********/

void WindowLa::on_actionMath_1_2_triggered(bool checked)
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

void WindowLa::on_actionMath_3_4_triggered(bool checked)
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

void WindowLa::on_pushButton_cursorsHoff_clicked()
{
    m_ui->horizontalSlider_cursorH->hide();

    m_ui->pushButton_cursorsHon->show();
    m_ui->pushButton_cursorsHoff->hide();

    m_cursors1->showH(false);
    m_cursors2->showH(false);
    m_cursors3->showH(false);
    m_cursors4->showH(false);

    m_cursorsH_en = false;
}

void WindowLa::on_pushButton_cursorsHon_clicked()
{
    m_ui->horizontalSlider_cursorH->setValues(m_cursorH_min, m_cursorH_max);
    m_ui->horizontalSlider_cursorH->show();

    m_ui->pushButton_cursorsHon->hide();
    m_ui->pushButton_cursorsHoff->show();

    auto rngH = m_ui->customPlot->xAxis->range();
    auto rngV = m_ui->customPlot->yAxis->range();

    m_cursors1->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursors2->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursors3->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);
    m_cursors4->refresh(rngV.lower, rngV.upper, rngH.lower, rngH.upper, false);

    m_cursors1->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors1->setH_max(m_cursorH_max, rngH.lower, rngH.upper);
    m_cursors2->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors2->setH_max(m_cursorH_max, rngH.lower, rngH.upper);
    m_cursors3->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors3->setH_max(m_cursorH_max, rngH.lower, rngH.upper);
    m_cursors4->setH_min(m_cursorH_min, rngH.lower, rngH.upper);
    m_cursors4->setH_max(m_cursorH_max, rngH.lower, rngH.upper);

    m_cursors1->showH(true);
    m_cursors2->showH(true);
    m_cursors3->showH(true);
    m_cursors4->showH(true);

    m_cursorsH_en = true;
}

void WindowLa::on_cursorH_valuesChanged(int min, int max)
{
    m_cursorH_min = min;
    m_cursorH_max = max;

    auto rng = m_ui->customPlot->axisRect()->rangeZoomAxis(Qt::Horizontal)->range();
    //auto rng = m_ui->customPlot->xAxis->range();

    m_cursors1->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors1->setH_max(m_cursorH_max, rng.lower, rng.upper);
    m_cursors2->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors2->setH_max(m_cursorH_max, rng.lower, rng.upper);
    m_cursors3->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors3->setH_max(m_cursorH_max, rng.lower, rng.upper);
    m_cursors4->setH_min(m_cursorH_min, rng.lower, rng.upper);
    m_cursors4->setH_max(m_cursorH_max, rng.lower, rng.upper);
}

/********** QCP **********/

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

/********** right pannel - on/off **********/

/********** right pannel - on/off **********/

/********** right pannel - on/off **********/

/********** right pannel - on/off **********/

/******************************** private ********************************/


void WindowLa::closeEvent(QCloseEvent*)
{
    m_activeMsgs.clear();
    m_instrEnabled = false;

    Core::getInstance()->setMode(NO_MODE);
    emit closing(WindowLa::staticMetaObject.className());

     m_timer_plot->stop();
}

void WindowLa::showEvent(QShowEvent*)
{
    Core::getInstance()->setMode(LA);
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

    m_timer_plot->start((int)TIMER_LA_PLOT);
}

void WindowLa::rescaleYAxis()
{
    m_axis_ch1->axis(QCPAxis::atLeft)->setRange(0 - Y_LIM , 1 + Y_LIM);
    m_axis_ch2->axis(QCPAxis::atLeft)->setRange(0 - Y_LIM , 1 + Y_LIM);
    m_axis_ch3->axis(QCPAxis::atLeft)->setRange(0 - Y_LIM , 1 + Y_LIM);
    m_axis_ch4->axis(QCPAxis::atLeft)->setRange(0 - Y_LIM , 1 + Y_LIM);
}

void WindowLa::rescaleXAxis()
{
    assert(!m_t.isEmpty());
    m_axis_ch1->axis(QCPAxis::atBottom)->setRange(0, m_t[m_t.size()-1]);
    //m_axis_ch2->axis(QCPAxis::atBottom)->setRange(0, m_t_last);
    //m_axis_ch3->axis(QCPAxis::atBottom)->setRange(0, m_t_last);
    //m_axis_ch4->axis(QCPAxis::atBottom)->setRange(0, m_t_last);
}

void WindowLa::createX()
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

void WindowLa::updatePanel()
{
    createX();
    rescaleXAxis();
    rescaleYAxis();

    m_axis_ch1->setVisible(m_daqSet.ch1_en);
    m_axis_ch2->setVisible(m_daqSet.ch2_en);
    m_axis_ch3->setVisible(m_daqSet.ch3_en);
    m_axis_ch4->setVisible(m_daqSet.ch4_en);

    m_axis_ch1->axis(QCPAxis::atBottom)->setTickLabels(false);
    m_axis_ch2->axis(QCPAxis::atBottom)->setTickLabels(false);
    m_axis_ch3->axis(QCPAxis::atBottom)->setTickLabels(false);
    m_axis_ch4->axis(QCPAxis::atBottom)->setTickLabels(false);

    m_axis_ch1->setMinimumMargins(QMargins(25,15,15,0));
    m_axis_ch2->setMinimumMargins(QMargins(25,1,15,0));
    m_axis_ch3->setMinimumMargins(QMargins(25,1,15,0));
    m_axis_ch4->setMinimumMargins(QMargins(25,1,15,30));

    m_cursors1->showText(false);
    m_cursors2->showText(false);
    m_cursors3->showText(false);
    m_cursors4->showText(false);

    QCPAxisRect* top = m_axis_ch1;
    QCPAxisRect* bot = m_axis_ch4;
    QCPCursors* bot_cursors = m_cursors4;

    if (m_daqSet.ch4_en)
    {
        bot_cursors = m_cursors4;
        bot = m_axis_ch4;
        m_axis_ch4->axis(QCPAxis::atBottom)->setTickLabels(true);
    }
    else if (m_daqSet.ch3_en)
    {
        bot_cursors = m_cursors3;
        bot = m_axis_ch3;
        m_axis_ch3->axis(QCPAxis::atBottom)->setTickLabels(true);
    }
    else if (m_daqSet.ch2_en)
    {
        bot_cursors = m_cursors3;
        bot = m_axis_ch2;
        m_axis_ch2->axis(QCPAxis::atBottom)->setTickLabels(true);
    }
    else if (m_daqSet.ch1_en)
    {
        bot_cursors = m_cursors1;
        bot = m_axis_ch1;
        m_axis_ch1->axis(QCPAxis::atBottom)->setTickLabels(true);
    }

    if (m_daqSet.ch1_en)
        top = m_axis_ch1;
    else if (m_daqSet.ch2_en)
        top = m_axis_ch2;
    else if (m_daqSet.ch3_en)
        top = m_axis_ch3;
    else if (m_daqSet.ch4_en)
        top = m_axis_ch4;

    top->setMinimumMargins(QMargins(25,15,15,0));
    bot->setMinimumMargins(QMargins(25,1,15,30));

    bot_cursors->showText(true);

    enablePanel(true);
}

void WindowLa::enablePanel(bool en)
{

}
