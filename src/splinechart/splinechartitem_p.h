#ifndef SPLINECHARTITEM_P_H
#define SPLINECHARTITEM_P_H

#include "chartitem_p.h"
#include <QObject>
#include "qsplineseries.h"
#include "xychartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplineChartItem : public XYChartItem
{
    Q_OBJECT
public:
    SplineChartItem(QSplineSeries* series, QGraphicsObject *parent = 0);

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    void setPen(const QPen& pen);
    void setPointsVisible(bool visible);

protected:
    void setGeometry(QVector<QPointF>& points);

private:
    QPointF calculateGeometryControlPoint(int index) const;

private:
    QSplineSeries* m_series;
    QPainterPath m_path;
    QRectF m_rect;
    QPen m_pen;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SPLINECHARTITEM_P_H
