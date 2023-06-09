// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "barpercentwidget.h"

#include <QBarCategoryAxis>
#include <QBarSet>
#include <QChart>
#include <QLegend>
#include <QPercentBarSeries>
#include <QValueAxis>

BarPercentWidget::BarPercentWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto set0 = new QBarSet("Jane");
    auto set1 = new QBarSet("John");
    auto set2 = new QBarSet("Axel");
    auto set3 = new QBarSet("Mary");
    auto set4 = new QBarSet("Samantha");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;
    //![1]

    //![2]
    auto series = new QPercentBarSeries;
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    //![2]

    //![3]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Simple Percent Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
    QStringList categories {"Jan", "Feb", "Mar", "Apr", "May", "Jun"};
    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    auto axisY = new QValueAxis;
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
    createDefaultChartView(chart);
    //![6]
}
