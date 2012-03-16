#ifndef PIESLICEANIMATION_P_H_
#define PIESLICEANIMATION_P_H_

#include "piechartitem_p.h"
#include <QVariantAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieChartItem;

class PieSliceAnimation : public QVariantAnimation
{
public:
    PieSliceAnimation(PieChartItem *item);
    ~PieSliceAnimation();
    void setValue(PieSliceLayout& startValue, PieSliceLayout& endValue);
    void updateValue(PieSliceLayout& endValue);
    PieSliceLayout currentSliceValue();

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const;
    void updateCurrentValue(const QVariant &value);

private:
    PieChartItem *m_item;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
