// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/scatteranimation_p.h>
#include <private/scatterchartitem_p.h>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

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

QT_END_NAMESPACE
