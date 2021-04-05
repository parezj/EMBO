/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef INTERFACES_H
#define INTERFACES_H

#include "msg.h"


class IEmboInstrument
{
public :
    virtual ~IEmboInstrument() {}

    virtual std::vector<Msg*>& getActiveMsgs() = 0;
    virtual bool getInstrEnabled() = 0;

    bool m_instrEnabled = false;
    std::vector<Msg*> m_activeMsgs;
};

#endif // INTERFACES_H
