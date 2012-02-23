#ifndef AXISANIMATIONITEM_H_
#define AXISANIMATIONITEM_H_

#include "domain_p.h"
#include "axisitem_p.h"
#include <QGraphicsItem>
#include <QVariantAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxis;

class AxisAnimationItem : public AxisItem
{
    Q_OBJECT

public:
    AxisAnimationItem(AxisType type = X_AXIS,QGraphicsItem* parent = 0);
    ~AxisAnimationItem();

    void setLabelsAngle(int angle);

protected:
    void updateItems(QVector<qreal>& vector);

};

class AxisAnimator: public QVariantAnimation
{
public:
    AxisAnimator(AxisItem *axis);
    virtual ~AxisAnimator();
protected:
    virtual QVariant interpolated (const QVariant & from, const QVariant & to, qreal progress ) const;
    virtual void updateCurrentValue (const QVariant & value );
private:
    AxisItem* m_axis;
};

QTCOMMERCIALCHART_END_NAMESPACE



#endif /* AXISITEM_H_ */
