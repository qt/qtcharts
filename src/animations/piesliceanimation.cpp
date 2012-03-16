#include "piesliceanimation_p.h"
#include "piechartitem_p.h"
#include "qpieslice.h"

Q_DECLARE_METATYPE(QtCommercialChart::PieSliceLayout)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

qreal linearPos(qreal start, qreal end, qreal pos)
{
    return start + ((end - start) * pos);
}

QPointF linearPos(QPointF start, QPointF end, qreal pos)
{
    qreal x = linearPos(start.x(), end.x(), pos);
    qreal y = linearPos(start.y(), end.y(), pos);
    return QPointF(x, y);
}

PieSliceAnimation::PieSliceAnimation(PieChartItem *item, QPieSlice *slice)
    :QVariantAnimation(item),
    m_item(item),
    m_slice(slice)
{
}

PieSliceAnimation::~PieSliceAnimation()
{
}

void PieSliceAnimation::setValue(const PieSliceLayout &startValue, const PieSliceLayout &endValue)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setKeyValueAt(0.0, qVariantFromValue(startValue));
    setKeyValueAt(1.0, qVariantFromValue(endValue));
}

void PieSliceAnimation::updateValue(const PieSliceLayout &endValue)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setKeyValueAt(0.0, qVariantFromValue(currentSliceValue()));
    setKeyValueAt(1.0, qVariantFromValue(endValue));
}

PieSliceLayout PieSliceAnimation::currentSliceValue()
{
    return qVariantValue<PieSliceLayout>(currentValue());
}

QVariant PieSliceAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress) const
{
    PieSliceLayout startValue = qVariantValue<PieSliceLayout>(start);
    PieSliceLayout endValue = qVariantValue<PieSliceLayout>(end);

    PieSliceLayout result;
    result = endValue;
    result.m_center = linearPos(startValue.m_center, endValue.m_center, progress);
    result.m_radius = linearPos(startValue.m_radius, endValue.m_radius, progress);
    result.m_startAngle = linearPos(startValue.m_startAngle, endValue.m_startAngle, progress);
    result.m_angleSpan = linearPos(startValue.m_angleSpan, endValue.m_angleSpan, progress);

    return qVariantFromValue(result);
}

void PieSliceAnimation::updateCurrentValue(const QVariant &value)
{
    PieSliceLayout layout = qVariantValue<PieSliceLayout>(value);
    if (state() != QAbstractAnimation::Stopped) //workaround
        m_item->setLayout(m_slice, layout);
}

QTCOMMERCIALCHART_END_NAMESPACE
