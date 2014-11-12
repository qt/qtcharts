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

#include <private/scatteranimation_p.h>
#include <private/scatterchartitem_p.h>
#include <QtCore/QDebug>

QT_CHARTS_BEGIN_NAMESPACE

ScatterAnimation::ScatterAnimation(ScatterChartItem *item)
    : XYAnimation(item)
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
