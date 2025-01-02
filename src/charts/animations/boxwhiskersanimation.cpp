// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/boxwhiskersanimation_p.h>
#include <private/boxplotanimation_p.h>
#include <private/boxplotchartitem_p.h>
#include <private/boxwhiskersdata_p.h>


QT_BEGIN_NAMESPACE

BoxWhiskersAnimation::BoxWhiskersAnimation(BoxWhiskers *box, BoxPlotAnimation *boxPlotAnimation,
                                           int duration, QEasingCurve &curve)
    : ChartAnimation(box),
      m_box(box),
      m_changeAnimation(false),
      m_boxPlotAnimation(boxPlotAnimation)
{
    setDuration(duration);
    setEasingCurve(curve);
}

BoxWhiskersAnimation::~BoxWhiskersAnimation()
{
    if (m_boxPlotAnimation)
        m_boxPlotAnimation->removeBoxAnimation(m_box);
}

QVariant BoxWhiskersAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    BoxWhiskersData startData = qvariant_cast<BoxWhiskersData>(from);
    BoxWhiskersData endData = qvariant_cast<BoxWhiskersData>(to);
    BoxWhiskersData result;

    if (m_changeAnimation) {
        result.m_lowerExtreme = startData.m_lowerExtreme + progress * (endData.m_lowerExtreme - startData.m_lowerExtreme);
        result.m_lowerQuartile = startData.m_lowerQuartile + progress * (endData.m_lowerQuartile - startData.m_lowerQuartile);
        result.m_median = startData.m_median + progress * (endData.m_median - startData.m_median);
        result.m_upperQuartile = startData.m_upperQuartile + progress * (endData.m_upperQuartile - startData.m_upperQuartile);
        result.m_upperExtreme = startData.m_upperExtreme + progress * (endData.m_upperExtreme - startData.m_upperExtreme);
    } else {
        result.m_lowerExtreme = endData.m_median + progress * (endData.m_lowerExtreme - endData.m_median);
        result.m_lowerQuartile = endData.m_median + progress * (endData.m_lowerQuartile - endData.m_median);
        result.m_median = endData.m_median;
        result.m_upperQuartile = endData.m_median + progress * (endData.m_upperQuartile - endData.m_median);
        result.m_upperExtreme = endData.m_median + progress * (endData.m_upperExtreme - endData.m_median);
    }
    result.m_index = endData.m_index;
    result.m_boxItems = endData.m_boxItems;

    result.m_maxX = endData.m_maxX;
    result.m_minX = endData.m_minX;
    result.m_maxY = endData.m_maxY;
    result.m_minY = endData.m_minY;
    result.m_seriesIndex = endData.m_seriesIndex;
    result.m_seriesCount = endData.m_seriesCount;

    return QVariant::fromValue(result);
}

void BoxWhiskersAnimation::updateCurrentValue(const QVariant &value)
{
    const BoxWhiskersData data = qvariant_cast<BoxWhiskersData>(value);
    m_box->setLayout(data);
}

void BoxWhiskersAnimation::setup(const BoxWhiskersData &startData, const BoxWhiskersData &endData)
{
    setKeyValueAt(0.0, QVariant::fromValue(startData));
    setKeyValueAt(1.0, QVariant::fromValue(endData));
}

void BoxWhiskersAnimation::setEndData(const BoxWhiskersData &endData)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setEndValue(QVariant::fromValue(endData));
}

void BoxWhiskersAnimation::setStartData(const BoxWhiskersData &endData)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setStartValue(QVariant::fromValue(endData));
}

QT_END_NAMESPACE

#include "moc_boxwhiskersanimation_p.cpp"
