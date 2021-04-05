/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef MSG_H
#define MSG_H

#include "containers.h"

#include <QObject>
#include <QString>
#include <QDebug>


class Msg : public QObject
{
    Q_OBJECT

public:
    explicit Msg(const Msg& msg);
    explicit Msg(const QString cmd = "", bool isQuery = true, QObject* parent = 0);
    virtual ~Msg() {};

    void fire(const QString data);
    void fire(const QByteArray data);

    QString getCmd() { return this->m_cmd; }
    bool getIsQuery() { return this->m_isQuery; }
    QString getParams() { return this->m_params; }

    void setIsQuery(bool val) { this->m_isQuery = val; }
    void setParams(QString val) { this->m_params = val; }

protected slots:
    virtual void on_dataRx() {};

signals:
    void rx();
    void rx_bin();

    void ok(const QString val1 = "", const QString val2 = "");
    void err(const QString text, MsgBoxType type, bool needClose);

protected:
    QString m_cmd;
    QString m_rxData;
    QByteArray m_rxDataBin;
    bool m_isQuery;
    QString m_params = "";
};


#endif // MSG_H
