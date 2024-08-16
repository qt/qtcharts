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

#ifndef LINECHARTITEM_H
#define LINECHARTITEM_H

#include <QtCharts/QChartGlobal>
#include <private/xychart_p.h>
#include <QtCharts/QChart>
#include <QtGui/QPen>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QLineSeries;
class ChartPresenter;

class Q_CHARTS_EXPORT LineChartItem :  public XYChart
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit LineChartItem(QLineSeries *series, QGraphicsItem *item = 0);
    ~LineChartItem() {}

    //from QGraphicsItem
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;

    QPainterPath path() const { return m_fullPath; }

public Q_SLOTS:
    void handleSeriesUpdated() override;

protected:
    void updateGeometry() override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void suppressPoints() { m_pointsVisible = false; }
    void forceChartType(QChart::ChartType chartType) { m_chartType = chartType; }

private:
    QLineSeries *m_series;
    QPainterPath m_linePath;
    QPainterPath m_linePathPolarRight;
    QPainterPath m_linePathPolarLeft;
    QPainterPath m_fullPath;
    QPainterPath m_shapePath;

    QList<QPointF> m_linePoints;
    QRectF m_rect;
    QPen m_linePen;
    bool m_pointsVisible;
    QChart::ChartType m_chartType;

    bool m_pointLabelsVisible;
    qreal m_markerSize;
    QString m_pointLabelsFormat;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
    bool m_pointLabelsClipping;

    QPointF m_lastMousePos;
    QPointF m_lastHoveredMatchedPos;
    bool m_mousePressed;
};

QT_END_NAMESPACE

#endif
