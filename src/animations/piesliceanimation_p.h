#ifndef PIESLICEANIMATION_P_H_
#define PIESLICEANIMATION_P_H_

#include "piechartitem_p.h"
#include <QVariantAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieChartItem;
class QPieSlice;

class PieSliceAnimation : public QVariantAnimation
{
public:
    PieSliceAnimation(PieChartItem *item, QPieSlice *slice);
    ~PieSliceAnimation();
    void setValue(const PieSliceLayout &startValue, const PieSliceLayout &endValue);
    void updateValue(const PieSliceLayout &endValue);
    PieSliceLayout currentSliceValue();

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const;
    void updateCurrentValue(const QVariant &value);

private:
    PieChartItem *m_item;
    QPieSlice *m_slice;
    PieSliceLayout m_currentValue;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
