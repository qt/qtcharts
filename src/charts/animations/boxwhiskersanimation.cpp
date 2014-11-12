/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/boxwhiskersanimation_p.h>
#include <private/boxplotanimation_p.h>
#include <private/boxplotchartitem_p.h>
#include <private/boxwhiskersdata_p.h>

Q_DECLARE_METATYPE(QVector<QRectF>)
Q_DECLARE_METATYPE(QT_CHARTS_NAMESPACE::BoxWhiskersData)
Q_DECLARE_METATYPE(qreal)

QT_CHARTS_BEGIN_NAMESPACE

BoxWhiskersAnimation::BoxWhiskersAnimation(BoxWhiskers *box, BoxPlotAnimation *boxPlotAnimation)
    : ChartAnimation(box),
      m_box(box),
      m_changeAnimation(false),
      m_boxPlotAnimation(boxPlotAnimation)
{
    setDuration(ChartAnimationDuration);
    setEasingCurve(QEasingCurve::OutQuart);
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

    return qVariantFromValue(result);
}

void BoxWhiskersAnimation::updateCurrentValue(const QVariant &value)
{
    BoxWhiskersData data = qvariant_cast<BoxWhiskersData>(value);
    m_box->setLayout(data);
}

void BoxWhiskersAnimation::setup(const BoxWhiskersData &startData, const BoxWhiskersData &endData)
{
    setKeyValueAt(0.0, qVariantFromValue(startData));
    setKeyValueAt(1.0, qVariantFromValue(endData));
}

void BoxWhiskersAnimation::setEndData(const BoxWhiskersData &endData)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setEndValue(qVariantFromValue(endData));
}

void BoxWhiskersAnimation::setStartData(const BoxWhiskersData &endData)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();

    setStartValue(qVariantFromValue(endData));
}

#include "moc_boxwhiskersanimation_p.cpp"

QT_CHARTS_END_NAMESPACE

