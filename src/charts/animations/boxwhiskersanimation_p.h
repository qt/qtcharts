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

#ifndef BOXWHISKERSANIMATION_P_H
#define BOXWHISKERSANIMATION_P_H

#include <private/chartanimation_p.h>
#include <private/boxwhiskers_p.h>
#include <private/boxwhiskersdata_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class BoxPlotChartItem;
class BoxPlotAnimation;

class Q_CHARTS_PRIVATE_EXPORT BoxWhiskersAnimation : public ChartAnimation
{
    Q_OBJECT

public:
    BoxWhiskersAnimation(BoxWhiskers *box, BoxPlotAnimation *boxPlotAnimation, int duration,
                         QEasingCurve &curve);
    ~BoxWhiskersAnimation();

public: // from QVariantAnimation
    QVariant interpolated(const QVariant &from, const QVariant &to, qreal progress) const override;
    void updateCurrentValue(const QVariant &value) override;

    void setup(const BoxWhiskersData &startData, const BoxWhiskersData &endData);
    void setEndData(const BoxWhiskersData &endData);
    void setStartData(const BoxWhiskersData &endData);

    void moveMedianLine(bool move);

protected:
    friend class BoxPlotAnimation;
    BoxWhiskers *m_box;
    bool m_changeAnimation;
    BoxPlotAnimation *m_boxPlotAnimation;
};

QT_END_NAMESPACE

#endif // BOXWHISKERSANIMATION_P_H
