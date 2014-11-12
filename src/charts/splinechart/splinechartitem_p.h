/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef SPLINECHARTITEM_P_H
#define SPLINECHARTITEM_P_H

#include <QtCharts/QSplineSeries>
#include <private/xychart_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class SplineAnimation;

class SplineChartItem : public XYChart
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    SplineChartItem(QSplineSeries *series, QGraphicsItem *item = 0);

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
    QVector<QPointF> calculateControlPoints(const QVector<QPointF> &points);
    QVector<qreal> firstControlPoints(const QVector<qreal>& vector);
    void updateChart(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, int index);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

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
    QVector<QPointF> m_controlPoints;
    QVector<QPointF> m_visiblePoints;
    SplineAnimation *m_animation;

    bool m_pointLabelsVisible;
    QString m_pointLabelsFormat;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;

    QPointF m_lastMousePos;
    bool m_mousePressed;

    friend class SplineAnimation;
};

QT_CHARTS_END_NAMESPACE

#endif // SPLINECHARTITEM_P_H
