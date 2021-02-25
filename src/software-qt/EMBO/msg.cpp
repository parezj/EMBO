/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "msg.h"

#include <QString>


Msg::Msg(QString txData, QObject* parent) : QObject(parent), txData(txData)
{
    connect(this, &Msg::rx, this, &Msg::on_dataRx);
}

void Msg::fire(QString data)
{
    rxData = data.isEmpty() ? "" : data;
    emit rx();
}

void Msg::setTxData(QString data)
{
    this->txData = data;
}

QString Msg::getTxData()
{
    return this->txData;
}
