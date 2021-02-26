/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "utils.h"

#include <QString>

QString format_unit(double value, QString unit)
{
    if (value < 0.000000001)
        return(QString::number(value * 1000000000000) + " p" + unit);
    else if (value < 0.000001)
        return(QString::number(value * 1000000000) + " n" + unit);
    else if (value < 0.001)
        return(QString::number(value * 1000000) + " u" + unit);
    else if (value < 1)
        return(QString::number(value * 1000) + " m" + unit);
    else if (value < 1000)
        return(QString::number(value * 1) + " " + unit);
    else if (value < 1000000)
        return(QString::number(value * 0.001) + " k" + unit);
    else if (value < 1000000000)
        return(QString::number(value * 0.000001) + " M" + unit);
    else if (value < 1000000000000)
        return(QString::number(value * 0.000000001) + " G" + unit);
    else
        return(QString::number(value * 0.000000000001) + " T" + unit);
}
