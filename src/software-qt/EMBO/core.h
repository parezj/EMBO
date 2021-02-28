/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CORE_H
#define CORE_H

#include "msg.h"

#include <QObject>
#include <QTimer>
#include <QString>
#include <QSerialPort>
#include <QVector>

#define TIMER_RX        2000
#define TIMER_COMM      20
#define TIMER_RENDER    25

#define INVALID_MSG     "Invalid message!"

/******************************** Protocol ********************************/

#define EMBO_NEWLINE        "\r\n"
#define EMBO_DELIM1         ";"
#define EMBO_DELIM2         ","

#define EMBO_OK             "OK"

#define EMBO_IDN            "*IDN"
#define EMBO_RST            "*RST"

#define EMBO_SYS_LIMS       ":SYS:LIM"
#define EMBO_SYS_INFO       ":SYS:INFO"
#define EMBO_SYS_MODE       ":SYS:MODE"

#define EMBO_VM_READ        ":VM:READ"

#define EMBO_SCOP_READ      ":SCOP:READ"
#define EMBO_SCOP_SET       ":SCOP:SET"
#define EMBO_SCOP_FORCETRIG ":SCOP:FORC"
#define EMBO_SCOP_AVERAGE   ":SCOP:AVER"

#define EMBO_LA_READ        ":LA:READ"
#define EMBO_LA_SET         ":LA:SET"
#define EMBO_LA_FORCETRIG   ":LA:FORC"

#define EMBO_CNTR_ENABLE    ":CNTR:ENA"
#define EMBO_CNTR_READ      ":CNTR:READ"

#define EMBO_SGEN_SET       ":SGEN:SET"

#define EMBO_PWM_SET        ":PWM:SET"

#define EMBO_READY_A        "ReadyA"
#define EMBO_READY_N        "ReadyD"
#define EMBO_READY_D        "ReadyA"


/***************************** Messages - SYS *****************************/

class Msg_Idn : public Msg
{
public:
    explicit Msg_Idn(QObject* parent=0) : Msg(EMBO_IDN, true, parent) {};
    virtual void on_dataRx();
};

class Msg_Rst : public Msg
{
public:
    explicit Msg_Rst(QObject* parent=0) : Msg(EMBO_RST, false, parent) {};
    virtual void on_dataRx();
};

class Msg_SYS_Lims : public Msg
{
public:
    explicit Msg_SYS_Lims(QObject* parent=0) : Msg(EMBO_SYS_LIMS, true, parent) {};
    virtual void on_dataRx();
};

class Msg_SYS_Info : public Msg
{
public:
    explicit Msg_SYS_Info(QObject* parent=0) : Msg(EMBO_SYS_INFO, true, parent) {};
    virtual void on_dataRx();
};

class Msg_SYS_Mode : public Msg
{
public:
    explicit Msg_SYS_Mode(QObject* parent=0) : Msg(EMBO_SYS_MODE, true, parent) {};
    virtual void on_dataRx();
};

/***************************** Messages - VM ****************************/

class Msg_VM_Read : public Msg
{
public:
    explicit Msg_VM_Read(QObject* parent=0) : Msg(EMBO_VM_READ, true, parent) {};
    virtual void on_dataRx();
};

/***************************** Messages - SCOP **************************/

class Msg_SCOP_Read : public Msg
{
public:
    explicit Msg_SCOP_Read(QObject* parent=0) : Msg(EMBO_SCOP_READ, true, parent) {};
    virtual void on_dataRx();
};

class Msg_SCOP_Set : public Msg
{
public:
    explicit Msg_SCOP_Set(QObject* parent=0) : Msg(EMBO_SCOP_SET, true, parent) {};
    virtual void on_dataRx();
};

class Msg_SCOP_ForceTrig : public Msg
{
public:
    explicit Msg_SCOP_ForceTrig(QObject* parent=0) : Msg(EMBO_SCOP_FORCETRIG, false, parent) {};
    virtual void on_dataRx();
};

class Msg_SCOP_Average : public Msg
{
public:
    explicit Msg_SCOP_Average(QObject* parent=0) : Msg(EMBO_SCOP_AVERAGE, false, parent) {};
    virtual void on_dataRx();
};

/***************************** Messages - LA ****************************/

class Msg_LA_Read : public Msg
{
public:
    explicit Msg_LA_Read(QObject* parent=0) : Msg(EMBO_LA_READ, true, parent) {};
    virtual void on_dataRx();
};

class Msg_LA_Set : public Msg
{
public:
    explicit Msg_LA_Set(QObject* parent=0) : Msg(EMBO_LA_SET, true, parent) {};
    virtual void on_dataRx();
};

class Msg_LA_ForceTrig : public Msg
{
public:
    explicit Msg_LA_ForceTrig(QObject* parent=0) : Msg(EMBO_LA_FORCETRIG, false, parent) {};
    virtual void on_dataRx();
};

/***************************** Messages - CNTR **************************/

class Msg_CNTR_Enable : public Msg
{
public:
    explicit Msg_CNTR_Enable(QObject* parent=0) : Msg(EMBO_CNTR_ENABLE, false, parent) {};
    virtual void on_dataRx();
};

class Msg_CNTR_Read : public Msg
{
public:
    explicit Msg_CNTR_Read(QObject* parent=0) : Msg(EMBO_CNTR_READ, true, parent) {};
    virtual void on_dataRx();
};

/***************************** Messages - SGEN **************************/

class Msg_SGEN_Set : public Msg
{
public:
    explicit Msg_SGEN_Set(QObject* parent=0) : Msg(EMBO_SGEN_SET, true, parent) {};
    virtual void on_dataRx();
};

/***************************** Messages - PWM ***************************/

class Msg_PWM_Set : public Msg
{
public:
    explicit Msg_PWM_Set(QObject* parent=0) : Msg(EMBO_PWM_SET, true, parent) {};
    virtual void on_dataRx();
};

/********************************* Core *********************************/

enum State
{
    DISCONNECTED,
    OPENING,
    CONNECTING,
    CONNECTED
};

enum Mode
{
    VM,
    SCOPE,
    LA
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
    int fcpu;
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
    int cntr_freq;
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
    bool open(QString port);
    bool close();
    void start();
    void err(QString name, bool needClose);
    void dispose();

    const QString getPort() { return m_serial->portName(); }
    DevInfo* getDevInfo() const { return devInfo; }
    void setMode(Mode mode, bool alsoLast) { m_mode = mode; if (alsoLast) m_mode_last = mode; }

    static Core* getInstance(QObject* parent = 0)
    {
        if (m_instance == Q_NULLPTR)
            m_instance = new Core(parent);
        return m_instance;
    }

public slots:
    void on_start();
    void on_open(const QString port);
    void on_msgAdd(Msg* const msg);
    void on_close();

signals:
    void stateChanged(const State state);
    void errorHappend(const QString name);
    void finished();

private:
    explicit Core(QObject* parent = 0);

    void send();

    void on_serial_errorOccurred(QSerialPort::SerialPortError error);
    void on_serial_readyRead();
    void on_timer_rxTimeout();
    void on_timer_comm();
    void on_timer_render();

    /* instance */
    static Core* m_instance;

    QSerialPort* m_serial = nullptr;
    State m_state = DISCONNECTED;

    /* helpers */
    bool close_init = false;
    Mode m_mode;
    Mode m_mode_last;

    /* timers */
    QTimer* m_timer_rxTimeout;
    QTimer* m_timer_render;
    QTimer* m_timer_comm;

    /* data */
    DevInfo* devInfo; // TODO const

    /* message buffers */
    QVector<Msg*> m_waitingMsgs;
    QVector<Msg*> m_activeMsgs;
    QString m_mainBuffer = "";
    int m_submsgIt = 0;

    /* message objects */
    Msg_Idn* m_msg_idn;
    Msg_Rst* m_msg_rst;
    Msg_SYS_Lims* m_msg_sys_lims;
    Msg_SYS_Info* m_msg_sys_info;
    Msg_SYS_Mode* m_msg_sys_mode;
    Msg_VM_Read* m_msg_vm_read;
    Msg_SCOP_Set* m_msg_scope_set;
    Msg_SCOP_Read* m_msg_scope_read;
    Msg_SCOP_ForceTrig* m_msg_scope_forcetrig;
    Msg_SCOP_Average* m_msg_scope_average;
    Msg_LA_Set* m_msg_la_set;
    Msg_LA_Read* m_msg_la_read;
    Msg_LA_ForceTrig* m_msg_la_forcetrig;
    Msg_CNTR_Enable* m_msg_cntr_enable;
    Msg_CNTR_Read* m_msg_cntr_read;
    Msg_SGEN_Set* m_msg_sgen_set;
    Msg_PWM_Set* m_msg_pwm_set;
};

#endif // CORE_H
