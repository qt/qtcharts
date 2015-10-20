/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
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

#ifndef PIEANIMATION_P_H
#define PIEANIMATION_P_H

#include <private/chartanimation_p.h>
#include <private/piechartitem_p.h>
#include <private/piesliceanimation_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class PieChartItem;

class PieAnimation : public ChartAnimation
{
    Q_OBJECT

public:
    PieAnimation(PieChartItem *item, int duration, QEasingCurve &curve);
    ~PieAnimation();
    ChartAnimation *updateValue(PieSliceItem *sliceItem, const PieSliceData &newValue);
    ChartAnimation *addSlice(PieSliceItem *sliceItem, const PieSliceData &endValue, bool startupAnimation);
    ChartAnimation *removeSlice(PieSliceItem *sliceItem);

public: // from QVariantAnimation
    void updateCurrentValue(const QVariant &value);

private:
    PieChartItem *m_item;
    QHash<PieSliceItem *, PieSliceAnimation *> m_animations;
    int m_animationDuration;
    QEasingCurve m_animationCurve;
};

QT_CHARTS_END_NAMESPACE

#endif
