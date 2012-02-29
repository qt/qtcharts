#include "axisanimationitem_p.h"
#include <QTimer>

Q_DECLARE_METATYPE(QVector<qreal>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

const static int duration = 500;

AxisAnimationItem::AxisAnimationItem(AxisType type,QGraphicsItem* parent) :
AxisItem(type,parent),
m_animation(new AxisAnimator(this,this))
{
}

AxisAnimationItem::~AxisAnimationItem()
{
}

void AxisAnimationItem::updateItems(QVector<qreal>& oldLayout,QVector<qreal>& newLayout)
{
    if(newLayout.count()==0) return;
    oldLayout.resize(newLayout.size());

    if(m_animation->state()!=QAbstractAnimation::Stopped){
       m_animation->stop();
    }

    m_animation->setDuration(duration);
    m_animation->setEasingCurve(QEasingCurve::InOutBack);
    m_animation->setKeyValueAt(0.0, qVariantFromValue(oldLayout));
    m_animation->setKeyValueAt(1.0, qVariantFromValue(newLayout));
    QTimer::singleShot(0,m_animation,SLOT(start()));
    oldLayout = newLayout;
}

void AxisAnimationItem::setLabelsAngle(int angle)
{
    AxisItem::setLabelsAngle(angle);
}

AxisAnimator::AxisAnimator(AxisItem *axis,QObject *parent): QVariantAnimation(parent),
    m_axis(axis)
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
