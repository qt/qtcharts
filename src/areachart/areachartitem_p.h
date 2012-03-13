#ifndef AREACHARTITEM_H
#define AREACHARTITEM_H

#include "qchartglobal.h"
#include "linechartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAreaSeries;
class AreaChartItem;

class AreaChartItem :  public QObject ,public ChartItem
{
    Q_OBJECT
public:
    AreaChartItem(QAreaSeries* areaSeries, QGraphicsItem *parent = 0);
    ~ AreaChartItem();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    void setPointsVisible(bool visible);
    void updatePath();
public slots:
    void handleUpdated();
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF& size);

private:
    QAreaSeries* m_series;
    LineChartItem* m_upper;
    LineChartItem* m_lower;
    QPainterPath m_path;
    QRectF m_rect;
    QRectF m_clipRect;
    QPen m_pen;
    QBrush m_brush;
};

class AreaBoundItem : public LineChartItem
{
public:
    AreaBoundItem(AreaChartItem* item,QLineSeries* lineSeries):LineChartItem(lineSeries),
    m_item(item){};

    ~AreaBoundItem(){};

    void setLayout(QVector<QPointF>& points){
        LineChartItem::setLayout(points);
        m_item->updatePath();
    }

private:
    AreaChartItem* m_item;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
