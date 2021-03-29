/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "utils.h"

#include <QString>
#include <QDebug>
#include <QMessageBox>

#include <math.h>


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

double lin_to_exp_1to36M(double x, bool inverse)
{
    const double a = 0.999999516693728;
    const double b = 0.0000004833063883257437;

    double ret = inverse ? ((a * log(x)) / b) : (a * exp(b * x));
    //qInfo() << ret;

    return ret;
}

void msgBox(QMainWindow* window, QString text, MsgBoxType type)
{
   QMessageBox* msgBox = new QMessageBox(window);
   msgBox->setAttribute(Qt::WA_DeleteOnClose);
   msgBox->setText(text);
   msgBox->setMinimumWidth(200);
   msgBox->setMinimumHeight(60);

   if (type == INFO)
   {
       msgBox->setIcon(QMessageBox::Information);
       msgBox->setStandardButtons(QMessageBox::Ok);
       msgBox->setWindowTitle("EMBO - Information");
   }
   else if (type == QUESTION)
   {
       msgBox->setIcon(QMessageBox::Question);
       msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
       msgBox->setWindowTitle("EMBO - Question");
   }
   else if (type == WARNING)
   {
       msgBox->setIcon(QMessageBox::Warning);
       msgBox->setStandardButtons(QMessageBox::Ok);
       msgBox->setWindowTitle("EMBO - Warning");
   }
   else if (type == CRITICAL)
   {
       msgBox->setIcon(QMessageBox::Critical);
       msgBox->setStandardButtons(QMessageBox::Ok);
       msgBox->setWindowTitle("EMBO - Error");
   }

   msgBox->setModal( false );
   msgBox->open(window, SLOT(msgBoxClosed(QAbstractButton*)));
}
