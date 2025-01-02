// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/candlestick_p.h>
#include <private/candlestickanimation_p.h>
#include <private/candlestickbodywicksanimation_p.h>


QT_BEGIN_NAMESPACE

CandlestickBodyWicksAnimation::CandlestickBodyWicksAnimation(Candlestick *candlestick,
                                                             CandlestickAnimation *animation,
                                                             int duration, QEasingCurve &curve)
    : ChartAnimation(candlestick),
      m_candlestick(candlestick),
      m_candlestickAnimation(animation),
      m_changeAnimation(false)
{
    setDuration(duration);
    setEasingCurve(curve);
}

CandlestickBodyWicksAnimation::~CandlestickBodyWicksAnimation()
{
    if (m_candlestickAnimation)
        m_candlestickAnimation->removeCandlestickAnimation(m_candlestick);
}

void CandlestickBodyWicksAnimation::setup(const CandlestickData &startData,
                                          const CandlestickData &endData)
{
    setKeyValueAt(0.0, QVariant::fromValue(startData));
    setKeyValueAt(1.0, QVariant::fromValue(endData));
}

void CandlestickBodyWicksAnimation::setStartData(const CandlestickData &startData)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setStartValue(QVariant::fromValue(startData));
}

void CandlestickBodyWicksAnimation::setEndData(const CandlestickData &endData)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setEndValue(QVariant::fromValue(endData));
}

void CandlestickBodyWicksAnimation::updateCurrentValue(const QVariant &value)
{
    const CandlestickData data = qvariant_cast<CandlestickData>(value);
    m_candlestick->setLayout(data);
}

QVariant CandlestickBodyWicksAnimation::interpolated(const QVariant &from, const QVariant &to,
                                                     qreal progress) const
{
    CandlestickData startData = qvariant_cast<CandlestickData>(from);
    CandlestickData endData = qvariant_cast<CandlestickData>(to);
    CandlestickData result = endData;

    if (m_changeAnimation) {
        result.m_open = startData.m_open + progress * (endData.m_open - startData.m_open);
        result.m_high = startData.m_high + progress * (endData.m_high - startData.m_high);
        result.m_low = startData.m_low + progress * (endData.m_low - startData.m_low);
        result.m_close = startData.m_close + progress * (endData.m_close - startData.m_close);
    } else {
        const qreal median = (endData.m_open + endData.m_close) / 2;
        result.m_low = median + progress * (endData.m_low - median);
        result.m_close = median + progress * (endData.m_close - median);
        result.m_open = median + progress * (endData.m_open - median);
        result.m_high = median + progress * (endData.m_high - median);
    }

    return QVariant::fromValue(result);
}

QT_END_NAMESPACE

#include "moc_candlestickbodywicksanimation_p.cpp"
