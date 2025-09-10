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

#ifndef BOXPLOTANIMATION_P_H
#define BOXPLOTANIMATION_P_H

#include <private/chartanimation_p.h>
#include <private/boxwhiskers_p.h>
#include <private/boxwhiskersdata_p.h>
#include <private/boxwhiskersanimation_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/qhash.h>

QT_BEGIN_NAMESPACE

class BoxPlotChartItem;

class Q_CHARTS_EXPORT BoxPlotAnimation : public QObject
{
    Q_OBJECT
public:
    BoxPlotAnimation(BoxPlotChartItem *item, int duration, QEasingCurve &curve);
    ~BoxPlotAnimation();

    void addBox(BoxWhiskers *box);
    ChartAnimation *boxAnimation(BoxWhiskers *box);
    ChartAnimation *boxChangeAnimation(BoxWhiskers *box);

    void setAnimationStart(BoxWhiskers *box);
    void stopAll();
    void removeBoxAnimation(BoxWhiskers *box);

protected:
    BoxPlotChartItem *m_item;
    QHash<BoxWhiskers *, BoxWhiskersAnimation *> m_animations;
    int m_animationDuration;
    QEasingCurve m_animationCurve;
};

QT_END_NAMESPACE

#endif // BOXPLOTANIMATION_P_H
