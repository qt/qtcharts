// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef SPLINECHARTITEM_P_H
#define SPLINECHARTITEM_P_H

#include <QtCharts/QSplineSeries>
#include <private/xychart_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class SplineAnimation;

class Q_CHARTS_EXPORT SplineChartItem : public XYChart
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    SplineChartItem(QSplineSeries *series, QGraphicsItem *item = 0);

    //from QGraphicsItem
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;

    void setControlGeometryPoints(const QList<QPointF> &points);
    QList<QPointF> controlGeometryPoints() const;

    void setAnimation(SplineAnimation *animation);
    ChartAnimation *animation() const override;

public Q_SLOTS:
    void handleSeriesUpdated() override;

protected:
    void updateGeometry() override;
    QList<QPointF> calculateControlPoints(const QList<QPointF> &points);
    QList<qreal> firstControlPoints(const QList<qreal> &list);
    void updateChart(const QList<QPointF> &oldPoints, const QList<QPointF> &newPoints, int index) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QSplineSeries *m_series;
    QPainterPath m_path;
    QPainterPath m_pathPolarRight;
    QPainterPath m_pathPolarLeft;
    QPainterPath m_fullPath;
    QRectF m_rect;
    QPen m_linePen;
    QPen m_pointPen;
    bool m_pointsVisible;
    QList<QPointF> m_controlPoints;
    QList<QPointF> m_visiblePoints;
    SplineAnimation *m_animation;

    bool m_pointLabelsVisible;
    qreal m_markerSize;
    QString m_pointLabelsFormat;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
    bool m_pointLabelsClipping;

    QPointF m_lastMousePos;
    QPointF m_lastHoveredMatchedPos;
    bool m_mousePressed;

    friend class SplineAnimation;
};

QT_END_NAMESPACE

#endif // SPLINECHARTITEM_P_H
