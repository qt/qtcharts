// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "temperaturerecordswidget.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QLegend>
#include <QStackedBarSeries>
#include <QValueAxis>

TemperatureRecordsWidget::TemperatureRecordsWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto low = new QBarSet("Min");
    auto high = new QBarSet("Max");

    *low << -52 << -50 << -45.3 << -37.0 << -25.6 << -8.0
         << -6.0 << -11.8 << -19.7 << -32.8 << -43.0 << -48.0;
    *high << 11.9 << 12.8 << 18.5 << 26.5 << 32.0 << 34.8
          << 38.2 << 34.8 << 29.8 << 20.4 << 15.1 << 11.8;
    //![1]

    //![2]
    auto series = new QStackedBarSeries;
    series->append(low);
    series->append(high);
    //![2]

    //![3]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Temperature records in Celcius");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
    QStringList categories = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);
    axisX->setTitleText("Month");
    chart->addAxis(axisX, Qt::AlignBottom);
    auto axisY = new QValueAxis;
    axisY->setRange(-52, 52);
    axisY->setTitleText("Temperature [&deg;C]");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
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
