#include "qchart.h"
#include "xylinechart_p.h"

QCHART_BEGIN_NAMESPACE

QChart::QChart(QGraphicsItem* parent):QGraphicsItem(parent),
m_marginSize(0)
{
  //  setFlags(QGraphicsItem::ItemClipsChildrenToShape);
}

QChart::~QChart(){}


QChart* QChart::createXYLineChart(const QList<QXYSeries*>& dataset)
{

    XYLineChart* chart = new XYLineChart();
    foreach (const QXYSeries* series,dataset) {
    chart->addXYSeries(series);
    }
    return chart;
}

void QChart::setMargin(int margin)
{
	m_marginSize=margin;
}

QCHART_END_NAMESPACE
