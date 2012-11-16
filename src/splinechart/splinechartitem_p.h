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

#ifndef SPLINECHARTITEM_P_H
#define SPLINECHARTITEM_P_H

#include "qsplineseries.h"
#include "xychart_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplineAnimation;

class SplineChartItem : public XYChart
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    SplineChartItem(QSplineSeries *series, QGraphicsItem* item = 0);

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    void setControlGeometryPoints(QVector<QPointF>& points);
    QVector<QPointF> controlGeometryPoints() const;

    void setAnimation(SplineAnimation *animation);
    ChartAnimation *animation() const;

public Q_SLOTS:
    void handleUpdated();

protected:
    void updateGeometry();
    void updateChart(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, int index);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    QPointF calculateGeometryControlPoint(int index) const;

private:
    QSplineSeries *m_series;
    QPainterPath m_path;
    QRectF m_rect;
    QPen m_linePen;
    QPen m_pointPen;
    bool m_pointsVisible;
    QVector<QPointF> m_controlPoints;
    SplineAnimation *m_animation;

    friend class SplineAnimation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SPLINECHARTITEM_P_H
