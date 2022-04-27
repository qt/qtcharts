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

#ifndef SPLINEANIMATION_P_H
#define SPLINEANIMATION_P_H

#include <private/xyanimation_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QPointF>

typedef QPair<QList<QPointF>, QList<QPointF>> SplineVector;

QT_BEGIN_NAMESPACE

class SplineChartItem;

class Q_CHARTS_PRIVATE_EXPORT SplineAnimation : public XYAnimation
{
public:
    SplineAnimation(SplineChartItem *item, int duration, QEasingCurve &curve);
    ~SplineAnimation();
    void setup(const QList<QPointF> &oldPoints, const QList<QPointF> &newPoints,
               const QList<QPointF> &oldContorlPoints, const QList<QPointF> &newControlPoints,
               int index = -1);

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const override;
    void updateCurrentValue(const QVariant &value) override;
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) override;

private:
    SplineVector m_oldSpline;
    SplineVector m_newSpline;
    SplineChartItem *m_item;
    bool m_valid;
};

QT_END_NAMESPACE

#endif
