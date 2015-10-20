/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include "drilldownseries.h"
#include "drilldownchart.h"

QT_CHARTS_USE_NAMESPACE

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
    QStringList months;
    months << "May" << "Jun" << "Jul" << "Aug" << "Sep";
    QStringList weeks;
    weeks << "week 1" << "week 2" << "week 3" << "week 4";
    QStringList plants;
    plants << "Habanero" << "Lemon Drop" << "Starfish" << "Aji Amarillo";
//! [2]

//! [3]
    // Create drilldown structure
    DrilldownBarSeries *seasonSeries = new DrilldownBarSeries(months, drilldownChart);
    seasonSeries->setName("Crop by month - Season");

    // Each month in season series has drilldown series for weekly data
    for (int month = 0; month < months.count(); month++) {

        // Create drilldown series for every week
        DrilldownBarSeries *weeklySeries = new DrilldownBarSeries(weeks, drilldownChart);
        seasonSeries->mapDrilldownSeries(month, weeklySeries);

        // Drilling down from weekly data brings us back to season data.
        for (int week = 0; week < weeks.count(); week++) {
            weeklySeries->mapDrilldownSeries(week, seasonSeries);
            weeklySeries->setName(QString("Crop by week - " + months.at(month)));
        }

        // Use clicked signal to implement drilldown
        QObject::connect(weeklySeries, SIGNAL(clicked(int,QBarSet*)), drilldownChart, SLOT(handleClicked(int,QBarSet*)));
    }

    // Enable drilldown from season series using clicked signal
    QObject::connect(seasonSeries, SIGNAL(clicked(int,QBarSet*)), drilldownChart, SLOT(handleClicked(int,QBarSet*)));
//! [3]

//! [4]
    // Fill monthly and weekly series with data
    foreach (QString plant, plants) {
        QBarSet *monthlyCrop = new QBarSet(plant);
        for (int month = 0; month < months.count(); month++) {
            QBarSet *weeklyCrop = new QBarSet(plant);
            for (int week = 0; week < weeks.count(); week++)
                *weeklyCrop << (qrand() % 20);
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
    drilldownChart->axisX()->setGridLineVisible(false);
    drilldownChart->legend()->setVisible(true);
    drilldownChart->legend()->setAlignment(Qt::AlignBottom);
//! [6]

    QChartView *chartView = new QChartView(drilldownChart);
    window.setCentralWidget(chartView);
    window.resize(480, 300);
    window.show();

    return a.exec();
}

