// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "chartview.h"
#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_USE_NAMESPACE

ChartView::ChartView(QWidget *parent)
    : QChartView(new QChart(), parent),
      m_scatter(0),
      m_scatter2(0)
{
    setRenderHint(QPainter::Antialiasing);

    chart()->setTitle("Click to interact with scatter points");

    m_scatter = new QScatterSeries();
    m_scatter->setName("scatter1");
    for (qreal x(0.5); x <= 4.0; x += 0.5) {
        for (qreal y(0.5); y <= 4.0; y += 0.5)
            *m_scatter << QPointF(x, y);
    }
    m_scatter2 = new QScatterSeries();
    m_scatter2->setName("scatter2");

    chart()->addSeries(m_scatter2);
    chart()->addSeries(m_scatter);
    chart()->createDefaultAxes();
    chart()->axes(Qt::Horizontal).first()->setRange(0, 4.5);
    chart()->axes(Qt::Vertical).first()->setRange(0, 4.5);

    connect(m_scatter, &QScatterSeries::clicked, this, &ChartView::handleClickedPoint);
}

ChartView::~ChartView()
{
}

void ChartView::handleClickedPoint(const QPointF &point)
{
    QPointF clickedPoint = point;
    // Find the closest point from series 1
    QPointF closest(INT_MAX, INT_MAX);
    qreal distance(INT_MAX);
    const auto points = m_scatter->points();
    for (const QPointF &currentPoint : points) {
        qreal currentDistance = qSqrt((currentPoint.x() - clickedPoint.x())
                                      * (currentPoint.x() - clickedPoint.x())
                                      + (currentPoint.y() - clickedPoint.y())
                                      * (currentPoint.y() - clickedPoint.y()));
        if (currentDistance < distance) {
            distance = currentDistance;
            closest = currentPoint;
        }
    }

    // Remove the closes point from series 1 and append it to series 2
    m_scatter->remove(closest);
    m_scatter2->append(closest);
}
