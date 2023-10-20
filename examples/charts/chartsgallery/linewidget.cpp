// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "linewidget.h"

#include <QChart>
#include <QLineSeries>

LineWidget::LineWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto series = new QLineSeries;
    //![1]

    //![2]
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    //![2]

    //![3]
    auto chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple Line Chart");
    //![3]

    //![4]
    createDefaultChartView(chart);
    //![4]
}
