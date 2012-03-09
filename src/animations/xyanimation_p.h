#ifndef XYCHARTANIMATION_P_H_
#define XYCHARTANIMATION_P_H_
#include "chartanimation_p.h"
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class XYChartItem;

class XYAnimation : public ChartAnimation
{
public:
	enum Animation { LineDrawAnimation, MoveDownAnimation, MoveUpAnimation };
    XYAnimation(XYChartItem *item);
    ~XYAnimation();
    void setAnimationType(Animation type);
    void setValues(QVector<QPointF>& oldPoints,QVector<QPointF>& newPoints);
    void updateValues(QVector<QPointF>& newPoints);

protected:
    QVariant interpolated(const QVariant &start, const QVariant & end, qreal progress ) const;
    void updateCurrentValue (const QVariant & value );
    void updateState ( QAbstractAnimation::State newState, QAbstractAnimation::State oldState);

private:
    XYChartItem *m_item;
    Animation m_type;
    QVector<QPointF> m_points;
    bool m_dirty;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
