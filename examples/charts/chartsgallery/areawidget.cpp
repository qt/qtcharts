// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "areawidget.h"

#include <QAreaSeries>
#include <QChart>
#include <QLineSeries>

AreaWidget::AreaWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto series0 = new QLineSeries;
    auto series1 = new QLineSeries;
    //![1]

    //![2]
    *series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
             << QPointF(16, 7) << QPointF(18, 5);
    *series1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12, 3)
             << QPointF(16, 4) << QPointF(18, 3);
    //![2]

    //![3]
    auto series = new QAreaSeries(series0, series1);
    series->setName("Batman");
    QPen pen(0x059605);
    pen.setWidth(3);
    series->setPen(pen);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, 0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    series->setBrush(gradient);
    //![3]

    //![4]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Simple Area Chart");
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, 20);
    chart->axes(Qt::Vertical).first()->setRange(0, 10);
    //![4]

    //![5]
    createDefaultChartView(chart);
    //![5]
}
