/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "utils.h"

#include <QString>

QString format_unit(double value, QString unit, int precision)
{
    if (value < 0.000000001)
        return(QString::number(value * 1000000000000, 'd', precision) + " p" + unit);
    else if (value < 0.000001)
        return(QString::number(value * 1000000000, 'd', precision) + " n" + unit);
    else if (value < 0.001)
        return(QString::number(value * 1000000, 'd', precision) + " u" + unit);
    else if (value < 1)
        return(QString::number(value * 1000, 'd', precision) + " m" + unit);
    else if (value < 1000)
        return(QString::number(value * 1, 'd', precision) + " " + unit);
    else if (value < 1000000)
        return(QString::number(value * 0.001, 'd', precision) + " k" + unit);
    else if (value < 1000000000)
        return(QString::number(value * 0.000001, 'd', precision) + " M" + unit);
    else if (value < 1000000000000)
        return(QString::number(value * 0.000000001, 'd', precision) + " G" + unit);
    else
        return(QString::number(value * 0.000000000001, 'd', precision) + " T" + unit);
}
