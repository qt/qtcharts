// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/piesliceanimation_p.h>
#include <private/piechartitem_p.h>


QT_BEGIN_NAMESPACE

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

PieSliceAnimation::PieSliceAnimation(PieSliceItem *sliceItem)
    : ChartAnimation(sliceItem),
      m_sliceItem(sliceItem),
      m_currentValue(m_sliceItem->m_data)
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

    setKeyValueAt(0.0, QVariant::fromValue(startValue));
    setKeyValueAt(1.0, QVariant::fromValue(endValue));
}

void PieSliceAnimation::updateValue(const PieSliceData &endValue)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setKeyValueAt(0.0, QVariant::fromValue(m_currentValue));
    setKeyValueAt(1.0, QVariant::fromValue(endValue));
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
    PieSliceData startValue = qvariant_cast<PieSliceData>(start);
    PieSliceData endValue = qvariant_cast<PieSliceData>(end);

    PieSliceData result;
    result = endValue;
    result.m_center = linearPos(startValue.m_center, endValue.m_center, progress);
    result.m_radius = linearPos(startValue.m_radius, endValue.m_radius, progress);
    result.m_startAngle = linearPos(startValue.m_startAngle, endValue.m_startAngle, progress);
    result.m_angleSpan = linearPos(startValue.m_angleSpan, endValue.m_angleSpan, progress);
    result.m_slicePen = linearPos(startValue.m_slicePen, endValue.m_slicePen, progress);
    result.m_sliceBrush = linearPos(startValue.m_sliceBrush, endValue.m_sliceBrush, progress);
    result.m_holeRadius = linearPos(startValue.m_holeRadius, endValue.m_holeRadius, progress);

    return QVariant::fromValue(result);
}

void PieSliceAnimation::updateCurrentValue(const QVariant &value)
{
    if (state() != QAbstractAnimation::Stopped) { //workaround
        m_currentValue = qvariant_cast<PieSliceData>(value);
        m_sliceItem->setLayout(m_currentValue);
    }
}

QT_END_NAMESPACE
