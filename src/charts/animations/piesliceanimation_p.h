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

#ifndef PIESLICEANIMATION_P_H
#define PIESLICEANIMATION_P_H

#include <private/chartanimation_p.h>
#include <private/piesliceitem_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class PieChartItem;

class Q_CHARTS_EXPORT PieSliceAnimation : public ChartAnimation
{
public:
    PieSliceAnimation(PieSliceItem *sliceItem);
    ~PieSliceAnimation();
    void setValue(const PieSliceData &startValue, const PieSliceData &endValue);
    void updateValue(const PieSliceData &endValue);
    PieSliceData currentSliceValue();

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const override;
    void updateCurrentValue(const QVariant &value) override;

private:
    PieSliceItem *m_sliceItem;
    PieSliceData m_currentValue;
};

QT_END_NAMESPACE

#endif
