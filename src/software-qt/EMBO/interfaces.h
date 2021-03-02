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
    virtual Msg* getActiveMsg() = 0;
};

#endif // INTERFACES_H
