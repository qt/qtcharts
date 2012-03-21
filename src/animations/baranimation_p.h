#ifndef BARANIMATION_P_H_
#define BARANIMATION_P_H_

#include "chartanimation_p.h"
#include "barchartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class BarChartItem;
class QBarSet;
class BarSetAnimation;

class BarAnimation : public ChartAnimation
{
    Q_OBJECT

public:
    BarAnimation(BarChartItem *item);
    ~BarAnimation();

public: // from QVariantAnimation
    virtual QVariant interpolated (const QVariant & from, const QVariant & to, qreal progress ) const;
    virtual void updateCurrentValue (const QVariant & value );

public Q_SLOTS:

private:
    BarChartItem *m_item;
    QHash<QBarSet*, BarSetAnimation*> m_animations;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
