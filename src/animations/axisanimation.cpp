#include "axisanimation_p.h"
#include <QTimer>

Q_DECLARE_METATYPE(QVector<qreal>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE


AxisAnimation::AxisAnimation(AxisItem *axis): ChartAnimation(axis),
    m_axis(axis)
{
}

AxisAnimation::~AxisAnimation()
{
}

QVariant AxisAnimation::interpolated(const QVariant &start, const QVariant & end, qreal progress ) const
{
    QVector<qreal> startVector = qVariantValue<QVector<qreal> >(start);
    QVector<qreal> endVecotr = qVariantValue<QVector<qreal> >(end);
    QVector<qreal> result;

    Q_ASSERT(startVector.count() == endVecotr.count()) ;

    for(int i =0 ;i< startVector.count();i++){
           qreal value = startVector[i] + ((endVecotr[i]- startVector[i]) * progress);//qBound(0.0, progress, 1.0));
           result << value;
    }
    return qVariantFromValue(result);
}


void AxisAnimation::updateCurrentValue (const QVariant & value )
{
    if(state()!=QAbstractAnimation::Stopped)//workaround
    {
        QVector<qreal> vector = qVariantValue<QVector<qreal> >(value);
        Q_ASSERT(vector.count()!=0);
        m_axis->setLayout(vector);
    }

}

QTCOMMERCIALCHART_END_NAMESPACE
