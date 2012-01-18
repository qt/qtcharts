#ifndef XYLINECHARTITEM_H
#define XYLINECHARTITEM_H

#include "qchartconfig.h"
#include "qchart.h"
#include "xyplotdata_p.h"

QCHART_BEGIN_NAMESPACE

class QXYChartSeries;

class XYLineChartItem : public QGraphicsItem
{

public:
    XYLineChartItem(QXYChartSeries* m_series,QGraphicsItem *parent = 0);
    virtual ~ XYLineChartItem(){};

    //from QGraphicsItem
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //TODO: this is just temporary interface
    void setChartSize(const QRectF& size);
    void setXYPlotData(const XYPlotData& data);

private:
    QRectF m_rect;
    QPolygonF m_polyline;
    QXYChartSeries* m_series;
    XYPlotData m_xyPlotData;
    bool m_dirtyGeometry;
};

QCHART_END_NAMESPACE

#endif
