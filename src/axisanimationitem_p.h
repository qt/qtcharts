#ifndef AXISANIMATIONITEM_H_
#define AXISANIMATIONITEM_H_

#include "domain_p.h"
#include "axisitem_p.h"
#include <QGraphicsItem>
#include <QVariantAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class AxisAnimator;

class AxisAnimationItem : public AxisItem
{
    Q_OBJECT

public:
    AxisAnimationItem(QChartAxis* axis,AxisType type = X_AXIS,QGraphicsItem* parent = 0);
    ~AxisAnimationItem();

    void setLabelsAngle(int angle);

protected:
    virtual void updateItem();
private:
    AxisAnimator *m_animation;
};

class AxisAnimator: public QVariantAnimation
{
public:
    AxisAnimator(AxisItem *axis,QObject *parent = 0);
    ~AxisAnimator();
protected:
    virtual QVariant interpolated (const QVariant & from, const QVariant & to, qreal progress ) const;
    virtual void updateCurrentValue (const QVariant & value );
private:
    AxisItem* m_axis;
};

QTCOMMERCIALCHART_END_NAMESPACE



#endif /* AXISITEM_H_ */
