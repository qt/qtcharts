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
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& size);

protected:
    virtual void addPoint(const QPointF& );
    virtual void addPoints(const QVector<QPointF>& points);
    virtual void removePoint(const QPointF& point);
    virtual void replacePoint(const QPointF& oldPoint, const QPointF& newPoint);
    virtual void replacePoint(int index,const QPointF& point);
    virtual void updateItem(QVector<QPointF>& points,QVector<int>& map);
    virtual void applyGeometry(QVector<QPointF>& points);

    void clear();

    QPointF calculatePoint(int index) const;
    void calculatePoints(QVector<QPointF>& points,QVector<int>& map) const;

private:
    ChartPresenter* m_presenter;
    QPainterPath m_path;
    QSizeF m_size;
    QRectF m_rect;
    QRectF m_clipRect;
    Domain m_domain;
    QList<QGraphicsItem*> m_items;
    QVector<QPointF> m_points;
    QVector<int> m_map;
    QLineSeries* m_series;
    QPen m_pen;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
