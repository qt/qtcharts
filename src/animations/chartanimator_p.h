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

class ChartAnimator : public QObject
{
    Q_OBJECT
public:
    enum State{ShowState, ScrollUpState, ScrollDownState, ScrollLeftState, ScrollRightState, ZoomInState, ZoomOutState};

    ChartAnimator(QObject *parent = 0);
    virtual ~ChartAnimator();

    void addAnimation(ChartAxis *item);
    void addAnimation(PieChartItem *item);
    void addAnimation(ScatterChartItem *item);
    void addAnimation(LineChartItem *item);
    void addAnimation(SplineChartItem *item);
    void addAnimation(BarChartItem *item);
    void removeAnimation(Chart *item);

    void animationStarted();
    void updateLayout(XYChartItem *item, QVector<QPointF> &oldLayout, QVector<QPointF> &newLayout, int index);
    void updateLayout(SplineChartItem *item, QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, QVector<QPointF> &oldControlPoints, QVector<QPointF> &newContorlPoints, int index);
    void updateLayout(ChartAxis *item, QVector<qreal> &layout);

    void addAnimation(PieChartItem *item, PieSliceItem *sliceItem, const PieSliceData &sliceData, bool isEmpty);
    void removeAnimation(PieChartItem *item, PieSliceItem *sliceItem);
    void updateLayout(PieChartItem *item, const PieLayout &layout);
    void updateLayout(PieChartItem *item, PieSliceItem *sliceItem, const PieSliceData &sliceData);

    void updateLayout(BarChartItem *item, const QVector<QRectF> &oldLayout, const QVector<QRectF> &newLayout);

    void setState(State state,const QPointF &point = QPointF());

private:
     QMap<Chart *, ChartAnimation *> m_animations;
     State m_state;
     QPointF m_point;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
