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

#include "pieanimation_p.h"
#include "piesliceanimation_p.h"
#include "piechartitem_p.h"
#include <QParallelAnimationGroup>
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PieAnimation::PieAnimation(PieChartItem *item)
    :ChartAnimation(item),
    m_item(item)
{
}

PieAnimation::~PieAnimation()
{
}

void PieAnimation::updateValues(const PieLayout &newValues)
{
    foreach (QPieSlice *s, newValues.keys())
        updateValue(s, newValues.value(s));
}

void PieAnimation::updateValue(QPieSlice *slice, const PieSliceData &sliceData)
{
    PieSliceAnimation *animation = m_animations.value(slice);
    Q_ASSERT(animation);
    animation->stop();

    animation->updateValue(sliceData);
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutQuart);

    QTimer::singleShot(0, animation, SLOT(start()));
}

void PieAnimation::addSlice(QPieSlice *slice, const PieSliceData &sliceData, bool isEmpty)
{
    PieSliceAnimation *animation = new PieSliceAnimation(m_item, slice);
    m_animations.insert(slice, animation);

    PieSliceData startValue = sliceData;
    startValue.m_radius = 0;
    if (isEmpty)
        startValue.m_startAngle = 0;
    else
        startValue.m_startAngle = sliceData.m_startAngle + (sliceData.m_angleSpan / 2);
    startValue.m_angleSpan = 0;
    animation->setValue(startValue, sliceData);

    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutQuart);
    QTimer::singleShot(0, animation, SLOT(start()));
}

void PieAnimation::removeSlice(QPieSlice *slice)
{
    PieSliceAnimation *animation = m_animations.value(slice);
    Q_ASSERT(animation);
    animation->stop();

    PieSliceData endValue = animation->currentSliceValue();
    endValue.m_radius = 0;
    // TODO: find the actual angle where this slice disappears
    endValue.m_startAngle = endValue.m_startAngle + endValue.m_angleSpan;
    endValue.m_angleSpan = 0;

    animation->updateValue(endValue);
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutQuart);

    connect(animation, SIGNAL(finished()), this, SLOT(destroySliceAnimationComplete()));
    QTimer::singleShot(0, animation, SLOT(start()));
}

void PieAnimation::updateCurrentValue(const QVariant &)
{
    // nothing to do...
}

void PieAnimation::destroySliceAnimationComplete()
{
    PieSliceAnimation *animation = static_cast<PieSliceAnimation *>(sender());
    QPieSlice *slice = m_animations.key(animation);
    m_item->destroySlice(slice);
    delete m_animations.take(slice);
}

#include "moc_pieanimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
