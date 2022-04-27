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

#ifndef CANDLESTICKBODYWICKSANIMATION_P_H
#define CANDLESTICKBODYWICKSANIMATION_P_H

#include <private/candlestickdata_p.h>
#include <private/chartanimation_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Candlestick;
class CandlestickAnimation;

class Q_CHARTS_PRIVATE_EXPORT CandlestickBodyWicksAnimation : public ChartAnimation
{
    Q_OBJECT

public:
    CandlestickBodyWicksAnimation(Candlestick *candlestick, CandlestickAnimation *animation,
                                  int duration, QEasingCurve &curve);
    ~CandlestickBodyWicksAnimation();

    void setup(const CandlestickData &startData, const CandlestickData &endData);
    void setStartData(const CandlestickData &startData);
    void setEndData(const CandlestickData &endData);

    // from QVariantAnimation
    void updateCurrentValue(const QVariant &value) override;
    QVariant interpolated(const QVariant &from, const QVariant &to, qreal progress) const override;

protected:
    Candlestick *m_candlestick;
    CandlestickAnimation *m_candlestickAnimation;
    bool m_changeAnimation;

    friend class CandlestickAnimation;
};

QT_END_NAMESPACE

#endif // CANDLESTICKBODYWICKSANIMATION_P_H
