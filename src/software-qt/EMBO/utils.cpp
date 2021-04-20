/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "utils.h"
#include "containers.h"

#include <QString>
#include <QDebug>
#include <QMessageBox>

#include <math.h>


QString format_unit(double value, QString unit, int precision)
{
    const QString r = "\\.*0+$";

    double scale;
    QString prefix;

    if (value < 0.000000001) {
        scale = 1000000000000;
        prefix = " p";
    }
    else if (value < 0.000001) {
        scale = 1000000000;
        prefix = " n";
    }
    else if (value < 0.001) {
        scale = 1000000;
        prefix = " u";
    }
    else if (value < 1) {
        scale = 1000;
        prefix = " m";
    }
    else if (value < 1000) {
        scale = 1;
        prefix = " ";
    }
    else if (value < 1000000) {
        scale = 0.001;
        prefix = " k";
    }
    else if (value < 1000000000) {
        scale = 0.000001;
        prefix = " M";
    }
    else if (value < 1000000000000) {
        scale = 0.000000001;
        prefix = " G";
    }
    else {
        scale = 0.000000000001;
        prefix = " T";
    }

    QString ret = QString::number(value * scale, 'd', precision);

    if (ret.contains('.'))
        return ret.remove(QRegExp(r)) + prefix + unit;
    else
        return ret + prefix + unit;
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

int get_vals_from_circ(int from, int total, int bufflen, DaqBits daq_bits, double vcc, uint8_t* buff,
                       QVector<double>* ch1, QVector<double>* ch2, QVector<double>* ch3, QVector<double>* ch4,
                       double gain1, double gain2, double gain3, double gain4,
                       double offset1, double offset2, double offset3, double offset4)
{
    assert(total > 0 && bufflen >= total && buff != NULL);

    int found = 0;
    int ch_num = 0;

    if (ch1 != NULL) ch_num++;
    if (ch2 != NULL) ch_num++;
    if (ch3 != NULL) ch_num++;
    if (ch4 != NULL) ch_num++;

    QVector<double>* _ch1 = NULL;
    QVector<double>* _ch2 = NULL;
    QVector<double>* _ch3 = NULL;
    QVector<double>* _ch4 = NULL;

    QVector<double>* ch1_copy = ch1;
    QVector<double>* ch2_copy = ch2;
    QVector<double>* ch3_copy = ch3;

    QVector<double>** it;

    for (int i = 0; i < ch_num; i++) // sort algorithm
    {
        if      (i == 0) it = &_ch1;
        else if (i == 1) it = &_ch2;
        else if (i == 2) it = &_ch3;
        else             it = &_ch4;

        if      (i < 1 && ch1_copy != NULL) { *it = ch1_copy; ch1_copy = NULL; continue; }
        else if (i < 2 && ch2_copy != NULL) { *it = ch2_copy; ch2_copy = NULL; continue; }
        else if (i < 3 && ch3_copy != NULL) { *it = ch3_copy; ch3_copy = NULL; continue; }
        else                                { *it = ch4; continue; }
    }

    int k1 = 0, k2 = 0, k3 = 0, k4 = 0;
    for (int k = 0, i = from; k < total; k++, i++)
    {
        if (i >= bufflen)
            i = 0;

        found++;
        double val;

        if (daq_bits == B12)
        {
            uint16_t raw = (*((uint16_t*)(((uint8_t*)buff)+(i*2))));
            val = (raw / 4095.0) * vcc;
        }
        else if (daq_bits == B8)
        {
            uint16_t raw = (((uint8_t*)buff)[i]);
            val = (raw / 255.0) * vcc;
        }
        else assert(0);

        if (i % ch_num == 0)
        {
            if (_ch1 != NULL)
                (*_ch1)[k1++] = (gain1 * val) + offset1;
        }
        else if (ch_num > 1 && i % ch_num == 1)
        {
            if (_ch2 != NULL)
                (*_ch2)[k2++] = (gain2 * val) + offset2;
        }
        else if (ch_num > 2 && i % ch_num == 2)
        {
            if (_ch3 != NULL)
                (*_ch3)[k3++] = (gain3 * val) + offset3;
        }
        else if (ch_num > 3) // && i % ch_num == 3)
        {
            if (_ch4 != NULL)
                (*_ch4)[k4++] = (gain4 * val) + offset4;
        }
    }
    return found;
}
