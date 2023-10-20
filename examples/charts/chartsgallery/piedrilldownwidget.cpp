// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "piedrilldownchart.h"
#include "piedrilldownslice.h"
#include "piedrilldownwidget.h"

#include <QChart>
#include <QLegend>
#include <QPieSeries>
#include <QRandomGenerator>

PieDrilldownWidget::PieDrilldownWidget(QWidget *parent)
    : ContentWidget(parent)
{
    auto *chart = new PieDrilldownChart;
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    auto yearSeries = new QPieSeries(this);
    yearSeries->setName("Sales by year - All (Click on slice to drill down)");

    const QStringList months = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    const QStringList names = {
        "Jane", "John", "Axel", "Mary", "Susan", "Bob"
    };

    for (const QString &name : names) {
        auto series = new QPieSeries(this);
        series->setName("Sales by month - " + name);

        for (const QString &month : months)
            *series << new PieDrilldownSlice(QRandomGenerator::global()->bounded(1000), month, yearSeries);

        QObject::connect(series, &QPieSeries::clicked, chart, &PieDrilldownChart::handleSliceClicked);

        *yearSeries << new PieDrilldownSlice(series->sum(), name, series);
    }

    QObject::connect(yearSeries, &QPieSeries::clicked, chart, &PieDrilldownChart::handleSliceClicked);

    chart->changeSeries(yearSeries);

    createDefaultChartView(chart);
}
