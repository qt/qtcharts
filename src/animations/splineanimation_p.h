#ifndef SPLINEANIMATION_P_H_
#define SPLINEANIMATION_P_H_
#include "chartanimation_p.h"
#include <QPointF>

typedef  QPair<QVector<QPointF >, QVector<QPointF > >  SplineVector;

QTCOMMERCIALCHART_BEGIN_NAMESPACE


class SplineChartItem;

class SplineAnimation : public ChartAnimation
{
public:

    SplineAnimation(SplineChartItem* item);
    ~SplineAnimation();
    void setValues(QVector<QPointF>& oldPoints,QVector<QPointF>& newPoints,QVector<QPointF>& oldContorlPoints,QVector<QPointF>& newControlPoints,int index);

protected:
    QVariant interpolated(const QVariant &start, const QVariant & end, qreal progress ) const;
    void updateCurrentValue (const QVariant & value );

private:
    SplineVector m_oldSpline;
    SplineChartItem* m_item;
    bool m_dirty;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
