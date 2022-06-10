// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/pieanimation_p.h>
#include <private/piesliceanimation_p.h>
#include <private/piechartitem_p.h>

QT_BEGIN_NAMESPACE

PieAnimation::PieAnimation(PieChartItem *item, int duration, QEasingCurve &curve)
    : ChartAnimation(item),
      m_item(item),
      m_animationDuration(duration),
      m_animationCurve(curve)
{
    Q_UNUSED(m_item);
}

PieAnimation::~PieAnimation()
{
}

ChartAnimation *PieAnimation::updateValue(PieSliceItem *sliceItem, const PieSliceData &sliceData)
{
    PieSliceAnimation *animation = m_animations.value(sliceItem);
    if (!animation) {
        animation = new PieSliceAnimation(sliceItem);
        animation->setDuration(m_animationDuration);
        animation->setEasingCurve(m_animationCurve);
        m_animations.insert(sliceItem, animation);
    } else {
        animation->stop();
    }

    animation->updateValue(sliceData);

    return animation;
}

ChartAnimation *PieAnimation::addSlice(PieSliceItem *sliceItem, const PieSliceData &sliceData, bool startupAnimation)
{
    PieSliceAnimation *animation = new PieSliceAnimation(sliceItem);
    animation->setDuration(m_animationDuration);
    animation->setEasingCurve(m_animationCurve);
    m_animations.insert(sliceItem, animation);

    PieSliceData startValue = sliceData;
    startValue.m_radius = 0;
    if (startupAnimation)
        startValue.m_startAngle = 0;
    else
        startValue.m_startAngle = sliceData.m_startAngle + (sliceData.m_angleSpan / 2);
    startValue.m_angleSpan = 0;

    if (sliceData.m_holeRadius > 0)
        startValue.m_radius = sliceData.m_holeRadius;

    animation->setValue(startValue, sliceData);

    return animation;
}

ChartAnimation *PieAnimation::removeSlice(PieSliceItem *sliceItem)
{
    PieSliceAnimation *animation = m_animations.value(sliceItem);
    Q_ASSERT(animation);
    animation->stop();

    PieSliceData endValue = animation->currentSliceValue();
    if (endValue.m_holeRadius > 0)
        endValue.m_radius = endValue.m_holeRadius;
    else
        endValue.m_radius = 0;
    endValue.m_startAngle = endValue.m_startAngle + endValue.m_angleSpan;
    endValue.m_angleSpan = 0;
    endValue.m_isLabelVisible = false;

    animation->updateValue(endValue);

    // PieSliceItem is the parent of PieSliceAnimation so the animation will be deleted as well..
    connect(animation, SIGNAL(finished()), sliceItem, SLOT(deleteLater()));
    m_animations.remove(sliceItem);

    return animation;
}

void PieAnimation::updateCurrentValue(const QVariant &)
{
    // nothing to do...
}

QT_END_NAMESPACE

#include "moc_pieanimation_p.cpp"
