/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CORE_H
#define CORE_H

#include "window_scope.h"
#include "window_la.h"
#include "window_vm.h"
#include "window_cntr.h"
#include "window_pwm.h"
#include "window_sgen.h"

#include "msg.h"
#include "messages.h"

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QString>
#include <QSerialPort>
#include <QVector>

#define UPDATE_URL      "http://embo.jakubparez.com/updates.json"

#define TIMER_COMM      10
#define TIMER_COMM_MIN  1
#define TIMER_RX        1000
#define TIMER_RENDER    100

#define LATENCY_AVG     25

#define INVALID_MSG     "Invalid message! "
#define COMM_FATAL_ERR  "Communication fatal error! "

#define EMBO_TITLE      "EMBO"
#define EMBO_TITLE2     "EMBO - EMBedded Oscilloscope"
#define EMBO_ABOUT_TXT  "<b>EMBedded Oscilloscope</b><br><br>CTU FEE © 2020-2021 Jakub Pařez<br><br>\
EMBO is useful tool for every electronics enthusiast.<br>\
For just few dollar hardware (STM32 BluePill) can become a powerfull scope, logic analyzer, voltmeter, counter, \
PWM and signal generator.<br>And of course, it's opensource! \
<br><br>EMBO uses this free software:<br>\
<a href='https://www.qcustomplot.com'>QCustomPlot</a><br>\
<a href='https://github.com/alex-spataru/QSimpleUpdater'>alex-spataru / QSimpleUpdater </a><br>\
<a href='https://github.com/buzzySmile/qBreakpad'>buzzySmile / qBreakpad</a><br>\
<a href='https://chromium.googlesource.com/breakpad/breakpad'>Google Breakpad</a><br>\
<a href='https://chromium.googlesource.com/linux-syscall-support'>Linux Syscall Support</a>\
<br><br>Compiled " __DATE__ " " __TIME__ " with <b>Qt " QT_VERSION_STR "</b><br><br>\
<a href='https://github.com/parezj/EMBO'>github.com/parezj/EMBO</a>"

#define CFG_MAIN_PORT       "main/port"

#define EMBO_NEWLINE        "\r\n"
#define EMBO_DELIM1         ";"
#define EMBO_DELIM2         ","

#define EMBO_TRUE           "1"
#define EMBO_FALSE          "0"
#define EMBO_OK             "\"OK\""

#define EMBO_READY_A        "ReadyA"
#define EMBO_READY_N        "ReadyN"
#define EMBO_READY_D        "ReadyD"

enum State
{
    DISCONNECTED,
    OPENING,
    CONNECTING1,
    CONNECTING2,
    CONNECTED
};

class DevInfo : public QObject
{
Q_OBJECT
public:
    DevInfo(QObject* parent) : QObject(parent) { }

    /* IDN */
    QString name;
    QString fw;

    /* SYS:INFO */
    QString rtos;
    QString ll;
    QString comm;
    QString fcpu;
    int ref_mv;
    QString pins_scope_vm;
    QString pins_la;
    QString pins_cntr;
    QString pins_pwm;
    QString pins_sgen;

    /* SYS:LIM */
    int adc_fs_12b;
    int adc_fs_8b;
    int mem;
    int la_fs;
    int pwm_fs;
    int adc_num;
    bool adc_dualmode;
    bool adc_interleaved;
    bool adc_bit8;
    bool dac;
    int vm_mem;
    int vm_fs;
    int cntr_timeout;
    int sgen_maxf;
    int sgen_maxmem;
};

class Core : public QObject
{
Q_OBJECT

public:
    ~Core();

    void setUp();
    bool openComm(QString port);
    void openCommInit();
    bool closeComm();
    void startComm();
    void err(QString name, bool needClose);
    void msgAdd(Msg* msg, bool isQuery, QString params = "");

    QVector<IEmboInstrument*> emboInstruments;

     /* setters getters */
    const QString getPort() { return m_serial->portName(); }
    DevInfo* getDevInfo() const { return m_devInfo; }
    int getLatencyMs();
    QString getUptime() { return m_uptime; }
    void setUptime(QString uptime) { m_uptime = uptime; }
    void setMode(Mode mode, bool alsoLast = false) { m_mode = mode; if (alsoLast) m_mode_last = mode; }

     /* singleton */
    static Core* getInstance(QObject* parent = 0)
    {
        if (m_instance == Q_NULLPTR)
            m_instance = new Core(parent);
        return m_instance;
    }

public slots:
    void on_startThread();
    void on_openComm(const QString port);
    //void on_msgAdd(Msg* msg);
    void on_closeComm(bool force);
    void on_dispose();

signals:
    void daqReady(Ready ready);
    void stateChanged(const State state);
    void msgDisplay(const QString name, MsgBoxType type);
    void latencyAndUptime(int latency, int commTimeout, const QString uptime);
    void finished();

private slots:
    void on_serial_errorOccurred(QSerialPort::SerialPortError error);
    void on_serial_readyRead();
    void on_timer_rxTimeout();
    void on_timer_comm();
    void on_timer_render();

private:
    explicit Core(QObject* parent = 0);

    void send();
    void openComm2();

    /* instance */
    static Core* m_instance;

    QSerialPort* m_serial = Q_NULLPTR;
    State m_state = DISCONNECTED;

    /* helpers */
    bool m_binary_mode = false;
    bool m_close_init = false;
    bool m_open_comm = false;
    Mode m_mode = Mode::NO_MODE;
    Mode m_mode_last = Mode::NO_MODE;

    /* timers */
    QTimer* m_timer_rxTimeout;
    QTimer* m_timer_render;
    QTimer* m_timer_comm;

    /* latency timer */
    QElapsedTimer m_timer_latency;
    int m_latency = 0;
    int m_latencyVals[LATENCY_AVG];
    int m_latencyCnt = 0;
    int m_latencyIt = 0;

    /* latency avg val and rx timeout */
    int m_latencyAvgMs = 0;
    int m_commTimeoutMs = 0;

    /* data */
    DevInfo* m_devInfo; // const
    QString m_uptime = "";

    /* message buffers */
    QVector<Msg*> m_waitingMsgs;
    QVector<Msg*> m_activeMsgs;
    QByteArray m_mainBuffer;
    int m_submsgIt = 0;

    /* message objects */
    Msg_Idn* m_msg_idn;
    Msg_Rst* m_msg_rst;
    //Msg_Stb* m_msg_stb;
    //Msg_Cls* m_msg_cls;
    Msg_Dummy* m_msg_dummy;
    Msg_SYS_Lims* m_msg_sys_lims;
    Msg_SYS_Info* m_msg_sys_info;
    Msg_SYS_Mode* m_msg_sys_mode;
    Msg_SYS_Uptime* m_msg_sys_uptime;
};

#endif // CORE_H
