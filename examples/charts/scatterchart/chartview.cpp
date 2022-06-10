// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "chartview.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>

ChartView::ChartView(QWidget *parent) :
    QChartView(new QChart(), parent)
{
    //![1]
    QScatterSeries *series0 = new QScatterSeries();
    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(15.0);

    QScatterSeries *series1 = new QScatterSeries();
    series1->setName("scatter2");
    series1->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series1->setMarkerSize(20.0);

    QScatterSeries *series2 = new QScatterSeries();
    series2->setName("scatter3");
    series2->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series2->setMarkerSize(30.0);
    //![1]

    //![2]
    series0->append(0, 6);
    series0->append(2, 4);
    series0->append(3, 8);
    series0->append(7, 4);
    series0->append(10, 5);

    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10, 2);
    *series2 << QPointF(1, 5) << QPointF(4, 6) << QPointF(6, 3) << QPointF(9, 5);
    //![2]

    //![3]
    QPainterPath starPath;
    starPath.moveTo(28, 15);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(14 + 14 * qCos(0.8 * i * M_PI),
                        15 + 14 * qSin(0.8 * i * M_PI));
    }
    starPath.closeSubpath();

    QImage star(30, 30, QImage::Format_ARGB32);
    star.fill(Qt::transparent);

    QPainter painter(&star);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QRgb(0xf6a625));
    painter.setBrush(painter.pen().color());
    painter.drawPath(starPath);

    series2->setBrush(star);
    series2->setPen(QColor(Qt::transparent));
    //![3]

    //![4]
    setRenderHint(QPainter::Antialiasing);
    chart()->addSeries(series0);
    chart()->addSeries(series1);
    chart()->addSeries(series2);

    chart()->setTitle("Simple scatterchart example");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);
    //![4]

    //![5]
    chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    //![5]
}
