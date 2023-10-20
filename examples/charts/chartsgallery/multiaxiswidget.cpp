// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "multiaxiswidget.h"

#include <QCategoryAxis>
#include <QChart>
#include <QLineSeries>
#include <QSplineSeries>
#include <QValueAxis>

MultiAxisWidget::MultiAxisWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto chart = new QChart;
    chart->legend()->hide();
    chart->setTitle("Multiple Vertical Axes in Chart");
    //![1]

    //![2]
    auto axisX = new QValueAxis;
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);
    //![2]

    //![3]
    auto series = new QSplineSeries;
    *series << QPointF(1, 5) << QPointF(3.5, 18) << QPointF(4.8, 7.5) << QPointF(10, 2.5);
    chart->addSeries(series);

    auto axisY = new QValueAxis;
    axisY->setLinePenColor(series->pen().color());

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    //![3]

    //![4]
    series = new QSplineSeries;
    *series << QPointF(1, 0.5) << QPointF(1.5, 4.5) << QPointF(2.4, 2.5) << QPointF(4.3, 12.5)
            << QPointF(5.2, 3.5) << QPointF(7.4, 16.5) << QPointF(8.3, 7.5) << QPointF(10, 17);
    chart->addSeries(series);

    auto axisY3 = new QCategoryAxis;
    axisY3->append("Low", 5);
    axisY3->append("Medium", 12);
    axisY3->append("High", 17);
    axisY3->setLinePenColor(series->pen().color());
    axisY3->setGridLinePen((series->pen()));

    chart->addAxis(axisY3, Qt::AlignRight);
    series->attachAxis(axisX);
    series->attachAxis(axisY3);
    //![4]

    //![5]
    createDefaultChartView(chart);
    //![5]
}
