// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "interactionschart.h"

#include <QLineSeries>
#include <QtMath>
#include <QValueAxis>

InteractionsChart::InteractionsChart(QGraphicsItem *parent, Qt::WindowFlags wFlags, QLineSeries *series)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags), m_series(series)
{
}

void InteractionsChart::clickPoint(const QPointF &point)
{
    // Find the closest data point
    m_movingPoint = QPoint();
    m_clicked = false;
    const auto points = m_series->points();
    for (QPointF p : points) {
        if (distance(p, point) < distance(m_movingPoint, point)) {
            m_movingPoint = p;
            m_clicked = true;
        }
    }
}

qreal InteractionsChart::distance(const QPointF &p1, const QPointF &p2)
{
    return qSqrt((p1.x() - p2.x()) * (p1.x() - p2.x())
                 + (p1.y() - p2.y()) * (p1.y() - p2.y()));
}

void InteractionsChart::setPointClicked(bool clicked)
{
    m_clicked = clicked;
}

void InteractionsChart::handlePointMove(const QPoint &point)
{
    if (m_clicked) {
        // Map the point clicked from the ChartView to the area occupied by the chart
        QPoint mappedPoint = point;
        mappedPoint.setX(point.x() - this->plotArea().x());
        mappedPoint.setY(point.y() - this->plotArea().y());

        // Get the x and y axis to be able to convert the mapped coordinate point to the chart scale
        QAbstractAxis *axisx = axes(Qt::Horizontal).first();
        QValueAxis *haxis = nullptr;
        if (axisx->type() == QAbstractAxis::AxisTypeValue)
            haxis = qobject_cast<QValueAxis *>(axisx);

        QAbstractAxis *axisy = axes(Qt::Vertical).first();
        QValueAxis *vaxis = nullptr;
        if (axisy->type() == QAbstractAxis::AxisTypeValue)
            vaxis = qobject_cast<QValueAxis *>(axisy);

        if (haxis && vaxis) {
            // Calculate the "unit" between points on the x y axis
            double xUnit = this->plotArea().width() / haxis->max();
            double yUnit = this->plotArea().height() / vaxis->max();

            // Convert the mappedPoint to the actual chart scale
            double x = mappedPoint.x() / xUnit;
            double y = vaxis->max() - mappedPoint.y() / yUnit;

            // Replace the old point with the new one
            m_series->replace(m_movingPoint, QPointF(x, y));

            // Update the m_movingPoint so we are able to do the replace also during mousemoveEvent
            m_movingPoint.setX(x);
            m_movingPoint.setY(y);
        }
    }
}

