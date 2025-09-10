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

#ifndef AREACHARTITEM_H
#define AREACHARTITEM_H

#include <QtCharts/QChartGlobal>
#include <private/linechartitem_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCharts/QAreaSeries>
#include <QtGui/QPen>

QT_BEGIN_NAMESPACE

class AreaChartItem;

class Q_CHARTS_EXPORT AreaChartItem : public ChartItem
{
    Q_OBJECT
public:
    AreaChartItem(QAreaSeries *areaSeries, QGraphicsItem* item = 0);
    ~AreaChartItem();

    //from QGraphicsItem
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;

    LineChartItem *upperLineItem() const { return m_upper; }
    LineChartItem *lowerLineItem() const { return m_lower; }

    void updatePath();

    void setPresenter(ChartPresenter *presenter) override;
    QAreaSeries *series() const { return m_series; }

    void setUpperSeries(QLineSeries *series);
    void setLowerSeries(QLineSeries *series);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

Q_SIGNALS:
    void clicked(const QPointF &point);
    void hovered(const QPointF &point, bool state);
    void pressed(const QPointF &point);
    void released(const QPointF &point);
    void doubleClicked(const QPointF &point);

public Q_SLOTS:
    void handleUpdated();
    void handleDomainUpdated() override;

private:
    void fixEdgeSeriesDomain(LineChartItem *edgeSeries);

    QAreaSeries *m_series;
    LineChartItem *m_upper;
    LineChartItem *m_lower;
    QPainterPath m_path;
    QRectF m_rect;
    QPen m_linePen;
    QPen m_pointPen;
    QBrush m_brush;
    bool m_pointsVisible;

    bool m_pointLabelsVisible;
    QString m_pointLabelsFormat;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
    bool m_pointLabelsClipping;

    QPointF m_lastMousePos;
    bool m_mousePressed;

};

class Q_CHARTS_EXPORT AreaBoundItem : public LineChartItem
{
public:
    AreaBoundItem(AreaChartItem *area, QLineSeries *lineSeries,QGraphicsItem* item = 0)
        : LineChartItem(lineSeries, item), m_item(area)
    {
        // We do not actually want to draw anything from LineChartItem.
        // Drawing is done in AreaChartItem only.
        setVisible(false);
    }
    ~AreaBoundItem() {}

    void updateGeometry() override
    {
        // Make sure the series is in a chart before trying to update
        if (m_item->series()->chart()) {
            // Turn off points drawing from component line chart item, as that
            // messes up the fill for area series.
            suppressPoints();
            // Component lineseries are not necessarily themselves on the chart,
            // so get the chart type for them from area chart.
            forceChartType(m_item->series()->chart()->chartType());
            LineChartItem::updateGeometry();
            m_item->updatePath();
        }
    }

private:
    AreaChartItem *m_item;
};

QT_END_NAMESPACE

#endif
