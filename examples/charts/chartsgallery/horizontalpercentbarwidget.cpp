// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "horizontalpercentbarwidget.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QHorizontalPercentBarSeries>
#include <QLegend>
#include <QValueAxis>

HorizontalPercentBarWidget::HorizontalPercentBarWidget(QWidget *parent)
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
    auto series = new QHorizontalPercentBarSeries;
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    //![2]

    //![3]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Simple Horizontal Percent Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
    QStringList categories {"Jan", "Feb", "Mar", "Apr", "May", "Jun"};
    auto axisY = new QBarCategoryAxis;
    axisY->append(categories);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    auto axisX = new QValueAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    //![4]

    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
    createDefaultChartView(chart);
    //![6]
}
