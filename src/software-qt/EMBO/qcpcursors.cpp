/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "qcpcursors.h"
#include "css.h"


QCPCursors::QCPCursors(QCustomPlot* plot, QString layerName, int hMin, int hMax, int vMin, int vMax)
{
    m_plot = plot;
    m_layerName = layerName;

    plot->addLayer(m_layerName, 0, QCustomPlot::limAbove);
    m_cursorsLayer = new QCPLayer(m_plot, m_layerName);
    m_cursorsLayer->setMode(QCPLayer::lmBuffered);

    m_cursorH_min = new QCPItemLine(m_plot);
    m_cursorH_max = new QCPItemLine(m_plot);
    m_cursorH_min_diff = new QCPItemLine(m_plot);
    m_cursorH_max_diff = new QCPItemLine(m_plot);

    m_cursorV_min = new QCPItemLine(m_plot);
    m_cursorV_max = new QCPItemLine(m_plot);
    m_cursorV_min_diff = new QCPItemLine(m_plot);
    m_cursorV_max_diff = new QCPItemLine(m_plot);

    m_textH_diff = new QCPItemText(m_plot);
    m_textV_diff = new QCPItemText(m_plot);

    m_cursorH_min->setLayer(m_cursorsLayer);
    m_cursorH_max->setLayer(m_cursorsLayer);
    m_cursorH_min_diff->setLayer(m_cursorsLayer);
    m_cursorH_max_diff->setLayer(m_cursorsLayer);

    m_cursorV_min->setLayer(m_cursorsLayer);
    m_cursorV_max->setLayer(m_cursorsLayer);
    m_cursorV_min_diff->setLayer(m_cursorsLayer);
    m_cursorV_max_diff->setLayer(m_cursorsLayer);

    m_textH_diff->setLayer(m_cursorsLayer);
    m_textV_diff->setLayer(m_cursorsLayer);

    QFont font1("Roboto", 12, QFont::Normal);
    m_textH_diff->setFont(font1);
    m_textV_diff->setFont(font1);

    m_textH_diff->setColor(QColor(COLOR7));
    m_textV_diff->setColor(QColor(COLOR7));

    m_cursorH_min->setPen(QPen(QColor(COLOR3), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorH_max->setPen(QPen(QColor(COLOR3), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorV_min->setPen(QPen(QColor(COLOR3), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorV_max->setPen(QPen(QColor(COLOR3), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

    m_cursorH_min_diff->setPen(QPen(QColor(COLOR7), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorH_max_diff->setPen(QPen(QColor(COLOR7), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorV_min_diff->setPen(QPen(QColor(COLOR7), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorV_max_diff->setPen(QPen(QColor(COLOR7), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

    m_cursorH_min_diff->setTail(QCPLineEnding::esFlatArrow);
    m_cursorH_min_diff->setHead(QCPLineEnding::esFlatArrow);
    m_cursorH_max_diff->setTail(QCPLineEnding::esFlatArrow);
    m_cursorH_max_diff->setHead(QCPLineEnding::esFlatArrow);

    m_cursorV_min_diff->setTail(QCPLineEnding::esFlatArrow);
    m_cursorV_min_diff->setHead(QCPLineEnding::esFlatArrow);
    m_cursorV_max_diff->setTail(QCPLineEnding::esFlatArrow);
    m_cursorV_max_diff->setHead(QCPLineEnding::esFlatArrow);

    m_H_min = hMin;
    m_H_max = hMax;
    m_V_min = vMin;
    m_V_max = vMax;

    reCalc();

    m_cursorsLayer->setVisible(false);
    m_cursorsLayer->replot();
}

QCPCursors::~QCPCursors()
{
}

void QCPCursors::setH_min(int x)
{
    m_H_min = x;
    reCalc();

    m_cursorsLayer->replot();
}

void QCPCursors::setH_max(int x)
{
    m_H_max = x;
    reCalc();

    m_cursorsLayer->replot();
}

void QCPCursors::setV_min(int y)
{
    m_V_min = y;
    reCalc();

    m_cursorsLayer->replot();
}

void QCPCursors::setV_max(int y)
{
    m_V_max = y;
    reCalc();

    m_cursorsLayer->replot();
}

void QCPCursors::show(bool val)
{
    m_cursorsLayer->setVisible(val);
}

void QCPCursors::reCalc()
{

}
