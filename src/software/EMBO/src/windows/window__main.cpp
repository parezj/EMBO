/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window__main.h"
#include "ui_window__main.h"
#include "core.h"
#include "utils.h"
#include "settings.h"
#include "css.h"

#ifndef Q_OS_UNIX
#include "QBreakpadHandler.h"
#endif
#include "QSimpleUpdater.h"

#include <QDebug>
#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QDirIterator>
#include <QLabel>
#include <QGridLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <QListView>
#include <QSpacerItem>
#include <QFontDatabase>
#include <QThread>
#include <QTimer>
#include <QSettings>
#include <QCloseEvent>
#include <QtSerialPort/QSerialPortInfo>


WindowMain::WindowMain(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::WindowMain)
{
    QStringList addedFonts = addFontsFromResources();
    //for ( const QString& font : addedFonts )
    //    qInfo() << "Added font: " << font;
    //QFont font("Roboto");
    //QApplication::setFont(font);

    m_ui->setupUi(this);

#ifndef Q_OS_UNIX
    QBreakpadInstance.setDumpPath(QLatin1String("crashes"));
#endif

    QThread* t1 = new QThread(this);
    auto core = Core::getInstance();

    m_w_scope = new WindowScope();
    m_w_la = new WindowLa();
    m_w_vm = new WindowVm();
    m_w_cntr = new WindowCntr();
    m_w_pwm = new WindowPwm();
    m_w_sgen = new WindowSgen();

    core->emboInstruments.append(m_w_scope);
    core->emboInstruments.append(m_w_la);
    core->emboInstruments.append(m_w_vm);
    core->emboInstruments.append(m_w_cntr);
    core->emboInstruments.append(m_w_pwm);
    core->emboInstruments.append(m_w_sgen);

    qRegisterMetaType<State>("State");
    qRegisterMetaType<Msg>("Msg");
    qRegisterMetaType<MsgBoxType>("MsgBoxType");
    qRegisterMetaType<Ready>("Ready");
    qRegisterMetaType<DaqBits>("DaqBits");
    qRegisterMetaType<DaqTrigEdge>("DaqTrigEdge");
    qRegisterMetaType<DaqTrigMode>("DaqTrigMode");
    qRegisterMetaType<SgenMode>("SgenMode");

    //connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(on_close()));

    connect(core, &Core::latencyAndUptime, this, &WindowMain::on_latencyAndUptime, Qt::QueuedConnection);
    connect(core, &Core::stateChanged, this, &WindowMain::on_coreState_changed, Qt::QueuedConnection);
    connect(core, &Core::msgDisplay, this, &WindowMain::on_msgDisplay, Qt::QueuedConnection);
    connect(this, &WindowMain::openComm, core, &Core::on_openComm, Qt::QueuedConnection);
    connect(this, &WindowMain::closeComm, core, &Core::on_closeComm, Qt::QueuedConnection);
    connect(this, &WindowMain::disposeCore, core, &Core::on_dispose, Qt::QueuedConnection);

    connect(t1, SIGNAL(started()), core, SLOT(on_startThread()));
    connect(core, SIGNAL(finished()), t1, SLOT(quit()), Qt::DirectConnection);
    connect(core, SIGNAL(finished()), core, SLOT(deleteLater()));
    connect(t1, SIGNAL(finished()), t1, SLOT(deleteLater()));

    connect(m_w_scope, &WindowScope::closing, this, &WindowMain::on_instrClose);
    connect(m_w_scope, &WindowScope::showPwm, this, &WindowMain::on_showPwm);
    connect(m_w_la, &WindowLa::closing, this, &WindowMain::on_instrClose);
    connect(m_w_vm, &WindowVm::closing, this, &WindowMain::on_instrClose);
    connect(m_w_cntr, &WindowCntr::closing, this, &WindowMain::on_instrClose);
    connect(m_w_pwm, &WindowPwm::closing, this, &WindowMain::on_instrClose);
    connect(m_w_sgen, &WindowSgen::closing, this, &WindowMain::on_instrClose);

    connect(m_ui->actionEMBO_Help, SIGNAL(triggered()), Core::getInstance(), SLOT(on_actionEMBO_Help()));

    core->moveToThread(t1);
    t1->start();

    m_ui->pushButton_disconnect->hide();
    m_ui->groupBox_scope->hide();
    m_ui->groupBox_la->hide();
    m_ui->groupBox_vm->hide();
    m_ui->groupBox_pwm->hide();
    m_ui->groupBox_sgen->hide();
    m_ui->groupBox_cntr->hide();

    m_icon_plugOn = QPixmap(":/main/img/plug_on.png");
    m_icon_plugOff = QPixmap(":/main/img/plug_off.png");
    m_img_chip = QPixmap(":/main/img/chip.png");
    m_img_bluepill = QPixmap(":/main/img/bluepill2.png");
    m_img_nucleoF303 = QPixmap(":/main/img/nucleo-f303.png");
    m_img_nucleo32 = QPixmap(":/main/img/nucleo-32.png");
    m_img_unknown = QPixmap(":/main/img/unknown2.png");

    statusBarLoad();

    m_ui->groupBox_scope->setStyleSheet(CSS_INSTR_GROUP_SCOPE);
    m_ui->groupBox_la->setStyleSheet(CSS_INSTR_GROUP_LA);
    m_ui->groupBox_vm->setStyleSheet(CSS_INSTR_GROUP_VM);
    m_ui->groupBox_pwm->setStyleSheet(CSS_INSTR_GROUP_PWM);
    m_ui->groupBox_sgen->setStyleSheet(CSS_INSTR_GROUP_SGEN);
    m_ui->groupBox_cntr->setStyleSheet(CSS_INSTR_GROUP_CNTR);

    m_ui->groupBox_device->setStyleSheet(CSS_GROUP2);
    m_ui->groupBox_instr1->setStyleSheet(CSS_GROUP2);
    m_ui->groupBox_instr2->setStyleSheet(CSS_GROUP2);
    m_ui->groupBox_ports->setStyleSheet(CSS_GROUP2);

    m_ui->pushButton_connect->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_CONNECT);
    m_ui->pushButton_disconnect->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_DISCONNECT);
    m_ui->pushButton_scan->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_SCAN);

    m_ui->pushButton_scope->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_SCOPE);
    m_ui->pushButton_la->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_LA);
    m_ui->pushButton_vm->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM);
    m_ui->pushButton_cntr->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_CNTR);
    m_ui->pushButton_pwm->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_PWM);
    m_ui->pushButton_sgen->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_SGEN);

    auto updater = QSimpleUpdater::getInstance();

    updater->setDownloaderEnabled(UPDATE_URL, true);
    updater->setModuleVersion (UPDATE_URL, APP_VERSION);
    updater->setNotifyOnFinish (UPDATE_URL, true);
    updater->setNotifyOnUpdate (UPDATE_URL, true);
    updater->setUseCustomAppcast (UPDATE_URL, false);
    //updater->setDownloaderEnabled (UPDATE_URL, true);
    //updater->setMandatoryUpdate (UPDATE_URL, false);
    //updater->setModuleName(UPDATE_URL, "EMBO");

    /*
    if (QSysInfo::productType().toLower().contains("windows"))
        updater->setModuleName(UPDATE_URL, "EMBO-Windows");
    else if (QSysInfo::productType().toLower().contains("mac"))
        updater->setModuleName(UPDATE_URL, "EMBO-macOS");
    else if (QSysInfo::productType().toLower().contains("ubuntu"))
        updater->setModuleName(UPDATE_URL, "EMBO-Ubunut");
    */

    connect (updater, SIGNAL (checkingFinished  (QString)), this, SLOT(updateChangelog(QString)));
    //connect (updater, SIGNAL (appcastDownloaded (QString, QByteArray)), this,  SLOT(displayAppcast(QString, QByteArray)));

    qInfo() << "EMBO version: " << APP_VERSION;

    m_movie_logo = new QMovie(":/main/img/ctu_meas_small.gif");
    m_ui->label_cvutlogo->setMovie(m_movie_logo);
    m_movie_logo->start();
    m_movie_logo->stop();

    setDisconnected();
    on_pushButton_scan_clicked();

#if defined(Q_OS_WIN)
    m_ui->label_titlePrimary->move(TITLE_LEFT, TITLE_TOP_WIN);
    m_ui->label_titleSecondary->move(TITLE_LEFT, TITLE_TOP_WIN);
    m_ui->label_titlePorts->move(TITLE_LEFT, TITLE_TOP_WIN);
#else
    m_ui->label_titlePrimary->move(TITLE_LEFT, TITLE_TOP_UNIX);
    m_ui->label_titleSecondary->move(TITLE_LEFT, TITLE_TOP_UNIX);
    m_ui->label_titlePorts->move(TITLE_LEFT, TITLE_TOP_UNIX);
#endif
}

WindowMain::~WindowMain()
{
    delete m_ui;

    delete m_w_scope;
    delete m_w_la;
    delete m_w_vm;
    delete m_w_cntr;
    delete m_w_pwm;
    delete m_w_sgen;
}

/* private methods */

void WindowMain::statusBarLoad()
{
    m_status_icon_comm = new QLabel(this);
    m_status_comm = new QLabel(" Disconnected ", this);
    m_status_latency = new QLabel("", this);
    m_status_latency->setToolTip("[fixed spacing + real mean] (real peak)");
    m_status_latency->setMinimumWidth(220);
    m_status_uptime = new QLabel("", this);

    QSpacerItem* status_spacer1 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QLabel* status_spacer0   = new QLabel("<span>&nbsp;</span>", this);
    QLabel* status_ctu       = new QLabel("<a href='https://meas.fel.cvut.cz/' style='color: black; text-decoration:none'>&nbsp;CTU FEE&nbsp;©&nbsp;2021&nbsp;</a>", this);
    QLabel* status_spacer2   = new QLabel("<span>&nbsp;</span>", this);
    QLabel* status_spacer3   = new QLabel("<span>&nbsp;</span>", this);
    QLabel* status_spacer4   = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer5   = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer6   = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer7   = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_spacer8   = new QLabel("<span>&nbsp;&nbsp;&nbsp;</span>", this);
    QLabel* status_icon_jp   = new QLabel(this);
    QLabel* status_author    = new QLabel("<a href='https://www.jakubparez.com' style='color: black; text-decoration:none'>&nbsp;Jakub Pařez&nbsp;</a>&nbsp;", this);

    status_ctu->connect(status_ctu, &QLabel::linkActivated, [](const QString &link) {
        QDesktopServices::openUrl(QUrl(link));
    });
    status_author->connect(status_author, &QLabel::linkActivated, [](const QString &link) {
        QDesktopServices::openUrl(QUrl(link));
    });

    status_ctu->setStyleSheet(":hover{background:#FFFFFF;border-radius:5px}");
    status_author->setStyleSheet(":hover{background:#FFFFFF;border-radius:5px}");

    QWidget* widget = new QWidget();
    QFont font1("Roboto", 11, QFont::Normal);

    m_status_comm->setFont(font1);
    m_status_latency->setFont(font1);
    m_status_uptime->setFont(font1);
    status_ctu->setFont(font1);
    status_author->setFont(font1);

    QPixmap icon_jp = QPixmap(":/main/img/jp.png");

    m_status_icon_comm->setPixmap(m_icon_plugOff);
    m_status_icon_comm->setFixedWidth(15);
    m_status_icon_comm->setFixedHeight(18);
    m_status_icon_comm->setScaledContents(true);
    status_icon_jp->setPixmap(icon_jp);
    status_icon_jp->setFixedWidth(17);
    status_icon_jp->setFixedHeight(17);
    status_icon_jp->setScaledContents(true);

    m_status_line1 = new QFrame(this);
    m_status_line1->setFrameShape(QFrame::VLine);
    m_status_line1->setFrameShadow(QFrame::Plain);
    m_status_line1->setStyleSheet("color:gray;");
    m_status_line1->setFixedHeight(18);

    m_status_line2 = new QFrame(this);
    m_status_line2->setFrameShape(QFrame::VLine);
    m_status_line2->setFrameShadow(QFrame::Plain);
    m_status_line2->setStyleSheet("color:gray;");
    m_status_line2->setFixedHeight(18);

    m_status_line3 = new QFrame(this);
    m_status_line3->setFrameShape(QFrame::VLine);
    m_status_line3->setFrameShadow(QFrame::Plain);
    m_status_line3->setStyleSheet("color:gray;");
    m_status_line3->setFixedHeight(18);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(status_spacer0,     0,0, 1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_icon_comm, 0,1, 1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_comm,      0,2, 1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer4,     0,3, 1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_line1,     0,4, 1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer5,     0,5, 1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_latency,   0,6, 1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer6,     0,7, 1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_line2,     0,8, 1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer7,     0,9, 1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_uptime,    0,10,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer8,     0,11, 1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->addWidget(m_status_line3,     0,12,1,1,Qt::AlignVCenter);
    layout->addItem(status_spacer1,       0,13,1,1,Qt::AlignVCenter);
    layout->addWidget(status_ctu,         0,14,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer2,     0,15,1,1,Qt::AlignVCenter);
    layout->addWidget(status_icon_jp,     0,16,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer3,     0,17,1,1,Qt::AlignVCenter);
    layout->addWidget(status_author,      0,18,1,1,Qt::AlignVCenter);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);
}

QStringList WindowMain::addFontsFromResources(const QStringList& filters)
{
    QStringList addedFonts;
    QDirIterator iter(QStringLiteral(":/fonts"), filters, QDir::Files|QDir::Readable, QDirIterator::Subdirectories);
    while (iter.hasNext())
    {
        const QString& entry = iter.next();
        if ( QFontDatabase::addApplicationFont(entry) >= 0 )
            addedFonts << entry;
    }
    return addedFonts;
}

void WindowMain::loadSettings()
{
    QString port_saved = Settings::getValue(CFG_MAIN_PORT, "").toString();

    for(int i = 0; i < m_ui->listWidget_ports->count(); ++i)
    {
        if (m_ui->listWidget_ports->item(i)->data(Qt::UserRole) == port_saved)
            m_ui->listWidget_ports->setCurrentRow(i);
    }

    int run_month = Settings::getValue(CFG_RUN_MONTH, -1).toInt();
    int curr_month = QDate::currentDate().month();

    if (curr_month != run_month)
    {
        auto updater = QSimpleUpdater::getInstance();

        updater->setNotifyOnFinish (UPDATE_URL, false);
        updater->checkForUpdates(UPDATE_URL);
    }

    Settings::setValue(CFG_RUN_MONTH, curr_month);
}

void WindowMain::saveSettings()
{
    Settings::setValue(CFG_MAIN_PORT, m_ui->listWidget_ports->currentItem()->data(Qt::UserRole).toString());
}

void WindowMain::setConnected()
{
    m_ui->pushButton_connect->hide();
    m_ui->pushButton_disconnect->show();

    this->setWindowTitle(EMBO_TITLE2 " (" + m_ui->listWidget_ports->currentItem()->toolTip()+ ")");
    m_status_comm->setText(" Connected (" + m_ui->listWidget_ports->currentItem()->data(Qt::UserRole).toString() + ")");
    m_ui->listWidget_ports->currentItem()->setIcon(QIcon(":/main/img/serial2_busy.png"));

    m_status_icon_comm->setPixmap(m_icon_plugOn);

    m_ui->groupBox_scope->show();
    m_ui->groupBox_la->show();
    m_ui->groupBox_vm->show();
    m_ui->groupBox_pwm->show();
    m_ui->groupBox_sgen->show();
    m_ui->groupBox_cntr->show();

    auto info = Core::getInstance()->getDevInfo();

    m_ui->label_deviceName->setText(info->name);
    m_ui->label_dev_fw->setText(info->fw);
    m_ui->label_dev_ll->setText(info->ll);
    m_ui->label_dev_fcpu->setText(info->fcpu + " MHz");
    m_ui->label_dev_rtos->setText(info->rtos);
    m_ui->label_dev_comm->setText(info->comm);
    m_ui->label_dev_vref->setText(QString::number(info->ref_mv) + " mV");

    QString n = info->name.toLower();
    if (n.contains("bluepill"))
        m_ui->label_boardImg->setPixmap(m_img_bluepill);
    else if (n.contains("nucleo32"))
        m_ui->label_boardImg->setPixmap(m_img_nucleo32);
    else if (n.contains("nucleo"))
        m_ui->label_boardImg->setPixmap(m_img_nucleoF303);
    else
        m_ui->label_boardImg->setPixmap(m_img_chip);

    m_ui->label_scope_fs->setText(format_unit(info->adc_fs_12b, "Sps", 3));

    if (info->adc_bit8)
        m_ui->label_scope_mem->setText(format_unit((info->mem / 2), "", 3) + " / " + format_unit(info->mem, "S", 3));
    else
        m_ui->label_scope_mem->setText(format_unit((info->mem / 2), "S", 3));

    m_ui->label_scope_bits->setText(info->adc_bit8 ? "12 / 8 bit" : "12 bit");
    m_ui->label_scope_modes->setText(QString::number(info->daq_ch) + "ch " + QString::number(info->adc_num) + "ADC " + (info->adc_dualmode ? "D" : "") +
                                     (info->adc_dualmode && info->adc_interleaved ? "+" : "") + (info->adc_interleaved ? "I" : ""));
    m_ui->label_scope_pins->setText(info->pins_scope_vm.replace("-", ", "));

    m_ui->label_la_fs->setText(format_unit(info->la_fs, "Sps", 3));
    m_ui->label_la_mem->setText(format_unit(info->mem, "S", 3));
    //m_ui->label_la_protocols->setText("Serial, I2C, SPI");
    m_ui->label_la_pins->setText(info->pins_la.replace("-", ", "));

    m_ui->label_vm_fs->setText(format_unit(info->vm_fs, "Sps", 0));
    //m_ui->label_vm_mem->setText(format_unit(info->vm_mem, "S", 0));
    m_ui->label_vm_bits->setText("12 bit");
    m_ui->label_vm_pins->setText(info->pins_scope_vm.replace("-", ", "));

    m_ui->label_cntr_maxf->setText(format_unit(info->cntr_maxf, "Hz", 0));
    m_ui->label_cntr_timeout->setText(QString::number(info->cntr_timeout) + " ms");
    m_ui->label_cntr_pins->setText(info->pins_cntr);

    m_ui->label_pwm_mode->setText(info->pwm2 ? "2ch sync" : "1ch");
    m_ui->label_pwm_freq->setText(format_unit(info->pwm_fs, "Hz", 0));
    m_ui->label_pwm_pins->setText(info->pins_pwm.replace("-", ", "));

    if (info->dac > 0)
    {
        m_ui->label_sgen_freq->setText(format_unit(info->sgen_maxf, "Hz", 3));
        m_ui->label_sgen_mode->setText(info->dac == 2 ? "2ch" : "1ch");
        m_ui->label_sgen_mem->setText(format_unit(info->sgen_maxmem, "S", 0));
        m_ui->label_sgen_pins->setText(info->pins_sgen.replace("-", ", "));
        m_ui->groupBox_sgen->show();
    }
    else m_ui->groupBox_sgen->hide();

    QString s1 = info->pwm2 ? "s" : "";
    QString s2 = info->dac == 2 ? "s" : "";

    m_w_scope->setWindowTitle("EMBO - Oscilloscope [" + QString::number(info->daq_ch) + " channel] (pins: " + m_ui->label_scope_pins->text() + ")");
    m_w_la->setWindowTitle("EMBO - Logic Analyzer [" + QString::number(info->daq_ch) + " channel] (pins: " + m_ui->label_la_pins->text() + ")");
    m_w_vm->setWindowTitle("EMBO - Voltmeter [" + QString::number(info->daq_ch) + " channel] (Pins: " + m_ui->label_vm_pins->text() + ")");
    m_w_cntr->setWindowTitle("EMBO - Counter [1 channel] (pin: " + m_ui->label_cntr_pins->text() + ")");
    m_w_pwm->setWindowTitle("EMBO - PWM Generator [" + QString((info->pwm2 ? "2" : "1")) + " channel] (pin" + s1 + ": " + m_ui->label_pwm_pins->text() + ")");
    m_w_sgen->setWindowTitle("EMBO - Signal Generator [" + QString((info->dac == 2 ? "2" : "1")) + " channel] (pin" + s2 + ": " + m_ui->label_sgen_pins->text() + ")");

    m_status_latency->setText("?");
    m_status_uptime->setText("?");
    m_status_line1->show();
    m_status_line2->show();
    m_status_line3->show();

    m_ui->label_dev1->show();
    m_ui->label_dev2->show();
    m_ui->label_dev3->show();
    m_ui->label_dev4->show();
    m_ui->label_dev5->show();
    m_ui->label_dev6->show();

    m_ui->label_dev_fw->show();
    m_ui->label_dev_ll->show();
    m_ui->label_dev_comm->show();
    m_ui->label_dev_fcpu->show();
    m_ui->label_dev_rtos->show();
    m_ui->label_dev_vref->show();

    m_movie_logo->start();

    m_connected = true;
}

void WindowMain::setDisconnected()
{
    this->setWindowTitle(EMBO_TITLE2);

    m_ui->pushButton_connect->setText("Connect");
    m_ui->pushButton_connect->setEnabled(true);
    m_ui->pushButton_disconnect->hide();
    m_ui->pushButton_connect->show();

    m_status_comm->setText(" Disconnected");
    m_status_icon_comm->setPixmap(m_icon_plugOff);

    auto item = m_ui->listWidget_ports->currentItem();
    if (item != Q_NULLPTR)
        item->setIcon(QIcon(":/main/img/serial2.png"));

    m_ui->listWidget_ports->setEnabled(true);
    m_ui->pushButton_scan->setEnabled(true);
    m_ui->groupBox_scope->hide();
    m_ui->groupBox_la->hide();
    m_ui->groupBox_vm->hide();
    m_ui->groupBox_pwm->hide();
    m_ui->groupBox_sgen->hide();
    m_ui->groupBox_cntr->hide();

    m_ui->label_deviceName->setText("NOT CONNECTED");
    m_ui->label_dev_fw->setText("-");
    m_ui->label_dev_ll->setText("-");
    m_ui->label_dev_fcpu->setText("-");
    m_ui->label_dev_rtos->setText("-");
    m_ui->label_dev_comm->setText("-");
    m_ui->label_dev_vref->setText("-");
    m_ui->label_boardImg->setPixmap(m_img_unknown);

    m_ui->label_scope_fs->setText("-");
    m_ui->label_scope_mem->setText("-");
    m_ui->label_scope_bits->setText("-");
    m_ui->label_scope_modes->setText("-");
    m_ui->label_scope_pins->setText("-");

    m_ui->label_la_fs->setText("-");
    m_ui->label_la_mem->setText("-");
    //m_ui->label_la_protocols->setText("-");
    m_ui->label_la_pins->setText("-");

    m_ui->label_vm_fs->setText("-");
    //m_ui->label_vm_mem->setText("-");
    m_ui->label_vm_bits->setText("-");
    m_ui->label_vm_pins->setText("-");

    m_ui->label_cntr_maxf->setText("-");
    m_ui->label_cntr_timeout->setText("-");
    m_ui->label_cntr_pins->setText("-");

    m_ui->label_pwm_mode->setText("-");
    m_ui->label_pwm_freq->setText("-");
    m_ui->label_pwm_pins->setText("-");

    m_ui->label_sgen_freq->setText("-");
    m_ui->label_sgen_mem->setText("-");
    m_ui->label_sgen_pins->setText("-");

    m_w_scope->close();
    m_w_la->close();
    m_w_vm->close();
    m_w_cntr->close();
    m_w_pwm->close();
    m_w_sgen->close();

    m_status_latency->setText("");
    m_status_uptime->setText("");
    m_status_line1->hide();
    m_status_line2->hide();
    m_status_line3->hide();

    m_ui->label_dev1->hide();
    m_ui->label_dev2->hide();
    m_ui->label_dev3->hide();
    m_ui->label_dev4->hide();
    m_ui->label_dev5->hide();
    m_ui->label_dev6->hide();

    m_ui->label_dev_fw->hide();
    m_ui->label_dev_ll->hide();
    m_ui->label_dev_comm->hide();
    m_ui->label_dev_fcpu->hide();
    m_ui->label_dev_rtos->hide();
    m_ui->label_dev_vref->hide();

    m_movie_logo->stop();
    m_movie_logo->start();
    m_movie_logo->stop();

    //on_instrClose(WindowScope::staticMetaObject.className());
    //on_instrClose(WindowCntr::staticMetaObject.className());
    //on_instrClose(WindowPwm::staticMetaObject.className());
    //on_instrClose(WindowSgen::staticMetaObject.className());

    m_connected = false;
}

/* private slots */

void WindowMain::closeEvent(QCloseEvent* event)
{
    if (event != Q_NULLPTR)
        event->ignore();

    if (m_connected)
    {
        /*
        this->activateWindow();
        if (QMessageBox::Yes == QMessageBox::question(this, EMBO_TITLE, "Device is connected! Do you want to disconnect and exit anyway?",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
        */
            m_close_init = true;
            on_pushButton_disconnect_clicked();
        //}
        return;
    }

    m_w_scope->close();
    m_w_la->close();
    m_w_vm->close();
    m_w_cntr->close();
    m_w_pwm->close();
    m_w_sgen->close();

    auto core = Core::getInstance();
    emit disposeCore();
    if (core != Q_NULLPTR)
        core->thread()->wait();

    qInfo() << "Core thread joined";

    if (event != Q_NULLPTR)
    {
        event->accept();
        qInfo() << "Quit1";
    }
}

void WindowMain::on_actionAbout_triggered()
{
    QMessageBox::about(this, EMBO_TITLE, EMBO_ABOUT_TXT);
}

void WindowMain::on_pushButton_scan_clicked()
{
    m_ui->listWidget_ports->clear();

    auto ports = QSerialPortInfo::availablePorts();
    int ports_sz = ports.size();

    m_ui->label_titlePorts->setText("Ports (" + QString::number(ports_sz) + ")");

    if (ports_sz > 0)
    {
        for(auto port : ports)
        {
            qInfo() << port.portName() << " " << port.description() << " " << port.manufacturer() << " " << port.isBusy();

            QListWidgetItem* item = new QListWidgetItem(m_ui->listWidget_ports);
            item->setIcon(port.isBusy() ? QIcon(":/main/img/serial2_red.png") : QIcon(":/main/img/serial2.png"));
            QString val = port.portName() + (port.description().size() > 0 ? (" — " + port.description()) : "");
            item->setText(val.size() <= 20 ? val : val.left(16) + "...");
            item->setToolTip(val + (port.manufacturer().size() > 0 ? (" (" + port.manufacturer() + ")") : ""));
            item->setData(Qt::UserRole, port.portName());

            m_ui->listWidget_ports->addItem(item);
        }
        m_ui->listWidget_ports->setCurrentRow(0);
        m_ui->pushButton_connect->setEnabled(true);
    }
    else
    {
        m_ui->pushButton_connect->setEnabled(false);
    }

    loadSettings();
}

void WindowMain::on_pushButton_connect_clicked()
{
    m_ui->listWidget_ports->setEnabled(false);
    m_ui->pushButton_scan->setEnabled(false);
    //m_ui->pushButton_connect->setText("Wait...");
    m_ui->pushButton_connect->setEnabled(false);

    m_status_comm->setText(" Connecting...");

    QString selPort = m_ui->listWidget_ports->currentItem()->data(Qt::UserRole).toString();

    saveSettings();

    emit openComm(selPort);
}

void WindowMain::on_pushButton_disconnect_clicked()
{
    m_ui->pushButton_connect->setText("Wait...");
    m_ui->pushButton_connect->setEnabled(false);

    m_w_scope->hide();
    m_w_la->hide();
    m_w_vm->hide();
    m_w_cntr->hide();
    m_w_pwm->hide();
    m_w_sgen->hide();

    emit closeComm(false);
}

void WindowMain::on_latencyAndUptime(int latency_fix, int latency_mean, int latency_max, const QString uptime)
{
    m_status_latency->setText("Latency: " + QString::number(latency_fix) + "+" + QString::number(latency_mean) +
                              " ms (max " + QString::number(latency_max) + " ms)");
    m_status_uptime->setText("Uptime: " + uptime);

    if (m_w_vm->isVisible())
        m_ui->label_dev_vref->setText(QString::number(Core::getInstance()->getDevInfo()->ref_mv) + " mV");
}

void WindowMain::on_coreState_changed(const State newState)
{
    if (newState == CONNECTED)
    {
        setConnected();
    }
    else if (newState == DISCONNECTED)
    {
        setDisconnected();

        if (m_close_init)
        {
            m_close_init = false;
            closeEvent(Q_NULLPTR);
            qInfo() << "Quit2";
            QCoreApplication::quit();
        }
    }
    m_state_old = newState;
}

void WindowMain::on_msgDisplay(const QString text, MsgBoxType type)
{
    msgBox(this, text, type);
}

void WindowMain::on_instrClose(const char* className)
{
    if (className == WindowScope::staticMetaObject.className() ||
        className == WindowLa::staticMetaObject.className() ||
        className == WindowVm::staticMetaObject.className())
    {
        instrFirstRowEnable(true);
    }
    else if (className == WindowCntr::staticMetaObject.className())
    {
        m_ui->pushButton_cntr->setEnabled(true);
        m_ui->pushButton_cntr->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_CNTR);

        m_ui->groupBox_cntr->setEnabled(true);
        m_ui->groupBox_cntr->setStyleSheet(CSS_INSTR_GROUP_CNTR);
    }
    else if (className == WindowPwm::staticMetaObject.className())
    {
        m_ui->pushButton_pwm->setEnabled(true);
        m_ui->pushButton_pwm->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_PWM);

        m_ui->groupBox_pwm->setEnabled(true);
        m_ui->groupBox_pwm->setStyleSheet(CSS_INSTR_GROUP_PWM);
    }
    else if (className == WindowSgen::staticMetaObject.className())
    {
        m_ui->pushButton_sgen->setEnabled(true);
        m_ui->pushButton_sgen->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_SGEN);

        m_ui->groupBox_sgen->setEnabled(true);
        m_ui->groupBox_sgen->setStyleSheet(CSS_INSTR_GROUP_SGEN);
    }
}

void WindowMain::instrFirstRowEnable(bool enable)
{
    if (enable)
    {
        m_ui->pushButton_scope->setEnabled(true);
        m_ui->pushButton_la->setEnabled(true);
        m_ui->pushButton_vm->setEnabled(true);

        m_ui->groupBox_scope->setStyleSheet(CSS_INSTR_GROUP_SCOPE);
        m_ui->groupBox_la->setStyleSheet(CSS_INSTR_GROUP_LA);
        m_ui->groupBox_vm->setStyleSheet(CSS_INSTR_GROUP_VM);

        m_ui->pushButton_scope->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_SCOPE);
        m_ui->pushButton_la->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_LA);
        m_ui->pushButton_vm->setStyleSheet(CSS_BUTTON_ON CSS_BUTTON_VM);
    }
    else
    {
        m_ui->groupBox_scope->setStyleSheet(CSS_INSTR_GROUP_OFF);
        m_ui->groupBox_la->setStyleSheet(CSS_INSTR_GROUP_OFF);
        m_ui->groupBox_vm->setStyleSheet(CSS_INSTR_GROUP_OFF);
    }
}

void WindowMain::on_pushButton_scope_clicked()
{   
    m_w_scope->show();
    m_w_scope->setWindowState( (windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    m_w_scope->raise();  // MacOS
    m_w_scope->activateWindow(); // Windows

    m_ui->pushButton_scope->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_SCOPE);

    m_ui->groupBox_la->setStyleSheet(CSS_INSTR_GROUP_OFF);
    m_ui->groupBox_vm->setStyleSheet(CSS_INSTR_GROUP_OFF);

    m_ui->pushButton_la->setEnabled(false);
    m_ui->pushButton_vm->setEnabled(false);

    instrFirstRowEnable(false);
}

void WindowMain::on_pushButton_la_clicked()
{
    m_w_la->show();
    m_w_la->setWindowState( (windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    m_w_la->raise();  // MacOS
    m_w_la->activateWindow(); // Windows

    m_ui->pushButton_la->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_LA);

    m_ui->groupBox_scope->setStyleSheet(CSS_INSTR_GROUP_OFF);
    m_ui->groupBox_vm->setStyleSheet(CSS_INSTR_GROUP_OFF);

    m_ui->pushButton_scope->setEnabled(false);
    m_ui->pushButton_vm->setEnabled(false);

    instrFirstRowEnable(false);
}

void WindowMain::on_pushButton_vm_clicked()
{
    m_w_vm->show();
    m_w_vm->setWindowState( (windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    m_w_vm->raise();  // MacOS
    m_w_vm->activateWindow(); // Windows

    m_ui->pushButton_vm->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_VM);

    m_ui->groupBox_scope->setStyleSheet(CSS_INSTR_GROUP_OFF);
    m_ui->groupBox_la->setStyleSheet(CSS_INSTR_GROUP_OFF);

    m_ui->pushButton_scope->setEnabled(false);
    m_ui->pushButton_la->setEnabled(false);

    instrFirstRowEnable(false);
}

void WindowMain::on_pushButton_cntr_clicked()
{
    m_w_cntr->show();
    m_w_cntr->setWindowState( (windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    m_w_cntr->raise();  // MacOS
    m_w_cntr->activateWindow(); // Windows

    m_ui->pushButton_cntr->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_CNTR);
    m_ui->groupBox_cntr->setStyleSheet(CSS_INSTR_GROUP_OFF);
}

void WindowMain::on_pushButton_pwm_clicked()
{
    m_w_pwm->show();
    m_w_pwm->setWindowState( (windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    m_w_pwm->raise();  // MacOS
    m_w_pwm->activateWindow(); // Windows

    m_ui->pushButton_pwm->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_PWM);
    m_ui->groupBox_pwm->setStyleSheet(CSS_INSTR_GROUP_OFF);
}

void WindowMain::on_pushButton_sgen_clicked()
{
    m_w_sgen->show();
    m_w_sgen->setWindowState( (windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    m_w_sgen->raise();  // MacOS
    m_w_sgen->activateWindow(); // Windows

    m_ui->pushButton_sgen->setStyleSheet(CSS_BUTTON_OFF CSS_BUTTON_SGEN);
    m_ui->groupBox_sgen->setStyleSheet(CSS_INSTR_GROUP_OFF);
}

void WindowMain::on_actionCheck_Updates_triggered()
{
    auto updater = QSimpleUpdater::getInstance();

    updater->setNotifyOnFinish (UPDATE_URL, true);
    updater->checkForUpdates(UPDATE_URL);

    //updateChangelog(UPDATE_URL);
}

void WindowMain::on_showPwm()
{
    m_w_pwm->show();
}

void WindowMain::updateChangelog (const QString& url)
{
    auto updater = QSimpleUpdater::getInstance();

    QMessageBox::information(this, EMBO_TITLE, updater->getChangelog(url));
    qInfo() << updater->getChangelog(url);
}

/*
void WindowMain::displayAppcast (const QString& url, const QByteArray& reply)
{
    //auto updater = QSimpleUpdater::getInstance();

    QString text = "This is the downloaded appcast: <p><pre>" +
                   QString::fromUtf8 (reply) +
                   "</pre></p><p> If you need to store more information on the "
                   "appcast (or use another format), just use the "
                   "<b>QSimpleUpdater::setCustomAppcast()</b> function. "
                   "It allows your application to interpret the appcast "
                   "using your code and not QSU's code.</p>";

    QMessageBox::information(this, EMBO_TITLE, text);
    qInfo() << text;
}
*/
