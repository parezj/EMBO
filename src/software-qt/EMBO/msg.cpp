/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "msg.h"

#include <QString>

Msg::Msg(const Msg& msg) : QObject(msg.parent())
{
    m_cmd = msg.m_cmd;
    m_isQuery = msg.m_isQuery;
    m_params = msg.m_params;
}

Msg::Msg(QString cmd, bool isQuery, QObject* parent) : QObject(parent), m_cmd(cmd), m_isQuery(isQuery)
{
    connect(this, &Msg::rx, this, &Msg::on_dataRx);
}

void Msg::fire(QString data)
{
    m_rxData = data.isEmpty() ? "" : data;
    emit rx();
}

