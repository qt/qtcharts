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

#ifndef CHARTANIMATION_H
#define CHARTANIMATION_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QVariantAnimation>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

const static int ChartAnimationDuration = 1000;

class Q_CHARTS_EXPORT ChartAnimation: public QVariantAnimation
{
    Q_OBJECT
public:
    ChartAnimation(QObject *parent = 0);

    void stopAndDestroyLater();

public Q_SLOTS:
    void startChartAnimation();

protected:
    bool m_destructing;
};

QT_END_NAMESPACE

#endif /* CHARTANIMATION_H */
