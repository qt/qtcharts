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

#include "scatteranimation_p.h"
#include "scatterchartitem_p.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

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

QTCOMMERCIALCHART_END_NAMESPACE
