#ifndef LINECHARTITEM_H
#define LINECHARTITEM_H

#include "qchartglobal.h"
#include "chartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class QLineSeries;

class LineChartItem :  public QObject , public ChartItem
{
     Q_OBJECT
public:
    LineChartItem(QLineSeries* series,QGraphicsItem *parent = 0);
    ~ LineChartItem(){};

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    void setPen(const QPen& pen);
    void setPointsVisible(bool visible);

public slots:
    void handlePointAdded(int index);
    void handlePointRemoved(int index);
    void handlePointReplaced(int index);
    void handleUpdated();
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF& size);

public:
    virtual void updateItem(QVector<QPointF>& oldPoints,QVector<QPointF>& newPoints);
    virtual void updateItem(QVector<QPointF>& oldPoints,int index,QPointF& newPoint);
    virtual void applyGeometry(QVector<QPointF>& points);
    void createPoints(int count);
    void clearPoints(int count);
    QPointF calculateGeometryPoint(int index) const;
    QVector<QPointF> calculateGeometryPoints() const;

protected:
    qreal m_minX;
    qreal m_maxX;
    qreal m_minY;
    qreal m_maxY;
    QPainterPath m_path;
    QRectF m_rect;
    QLineSeries* m_series;
    QSizeF m_size;
    QRectF m_clipRect;
    QGraphicsItemGroup m_items;
    QVector<QPointF> m_points;
    QPen m_pen;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
