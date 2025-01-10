// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "piewidget.h"

#include <QChart>
#include <QPieSeries>
#include <QPieSlice>

PieWidget::PieWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto series = new QPieSeries;
    series->append("Jane", 1);
    series->append("Joe", 2);
    series->append("Andy", 3);
    series->append("Barbara", 4);
    series->append("Axel", 5);
    //![1]

    //![2]
    QPieSlice *slice = series->slices().at(1);
    slice->setExploded();
    slice->setLabelVisible();
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);
    //![2]

    //![3]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Simple Pie Chart");
    chart->legend()->hide();
    //![3]

    //![4]
    createDefaultChartView(chart);
    //![4]
}
