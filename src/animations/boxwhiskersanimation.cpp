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

#include "boxwhiskersanimation_p.h"
#include "boxplotanimation_p.h"
#include "boxplotchartitem_p.h"
#include "boxwhiskersdata_p.h"

Q_DECLARE_METATYPE(QVector<QRectF>)
Q_DECLARE_METATYPE(QTCOMMERCIALCHART_NAMESPACE::BoxWhiskersData)
Q_DECLARE_METATYPE(qreal)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BoxWhiskersAnimation::BoxWhiskersAnimation(BoxPlotChartItem *item)
    : ChartAnimation(item),
      m_item(item)
{
    setDuration(ChartAnimationDuration);
    setEasingCurve(QEasingCurve::OutQuart);
}

BoxWhiskersAnimation::BoxWhiskersAnimation(BoxWhiskers *box)
    : ChartAnimation(box),
      m_box(box)
{
    setDuration(ChartAnimationDuration);
    setEasingCurve(QEasingCurve::OutQuart);
}

BoxWhiskersAnimation::~BoxWhiskersAnimation()
{
}

QVariant BoxWhiskersAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    BoxWhiskersData startData = qvariant_cast<BoxWhiskersData>(from);
    BoxWhiskersData endData = qvariant_cast<BoxWhiskersData>(to);
    BoxWhiskersData result;

    if (endData.m_index == 1) {
        //qDebug() << "endData.m_lowerExtreme = " << endData.m_lowerExtreme;
        //qDebug() << "endData.m_median = " << endData.m_median;
    }

    result.m_lowerExtreme = endData.m_median + progress * (endData.m_lowerExtreme - endData.m_median);
    result.m_lowerQuartile = endData.m_median + progress * (endData.m_lowerQuartile - endData.m_median);
    result.m_median = endData.m_median;
    result.m_upperQuartile = endData.m_median + progress * (endData.m_upperQuartile - endData.m_median);
    result.m_upperExtreme = endData.m_median + progress * (endData.m_upperExtreme - endData.m_median);
    result.m_index = endData.m_index;
    result.m_boxItems = endData.m_boxItems;

//    result.m_lowerExtreme = endData.m_lowerExtreme;
//    result.m_lowerQuartile = endData.m_lowerQuartile;
//    result.m_median = endData.m_median;
//    result.m_upperQuartile = endData.m_upperQuartile;
//    result.m_upperExtreme = endData.m_upperExtreme;
//    result.m_index = endData.m_index;
//    result.m_boxItems = endData.m_boxItems;

    result.m_maxX = endData.m_maxX;
    result.m_minX = endData.m_minX;
    result.m_maxY = endData.m_maxY;
    result.m_minY = endData.m_minY;
    //result.m_domainSize = endData.m_domainSize;

    return qVariantFromValue(result);
}

void BoxWhiskersAnimation::updateCurrentValue(const QVariant &value)
{
    BoxWhiskersData data = qvariant_cast<BoxWhiskersData>(value);
    m_box->setLayout(data);
}

void BoxWhiskersAnimation::setup(const BoxWhiskersData &startData, const BoxWhiskersData &endData)
{
    if (endData.m_index == 0) {
        qDebug() << "BoxPlotAnimation::setup m_upperExtreme" << endData.m_upperExtreme;
    }
    setKeyValueAt(0.0, qVariantFromValue(startData));
    setKeyValueAt(1.0, qVariantFromValue(endData));
}

#include "moc_boxwhiskersanimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

