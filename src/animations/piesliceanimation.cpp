#include "piesliceanimation_p.h"
#include "piechartitem_p.h"
#include "qpieslice.h"

Q_DECLARE_METATYPE(QtCommercialChart::PieSliceData)

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

QPen linearPos(QPen start, QPen end, qreal pos)
{
    QColor c;
    c.setRedF(linearPos(start.color().redF(), end.color().redF(), pos));
    c.setGreenF(linearPos(start.color().greenF(), end.color().greenF(), pos));
    c.setBlueF(linearPos(start.color().blueF(), end.color().blueF(), pos));
    end.setColor(c);
    return end;
}

QBrush linearPos(QBrush start, QBrush end, qreal pos)
{
    QColor c;
    c.setRedF(linearPos(start.color().redF(), end.color().redF(), pos));
    c.setGreenF(linearPos(start.color().greenF(), end.color().greenF(), pos));
    c.setBlueF(linearPos(start.color().blueF(), end.color().blueF(), pos));
    end.setColor(c);
    return end;
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

void PieSliceAnimation::setValue(const PieSliceData &startValue, const PieSliceData &endValue)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    m_currentValue = startValue;

    setKeyValueAt(0.0, qVariantFromValue(startValue));
    setKeyValueAt(1.0, qVariantFromValue(endValue));
}

void PieSliceAnimation::updateValue(const PieSliceData &endValue)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setKeyValueAt(0.0, qVariantFromValue(m_currentValue));
    setKeyValueAt(1.0, qVariantFromValue(endValue));
}

PieSliceData PieSliceAnimation::currentSliceValue()
{
    // NOTE:
    // We must use an internal current value because QVariantAnimation::currentValue() is updated
    // before the animation is actually started. So if we get 2 updateValue() calls in a row the currentValue()
    // will have the end value set from the first call and the second call will interpolate that instead of
    // the original current value as it was before the first call.
    return m_currentValue;
}

QVariant PieSliceAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress) const
{
    PieSliceData startValue = qVariantValue<PieSliceData>(start);
    PieSliceData endValue = qVariantValue<PieSliceData>(end);

    PieSliceData result;
    result = endValue;
    result.m_center = linearPos(startValue.m_center, endValue.m_center, progress);
    result.m_radius = linearPos(startValue.m_radius, endValue.m_radius, progress);
    result.m_startAngle = linearPos(startValue.m_startAngle, endValue.m_startAngle, progress);
    result.m_angleSpan = linearPos(startValue.m_angleSpan, endValue.m_angleSpan, progress);
    result.m_slicePen = linearPos(startValue.m_slicePen, endValue.m_slicePen, progress);
    result.m_sliceBrush = linearPos(startValue.m_sliceBrush, endValue.m_sliceBrush, progress);

    return qVariantFromValue(result);
}

void PieSliceAnimation::updateCurrentValue(const QVariant &value)
{
    if (state() != QAbstractAnimation::Stopped) { //workaround
        m_currentValue = qVariantValue<PieSliceData>(value);
        m_item->setLayout(m_slice, m_currentValue);
    }
}

QTCOMMERCIALCHART_END_NAMESPACE
