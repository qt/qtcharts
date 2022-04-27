/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

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

QT_BEGIN_NAMESPACE

class Candlestick;
class CandlestickChartItem;
class CandlestickBodyWicksAnimation;

class Q_CHARTS_PRIVATE_EXPORT CandlestickAnimation : public QObject
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
