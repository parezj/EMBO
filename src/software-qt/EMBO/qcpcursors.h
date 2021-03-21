/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef QCPCURSORS_H
#define QCPCURSORS_H

#include <QObject>
#include "lib/qcustomplot.h"

/* dual cursors */

class QCPCursors : public QObject
{
    Q_OBJECT

public:
    QCPCursors(QObject* parent, QCustomPlot* plot,
               QColor colorH = Qt::black, QColor colorV = Qt::black,
               QColor colorDiff = Qt::black, QColor colorText = Qt::black);

    void setH_min(int percent, double hRangeMin, double hRangeMax);
    void setH_max(int percent, double hRangeMin, double hRangeMax);
    void setV_min(int percent, double vRangeMin, double vRangeMax);
    void setV_max(int percent, double vRangeMin, double vRangeMax);

    void refresh(double vRangeMin, double vRangeMax, double hRangeMin, double hRangeMax, bool replot = true);

    void showH(bool val);
    void showV(bool val);

    static int getUniqueNum() { return uniqueNum++; };

private:
    void reCalc();

    static int uniqueNum;

    QCustomPlot* m_plot;
    QCPGraph* m_graph;

    QCPLayer* m_cursorsLayerH;
    QCPLayer* m_cursorsLayerV;

    QCPItemLine* m_cursorH_min;
    QCPItemLine* m_cursorH_max;
    QCPItemLine* m_cursorH_diff;

    QCPItemLine* m_cursorV_min;
    QCPItemLine* m_cursorV_max;
    QCPItemLine* m_cursorV_diff;

    QCPItemText* m_textH_min;
    QCPItemText* m_textH_max;
    QCPItemText* m_textH_diff;

    QCPItemText* m_textV_min;
    QCPItemText* m_textV_max;
    QCPItemText* m_textV_diff;

    int m_hMinVal;
    int m_hMaxVal;
    int m_vMinVal;
    int m_vMaxVal;

    double m_hRangeMin;
    double m_hRangeMax;
    double m_vRangeMin;
    double m_vRangeMax;
};

/* single cursor without text */

class QCPCursor : public QObject
{
    Q_OBJECT

public:
    QCPCursor(QObject* parent, QCustomPlot* plot, bool horizontal = true,
              QColor color = Qt::black, Qt::PenStyle style = Qt::DashLine);

    void setValue(int percent, double rangeMin, double rangeMax);
    void refresh(double rangeMin, double rangeMax, bool replot = true);
    void show(bool val);

private:
    void reCalc();

    QCustomPlot* m_plot;
    QCPGraph* m_graph;

    QCPLayer* m_cursorLayer;
    QCPItemLine* m_cursor;

    int m_value;
    double m_rangeMin;
    double m_rangeMax;
    bool m_horizontal;
};


#endif // QCPCURSORS_H
