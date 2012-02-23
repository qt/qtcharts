#include "axisanimationitem_p.h"
#include <QPropertyAnimation>

Q_DECLARE_METATYPE(QVector<qreal>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

const static int duration = 500;

AxisAnimationItem::AxisAnimationItem(AxisType type,QGraphicsItem* parent) :
AxisItem(type,parent)
{
}

AxisAnimationItem::~AxisAnimationItem()
{
}

void AxisAnimationItem::updateItems(QVector<qreal>& vector1)
{
    QVector<qreal> vector0 = vector1;
    calculateLayout(vector1);
    if(vector1.count()==0) return;
    vector0.resize(vector1.size());

    AxisAnimator *animation = new AxisAnimator(this);
    animation->setDuration(duration);
    animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->setKeyValueAt(0.0, qVariantFromValue(vector0));
    animation->setKeyValueAt(1.0, qVariantFromValue(vector1));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void AxisAnimationItem::setLabelsAngle(int angle)
{
    AxisItem::setLabelsAngle(angle);
}

AxisAnimator::AxisAnimator(AxisItem *axis): m_axis(axis)
{
}

AxisAnimator::~AxisAnimator()
{
}

QVariant AxisAnimator::interpolated(const QVariant &start, const QVariant & end, qreal progress ) const
{
    QVector<qreal> startVector = qVariantValue<QVector<qreal> >(start);
    QVector<qreal> endVecotr = qVariantValue<QVector<qreal> >(end);
    QVector<qreal> result;
    Q_ASSERT(startVector.count() == endVecotr.count());

    for(int i =0 ;i< startVector.count();i++){
           qreal value = startVector[i] + ((endVecotr[i]- startVector[i]) * progress);//qBound(0.0, progress, 1.0));
           result << value;
    }
    return qVariantFromValue(result);
}


void AxisAnimator::updateCurrentValue (const QVariant & value )
{
    QVector<qreal> vector = qVariantValue<QVector<qreal> >(value);
    m_axis->applyLayout(vector);
}

#include "moc_axisanimationitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
