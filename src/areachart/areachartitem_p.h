#ifndef AREACHARTITEM_H
#define AREACHARTITEM_H

#include "qchartglobal.h"
#include "linechartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAreaSeries;
class AreaChartItem;

class AreaChartItem : public ChartItem
{
    Q_OBJECT
public:
    AreaChartItem(QAreaSeries* areaSeries, ChartPresenter *presenter);
    ~ AreaChartItem();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    LineChartItem* upperLineItem() const { return m_upper ;}
    LineChartItem* lowerLineItem() const { return m_lower ;}

    void updatePath();

protected:
    void mousePressEvent( QGraphicsSceneMouseEvent * event );

signals:
    void clicked(const QPointF& point);

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
    QPen m_linePen;
    QPen m_pointPen;
    QBrush m_brush;
    bool m_pointsVisible;

};

class AreaBoundItem : public LineChartItem
{
public:
    AreaBoundItem(AreaChartItem* item,QLineSeries* lineSeries):LineChartItem(lineSeries,0),
    m_item(item){
    };

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
