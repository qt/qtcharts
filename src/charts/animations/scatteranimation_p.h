// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef SCATTERANIMATION_P_H
#define SCATTERANIMATION_P_H

#include <private/xyanimation_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class ScatterChartItem;

class Q_CHARTS_EXPORT ScatterAnimation : public XYAnimation
{
public:
    ScatterAnimation(ScatterChartItem *item, int duration, QEasingCurve &curve);
    ~ScatterAnimation();

protected:

    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) override;
};

QT_END_NAMESPACE

#endif
