#ifndef AXISANIMATIONITEM_H_
#define AXISANIMATIONITEM_H_

#include "axisitem_p.h"
#include "chartanimation_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

class AxisAnimation: public ChartAnimation
{
public:
    AxisAnimation(AxisItem *axis);
    ~AxisAnimation();
protected:
    virtual QVariant interpolated (const QVariant & from, const QVariant & to, qreal progress ) const;
    virtual void updateCurrentValue (const QVariant & value );
private:
    AxisItem* m_axis;
};

QTCOMMERCIALCHART_END_NAMESPACE



#endif /* AXISITEM_H_ */
