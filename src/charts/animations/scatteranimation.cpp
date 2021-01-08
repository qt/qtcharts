/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include <private/scatteranimation_p.h>
#include <private/scatterchartitem_p.h>
#include <QtCore/QDebug>

QT_CHARTS_BEGIN_NAMESPACE

ScatterAnimation::ScatterAnimation(ScatterChartItem *item, int duration, QEasingCurve &curve)
    : XYAnimation(item, duration, curve)
{
}

ScatterAnimation::~ScatterAnimation()
{
}

void ScatterAnimation::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    XYAnimation::updateState(newState, oldState);

    if (oldState == QAbstractAnimation::Running && newState == QAbstractAnimation::Stopped
        && animationType() == RemovePointAnimation) {
        // Removing a point from scatter chart will keep extra marker item after animation stops.
        // Also, if the removed point was not the last one in series, points after the removed one
        // will report wrong coordinates when clicked. To fix these issues, update geometry after
        // point removal animation has finished.
        chartItem()->updateGeometry();
    }
}

QT_CHARTS_END_NAMESPACE
