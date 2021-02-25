/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef MSG_H
#define MSG_H

#include <QObject>
#include <QString>


class Msg : public QObject
{
Q_OBJECT

public:
    explicit Msg(QString msg = "", QObject* parent = 0);
    virtual ~Msg() {};

    void fire(QString data);
    void setTxData(QString data);
    QString getTxData();

protected slots:
    virtual void on_dataRx() {};

signals:
    void rx();

protected:
    void* core;
    QString txData;
    QString rxData;
};


#endif // MSG_H
