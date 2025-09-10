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

#ifndef BARANIMATION_P_H
#define BARANIMATION_P_H

#include <private/chartanimation_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class AbstractBarChartItem;

class Q_CHARTS_EXPORT BarAnimation : public ChartAnimation
{
    Q_OBJECT

public:
    BarAnimation(AbstractBarChartItem *item, int duration, QEasingCurve &curve);
    ~BarAnimation();

public: // from QVariantAnimation
    QVariant interpolated(const QVariant &from, const QVariant &to, qreal progress) const override;
    void updateCurrentValue(const QVariant &value) override;

    void setup(const QList<QRectF> &oldLayout, const QList<QRectF> &newLayout);

protected:
    AbstractBarChartItem *m_item;
};

QT_END_NAMESPACE

#endif // BARANIMATION_P_H
