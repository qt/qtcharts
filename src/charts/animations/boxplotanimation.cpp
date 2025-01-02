// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/boxplotanimation_p.h>
#include <private/boxplotchartitem_p.h>
#include <private/boxwhiskersdata_p.h>
#include <private/boxwhiskersanimation_p.h>

QT_BEGIN_NAMESPACE

BoxPlotAnimation::BoxPlotAnimation(BoxPlotChartItem *item, int duration, QEasingCurve &curve)
    : QObject(item),
    m_item(item),
    m_animationDuration(duration),
    m_animationCurve(curve)
{
}

BoxPlotAnimation::~BoxPlotAnimation()
{
}

void BoxPlotAnimation::addBox(BoxWhiskers *box)
{
    BoxWhiskersAnimation *animation = m_animations.value(box);
    if (!animation) {
        animation = new BoxWhiskersAnimation(box, this, m_animationDuration, m_animationCurve);
        m_animations.insert(box, animation);
        BoxWhiskersData start;
        start.m_lowerExtreme = box->m_data.m_median;
        start.m_lowerQuartile = box->m_data.m_median;
        start.m_median = box->m_data.m_median;
        start.m_upperQuartile = box->m_data.m_median;
        start.m_upperExtreme = box->m_data.m_median;
        animation->setup(start, box->m_data);

    } else {
        animation->stop();
        animation->setEndData(box->m_data);
    }
}

ChartAnimation *BoxPlotAnimation::boxAnimation(BoxWhiskers *box)
{
    BoxWhiskersAnimation *animation = m_animations.value(box);
    if (animation)
        animation->m_changeAnimation = false;

    return animation;
}

ChartAnimation *BoxPlotAnimation::boxChangeAnimation(BoxWhiskers *box)
{
    BoxWhiskersAnimation *animation = m_animations.value(box);
    animation->m_changeAnimation = true;
    animation->setEndData(box->m_data);

    return animation;
}

void BoxPlotAnimation::setAnimationStart(BoxWhiskers *box)
{
    BoxWhiskersAnimation *animation = m_animations.value(box);
    animation->setStartData(box->m_data);
}

void BoxPlotAnimation::stopAll()
{
    foreach (BoxWhiskers *box, m_animations.keys()) {
        BoxWhiskersAnimation *animation = m_animations.value(box);
        animation->stopAndDestroyLater();
        m_animations.remove(box);
    }
}

void BoxPlotAnimation::removeBoxAnimation(BoxWhiskers *box)
{
    m_animations.remove(box);
}

QT_END_NAMESPACE

#include "moc_boxplotanimation_p.cpp"
