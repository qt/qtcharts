/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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

#include "chartanimator_p.h"
#include "axisanimation_p.h"
#include "xyanimation_p.h"
#include "splineanimation_p.h"
#include "xychart_p.h"
#include "pieanimation_p.h"
#include "baranimation_p.h"
#include "barchartitem_p.h"
#include "stackedbaranimation_p.h"
#include "stackedbarchartitem_p.h"
#include "percentbaranimation_p.h"
#include "percentbarchartitem_p.h"
#include "areachartitem_p.h"
#include "splinechartitem_p.h"
#include "scatterchartitem_p.h"
#include "chartaxis_p.h"
#include <QTimer>

Q_DECLARE_METATYPE(QVector<QPointF>)
Q_DECLARE_METATYPE(QVector<qreal>)
Q_DECLARE_METATYPE(QVector<QRectF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartAnimator::ChartAnimator(QObject *parent):QObject(parent)
{
}

ChartAnimator::~ChartAnimator()
{
}
void ChartAnimator::addAnimation(PieChartItem *item)
{
    ChartAnimation *animation = m_animations.value(item);

    if (!animation) {
        animation = new PieAnimation(item);
        m_animations.insert(item, animation);
    }

    item->setAnimator(this);
}

void ChartAnimator::removeAnimation(Chart *item)
{
    item->setAnimator(0);
    m_animations.remove(item);
}

void ChartAnimator::addAnimation(PieChartItem *item, PieSliceItem *sliceItem, const PieSliceData &sliceData, bool startupAnimation)
{
    PieAnimation *animation = static_cast<PieAnimation *>(m_animations.value(item));
    Q_ASSERT(animation);
    animation->addSlice(sliceItem, sliceData, startupAnimation);
}

void ChartAnimator::removeAnimation(PieChartItem *item, PieSliceItem *sliceItem)
{
    PieAnimation *animation = static_cast<PieAnimation *>(m_animations.value(item));
    Q_ASSERT(animation);
    animation->removeSlice(sliceItem);
}

void ChartAnimator::updateAnimation(PieChartItem *item, PieSliceItem *sliceItem, const PieSliceData &sliceData)
{
    PieAnimation *animation = static_cast<PieAnimation *>(m_animations.value(item));
    Q_ASSERT(animation);
    animation->updateValue(sliceItem, sliceData);
}

#include "moc_chartanimator_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
