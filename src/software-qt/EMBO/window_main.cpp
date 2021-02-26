/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_main.h"
#include "ui_window_main.h"
#include "core.h"
#include "utils.h"

#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <QListView>
#include <QFontDatabase>
#include <QtSerialPort/QSerialPortInfo>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    auto core = Core::getInstance(this);
    connect(core, &Core::stateChanged, this, &MainWindow::on_coreState_changed);
    connect(core, &Core::errorHappend, this, &MainWindow::on_coreError_happend);

    connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(on_close()));

    m_ui->pushButton_disconnect->hide();
    m_ui->groupBox_scope->hide();
    m_ui->groupBox_la->hide();
    m_ui->groupBox_vm->hide();
    m_ui->groupBox_pwm->hide();
    m_ui->groupBox_sgen->hide();
    m_ui->groupBox_cntr->hide();

    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Bold.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Light.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Medium.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Regular.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Semibold.ttf");

    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Bold.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Light.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Medium.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Regular.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Semibold.ttf");

    QFont font("SF-UI-Display");
    font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);

    QWidget* widget = new QWidget();
    QFont font1( "SF-UI-Display", 10, QFont::Normal);
    m_status_icon = new QLabel(this);
    QLabel* status_txt = new QLabel(" Disconnected");
    QLabel* status_author = new QLabel("CTU FEE - Jakub Pařez 2021 ");

    m_img_plugOn = QPixmap(":/resources/img/plug_on.png");
    m_img_plugOff= QPixmap(":/resources/img/plug_off.png");
    m_img_bluepill = QPixmap(":/resources/img/bluepill2.png");
    m_img_nucleoF303 = QPixmap(":/resources/img/nucleo-f303.png");
    m_img_unknown = QPixmap(":/resources/img/unknown2.png");

    m_status_icon->setPixmap(m_img_plugOff);
    m_status_icon->setFixedWidth(15);
    m_status_icon->setFixedHeight(18);
    m_status_icon->setScaledContents(true);

    status_txt->setObjectName("status_txt");
    status_author->setObjectName("status_author");
    status_txt->setFont(font1);
    status_author->setFont(font1);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(m_status_icon,0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(status_txt,0,1,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->addWidget(status_author,0,2,1,1,Qt::AlignVCenter | Qt::AlignRight);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);

    QString style1 = "QGroupBox {background-color: rgb(238,238,238);border: 1px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \
                      QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}";

    //QString style1b = "QGroupBox {background-color: rgb(238,238,238);border: 1px solid gray; border-radius: 0px;  margin-top: 0.5em;}; \
    //                  QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}";

    m_ui->groupBox_scope->setStyleSheet(style1);
    m_ui->groupBox_la->setStyleSheet(style1);
    m_ui->groupBox_vm->setStyleSheet(style1);
    m_ui->groupBox_pwm->setStyleSheet(style1);
    m_ui->groupBox_sgen->setStyleSheet(style1);
    m_ui->groupBox_cntr->setStyleSheet(style1);

    QString style2 = "QGroupBox {background-color: rgb(220,220,220);border: 0px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \
                      QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}";

    m_ui->groupBox_device->setStyleSheet(style2);
    m_ui->groupBox_instr1->setStyleSheet(style2);
    m_ui->groupBox_instr2->setStyleSheet(style2);
    m_ui->groupBox_ports->setStyleSheet(style2);

    on_pushButton_scan_clicked();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_close()
{
    if (m_connected)
        Core::getInstance(this)->close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msg;
    msg.setText("About");
    msg.exec();
}

void MainWindow::on_actionOpen_triggered()
{
    QMessageBox msg;
    msg.setText("Open");
    msg.exec();
}

void MainWindow::on_pushButton_scan_clicked()
{
    m_ui->listWidget_ports->clear();

    for(const QSerialPortInfo port : QSerialPortInfo::availablePorts())
        m_ui->listWidget_ports->addItem(port.portName());

    if (m_ui->listWidget_ports->children().count() > 0)
        m_ui->listWidget_ports->setCurrentRow(0);

    m_ui->pushButton_connect->setEnabled(m_ui->listWidget_ports->children().count() > 0);
}

void MainWindow::on_pushButton_connect_clicked()
{
    m_ui->listWidget_ports->setEnabled(false);
    m_ui->pushButton_scan->setEnabled(false);
    m_ui->pushButton_connect->setText("Connecting");
    m_ui->pushButton_connect->setEnabled(false);

    QLabel *status_txt = m_ui->statusbar->findChild<QLabel*>("status_txt");
    status_txt->setText(" Connecting...");

    QModelIndex selIdx = m_ui->listWidget_ports->currentIndex();
    QString selPort = selIdx.data().toString();

    if (!Core::getInstance(this)->open(selPort))
    {
        on_coreError_happend("Serial port opening failed!");
        setDisconnected();
    }
}

void MainWindow::on_pushButton_disconnect_clicked()
{
    Core::getInstance(this)->close();
}

void MainWindow::setConnected()
{
    m_ui->pushButton_connect->hide();
    m_ui->pushButton_disconnect->show();

    QLabel *status_txt = m_ui->statusbar->findChild<QLabel*>("status_txt");
    status_txt->setText(" Connected (" + Core::getInstance(this)->getPort() + ")");
    m_status_icon->setPixmap(m_img_plugOn);
    m_ui->label_boardImg->setPixmap(m_img_nucleoF303);

    m_ui->groupBox_scope->show();
    m_ui->groupBox_la->show();
    m_ui->groupBox_vm->show();
    m_ui->groupBox_pwm->show();
    m_ui->groupBox_sgen->show();
    m_ui->groupBox_cntr->show();

    auto info = Core::getInstance(this)->devInfo;

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

    m_ui->label_scope_fs->setText(format_unit(info->adc_fs_12b, "Sps"));
    m_ui->label_scope_mem->setText(format_unit((info->mem / 2) / (1 * 2), "B") +
                                   (info->adc_bit8 ? " / " + format_unit(info->mem / (1 * 2), "B") : ""));
    m_ui->label_scope_bits->setText(info->adc_bit8 ? "12 / 8 bit" : "12 bit");
    m_ui->label_scope_modes->setText("4ch " + QString::number(info->adc_num) + "ADC " + (info->adc_dualmode ? "D" : "") +
                                     (info->adc_dualmode && info->adc_interleaved ? "+" : "") + (info->adc_interleaved ? "I" : ""));
    m_ui->label_scope_pins->setText(info->pins_scope_vm.replace("-", ", "));

    m_ui->label_la_fs->setText(format_unit(info->la_fs, "Sps"));
    m_ui->label_la_mem->setText(format_unit(info->mem, "B"));
    m_ui->label_la_protocols->setText("Serial, I2C, SPI");
    m_ui->label_la_pins->setText(info->pins_la.replace("-", ", "));

    m_ui->label_vm_fs->setText(format_unit(info->vm_fs, "Sps"));
    m_ui->label_vm_mem->setText(format_unit(info->vm_mem, "S"));
    m_ui->label_vm_bits->setText("12 bit");
    m_ui->label_vm_pins->setText(info->pins_scope_vm.replace("-", ", "));

    m_ui->label_cntr_freq->setText(format_unit(info->cntr_freq, "Hz"));
    m_ui->label_cntr_timeout->setText(format_unit(info->cntr_timeout, "ms"));
    m_ui->label_cntr_pins->setText(info->pins_cntr);

    m_ui->label_pwm_freq->setText(format_unit(info->pwm_fs, "Hz"));
    m_ui->label_pwm_pins->setText(info->pins_pwm.replace("-", ", "));

    if (info->dac)
    {
        m_ui->label_sgen_freq->setText(format_unit(info->sgen_maxf, "Hz"));
        m_ui->label_sgen_mem->setText(format_unit(info->sgen_maxmem, "S"));
        m_ui->label_sgen_pins->setText(info->pins_sgen);
        m_ui->groupBox_sgen->show();
    }
    else m_ui->groupBox_sgen->hide();

    m_connected = true;
}

void MainWindow::setDisconnected()
{
    m_ui->pushButton_connect->setText("Connect");
    m_ui->pushButton_connect->setEnabled(true);
    m_ui->pushButton_disconnect->hide();
    m_ui->pushButton_connect->show();

    QLabel *status_txt = m_ui->statusbar->findChild<QLabel*>("status_txt");
    status_txt->setText(" Disconnected");
    m_status_icon->setPixmap(m_img_plugOff);

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

    m_ui->label_cntr_freq->setText("-");
    m_ui->label_cntr_timeout->setText("-");
    m_ui->label_cntr_pins->setText("-");

    m_ui->label_pwm_freq->setText("-");
    m_ui->label_pwm_pins->setText("-");

    m_ui->label_sgen_freq->setText("-");
    m_ui->label_sgen_mem->setText("-");
    m_ui->label_sgen_pins->setText("-");

    m_connected = false;
}

void MainWindow::on_coreState_changed(State newState)
{
    if (newState == CONNECTED)
    {
        setConnected();
    }
    else if (newState == DISCONNECTED)
    {
        setDisconnected();
    }
}

void MainWindow::on_coreError_happend(QString name)
{
    QMessageBox msg("EMBO", name,
                   QMessageBox::Warning, QMessageBox::Ok | QMessageBox::Default,
                   QMessageBox::NoButton, QMessageBox::NoButton);
    msg.setWindowIcon(QIcon(":/resources/img/icon.png"));
    msg.exec();
}
