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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTANIMATOR_P_H
#define CHARTANIMATOR_P_H

#include "qchartglobal.h"
#include "chartanimation_p.h"
#include "piechartitem_p.h"
#include "barchartitem_p.h"
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class ChartAxis;
class AreaChartItem;
class SplineChartItem;
class ScatterChartItem;
class LineChartItem;
class XYChartItem;
class XYAnimation;

class ChartAnimator : public QObject
{
    Q_OBJECT
public:
    ChartAnimator(QObject *parent = 0);
    virtual ~ChartAnimator();

    void addAnimation(PieChartItem *item);
    void addAnimation(BarChartItem *item);
    void addAnimation(StackedBarChartItem *item);
    void addAnimation(PercentBarChartItem *item);
    void removeAnimation(Chart *item);

    void addAnimation(PieChartItem *item, PieSliceItem *sliceItem, const PieSliceData &sliceData, bool isEmpty);
    void removeAnimation(PieChartItem *item, PieSliceItem *sliceItem);
    void updateAnimation(PieChartItem *item, PieSliceItem *sliceItem, const PieSliceData &sliceData);

    void updateLayout(BarChartItem *item, const QVector<QRectF> &oldLayout, const QVector<QRectF> &newLayout);
    void updateLayout(StackedBarChartItem *item, const QVector<QRectF> &oldLayout, const QVector<QRectF> &newLayout);
    void updateLayout(PercentBarChartItem *item, const QVector<QRectF> &oldLayout, const QVector<QRectF> &newLayout);

private:
     QMap<Chart *, ChartAnimation *> m_animations;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
