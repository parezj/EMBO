/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef QCPCURSORS_H
#define QCPCURSORS_H

#include "lib/qcustomplot.h"

class QCPCursors
{
public:
    QCPCursors(QCustomPlot* plot, QString layerName = "cursorsLayer", int hMin = 250, int hMax = 750, int vMin = 250, int vMax = 750);
    ~QCPCursors();

    void setH_min(int x);
    void setH_max(int x);
    void setV_min(int y);
    void setV_max(int y);
    void show(bool val);

private:
    void reCalc();

    QCustomPlot* m_plot;

    QCPLayer* m_cursorsLayer;
    QString m_layerName;

    QCPItemLine* m_cursorH_min;
    QCPItemLine* m_cursorH_max;
    QCPItemLine* m_cursorH_min_diff;
    QCPItemLine* m_cursorH_max_diff;

    QCPItemLine* m_cursorV_min;
    QCPItemLine* m_cursorV_max;
    QCPItemLine* m_cursorV_min_diff;
    QCPItemLine* m_cursorV_max_diff;

    QCPItemText* m_textH_diff;
    QCPItemText* m_textV_diff;

    int m_H_min;
    int m_H_max;
    int m_V_min;
    int m_V_max;
};

#endif // QCPCURSORS_H
