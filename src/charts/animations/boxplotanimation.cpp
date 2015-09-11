/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/boxplotanimation_p.h>
#include <private/boxplotchartitem_p.h>
#include <private/boxwhiskersdata_p.h>
#include <private/boxwhiskersanimation_p.h>

QT_CHARTS_BEGIN_NAMESPACE

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

#include "moc_boxplotanimation_p.cpp"

QT_CHARTS_END_NAMESPACE
