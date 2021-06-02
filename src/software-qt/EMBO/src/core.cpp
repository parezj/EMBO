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
#include <QDesktopServices>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>


#define TIMER_COMM          10
#define TIMER_COMM_MIN      1
#define TIMER_RX            1500
#define TIMER_RENDER        100

#define MOVEMEAN_LATENCY    100


Core* Core::m_instance = Q_NULLPTR;

Core::Core(QObject* parent) : QObject(parent)
{
    m_meanLatency.setSize(MOVEMEAN_LATENCY);
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

    m_timer_rxTimeout->setSingleShot(true);
    m_timer_comm->setSingleShot(true);

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
    m_meanLatency.reset();
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
    //if (!params.isEmpty())
    msg->setParams(params);

    m_waitingMsgs.append(msg);
}

void Core::getLatencyMs(double& mean, double& max)
{
    mean = m_meanLatency.getMean(); // m_latency > TIMER_COMM ? m_latency - TIMER_COMM : 0);
    max = m_meanLatency.getMax();
}

void Core::sendRst(Mode mode)
{
    msgAdd(m_msg_rst, false, (mode == SCOPE ? "S" : (mode == LA ? "L" : "")));
    //msgAdd(m_msg_sys_mode, false, (mode == SCOPE ? "SCOPE" : (mode == LA ? "LA" : "VM"))); // TODO CHECK
}

void Core::on_actionEMBO_Help()
{
#if defined(Q_OS_WIN)
    QString help_path = QDir(QDir::currentPath() + QDir::separator() + "doc").filePath("EMBO.chm");
    qInfo() << help_path;
    QDesktopServices::openUrl(QUrl::fromUserInput(help_path));
#elif defined(Q_OS_UNIX) || defined(Q_OS_MAC)
    QDesktopServices::openUrl(QUrl(HELP_URL));
#endif
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

    m_latency = m_timer_latency.elapsed();
    m_meanLatency.addVal(m_latency);
    m_timer_latency.restart();
}

void Core::openComm2()
{
    m_open_comm = false;
    m_state = CONNECTING2;

    m_activeMsgs.append(m_msg_idn);
    m_activeMsgs.append(m_msg_sys_lims);
    m_activeMsgs.append(m_msg_sys_info);
    //m_msg_sys_mode->setIsQuery(true);
    //m_msg_sys_mode->setParams("");
    //m_activeMsgs.append(m_msg_sys_mode);

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
    /************************************* 1. READ ALL - APPEND TO BUFFER  *************************************/

    m_mainBuffer.append(m_serial->readAll());

    /************************************* 2. SPLIT BUFFER INTO MESSAGES  **************************************/

    int msg_cnt = 0;
    QByteArrayList messages;
    int bin_header_len = 0;
    int bin_len_total = 0;
    int bin_msg_it = -1;
    int hashIdx = m_mainBuffer.indexOf('#');

    if (hashIdx > -1) // binary message is somewhere in the buffer
    {
        int buf_sz = m_mainBuffer.size();
        auto left_part = m_mainBuffer.left(hashIdx);

        if (m_mainBuffer.size() > hashIdx + 5)
        {
            int n = m_mainBuffer[hashIdx + 1] - '0';
            int bin_len = m_mainBuffer.mid(hashIdx + 2, n).toInt();
            bin_len_total = 1 + n + bin_len;
            int bin_msg_start = 0;
            int bin_msg_end = 0;

            if (buf_sz >= hashIdx + bin_len_total) // binary message is complete into messages
            {
                bin_header_len = 2 + n;
                bin_msg_start = hashIdx;
                bin_msg_end = hashIdx + 1 + bin_len_total;
                bin_msg_it = 0;

                // split for message skipping binary message
                int j = 0;
                for(int i = 0; i < bin_msg_start; i++) { // split left side of buffer into messages
                    if (m_mainBuffer.at(i) == '\n') {
                        messages.append(m_mainBuffer.mid(j, (i - 1) - j));
                        msg_cnt++;
                        bin_msg_it++;
                        j = i + 1;
                    }
                }
                for(int i = bin_msg_end + 1; i < m_mainBuffer.length(); i++) { // split right side of buffer
                    if (m_mainBuffer.at(i) == '\n') {
                        messages.append(m_mainBuffer.mid(j, (i - 1) - j));
                        msg_cnt++;
                        j = i + 1;
                    }
                }
            }
        }
    }
    else // standard text messages only
    {
        // split for message
        messages = m_mainBuffer.split('\n');
        msg_cnt = m_mainBuffer.count('\n');

        for (int r = 0; r < messages.size(); r++) // remove \r
            if (!messages[r].isEmpty())
                messages[r] = messages[r].remove(messages[r].size() - 1, 1);
    }

    //qInfo() << "MSG CNT: " << msg_cnt;

    m_timer_rxTimeout->start(); // restart timeout timer


    /***************************************** 3. ITERATE MESSAGES  ******************************************/


    for(int i = 0; i < msg_cnt; i++) // iterate all full messages and split them into submessages
    {
        if (messages[i].isEmpty()) // skip empty message
            continue;

        //qInfo() << "rx msg: " << messages[i];

        m_mainBuffer = m_mainBuffer.right(m_mainBuffer.size() - (messages[i].size() + 2)); // remove message from buffer

        /************************************* 4. HANDLE ASYNC MESSAGE  *************************************/

        Ready ready = Ready::NOT_READY;

        if (messages[i].contains(EMBO_READY_A)) ready = Ready::READY_AUTO;
        if (messages[i].contains(EMBO_READY_N)) ready = Ready::READY_NORMAL;
        if (messages[i].contains(EMBO_READY_S)) ready = Ready::READY_SINGLE;
        if (messages[i].contains(EMBO_READY_F)) ready = Ready::READY_FORCED;
        if (messages[i].contains(EMBO_READY_D)) ready = Ready::READY_DISABLED;

        if (ready != Ready::NOT_READY) // handle RDY async message, which is different
        {
            qInfo() << messages[i];
            auto toks = messages[i].split(',');

            if (toks.size() == 2)
            {
                emit daqReady(ready, toks[1].toInt());
                continue;
            }
            else
            {
                err(COMM_FATAL_ERR + messages[i] + m_mainBuffer, true);
                return;
            }
        }

        /******************************** 5. SPLIT MESSAGE INTO SUBMESSAGES  *********************************/

        QByteArrayList submessages;

        if (i == bin_msg_it) // if message contains binary message, split to submessage is tricky
        {
            int bin_msg_start = messages[i].indexOf('#');
            int bin_msg_end = bin_msg_start + bin_len_total;

            // split for submessage skipping binary message
            int j = 0;
            int msg_len = messages[i].length();

            for(int k = 0; k < bin_msg_start; k++) { // split left side of message to submessage
                if (messages[i].at(k) == ';') {
                    submessages.append(messages[i].mid(j, k - j));
                    j = k + 1;
                }
            }
            for(int k = bin_msg_end + 1; k < msg_len; k++) { // split right side of message to submessage
                if (messages[i].at(k) == ';') {
                    submessages.append(messages[i].mid(j, k - j));
                    j = k + 1;
                }
            }
            if (j < msg_len)
                submessages.append(messages[i].mid(j, msg_len));

            //qInfo() << "BIN MSG submsg cnt: " << submessages.size();
        }
        else // split text message into submsg
        {
            submessages = messages[i].split(';');

            //qInfo() << "TXT MSG submsg cnt:" << submessages.size();
        }

        m_submsgIt = 0;
        int activeMsg_size = m_activeMsgs.size();

        /************************************* 6. ITERATE SUBMESSAGES ***************************************/

        for(const QByteArray submessage : submessages) // now iterate all submessages and do virtual actions
        {
            if (submessage.isEmpty()) // skip empty submessage
                continue;

            if (m_state == DISCONNECTED) // if closing return
                return;

            if (m_submsgIt >= activeMsg_size) // safety guard - if submessage iterator dont match current state return error
            {
                err(COMM_FATAL_ERR + messages[i] + m_mainBuffer, true);
                return;
            }

            /************************************* 7. EMIT CALLBACKS ****************************************/

            if (submessage.at(0) == '#')
                m_activeMsgs[m_submsgIt++]->fire(submessage.right(submessage.size() - bin_header_len)); // fire binary data action
            else
                m_activeMsgs[m_submsgIt++]->fire(QString(submessage)); // fire standard text message action
        }

        /************************************** 8. LAST MESSAGE - CLEANUP ***********************************/

        if (m_submsgIt == activeMsg_size) // success - do post actions, clean up, reset timers
        {
            m_submsgIt = 0;
            m_timer_rxTimeout->stop();
            m_activeMsgs.clear();

            m_commTimeoutMs = TIMER_COMM - m_latencyAvgMs;
            if (m_commTimeoutMs < TIMER_COMM_MIN)
                m_commTimeoutMs = TIMER_COMM_MIN;

            if (m_state == CONNECTING2)
                startComm();
            else if (m_state == CONNECTED)
                m_timer_comm->start(m_commTimeoutMs);
        }
    }
    if (m_open_comm)
        openComm2();
}

void Core::on_timer_rxTimeout()
{
    err("Communication timeout!", true);
}

void Core::on_timer_comm()
{
    if (m_close_init) // init close
    {
        m_close_init = false;
        closeComm();
        return;
    }

    if (!m_activeMsgs.isEmpty()) // CPU is not keeping up
    {
        qInfo() << "Communication is throttling!";
        return;
    }

    if (m_mode != NO_MODE && m_mode != m_mode_last) // mode change
    {
        m_msg_sys_mode->setIsQuery(false);
        m_msg_sys_mode->setParams(m_mode == LA ? "LA" : (m_mode == SCOPE ? "SCOPE" : "VM"));
        m_activeMsgs.append(m_msg_sys_mode);
    }
    m_mode_last = m_mode;

    int waitingSize = m_waitingMsgs.size(); // add messages from waiting queue
    if (waitingSize > 0)
    {
        m_activeMsgs.append(m_waitingMsgs.mid(0, waitingSize));
        m_waitingMsgs.remove(0, waitingSize);
    }

    for (auto instr : emboInstruments) // add active permanent messages
    {
        for (auto msg : instr->getActiveMsgs())
            m_activeMsgs.append(msg);
    }

    m_activeMsgs.append(m_msg_sys_uptime); // add uptime life check msg

    send(); // finally send all
}

void Core::on_timer_render()
{
    double latency_mean;
    double latency_max;

    getLatencyMs(latency_mean, latency_max);

    m_latencyAvgMs = (int)latency_mean;

    emit latencyAndUptime(m_commTimeoutMs, (int)latency_mean, (int)latency_max, getUptime());
    //emit coreRender();
}
