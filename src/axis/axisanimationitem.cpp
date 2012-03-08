#include "axisanimationitem_p.h"
#include <QTimer>

Q_DECLARE_METATYPE(QVector<qreal>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

const static int duration = 500;

AxisAnimationItem::AxisAnimationItem(QChartAxis* axis,AxisType type,QGraphicsItem* parent) :
AxisItem(axis,type,parent),
m_animation(new AxisAnimator(this,this))
{
}

AxisAnimationItem::~AxisAnimationItem()
{
}

void AxisAnimationItem::updateLayout(QVector<qreal>& newLayout)
{

    QVector<qreal> oldLayout = layout();

    if(newLayout.count()==0) return;

    if(zoomFactor()<0) {

        QRectF rect = geometry();
        oldLayout.resize(newLayout.count());

        for(int i=0,j=oldLayout.count()-1;i<(oldLayout.count()+1)/2;i++,j--)
        {
            oldLayout[i]= axisType()==X_AXIS?rect.left():rect.bottom();
            oldLayout[j]= axisType()==X_AXIS?rect.right():rect.top();
        }

    }
    else {

        int index = qMin(oldLayout.count()*zoomFactor(),newLayout.count()-1.0);
        oldLayout.resize(newLayout.count());

        for(int i=0;i<oldLayout.count();i++)
        {
            oldLayout[i]= oldLayout[index]; //axisType()==X_AXIS?rect.center.x():rect.center().y();
        }
    }

    if(m_animation->state()!=QAbstractAnimation::Stopped) {
        m_animation->stop();
    }

    m_animation->setDuration(duration);
    m_animation->setEasingCurve(QEasingCurve::OutQuart);
    QVariantAnimation::KeyValues value;
    m_animation->setKeyValues(value); //workaround for wrong interpolation call
    m_animation->setKeyValueAt(0.0, qVariantFromValue(oldLayout));
    m_animation->setKeyValueAt(1.0, qVariantFromValue(newLayout));

    QTimer::singleShot(0,m_animation,SLOT(start()));
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
    //Q_ASSERT(state()!=QAbstractAnimation::Stopped);
    if(state()!=QAbstractAnimation::Stopped)//workaround
    {
        QVector<qreal> vector = qVariantValue<QVector<qreal> >(value);
        m_axis->setLayout(vector);
    }

}

#include "moc_axisanimationitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
