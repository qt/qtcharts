#ifndef SPLINECHARTITEM_P_H
#define SPLINECHARTITEM_P_H

#include "qsplineseries.h"
#include "xychartitem_p.h"
#include "xychartanimationitem_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplineChartItem : public XYChartItem
{
    Q_OBJECT
public:
    SplineChartItem(QSplineSeries* series, QGraphicsItem *parent = 0);

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    void setLinePen(const QPen& pen);
    void setPointsVisible(bool visible);

public slots:
    void handleUpdated();

protected:
    void setGeometry(QVector<QPointF>& points);

private:
    QPointF calculateGeometryControlPoint(int index) const;

private:
    QSplineSeries* m_series;
    QPainterPath m_path;
    QRectF m_rect;
    QPen m_pen;

    template<class,class> friend class XYChartAnimator;
};

typedef XYChartAnimationItem<SplineChartItem,QSplineSeries> SplineChartAnimationItem;

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SPLINECHARTITEM_P_H
