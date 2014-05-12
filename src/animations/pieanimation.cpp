/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "pieanimation_p.h"
#include "piesliceanimation_p.h"
#include "piechartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PieAnimation::PieAnimation(PieChartItem *item)
    : ChartAnimation(item),
      m_item(item)
{
}

PieAnimation::~PieAnimation()
{
}

ChartAnimation *PieAnimation::updateValue(PieSliceItem *sliceItem, const PieSliceData &sliceData)
{
    PieSliceAnimation *animation = m_animations.value(sliceItem);
    if (!animation) {
        animation = new PieSliceAnimation(sliceItem);
        m_animations.insert(sliceItem, animation);
    } else {
        animation->stop();
    }

    animation->updateValue(sliceData);
    animation->setDuration(ChartAnimationDuration);
    animation->setEasingCurve(QEasingCurve::OutQuart);

    return animation;
}

ChartAnimation *PieAnimation::addSlice(PieSliceItem *sliceItem, const PieSliceData &sliceData, bool startupAnimation)
{
    PieSliceAnimation *animation = new PieSliceAnimation(sliceItem);
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
    animation->setDuration(ChartAnimationDuration);
    animation->setEasingCurve(QEasingCurve::OutQuart);

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
    animation->setDuration(ChartAnimationDuration);
    animation->setEasingCurve(QEasingCurve::OutQuart);

    // PieSliceItem is the parent of PieSliceAnimation so the animation will be deleted as well..
    connect(animation, SIGNAL(finished()), sliceItem, SLOT(deleteLater()));
    m_animations.remove(sliceItem);

    return animation;
}

void PieAnimation::updateCurrentValue(const QVariant &)
{
    // nothing to do...
}

#include "moc_pieanimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
