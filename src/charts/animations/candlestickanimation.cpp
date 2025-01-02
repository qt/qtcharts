// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/candlestick_p.h>
#include <private/candlestickanimation_p.h>
#include <private/candlestickbodywicksanimation_p.h>
#include <private/candlestickchartitem_p.h>
#include <private/candlestickdata_p.h>

QT_BEGIN_NAMESPACE

CandlestickAnimation::CandlestickAnimation(CandlestickChartItem *item, int duration,
                                           QEasingCurve &curve)
    : QObject(item),
      m_item(item),
      m_animationDuration(duration),
      m_animationCurve(curve)
{
}

CandlestickAnimation::~CandlestickAnimation()
{
}

void CandlestickAnimation::addCandlestick(Candlestick *candlestick)
{
    CandlestickBodyWicksAnimation *animation = m_animations.value(candlestick, 0);
    if (!animation) {
        animation = new CandlestickBodyWicksAnimation(candlestick, this, m_animationDuration,
                                                      m_animationCurve);
        m_animations.insert(candlestick, animation);

        qreal median = (candlestick->m_data.m_open + candlestick->m_data.m_close) / 2;
        CandlestickData start;
        start.m_open = median;
        start.m_high = median;
        start.m_low = median;
        start.m_close = median;
        animation->setup(start, candlestick->m_data);
    } else {
        animation->stop();
        animation->setEndData(candlestick->m_data);
    }
}

ChartAnimation *CandlestickAnimation::candlestickAnimation(Candlestick *candlestick)
{
    CandlestickBodyWicksAnimation *animation = m_animations.value(candlestick, 0);
    if (animation)
        animation->m_changeAnimation = false;

    return animation;
}

ChartAnimation *CandlestickAnimation::candlestickChangeAnimation(Candlestick *candlestick)
{
    CandlestickBodyWicksAnimation *animation = m_animations.value(candlestick, 0);
    if (animation) {
        animation->m_changeAnimation = true;
        animation->setEndData(candlestick->m_data);
    }

    return animation;
}

void CandlestickAnimation::setAnimationStart(Candlestick *candlestick)
{
    CandlestickBodyWicksAnimation *animation = m_animations.value(candlestick, 0);
    if (animation)
        animation->setStartData(candlestick->m_data);
}

void CandlestickAnimation::stopAll()
{
    foreach (Candlestick *candlestick, m_animations.keys()) {
        CandlestickBodyWicksAnimation *animation = m_animations.value(candlestick, 0);
        if (animation)
            animation->stopAndDestroyLater();
        m_animations.remove(candlestick);
    }
}

void CandlestickAnimation::removeCandlestickAnimation(Candlestick *candlestick)
{
    m_animations.remove(candlestick);
}

QT_END_NAMESPACE

#include "moc_candlestickanimation_p.cpp"
