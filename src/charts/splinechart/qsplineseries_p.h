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

#ifndef QSPLINESERIES_P_H
#define QSPLINESERIES_P_H

#include <private/qlineseries_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE


class Q_CHARTS_EXPORT QSplineSeriesPrivate: public QLineSeriesPrivate
{
    Q_OBJECT
public:
    QSplineSeriesPrivate(QSplineSeries *q);

    void initializeTheme(int index, ChartTheme* theme, bool forced = false) override;
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeAnimations(QChart::AnimationOptions options, int duration,
                              QEasingCurve &curve) override;

private:
    Q_DECLARE_PUBLIC(QSplineSeries)
};

QT_END_NAMESPACE

#endif
