/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef MESSAGES_H
#define MESSAGES_H

#include "msg.h"

#include <QObject>

#define EMBO_IDN            "*IDN"
#define EMBO_RST            "*RST"
#define EMBO_STB            "*STB"
#define EMBO_CLS            "*CLS"

#define EMBO_SYS_LIMS       ":SYS:LIM"
#define EMBO_SYS_INFO       ":SYS:INFO"
#define EMBO_SYS_MODE       ":SYS:MODE"
#define EMBO_SYS_UPTIME     ":SYS:UPT"

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

#define EMBO_SET_TRUE       "1"
#define EMBO_SET_FALSE      "0"

enum Mode
{
    NO_MODE = 0,
    VM = 1,
    SCOPE = 2,
    LA = 3
};

enum Ready
{
    NOT_READY = 0,
    READY_AUTO = 1,
    READY_NORMAL = 2,
    READY_DISABLED = 3
};

/***************************** Messages - SCPI *****************************/

class Msg_Idn : public Msg
{
    Q_OBJECT
public:
    explicit Msg_Idn(QObject* parent=0) : Msg(EMBO_IDN, true, parent) {};
    virtual void on_dataRx() override;
};

class Msg_Rst : public Msg
{
    Q_OBJECT
public:
    explicit Msg_Rst(QObject* parent=0) : Msg(EMBO_RST, false, parent) {};
    virtual void on_dataRx() override;
};

class Msg_Stb : public Msg
{
    Q_OBJECT
public:
    explicit Msg_Stb(QObject* parent=0) : Msg(EMBO_STB, true, parent) {};
    virtual void on_dataRx() override;
};

class Msg_Cls : public Msg
{
    Q_OBJECT
public:
    explicit Msg_Cls(QObject* parent=0) : Msg(EMBO_CLS, false, parent) {};
    virtual void on_dataRx() override;
};

/***************************** Messages - SYS *****************************/

class Msg_SYS_Lims : public Msg
{
    Q_OBJECT
public:
    explicit Msg_SYS_Lims(QObject* parent=0) : Msg(EMBO_SYS_LIMS, true, parent) {};
    virtual void on_dataRx() override;
};

class Msg_SYS_Info : public Msg
{
    Q_OBJECT
public:
    explicit Msg_SYS_Info(QObject* parent=0) : Msg(EMBO_SYS_INFO, true, parent) {};
    virtual void on_dataRx() override;
};

class Msg_SYS_Mode : public Msg
{
    Q_OBJECT
public:
    explicit Msg_SYS_Mode(QObject* parent=0) : Msg(EMBO_SYS_MODE, true, parent) {};
    virtual void on_dataRx() override;
};

class Msg_SYS_Uptime : public Msg
{
    Q_OBJECT
public:
    explicit Msg_SYS_Uptime(QObject* parent=0) : Msg(EMBO_SYS_UPTIME, true, parent) {};
    virtual void on_dataRx() override;
};

class Msg_Dummy : public Msg
{
    Q_OBJECT
public:
    explicit Msg_Dummy(QObject* parent=0) : Msg(EMBO_STB, true, parent) {};
    virtual void on_dataRx() override;
};

/***************************** Messages - VM ****************************/

class Msg_VM_Read : public Msg
{
    Q_OBJECT
public:
    explicit Msg_VM_Read(QObject* parent=0) : Msg(EMBO_VM_READ, true, parent) {};
    virtual void on_dataRx() override;
signals:
    void result(const QString ch1, const QString ch2, const QString ch3, const QString ch4, const QString vcc);
};

/***************************** Messages - SCOP **************************/

class Msg_SCOP_Read : public Msg
{
    Q_OBJECT
public:
    explicit Msg_SCOP_Read(QObject* parent=0) : Msg(EMBO_SCOP_READ, true, parent) {};
    virtual void on_dataRx() override;
signals:
    void result(const QByteArray data);
};

class Msg_SCOP_Set : public Msg
{
    Q_OBJECT
public:
    explicit Msg_SCOP_Set(QObject* parent=0) : Msg(EMBO_SCOP_SET, true, parent) {};
    virtual void on_dataRx() override;
signals:
    void result();
};

class Msg_SCOP_ForceTrig : public Msg
{
    Q_OBJECT
public:
    explicit Msg_SCOP_ForceTrig(QObject* parent=0) : Msg(EMBO_SCOP_FORCETRIG, false, parent) {};
    virtual void on_dataRx() override;
};

class Msg_SCOP_Average : public Msg
{
    Q_OBJECT
public:
    explicit Msg_SCOP_Average(QObject* parent=0) : Msg(EMBO_SCOP_AVERAGE, false, parent) {};
    virtual void on_dataRx() override;
};

/***************************** Messages - LA ****************************/

class Msg_LA_Read : public Msg
{
    Q_OBJECT
public:
    explicit Msg_LA_Read(QObject* parent=0) : Msg(EMBO_LA_READ, true, parent) {};
    virtual void on_dataRx() override;
signals:
    void result(const QByteArray data);
};

class Msg_LA_Set : public Msg
{
    Q_OBJECT
public:
    explicit Msg_LA_Set(QObject* parent=0) : Msg(EMBO_LA_SET, true, parent) {};
    virtual void on_dataRx() override;
signals:
    void result();
};

class Msg_LA_ForceTrig : public Msg
{
    Q_OBJECT
public:
    explicit Msg_LA_ForceTrig(QObject* parent=0) : Msg(EMBO_LA_FORCETRIG, false, parent) {};
    virtual void on_dataRx() override;
};

/***************************** Messages - CNTR **************************/

class Msg_CNTR_Enable : public Msg
{
    Q_OBJECT
public:
    explicit Msg_CNTR_Enable(QObject* parent=0) : Msg(EMBO_CNTR_ENABLE, true, parent) {};
    virtual void on_dataRx() override;
signals:
    void result(bool enabled, bool fastMode);
};

class Msg_CNTR_Read : public Msg
{
    Q_OBJECT
public:
    explicit Msg_CNTR_Read(QObject* parent=0) : Msg(EMBO_CNTR_READ, true, parent) {};
    virtual void on_dataRx() override;
signals:
    void result(const QString freq, const QString period);
};

/***************************** Messages - SGEN **************************/

enum SgenMode
{
    CONSTANT = 0,
    SINE = 1,
    TRIANGLE = 2,
    SAWTOOTH = 3,
    SQUARE = 4,
    NOISE = 5
};

class Msg_SGEN_Set : public Msg
{
    Q_OBJECT
public:
    explicit Msg_SGEN_Set(QObject* parent=0) : Msg(EMBO_SGEN_SET, true, parent) {};
    virtual void on_dataRx() override;
signals:
    void result(SgenMode mode, double freq, int ampl, int offset, bool enabled);
};

/***************************** Messages - PWM ***************************/

class Msg_PWM_Set : public Msg
{
    Q_OBJECT
public:
    explicit Msg_PWM_Set(QObject* parent=0) : Msg(EMBO_PWM_SET, true, parent) {};
    virtual void on_dataRx() override;
signals:
    void result(int freq, int duty1, int duty2, int offset, bool en1, bool en2, const QString freq_real);
};

#endif // MESSAGES_H
