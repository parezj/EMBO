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

    //connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(on_close()));

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
    connect(m_w_la, &WindowLa::closing, this, &WindowMain::on_instrClose);
    connect(m_w_vm, &WindowVm::closing, this, &WindowMain::on_instrClose);
    connect(m_w_cntr, &WindowCntr::closing, this, &WindowMain::on_instrClose);
    connect(m_w_pwm, &WindowPwm::closing, this, &WindowMain::on_instrClose);
    connect(m_w_sgen, &WindowSgen::closing, this, &WindowMain::on_instrClose);

    core->moveToThread(t1);
    t1->start();

    m_ui->pushButton_disconnect->hide();
    m_ui->groupBox_scope->hide();
    m_ui->groupBox_la->hide();
    m_ui->groupBox_vm->hide();
    m_ui->groupBox_pwm->hide();
    m_ui->groupBox_sgen->hide();
    m_ui->groupBox_cntr->hide();

    statusBarLoad();

    m_ui->groupBox_scope->setStyleSheet(QString(CSS_INSTR_GROUP_SCOPE));
    m_ui->groupBox_la->setStyleSheet(QString(CSS_INSTR_GROUP_LA));
    m_ui->groupBox_vm->setStyleSheet(QString(CSS_INSTR_GROUP_VM));
    m_ui->groupBox_pwm->setStyleSheet(QString(CSS_INSTR_GROUP_PWM));
    m_ui->groupBox_sgen->setStyleSheet(QString(CSS_INSTR_GROUP_SGEN));
    m_ui->groupBox_cntr->setStyleSheet(QString(CSS_INSTR_GROUP_CNTR));

    QString style2(CSS_GROUP2);

    m_ui->groupBox_device->setStyleSheet(style2);
    m_ui->groupBox_instr1->setStyleSheet(style2);
    m_ui->groupBox_instr2->setStyleSheet(style2);
    m_ui->groupBox_ports->setStyleSheet(style2);

    QString style3(CSS_BUTTON);

    m_ui->pushButton_connect->setStyleSheet(style3);
    m_ui->pushButton_disconnect->setStyleSheet(style3);
    m_ui->pushButton_scan->setStyleSheet(style3);

    m_ui->pushButton_scope->setStyleSheet(style3);
    m_ui->pushButton_la->setStyleSheet(style3);
    m_ui->pushButton_vm->setStyleSheet(style3);
    m_ui->pushButton_cntr->setStyleSheet(style3);
    m_ui->pushButton_pwm->setStyleSheet(style3);
    m_ui->pushButton_sgen->setStyleSheet(style3);

    on_pushButton_scan_clicked();
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
    m_status_comm = new QLabel(" Disconnected ");
    QSpacerItem* status_spacer1 = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QLabel* status_ctu = new QLabel("<a href='https://meas.fel.cvut.cz/' style='color: black; text-decoration:none'>CTU FEE&nbsp;-&nbsp;2021</a>");
    QLabel* status_spacer2 = new QLabel("<span>&nbsp;&nbsp;</span>");
    QLabel* status_spacer3 = new QLabel("<span>&nbsp;&nbsp;</span>");
    QLabel* status_icon_jp = new QLabel(this);
    QLabel* status_author = new QLabel("<a href='https://www.jakubparez.com' style='color: black; text-decoration:none'>Jakub Pařez</a>&nbsp;");

    status_ctu->connect(status_ctu, &QLabel::linkActivated, [](const QString &link) {
        QDesktopServices::openUrl(QUrl(link));
    });
    status_author->connect(status_author, &QLabel::linkActivated, [](const QString &link) {
        QDesktopServices::openUrl(QUrl(link));
    });

    status_ctu->setStyleSheet(":hover{background:#FFFFFF}");
    status_author->setStyleSheet(":hover{background:#FFFFFF}");

    QWidget* widget = new QWidget();
    QFont font1("Roboto", 11, QFont::Normal);

    m_status_comm->setFont(font1);
    status_ctu->setFont(font1);
    status_author->setFont(font1);

    m_icon_plugOn = QPixmap(":/main/resources/img/plug_on.png");
    m_icon_plugOff = QPixmap(":/main/resources/img/plug_off.png");
    m_img_bluepill = QPixmap(":/main/resources/img/bluepill2.png");
    m_img_nucleoF303 = QPixmap(":/main/resources/img/nucleo-f303.png");
    m_img_unknown = QPixmap(":/main/resources/img/unknown2.png");
    QPixmap icon_jp = QPixmap(":/main/resources/img/jp.png");

    m_status_icon_comm->setPixmap(m_icon_plugOff);
    m_status_icon_comm->setFixedWidth(15);
    m_status_icon_comm->setFixedHeight(18);
    m_status_icon_comm->setScaledContents(true);
    status_icon_jp->setPixmap(icon_jp);
    status_icon_jp->setFixedWidth(17);
    status_icon_jp->setFixedHeight(17);
    status_icon_jp->setScaledContents(true);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(m_status_icon_comm,0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(m_status_comm,0,1,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->addItem(status_spacer1,0,2,1,1,Qt::AlignVCenter);
    layout->addWidget(status_ctu,0,3,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer2,0,4,1,1,Qt::AlignVCenter);
    layout->addWidget(status_icon_jp,0,5,1,1,Qt::AlignVCenter);
    layout->addWidget(status_spacer3,0,6,1,1,Qt::AlignVCenter);
    layout->addWidget(status_author,0,7,1,1,Qt::AlignVCenter);
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
      if (m_ui->listWidget_ports->item(i)->text() == port_saved)
          m_ui->listWidget_ports->setCurrentRow(i);
  }
}

void WindowMain::saveSettings()
{
    Settings::setValue(CFG_MAIN_PORT, m_ui->listWidget_ports->currentIndex().data().toString());
}

void WindowMain::setConnected()
{
    m_ui->pushButton_connect->hide();
    m_ui->pushButton_disconnect->show();

    this->setWindowTitle(EMBO_TITLE2 " (" + Core::getInstance()->getPort()+ ")");
    m_status_comm->setText(" Connected (" + Core::getInstance()->getPort() + ")");

    m_status_icon_comm->setPixmap(m_icon_plugOn);
    m_ui->label_boardImg->setPixmap(m_img_nucleoF303);

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
    m_ui->label_dev_fcpu->setText(QString::number(info->fcpu) + " MHz");
    m_ui->label_dev_rtos->setText(info->rtos);
    m_ui->label_dev_comm->setText(info->comm);
    m_ui->label_dev_vref->setText(QString::number(info->ref_mv) + " mV");
    if (info->name.toLower().contains("bluepill"))
        m_ui->label_boardImg->setPixmap(m_img_bluepill);
    else if (info->name.toLower().contains("nucleo"))
        m_ui->label_boardImg->setPixmap(m_img_nucleoF303);

    m_ui->label_scope_fs->setText(format_unit(info->adc_fs_12b, "Sps", 0) + " / ch");
    m_ui->label_scope_mem->setText(format_unit((info->mem / 2) / (1 * 2), "B", 0) +
                                   (info->adc_bit8 ? " / " + format_unit(info->mem / (1 * 2), "B", 0) : ""));
    m_ui->label_scope_bits->setText(info->adc_bit8 ? "12 / 8 bit" : "12 bit");
    m_ui->label_scope_modes->setText("4ch " + QString::number(info->adc_num) + "ADC " + (info->adc_dualmode ? "D" : "") +
                                     (info->adc_dualmode && info->adc_interleaved ? "+" : "") + (info->adc_interleaved ? "I" : ""));
    m_ui->label_scope_pins->setText(info->pins_scope_vm.replace("-", ", "));

    m_ui->label_la_fs->setText(format_unit(info->la_fs, "Sps", 0) + " / ch");
    m_ui->label_la_mem->setText(format_unit(info->mem, "B", 0));
    m_ui->label_la_protocols->setText("Serial, I2C, SPI");
    m_ui->label_la_pins->setText(info->pins_la.replace("-", ", "));

    m_ui->label_vm_fs->setText(format_unit(info->vm_fs, "Sps", 0) + " / ch");
    m_ui->label_vm_mem->setText(format_unit(info->vm_mem, "S", 0));
    m_ui->label_vm_bits->setText("12 bit");
    m_ui->label_vm_pins->setText(info->pins_scope_vm.replace("-", ", "));

    m_ui->label_cntr_mode->setText("Precise/Fast"); // format_unit(info->cntr_freq, "Hz", 0)
    m_ui->label_cntr_timeout->setText(QString::number(info->cntr_timeout) + " ms");
    m_ui->label_cntr_pins->setText(info->pins_cntr);

    m_ui->label_pwm_mode->setText("2ch sync");
    m_ui->label_pwm_freq->setText(format_unit(info->pwm_fs, "Hz", 0));
    m_ui->label_pwm_pins->setText(info->pins_pwm.replace("-", ", "));

    if (info->dac)
    {
        m_ui->label_sgen_freq->setText(format_unit(info->sgen_maxf, "Hz", 0));
        m_ui->label_sgen_mem->setText(format_unit(info->sgen_maxmem, "S", 0));
        m_ui->label_sgen_pins->setText(info->pins_sgen);
        m_ui->groupBox_sgen->show();
    }
    //else m_ui->groupBox_sgen->hide(); // TODO DEBUG

    m_w_scope->setWindowTitle("EMBO - Oscilloscope [4 channel] (pins: " + m_ui->label_scope_pins->text() + ")");
    m_w_la->setWindowTitle("EMBO - Logic Analyzer [4 channel] (pins: " + m_ui->label_la_pins->text() + ")");
    m_w_vm->setWindowTitle("EMBO - Voltmeter [4 channel] (Pins: " + m_ui->label_vm_pins->text() + ")");
    m_w_cntr->setWindowTitle("EMBO - Counter (pin: " + m_ui->label_cntr_pins->text() + ")");
    m_w_pwm->setWindowTitle("EMBO - PWM Generator [2 channel] (pins: " + m_ui->label_pwm_pins->text() + ")");
    m_w_sgen->setWindowTitle("EMBO - Signal Generator (pin: " + m_ui->label_sgen_pins->text() + ")");

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
    m_ui->label_la_protocols->setText("-");
    m_ui->label_la_pins->setText("-");

    m_ui->label_vm_fs->setText("-");
    m_ui->label_vm_mem->setText("-");
    m_ui->label_vm_bits->setText("-");
    m_ui->label_vm_pins->setText("-");

    m_ui->label_cntr_mode->setText("-");
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

    //on_instrClose(WindowScope::staticMetaObject.className());
    //on_instrClose(WindowCntr::staticMetaObject.className());
    //on_instrClose(WindowPwm::staticMetaObject.className());
    //on_instrClose(WindowSgen::staticMetaObject.className());

    m_connected = false;
}

/* private slots */

void WindowMain::closeEvent(QCloseEvent* event)
{
    event->ignore();
    if (m_connected)
    {
        this->activateWindow();
        if (QMessageBox::Yes == QMessageBox::question(this, EMBO_TITLE, "Device is connected. Do you want to disconnect and exit anyway?",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
            m_close_init = true;
            on_pushButton_disconnect_clicked();
        }
        return;
    }

    event->accept();

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

    qInfo() << "Core thread quit and joined";
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

    m_ui->groupBox_ports->setTitle("Ports (" + QString::number(ports_sz) + ")");

    if (ports_sz > 0)
    {
        for(auto port : ports)
        {
            QListWidgetItem* item = new QListWidgetItem(m_ui->listWidget_ports);
            item->setIcon(QIcon(":/main/resources/img/serial2.png"));
            item->setText(port.portName());
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

    QString selPort = m_ui->listWidget_ports->currentIndex().data().toString();
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
            this->close();
        }
    }
    m_state_old = newState;
}

void WindowMain::on_msgDisplay(const QString text, MsgBoxType type)
{
    if (type == INFO)
        QMessageBox::information(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::NoButton);
    else if (type == QUESTION)
        QMessageBox::question(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::Yes | QMessageBox::No);
    else if (type == WARNING)
        QMessageBox::warning(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::NoButton);
    else if (type == CRITICAL)
        QMessageBox::critical(this, EMBO_TITLE, text, QMessageBox::Ok, QMessageBox::NoButton);
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
        m_ui->pushButton_cntr->setStyleSheet(QString(CSS_BUTTON));

        m_ui->groupBox_cntr->setEnabled(true);
        m_ui->groupBox_cntr->setStyleSheet(QString(CSS_INSTR_GROUP_CNTR));
    }
    else if (className == WindowPwm::staticMetaObject.className())
    {
        m_ui->pushButton_pwm->setEnabled(true);
        m_ui->pushButton_pwm->setStyleSheet(QString(CSS_BUTTON));

        m_ui->groupBox_pwm->setEnabled(true);
        m_ui->groupBox_pwm->setStyleSheet(QString(CSS_INSTR_GROUP_PWM));
    }
    else if (className == WindowSgen::staticMetaObject.className())
    {
        m_ui->pushButton_sgen->setEnabled(true);
        m_ui->pushButton_sgen->setStyleSheet(QString(CSS_BUTTON));

        m_ui->groupBox_sgen->setEnabled(true);
        m_ui->groupBox_sgen->setStyleSheet(QString(CSS_INSTR_GROUP_SGEN));
    }
}

void WindowMain::instrFirstRowEnable(bool enable)
{
    if (enable)
    {
        m_ui->pushButton_scope->setEnabled(true);
        m_ui->pushButton_la->setEnabled(true);
        m_ui->pushButton_vm->setEnabled(true);

        m_ui->groupBox_scope->setStyleSheet(QString(CSS_INSTR_GROUP_SCOPE));
        m_ui->groupBox_la->setStyleSheet(QString(CSS_INSTR_GROUP_LA));
        m_ui->groupBox_vm->setStyleSheet(QString(CSS_INSTR_GROUP_VM));

        m_ui->pushButton_scope->setStyleSheet(QString(CSS_BUTTON));
        m_ui->pushButton_la->setStyleSheet(QString(CSS_BUTTON));
        m_ui->pushButton_vm->setStyleSheet(QString(CSS_BUTTON));
    }
    else
    {
        m_ui->groupBox_scope->setStyleSheet(QString(CSS_INSTR_GROUP_OFF));
        m_ui->groupBox_la->setStyleSheet(QString(CSS_INSTR_GROUP_OFF));
        m_ui->groupBox_vm->setStyleSheet(QString(CSS_INSTR_GROUP_OFF));

        //m_ui->pushButton_scope->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));
        //m_ui->pushButton_la->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));
        //m_ui->pushButton_vm->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));
    }
}

void WindowMain::on_pushButton_scope_clicked()
{
    m_w_scope->show();
    m_w_scope->activateWindow();

    m_ui->pushButton_la->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));
    m_ui->pushButton_vm->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));

    m_ui->pushButton_la->setEnabled(false);
    m_ui->pushButton_vm->setEnabled(false);

    instrFirstRowEnable(false);
}

void WindowMain::on_pushButton_la_clicked()
{
    m_w_la->show();
    m_w_la->activateWindow();

    m_ui->pushButton_scope->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));
    m_ui->pushButton_vm->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));

    m_ui->pushButton_scope->setEnabled(false);
    m_ui->pushButton_vm->setEnabled(false);

    instrFirstRowEnable(false);
}

void WindowMain::on_pushButton_vm_clicked()
{
    m_w_vm->show();
    m_w_vm->activateWindow();

    m_ui->pushButton_scope->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));
    m_ui->pushButton_la->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));

    m_ui->pushButton_scope->setEnabled(false);
    m_ui->pushButton_la->setEnabled(false);

    instrFirstRowEnable(false);
}

void WindowMain::on_pushButton_cntr_clicked()
{
    m_w_cntr->show();
    m_w_cntr->activateWindow();

    //m_ui->pushButton_cntr->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));
    m_ui->groupBox_cntr->setStyleSheet(QString(CSS_INSTR_GROUP_OFF));
}

void WindowMain::on_pushButton_pwm_clicked()
{
    m_w_pwm->show();
    m_w_pwm->activateWindow();

    //m_ui->pushButton_pwm->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));
    m_ui->groupBox_pwm->setStyleSheet(QString(CSS_INSTR_GROUP_OFF));
}

void WindowMain::on_pushButton_sgen_clicked()
{
    m_w_sgen->show();
    m_w_sgen->activateWindow();

    //m_ui->pushButton_sgen->setStyleSheet(QString(CSS_INSTR_BUTTON_OFF));
    m_ui->groupBox_sgen->setStyleSheet(QString(CSS_INSTR_GROUP_OFF));
}
