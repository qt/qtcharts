// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "lineandbarwidget.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QLegend>
#include <QLineSeries>
#include <QValueAxis>

LineAndBarWidget::LineAndBarWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto set0 = new QBarSet("Jane");
    auto set1 = new QBarSet("John");
    auto set2 = new QBarSet("Axel");
    auto set3 = new QBarSet("Mary");
    auto set4 = new QBarSet("Sam");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;
    //![1]

    //![2]
    auto barseries = new QBarSeries;
    barseries->append(set0);
    barseries->append(set1);
    barseries->append(set2);
    barseries->append(set3);
    barseries->append(set4);
    //![2]

    //![8]
    auto lineseries = new QLineSeries;
    lineseries->setName("trend");
    lineseries->append(QPoint(0, 4));
    lineseries->append(QPoint(1, 15));
    lineseries->append(QPoint(2, 20));
    lineseries->append(QPoint(3, 4));
    lineseries->append(QPoint(4, 12));
    lineseries->append(QPoint(5, 17));
    //![8]

    //![3]
    auto chart = new QChart;
    chart->addSeries(barseries);
    chart->addSeries(lineseries);
    chart->setTitle("Line and Bar Chart");
    //![3]

    //![4]
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    lineseries->attachAxis(axisX);
    barseries->attachAxis(axisX);
    axisX->setRange(QString("Jan"), QString("Jun"));

    auto axisY = new QValueAxis;
    chart->addAxis(axisY, Qt::AlignLeft);
    lineseries->attachAxis(axisY);
    barseries->attachAxis(axisY);
    axisY->setRange(0, 20);
    //![4]

    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
    createDefaultChartView(chart);
    //![6]
}
