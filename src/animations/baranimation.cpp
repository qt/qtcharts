#include "baranimation_p.h"
#include "barchartitem_p.h"
#include <QParallelAnimationGroup>
#include <QTimer>

Q_DECLARE_METATYPE(QVector<QRectF>)
//Q_DECLARE_METATYPE(BarLayout)     // TODO?


QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarAnimation::BarAnimation(BarChartItem *item)
    :ChartAnimation(item),
    m_item(item)
{
}

BarAnimation::~BarAnimation()
{
}

QVariant BarAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    QVector<QRectF> startVector = qVariantValue<QVector<QRectF> > (from);
    QVector<QRectF> endVector = qVariantValue<QVector<QRectF> > (to);
    QVector<QRectF> result;

    Q_ASSERT(startVector.count() == endVector.count()) ;

    for(int i =0 ;i< startVector.count();i++){
        //QRectF value = startVector[i] + ((endVector[i] - startVector[i]) * progress);
        QPointF topLeft = startVector[i].topLeft() + ((endVector[i].topLeft() - startVector[i].topLeft()) * progress);
        QSizeF size = startVector[i].size() + ((endVector[i].size() - startVector[i].size()) * progress);
        QRectF value(topLeft,size);
        result << value;
    }
    return qVariantFromValue(result);
}

void BarAnimation::updateCurrentValue(const QVariant &value)
{
    QVector<QRectF> layout = qVariantValue<QVector<QRectF> >(value);
    m_item->setLayout(layout);
}

#include "moc_baranimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
