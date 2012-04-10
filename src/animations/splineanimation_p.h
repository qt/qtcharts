/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef SPLINEANIMATION_P_H
#define SPLINEANIMATION_P_H
#include "chartanimation_p.h"
#include <QPointF>

typedef  QPair<QVector<QPointF >, QVector<QPointF > >  SplineVector;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplineChartItem;

class SplineAnimation : public ChartAnimation
{
public:

    SplineAnimation(SplineChartItem *item);
    ~SplineAnimation();
    void setValues(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, QVector<QPointF> &oldContorlPoints, QVector<QPointF> &newControlPoints, int index);

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const;
    void updateCurrentValue(const QVariant &value);

private:
    SplineVector m_oldSpline;
    SplineChartItem *m_item;
    bool m_dirty;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
