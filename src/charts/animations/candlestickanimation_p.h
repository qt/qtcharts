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

#ifndef CANDLESTICKANIMATION_P_H
#define CANDLESTICKANIMATION_P_H

#include <private/chartanimation_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/qobject.h>
#include <QtCore/qhash.h>

QT_BEGIN_NAMESPACE

class Candlestick;
class CandlestickChartItem;
class CandlestickBodyWicksAnimation;

class Q_CHARTS_EXPORT CandlestickAnimation : public QObject
{
    Q_OBJECT

public:
    CandlestickAnimation(CandlestickChartItem *item, int duration, QEasingCurve &curve);
    ~CandlestickAnimation();

    void addCandlestick(Candlestick *candlestick);
    ChartAnimation *candlestickAnimation(Candlestick *candlestick);
    ChartAnimation *candlestickChangeAnimation(Candlestick *candlestick);

    void setAnimationStart(Candlestick *candlestick);
    void stopAll();
    void removeCandlestickAnimation(Candlestick *candlestick);

protected:
    QHash<Candlestick *, CandlestickBodyWicksAnimation *> m_animations;
    CandlestickChartItem *m_item;
    int m_animationDuration;
    QEasingCurve m_animationCurve;
};

QT_END_NAMESPACE

#endif // CANDLESTICKANIMATION_P_H
