#ifndef PIEANIMATION_P_H_
#define PIEANIMATION_P_H_

#include "chartanimation_p.h"
#include "piechartitem_p.h"
#include "piesliceanimation_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PieChartItem;

class PieAnimation : public ChartAnimation
{
    Q_OBJECT

public:
    PieAnimation(PieChartItem *item);
    ~PieAnimation();
    void updateValues(const PieLayout &newValues);
    void updateValue(QPieSlice *slice, const PieSliceData &newValue);
    void addSlice(QPieSlice *slice, const PieSliceData &endValue, bool isEmpty);
    void removeSlice(QPieSlice *slice);

public: // from QVariantAnimation
    void updateCurrentValue(const QVariant &value);

public Q_SLOTS:
    void destroySliceAnimationComplete();

private:
    PieChartItem *m_item;
    QHash<QPieSlice *, PieSliceAnimation *> m_animations;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
