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
#include "areachartitem_p.h"
#include "splinechartitem_p.h"
#include "scatterchartitem_p.h"
#include <QTimer>

Q_DECLARE_METATYPE(QVector<QPointF>)
Q_DECLARE_METATYPE(QVector<qreal>)
Q_DECLARE_METATYPE(QVector<QRectF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartAnimator::ChartAnimator(QObject *parent):QObject(parent),
    m_state(ShowState)
{
}

ChartAnimator::~ChartAnimator()
{
}

void ChartAnimator::addAnimation(ChartAxis *item)
{
    ChartAnimation *animation = m_animations.value(item);

    if (!animation) {
        animation = new AxisAnimation(item);
        m_animations.insert(item, animation);
    }

    item->setAnimator(this);
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

void ChartAnimator::addAnimation(BarChartItem *item)
{
    ChartAnimation *animation = m_animations.value(item);

    if (!animation) {
        animation = new BarAnimation(item);
        m_animations.insert(item, animation);
    }

    item->setAnimator(this);
}


void ChartAnimator::removeAnimation(Chart *item)
{
    item->setAnimator(0);
    m_animations.remove(item);
}

void ChartAnimator::updateLayout(ChartAxis *item , QVector<qreal> &newLayout)
{
    AxisAnimation *animation = static_cast<AxisAnimation*>(m_animations.value(item));

    Q_ASSERT(animation);

    QVector<qreal> oldLayout = item->layout();

    if (newLayout.count() == 0)
        return;

    switch (m_state) {
    case ZoomOutState: {
        QRectF rect = item->geometry();
        oldLayout.resize(newLayout.count());

        for(int i = 0, j = oldLayout.count() - 1; i < (oldLayout.count() + 1) / 2; ++i, --j) {
            oldLayout[i] = item->axisType() == ChartAxis::X_AXIS ? rect.left() : rect.bottom();
            oldLayout[j] = item->axisType() == ChartAxis::X_AXIS ? rect.right() : rect.top();
        }
    }
        break;
    case ZoomInState: {
        int index = qMin(oldLayout.count() * (item->axisType() == ChartAxis::X_AXIS ? m_point.x() : (1 - m_point.y())), newLayout.count() - 1.0);
        oldLayout.resize(newLayout.count());

        for(int i = 0; i < oldLayout.count(); i++)
            oldLayout[i]= oldLayout[index];
    }
        break;
    case ScrollDownState:
    case ScrollRightState: {
        oldLayout.resize(newLayout.count());

        for(int i = 0, j = i + 1; i < oldLayout.count() - 1; ++i, ++j)
            oldLayout[i]= oldLayout[j];
    }
        break;
    case ScrollUpState:
    case ScrollLeftState: {
        oldLayout.resize(newLayout.count());

        for(int i = oldLayout.count() - 1, j = i - 1; i > 0; --i, --j)
            oldLayout[i]= oldLayout[j];
    }
        break;
    default: {
        oldLayout.resize(newLayout.count());
        QRectF rect = item->geometry();
        for(int i = 0, j = oldLayout.count() - 1; i < oldLayout.count(); ++i, --j)
            oldLayout[i] = item->axisType() == ChartAxis::X_AXIS ? rect.left() : rect.top();
    }
        break;
    }


    if (animation->state() != QAbstractAnimation::Stopped)
        animation->stop();

    animation->setDuration(ChartAnimationDuration);
    animation->setEasingCurve(QEasingCurve::OutQuart);
    QVariantAnimation::KeyValues value;
    animation->setKeyValues(value); //workaround for wrong interpolation call
    animation->setKeyValueAt(0.0, qVariantFromValue(oldLayout));
    animation->setKeyValueAt(1.0, qVariantFromValue(newLayout));

    QTimer::singleShot(0, animation, SLOT(start()));
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

void ChartAnimator::updateLayout(BarChartItem *item, const QVector<QRectF> &oldLayout, const QVector<QRectF> &newLayout)
{
    BarAnimation *animation = static_cast<BarAnimation *>(m_animations.value(item));
    Q_ASSERT(animation);
    animation->setDuration(ChartAnimationDuration);
    animation->setKeyValueAt(0.0, qVariantFromValue(oldLayout));
    animation->setKeyValueAt(1.0, qVariantFromValue(newLayout));
    QTimer::singleShot(0, animation, SLOT(start()));
}


void ChartAnimator::setState(State state, const QPointF &point)
{
    m_state = state;
    m_point = point;
}

void ChartAnimator::startAnimation(XYAnimation* animation)
{
    Q_ASSERT(animation);
    if (animation->state() != QAbstractAnimation::Stopped)
    animation->stop();
    animation->setDuration(ChartAnimationDuration);
    animation->setEasingCurve(QEasingCurve::OutQuart);
    QTimer::singleShot(0, animation, SLOT(start()));
}

#include "moc_chartanimator_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
