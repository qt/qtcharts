#ifndef SPLINECHARTITEM_P_H
#define SPLINECHARTITEM_P_H

#include "chartitem_p.h"
#include <QObject>
#include "qsplineseries.h"
#include "linechartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplineChartItem : public LineChartItem
{
    Q_OBJECT
public:
    SplineChartItem(QSplineSeries* series, QGraphicsObject *parent = 0);

    void updateGeometry();

    void setGeometry(QVector<QPointF>& points);

    QPointF calculateGeometryControlPoint(int index) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);        
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SPLINECHARTITEM_P_H
