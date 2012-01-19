#ifndef XYLINECHARTITEM_H
#define XYLINECHARTITEM_H

#include "qchartglobal.h"
#include "qchart.h"
#include "xyplotdomain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QXYChartSeries;

class XYLineChartItem : public QGraphicsItem
{

public:
    XYLineChartItem(QXYChartSeries* m_series,QGraphicsItem *parent = 0);
    virtual ~ XYLineChartItem(){};

    //from QGraphicsItem
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updateXYPlotData(const XYPlotDomain& data);

private:
    QPolygonF m_polyline;
    QXYChartSeries* m_series;
    XYPlotDomain m_xyPlotData;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
