#ifndef SPLINEPRESENTER_P_H
#define SPLINEPRESENTER_P_H

#include "chartitem_p.h"
#include <QObject>
#include "qsplineseries.h"
#include "linechartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplinePresenter : public LineChartItem
{
    Q_OBJECT
public:
    SplinePresenter(QSplineSeries* series, QGraphicsObject *parent = 0);

    void updateGeometry();

    void applyGeometry(QVector<QPointF>& points);

    QPointF calculateGeometryControlPoint(int index) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
signals:
    
public slots:
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SPLINEPRESENTER_P_H
