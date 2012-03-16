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
    void setValues(QVector<QPointF>& oldPoints,QVector<QPointF>& newPoints,int index);

protected:
    QVariant interpolated(const QVariant &start, const QVariant & end, qreal progress ) const;
    void updateCurrentValue (const QVariant & value );

private:
    XYChartItem *m_item;
    QVector<QPointF> m_oldPoints;
    bool m_dirty;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
