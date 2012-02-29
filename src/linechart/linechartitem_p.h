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
    LineChartItem(ChartPresenter* presenter, QLineSeries* series,QGraphicsItem *parent = 0);
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
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& size);

public:
    virtual void updateItem(QVector<QPointF>& oldPoints,QVector<QPointF>& newPoints);
    virtual void updateItem(QVector<QPointF>& oldPoints,int index,QPointF& newPoint);
    void applyGeometry(QVector<QPointF>& points);
    void createPoints(int count);
    void clearPoints(int count);
    QPointF calculateGeometryPoint(int index) const;
    QVector<QPointF> calculateGeometryPoints() const;

private:
    ChartPresenter* m_presenter;
    QPainterPath m_path;
    QLineSeries* m_series;
    QSizeF m_size;
    QRectF m_rect;
    QRectF m_clipRect;
    Domain m_domain;
    QGraphicsItemGroup m_items;
    QVector<QPointF> m_points;
    QPen m_pen;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
