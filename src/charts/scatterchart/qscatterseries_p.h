// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QSCATTERSERIES_P_H
#define QSCATTERSERIES_P_H

#include <private/qxyseries_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT QScatterSeriesPrivate: public QXYSeriesPrivate
{
public:
    QScatterSeriesPrivate(QScatterSeries *q);
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeTheme(int index, ChartTheme* theme, bool forced = false) override;
    void initializeAnimations(QChart::AnimationOptions options, int duration,
                              QEasingCurve &curve) override;

private:
    QScatterSeries::MarkerShape m_shape;
    Q_DECLARE_PUBLIC(QScatterSeries)
};

QT_END_NAMESPACE

#endif
