/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef MSG_H
#define MSG_H

#include <QObject>
#include <QString>
#include <QDebug>

enum MsgBoxType
{
    INFO,
    QUESTION,
    WARNING,
    CRITICAL
};


class Msg : public QObject
{
    Q_OBJECT

public:
    explicit Msg(const Msg& msg);
    explicit Msg(QString cmd = "", bool isQuery = true, QObject* parent = 0);
    virtual ~Msg() {};

    void fire(QString data);

    QString getCmd() { return this->m_cmd; }
    bool getIsQuery() { return this->m_isQuery; }
    void setIsQuery(bool val) { this->m_isQuery = val; }
    QString getParams() { return this->m_params; }
    void setParams(QString val) { this->m_params = val; }

protected slots:
    virtual void on_dataRx() {};

signals:
    void rx();
    void err(QString text, MsgBoxType type, bool needClose);

protected:
    QString m_cmd;
    QString m_rxData;
    bool m_isQuery;
    QString m_params = "";
};


#endif // MSG_H
