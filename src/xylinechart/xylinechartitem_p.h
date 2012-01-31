#ifndef XYLINECHARTITEM_H
#define XYLINECHARTITEM_H

#include "qchartglobal.h"
#include "chartitem_p.h"
#include "charttheme_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QXYChartSeries;

class XYLineChartItem : public ChartItem
{

public:
    XYLineChartItem(QXYChartSeries* m_series,QGraphicsItem *parent = 0);
    ~ XYLineChartItem(){};

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};
   // virtual QPainterPath shape() const;

public: // from ChartObjectInterface
    void setSize(const QSize &size);
    void setTheme(ChartTheme *theme);
    void setPlotDomain(const PlotDomain& data);

private:
    void updateGeometry();

private:
    QRect m_rect;
    QPolygonF m_polyline;
    QXYChartSeries* m_series;
    PlotDomain m_plotDomain;
    QGraphicsPathItem *m_pathItem;
    SeriesTheme m_theme;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
