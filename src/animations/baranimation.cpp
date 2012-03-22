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
        qreal w = endVector[i].width();
        qreal h = startVector[i].height() + ((endVector[i].height() - startVector[i].height()) * progress);
        qreal x = endVector[i].topLeft().x();
        qreal y = endVector[i].topLeft().y() + endVector[i].height() - h;

        QPointF topLeft(x,y);
        QSizeF size(w,h);
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
