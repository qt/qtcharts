/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "boxplotanimation_p.h"
#include "boxplotchartitem_p.h"
#include "boxwhiskersdata_p.h"
#include "boxwhiskersanimation_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BoxPlotAnimation::BoxPlotAnimation(BoxPlotChartItem *item)
      : m_item(item)
{
}

BoxPlotAnimation::~BoxPlotAnimation()
{
}

void BoxPlotAnimation::addBox(BoxWhiskers *box)
{
    BoxWhiskersAnimation *animation = m_animations.value(box);
    if (!animation) {
        animation = new BoxWhiskersAnimation(box);
        m_animations.insert(box, animation);
        BoxWhiskersData start;
        start.m_median = box->m_data.m_median;
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
        animation->m_moveMedianLine = false;

    return animation;
}

ChartAnimation *BoxPlotAnimation::boxChangeAnimation(BoxWhiskers *box)
{
    BoxWhiskersAnimation *animation = m_animations.value(box);
    animation->m_moveMedianLine = true;
    animation->setEndData(box->m_data);

    return animation;
}

void BoxPlotAnimation::setAnimationStart(BoxWhiskers *box)
{
    BoxWhiskersAnimation *animation = m_animations.value(box);
    animation->setStartData(box->m_data);
}

//#include "moc_boxplotanimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
