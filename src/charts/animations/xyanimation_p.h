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

#ifndef XYANIMATION_P_H
#define XYANIMATION_P_H

#include <private/chartanimation_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QPointF>

QT_BEGIN_NAMESPACE

class XYChart;

class Q_CHARTS_EXPORT XYAnimation : public ChartAnimation
{
protected:
    enum Animation { AddPointAnimation, RemovePointAnimation, ReplacePointAnimation, NewAnimation };
public:
    XYAnimation(XYChart *item, int duration, QEasingCurve &curve);
    ~XYAnimation();
    void setup(const QList<QPointF> &oldPoints, const QList<QPointF> &newPoints, int index = -1);
    Animation animationType() const { return m_type; };

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const override;
    void updateCurrentValue(const QVariant &value) override;
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) override;
    XYChart *chartItem() { return m_item; }
protected:
    Animation m_type;
    bool m_dirty;
    int m_index;
private:
    XYChart *m_item;
    QList<QPointF> m_oldPoints;
    QList<QPointF> m_newPoints;
};

QT_END_NAMESPACE

#endif
