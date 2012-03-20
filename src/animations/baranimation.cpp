#include "baranimation_p.h"
#include "barchartitem_p.h"
#include <QParallelAnimationGroup>
#include <QTimer>

Q_DECLARE_METATYPE(QVector<QSizeF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarAnimation::BarAnimation(BarChartItem *item)
    :ChartAnimation(item),
    m_item(item)
{
}

BarAnimation::~BarAnimation()
{
}

void BarAnimation::updateValues(const BarLayout& layout)
{
    // TODO:
    qDebug() << "BarAnimation::updateValues";
}


QVariant BarAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    QVector<QSizeF> startVector = qVariantValue<QVector<QSizeF> > (from);
    QVector<QSizeF> endVector = qVariantValue<QVector<QSizeF> > (to);
    QVector<QSizeF> result;

    Q_ASSERT(startVector.count() == endVector.count()) ;

    for(int i =0 ;i< startVector.count();i++){
           QSizeF value = startVector[i] + ((endVector[i]- endVector[i]) * progress);
           result << value;
    }
    return qVariantFromValue(result);
}

void BarAnimation::updateCurrentValue(const QVariant &)
{
    // TODO?
}

#include "moc_baranimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
