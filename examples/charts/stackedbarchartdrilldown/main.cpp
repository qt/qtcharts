// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include "drilldownseries.h"
#include "drilldownchart.h"

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

//! [1]
    DrilldownChart *drilldownChart =  new DrilldownChart();
    drilldownChart->setAnimationOptions(QChart::SeriesAnimations);
//! [1]

//! [2]
    // Define categories
    const QStringList months = {
        "May", "Jun", "Jul", "Aug", "Sep"
    };
    const QStringList weeks = {
        "week 1", "week 2", "week 3", "week 4"
    };
    const QStringList plants = {
        "Habanero", "Lemon Drop", "Starfish", "Aji Amarillo"
    };
//! [2]

//! [3]
    // Create drilldown structure
    DrilldownBarSeries *seasonSeries = new DrilldownBarSeries(months, 320, drilldownChart);
    seasonSeries->setName("Crop by month - Season");

    // Each month in season series has drilldown series for weekly data
    for (int month = 0; month < months.count(); month++) {

        // Create drilldown series for every week
        DrilldownBarSeries *weeklySeries = new DrilldownBarSeries(weeks, 80, drilldownChart);
        seasonSeries->mapDrilldownSeries(month, weeklySeries);

        // Drilling down from weekly data brings us back to season data.
        for (int week = 0; week < weeks.count(); week++) {
            weeklySeries->mapDrilldownSeries(week, seasonSeries);
            weeklySeries->setName(QString("Crop by week - " + months.at(month)));
        }

        // Use clicked signal to implement drilldown
        QObject::connect(weeklySeries, &DrilldownBarSeries::clicked,
                         drilldownChart, &DrilldownChart::handleClicked);
    }

    // Enable drilldown from season series using clicked signal
    QObject::connect(seasonSeries, &DrilldownBarSeries::clicked,
                     drilldownChart, &DrilldownChart::handleClicked);
//! [3]

//! [4]
    // Fill monthly and weekly series with data
    for (const QString &plant : plants) {
        QBarSet *monthlyCrop = new QBarSet(plant);
        for (int month = 0; month < months.count(); month++) {
            QBarSet *weeklyCrop = new QBarSet(plant);
            for (int week = 0; week < weeks.count(); week++)
                *weeklyCrop << QRandomGenerator::global()->bounded(20);
            // Get the drilldown series from season series and add crop to it.
            seasonSeries->drilldownSeries(month)->append(weeklyCrop);
            *monthlyCrop << weeklyCrop->sum();
        }
        seasonSeries->append(monthlyCrop);
    }
//! [4]

//! [5]
    // Show season series in initial view
    drilldownChart->changeSeries(seasonSeries);
    drilldownChart->setTitle(seasonSeries->name());
//! [5]

//! [6]
    drilldownChart->axes(Qt::Horizontal).first()->setGridLineVisible(false);
    drilldownChart->legend()->setVisible(true);
    drilldownChart->legend()->setAlignment(Qt::AlignBottom);
//! [6]

    QChartView *chartView = new QChartView(drilldownChart);
    window.setCentralWidget(chartView);
    window.resize(480, 300);
    window.show();

    return a.exec();
}

