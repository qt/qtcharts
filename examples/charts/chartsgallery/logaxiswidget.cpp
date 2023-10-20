// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "logaxiswidget.h"

#include <QChart>
#include <QLineSeries>
#include <QLogValueAxis>
#include <QValueAxis>

LogAxisWidget::LogAxisWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto series = new QLineSeries;
    *series << QPointF(1.0, 1.0) << QPointF(2.0, 73.0) << QPointF(3.0, 268.0) << QPointF(4.0, 17.0)
            << QPointF(5.0, 4325.0) << QPointF(6.0, 723.0);
    //![1]

    //![2]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Logarithmic Axis");
    //![2]

    //![3]
    auto axisX = new QValueAxis;
    axisX->setTitleText("Data point");
    axisX->setLabelFormat("%i");
    axisX->setTickCount(series->count());
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QLogValueAxis;
    axisY->setTitleText("Values");
    axisY->setLabelFormat("%g");
    axisY->setBase(8.0);
    axisY->setMinorTickCount(-1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![3]

    //![4]
    createDefaultChartView(chart);
    //![4]
}
