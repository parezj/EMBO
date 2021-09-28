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
    QCPCursors(QObject* parent, QCustomPlot* plot, QCPAxisRect* rect = NULL, bool center = false,
               QColor colorH = Qt::black, QColor colorV = Qt::black,
               QColor colorDiff = Qt::black, QColor colorText = Qt::black);

    void setH_min(int percent, double hRangeMin, double hRangeMax);
    void setH_max(int percent, double hRangeMin, double hRangeMax);
    void setV_min(int percent, double vRangeMin, double vRangeMax);
    void setV_max(int percent, double vRangeMin, double vRangeMax);

    void refresh(double vRangeMin, double vRangeMax, double hRangeMin, double hRangeMax, bool replot = true);

    void showH(bool val);
    void showV(bool val);

    void showText(bool val);

    static int getUniqueNum() { return uniqueNum++; };
    static const QString formatUnitV(double value);
    static const QString formatUnitHz(double value);
    static const QString formatUnitS(double value);

private:
    void reCalcH();
    void reCalcV();

    static int uniqueNum;

    bool m_center;

    QCustomPlot* m_plot;

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
    QCPItemText* m_textH_diff2;

    QCPItemText* m_textV_min;
    QCPItemText* m_textV_max;
    QCPItemText* m_textV_diff;

    int m_hMinVal = 4;
    int m_hMaxVal = 6;
    int m_vMinVal = 4;
    int m_vMaxVal = 6;

    double m_hRangeMin = 0;
    double m_hRangeMax = 10;
    double m_vRangeMin = 0;
    double m_vRangeMax = 10;
};

/* single cursor without text */

class QCPCursor : public QObject
{
    Q_OBJECT

public:
    QCPCursor(QObject* parent, QCustomPlot* plot, QCPAxisRect* rect = NULL, bool horizontal = true, bool center = false,
              QColor colorLine = Qt::black, QColor colorText = Qt::black, Qt::PenStyle style = Qt::DashLine);

    void setValue(int percent, double vRangeMin, double vRangeMax, double hRangeMin, double hRangeMax);
    void refresh(double vRangeMin, double vRangeMax, double hRangeMin, double hRangeMax, bool replot = true);

    void show(bool val);
    void showText(bool val);

private:
    void reCalc();

    bool m_center;

    QCustomPlot* m_plot;
    QCPLayer* m_cursorLayer;

    QCPItemLine* m_cursor;
    QCPItemText* m_text;

    double m_hRangeMin = 0;
    double m_hRangeMax = 10;
    double m_vRangeMin = 0;
    double m_vRangeMax = 10;

    int m_value = 5;
    bool m_horizontal = true;
};


#endif // QCPCURSORS_H
