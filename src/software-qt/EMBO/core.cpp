/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "core.h"
#include "utils.h"
#include "msg.h"

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QSettings>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>


/****************************** Messages - SYS ******************************/

void Msg_Idn::on_dataRx()
{
    qInfo() << "IDN: " << m_rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (tokens.size() != 4)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    core->getDevInfo()->name = tokens[1];
    core->getDevInfo()->fw = tokens[2];
}

void Msg_Rst::on_dataRx()
{
    qInfo() << "RST: " << m_rxData;
    auto core = Core::getInstance(this);

    if (!m_rxData.contains(EMBO_OK))
        core->err("Reset failed!", false);
}

void Msg_SYS_Lims::on_dataRx()
{
    qInfo() << "SYS:LIM: " <<  m_rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (tokens.size() != 14)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    core->getDevInfo()->adc_fs_12b = tokens[0].toInt();
    core->getDevInfo()->adc_fs_8b = tokens[1].toInt();
    core->getDevInfo()->mem = tokens[2].toInt();
    core->getDevInfo()->la_fs = tokens[3].toInt();
    core->getDevInfo()->pwm_fs = tokens[4].toInt();
    core->getDevInfo()->adc_num = (tokens[5])[0].digitValue();
    core->getDevInfo()->adc_dualmode = tokens[5].contains('D');
    core->getDevInfo()->adc_interleaved = tokens[5].contains('I');
    core->getDevInfo()->adc_bit8 = tokens[6] == '1';
    core->getDevInfo()->dac = tokens[7] == '1';
    core->getDevInfo()->vm_fs = tokens[8].toInt();
    core->getDevInfo()->vm_mem = tokens[9].toInt();
    core->getDevInfo()->cntr_freq = tokens[10].toInt();
    core->getDevInfo()->cntr_timeout = tokens[11].toInt();
    core->getDevInfo()->sgen_maxf = tokens[12].toInt();
    core->getDevInfo()->sgen_maxmem = tokens[13].toInt();
}


void Msg_SYS_Info::on_dataRx()
{
    qInfo() << "SYS:INFO: " <<  m_rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (tokens.size() != 10)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    core->getDevInfo()->rtos = tokens[0];
    core->getDevInfo()->ll = tokens[1];
    core->getDevInfo()->comm = tokens[2];
    core->getDevInfo()->fcpu = tokens[3].toInt();
    core->getDevInfo()->ref_mv = tokens[4].toInt();
    core->getDevInfo()->pins_scope_vm = tokens[5];
    core->getDevInfo()->pins_la = tokens[6];
    core->getDevInfo()->pins_cntr = tokens[7];
    core->getDevInfo()->pins_pwm = tokens[8];
    core->getDevInfo()->pins_sgen = tokens[9];
}

void Msg_SYS_Mode::on_dataRx()
{
    qInfo() << "SYS:MODE: " <<  m_rxData;
    auto core = Core::getInstance(this);

    if (getIsQuery())
    {
        if (m_rxData.contains("SCOPE"))
            core->setMode(SCOPE, true);
        else if (m_rxData.contains("VM"))
            core->setMode(VM, true);
        else if (m_rxData.contains("LA"))
            core->setMode(LA, true);
        else
            core->err(INVALID_MSG + m_rxData, true);
    }
    else
    {
        if (!m_rxData.contains(EMBO_OK))
            core->err("Mode set failed!", true);
    }
}

/***************************** Messages - VM ****************************/

void Msg_VM_Read::on_dataRx()
{
    qInfo() << "VM:READ: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

/***************************** Messages - SCOP **************************/

void Msg_SCOP_Read::on_dataRx()
{
    qInfo() << "SCOP:READ: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_SCOP_Set::on_dataRx()
{
    qInfo() << "SCOP:SET: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_SCOP_ForceTrig::on_dataRx()
{
    qInfo() << "SCOP:FORC: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_SCOP_Average::on_dataRx()
{
    qInfo() << "SCOP:AVER: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

/***************************** Messages - LA ****************************/

void Msg_LA_Read::on_dataRx()
{
    qInfo() << "LA:READ: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_LA_Set::on_dataRx()
{
    qInfo() << "LA:SET: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_LA_ForceTrig::on_dataRx()
{
    qInfo() << "LA:FORC: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

/***************************** Messages - CNTR **************************/

void Msg_CNTR_Enable::on_dataRx()
{
    qInfo() << "CNTR:ENA: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_CNTR_Read::on_dataRx()
{
    qInfo() << "CNTR:READ: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

/***************************** Messages - SGEN **************************/

void Msg_SGEN_Set::on_dataRx()
{
    qInfo() << "SGEN:SET: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

/***************************** Messages - PWM ***************************/

void Msg_PWM_Set::on_dataRx()
{
    qInfo() << "PWM:SET: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

/********************************* Core *********************************/

Core* Core::m_instance = Q_NULLPTR;

Core::Core(QObject* parent) : QObject(parent)
{
}

Core::~Core()
{
    qInfo() << "Core destroyed";
}

void Core::on_start()
{
    m_serial = new QSerialPort();
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    m_timer_rxTimeout = new QTimer();
    m_timer_render = new QTimer();
    m_timer_comm = new QTimer();

    m_timer_rxTimeout->setTimerType(Qt::PreciseTimer);
    m_timer_comm->setTimerType(Qt::PreciseTimer);
    m_timer_render->setTimerType(Qt::PreciseTimer);

    m_msg_idn = new Msg_Idn(this);
    m_msg_rst = new Msg_Rst(this);
    m_msg_sys_lims = new Msg_SYS_Lims(this);
    m_msg_sys_info = new Msg_SYS_Info(this);
    m_msg_sys_mode = new Msg_SYS_Mode(this);
    m_msg_vm_read = new Msg_VM_Read(this);
    m_msg_scope_set = new Msg_SCOP_Set(this);
    m_msg_scope_read = new Msg_SCOP_Read(this);
    m_msg_scope_forcetrig = new Msg_SCOP_ForceTrig(this);
    m_msg_scope_average = new Msg_SCOP_Average(this);
    m_msg_la_set = new Msg_LA_Set(this);
    m_msg_la_read = new Msg_LA_Read(this);
    m_msg_la_forcetrig = new Msg_LA_ForceTrig(this);
    m_msg_cntr_enable = new Msg_CNTR_Enable(this);
    m_msg_cntr_read = new Msg_CNTR_Read(this);
    m_msg_sgen_set = new Msg_SGEN_Set(this);
    m_msg_pwm_set = new Msg_PWM_Set(this);

    devInfo = new DevInfo(this);

    connect(m_serial, &QSerialPort::errorOccurred, this, &Core::on_serial_errorOccurred);
    connect(m_serial, &QSerialPort::readyRead, this, &Core::on_serial_readyRead);

    connect(m_timer_rxTimeout, &QTimer::timeout, this, &Core::on_timer_rxTimeout);
    connect(m_timer_comm, &QTimer::timeout, this, &Core::on_timer_comm);
    connect(m_timer_render, &QTimer::timeout, this, &Core::on_timer_render);

    qInfo() << "Core started";
}

bool Core::open(QString port)
{
    m_serial->setPortName(port);
    m_state = OPENING;
    emit stateChanged(m_state);

    if (m_serial->open(QIODevice::ReadWrite))
    {
        m_state = CONNECTING;
        emit stateChanged(m_state);

        m_serial->flush();
        m_mainBuffer.clear();
        m_waitingMsgs.clear();
        m_activeMsgs.clear();

        assert(m_activeMsgs.isEmpty());
        m_activeMsgs.append(m_msg_idn);
        m_activeMsgs.append(m_msg_sys_lims);
        m_activeMsgs.append(m_msg_sys_info);
        m_msg_sys_mode->setIsQuery(true);
        m_activeMsgs.append(m_msg_sys_mode);
        send();

        return true;
    }
    else
    {
        err("Serial port opening failed!", true);
        m_state = DISCONNECTED;
        emit stateChanged(m_state);
        return false;
    }
}

bool Core::close()
{
    m_state = DISCONNECTED;
    m_serial->close(); // TODO enque
    m_timer_rxTimeout->stop();
    m_timer_comm->stop();
    m_timer_render->stop();

    emit stateChanged(m_state);
    return true;
}

void Core::start()
{
    m_state = CONNECTED;
    emit stateChanged(m_state);
    m_timer_comm->start(TIMER_COMM);
    m_timer_render->start(TIMER_RENDER);
}

void Core::err(QString name, bool needClose)
{
    emit errorHappend(name);
    if (needClose)
        close();
}

void Core::dispose()
{
    emit finished();
}

/* private */

void Core::send()
{
    assert(m_activeMsgs.size() > 0);

    QString tx;
    int it = 0;

    for(auto msg : m_activeMsgs)
    {
        if (it > 0)
            tx.append(EMBO_DELIM1);

        tx.append( msg->getCmd() +
                  (msg->getIsQuery() ? "?" : "") +
                  (msg->getParams().isEmpty() ? "" : " " + msg->getParams()));
        it++;
    }
    tx.append(EMBO_NEWLINE);

    m_serial->write(tx.toStdString().c_str(), tx.size());

    qInfo() << "sent: " << tx;
    m_timer_rxTimeout->start(TIMER_RX);
}

/* slots */

void Core::on_open(const QString port)
{
    open(port);
}

void Core::on_msgAdd(Msg* const msg)
{
    m_waitingMsgs.append(msg);
}

void Core::on_close()
{
    if (m_state == CONNECTED)
        close_init = true;
    else
        close();
}

void Core::on_serial_errorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
        err(m_serial->errorString(), true);
}

void Core::on_serial_readyRead()
{
    try // exceptions DO NOT work
    {
        const QByteArray data = m_serial->readAll();
        QString str = QString::fromUtf8(data);

        m_mainBuffer = m_mainBuffer.append(data);
        QStringList messages = m_mainBuffer.split(EMBO_NEWLINE, Qt::SkipEmptyParts);

        //qInfo() << "rx buffer: " << m_mainBuffer;

        for(int i = 0; i < m_mainBuffer.count(EMBO_NEWLINE); i++) // iterate all full msgs
        {
            //qInfo() << "rx msg: " << messages[i];

            m_mainBuffer = m_mainBuffer.right(m_mainBuffer.size() - (messages[i].size() + 2));

            if (messages[i] == EMBO_READY_A || messages[i] == EMBO_READY_N || messages[i] == EMBO_READY_D)
            {
                // emit READY signal
                continue;
            }
            QStringList submessages = messages[i].split(EMBO_DELIM1, Qt::SkipEmptyParts);

            m_submsgIt = 0;
            int activeMsg_size = m_activeMsgs.size();

            for(const QString submessage : submessages)
            {
                if (m_state == DISCONNECTED)
                    return;
                if (m_submsgIt >= activeMsg_size)
                {
                    err(COMM_FATAL_ERR + messages[i] + m_mainBuffer, true);
                    return;
                }

                m_activeMsgs[m_submsgIt++]->fire(submessage); // do main actions
            }
            if (m_submsgIt == activeMsg_size) // success - do post actions
            {
                m_submsgIt = 0;
                m_timer_rxTimeout->stop();
                m_activeMsgs.clear();

                if (m_state == CONNECTING)
                    start();
                else if (m_state == CONNECTED)
                    m_timer_comm->start();
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::exception_ptr p = std::current_exception();
        err((p ? p.__cxa_exception_type()->name() : " exception raised"), true);
    }
    catch (...)
    {
        err("exception raised", true);
    }
}

void Core::on_timer_rxTimeout()
{
    err("Communication timeout!", true);
}

void Core::on_timer_comm()
{
    if (close_init)
    {
        close_init = false;
        close();
        return;
    }

    if (!m_activeMsgs.isEmpty())
    {
        qInfo() << "Communication is throttling!";
        return;
    }

    if (m_mode != m_mode_last)
    {
        m_msg_sys_mode->setIsQuery(false);
        m_msg_sys_mode->setParams(m_mode == LA ? "LA" : (m_mode == SCOPE ? "SCOPE" : "VM"));
        m_activeMsgs.append(m_msg_sys_mode);
    }
    m_mode_last = m_mode;

    m_activeMsgs.append(m_waitingMsgs);
    m_waitingMsgs.clear();

    //if (cntr.enabled)
    // m_activeMsgs.append(CNTR READ);

    if (m_activeMsgs.isEmpty())
        m_activeMsgs.append(m_msg_idn);

    send();
}

void Core::on_timer_render()
{

}
