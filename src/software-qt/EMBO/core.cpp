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
#include <QElapsedTimer>
#include <QSettings>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>


Core* Core::m_instance = Q_NULLPTR;

Core::Core(QObject* parent) : QObject(parent)
{
}

Core::~Core()
{   
    qInfo() << "Core destroyed";
}

void Core::on_startThread()
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
    //m_msg_stb = new Msg_Stb(this);
    //m_msg_cls = new Msg_Cls(this);
    m_msg_dummy = new Msg_Dummy(this);
    m_msg_sys_lims = new Msg_SYS_Lims(this);
    m_msg_sys_info = new Msg_SYS_Info(this);
    m_msg_sys_mode = new Msg_SYS_Mode(this);
    m_msg_sys_uptime = new Msg_SYS_Uptime(this);

    m_devInfo = new DevInfo(this);

    connect(m_serial, &QSerialPort::errorOccurred, this, &Core::on_serial_errorOccurred);
    connect(m_serial, &QSerialPort::readyRead, this, &Core::on_serial_readyRead);

    connect(m_timer_rxTimeout, &QTimer::timeout, this, &Core::on_timer_rxTimeout);
    connect(m_timer_comm, &QTimer::timeout, this, &Core::on_timer_comm);
    connect(m_timer_render, &QTimer::timeout, this, &Core::on_timer_render);

    qInfo() << "Core thread started";
}

bool Core::openComm(QString port)
{
    m_serial->setPortName(port);
    m_state = OPENING;
    emit stateChanged(m_state);

    if (m_serial->open(QIODevice::ReadWrite))
    {
        qInfo() << ">>Connected1<<";
        m_state = CONNECTING1;
        emit stateChanged(m_state);

        m_serial->clear();

        m_mainBuffer.clear();
        m_waitingMsgs.clear();
        m_activeMsgs.clear();

        assert(m_activeMsgs.isEmpty());
        m_activeMsgs.append(m_msg_dummy);

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

void Core::openCommInit()
{
    m_open_comm = true;
}

bool Core::closeComm()
{
    m_state = DISCONNECTED;
    m_serial->close(); // TODO enque
    m_timer_rxTimeout->stop();
    m_timer_comm->stop();
    m_timer_render->stop();

    qInfo() << ">>Disconnected<<";
    emit stateChanged(m_state);
    return true;
}

void Core::startComm()
{
    qInfo() << ">>Connected2<<";
    m_state = CONNECTED;
    emit stateChanged(m_state);
    m_timer_comm->start(TIMER_COMM);
    m_timer_latency.restart();
    m_latencyIt = 0;
    m_latencyCnt = 0;
    m_timer_render->start(TIMER_RENDER);
}

void Core::err(QString name, bool needClose)
{
    emit msgDisplay(name, needClose ? CRITICAL : WARNING);
    qInfo() << "ERR: " + name;

    if (needClose)
        closeComm();
}

void Core::msgAdd(Msg* msg, bool isQuery, QString params)
{
    assert(msg != Q_NULLPTR);

    msg->setIsQuery(isQuery);
    if (!params.isEmpty())
        msg->setParams(params);

    m_waitingMsgs.append(msg);
}

int Core::getLatencyMs()
{
    m_latencyVals[m_latencyIt++] = m_latency > TIMER_COMM ? m_latency - TIMER_COMM : 0;

    if (m_latencyCnt < LATENCY_AVG)
        m_latencyCnt++;

    if (m_latencyIt >= LATENCY_AVG)
        m_latencyIt = 0;

    int ret = 0;
    for (int i = 0; i < m_latencyCnt; i++)
        ret += m_latencyVals[i];

    return ret / m_latencyCnt;
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
    m_timer_comm->stop();
}

void Core::openComm2()
{
    m_open_comm = false;
    m_state = CONNECTING2;

    m_activeMsgs.append(m_msg_idn);
    m_activeMsgs.append(m_msg_sys_lims);
    m_activeMsgs.append(m_msg_sys_info);
    m_msg_sys_mode->setIsQuery(true);
    m_activeMsgs.append(m_msg_sys_mode);

    send();
}

/* slots */

void Core::on_openComm(const QString port)
{
    openComm(port);
}

/*
void Core::on_msgAdd(Msg* msg)
{
    msgAdd(msg);
}
*/

void Core::on_closeComm(bool force)
{
    if (force || m_state != CONNECTED)
        closeComm();
    else
        m_close_init = true;
}

void Core::on_dispose()
{
    if (m_state == CONNECTED)
        closeComm();

    m_timer_rxTimeout->deleteLater();
    m_timer_comm->deleteLater();
    m_timer_render->deleteLater();

    emit finished();
    //this->thread()->quit();
}

/* private slots */

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

        int msg_cnt = 0;
        QStringList messages;
        int bin_header_len;
        int hashIdx = m_mainBuffer.indexOf('#');

        if (hashIdx > -1) // binary message
        {
            int buf_sz = m_mainBuffer.size();
            auto left_part = m_mainBuffer.left(hashIdx);

            messages = left_part.split(EMBO_NEWLINE, Qt::SkipEmptyParts);
            msg_cnt = left_part.count(EMBO_NEWLINE);

            if (m_mainBuffer.size() > hashIdx + 5)
            {
                int n = (m_mainBuffer.data())[hashIdx + 1].digitValue();
                int bin_len = m_mainBuffer.mid(hashIdx + 2, n).toInt();
                int bin_len_total = 1 + n + bin_len;

                if (buf_sz >= hashIdx + bin_len_total)
                {
                    bin_header_len = 2 + n;
                    messages.append(m_mainBuffer.mid(hashIdx, 1 + bin_len_total));
                    msg_cnt++;

                    auto right_part = m_mainBuffer.right(hashIdx + 1 + bin_len_total);
                    auto messages2 = right_part.split(EMBO_NEWLINE, Qt::SkipEmptyParts);
                    if (!messages2.isEmpty())
                    {
                        messages.append(messages2);
                        msg_cnt += right_part.count(EMBO_NEWLINE);
                    }
                }
            }
        }
        else // standard messages
        {
            messages = m_mainBuffer.split(EMBO_NEWLINE, Qt::SkipEmptyParts);
            msg_cnt = m_mainBuffer.count(EMBO_NEWLINE);
        }

        //qInfo() << "rx buffer: " << m_mainBuffer;
        m_timer_rxTimeout->stop();
        m_timer_rxTimeout->start();

        for(int i = 0; i < msg_cnt; i++) // iterate all full msgs
        {
            //qInfo() << "rx msg: " << messages[i];

            m_mainBuffer = m_mainBuffer.right(m_mainBuffer.size() - (messages[i].size() + 2));

            if (messages[i] == EMBO_READY_A || messages[i] == EMBO_READY_N || messages[i] == EMBO_READY_D)
            {
                qInfo() << messages[i];
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

                if (submessage.at(0) == '#')
                    m_activeMsgs[m_submsgIt++]->fire(submessage.right(submessage.size() - bin_header_len));
                else
                    m_activeMsgs[m_submsgIt++]->fire(submessage); // do main virtual action
            }

            if (m_submsgIt == activeMsg_size) // success - do post actions
            {
                m_submsgIt = 0;
                m_timer_rxTimeout->stop();
                m_activeMsgs.clear();

                if (m_state == CONNECTING2)
                    startComm();
                else if (m_state == CONNECTED)
                    m_timer_comm->start();
            }
        }
        if (m_open_comm)
            openComm2();
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
    if (m_close_init)
    {
        m_close_init = false;
        closeComm();
        return;
    }

    m_latency = m_timer_latency.elapsed();
    m_timer_latency.restart();

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

    int waitingSize = m_waitingMsgs.size();
    if (waitingSize > 0)
    {
        m_activeMsgs.append(m_waitingMsgs.mid(0, waitingSize));
        m_waitingMsgs.remove(0, waitingSize);
    }

    for (auto instr : emboInstruments)
    {
        auto activeMsg = instr->getActiveMsg();
        if (activeMsg != Q_NULLPTR)
            m_activeMsgs.append(activeMsg);
    }

    m_activeMsgs.append(m_msg_sys_uptime);

    send();
}

void Core::on_timer_render()
{
    emit latencyAndUptime(getLatencyMs(), getUptime());
}
