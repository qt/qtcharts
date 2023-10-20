// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "datetimeaxiswidget.h"

#include <QChart>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QFile>
#include <QLineSeries>
#include <QTextStream>
#include <QValueAxis>

DateTimeAxisWidget::DateTimeAxisWidget(QWidget *parent)
    : ContentWidget(parent)
{
}

bool DateTimeAxisWidget::doLoad()
{
    //![1]
    auto series = new QLineSeries;
    //![1]

    //![2]
    // data from http://www.swpc.noaa.gov/ftpdir/weekly/RecentIndices.txt
    // http://www.swpc.noaa.gov/ftpdir/weekly/README
    // http://www.weather.gov/disclaimer
    QFile sunSpots(":sun_spots");
    if (!sunSpots.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_loadError = QStringLiteral("Failed to load '%1' file.").arg(sunSpots.fileName());
        return false;
    }

    QTextStream stream(&sunSpots);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.startsWith("#") || line.startsWith(":"))
            continue;
        QStringList values = line.split(QLatin1Char(' '), Qt::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 15));
        series->append(momentInTime.toMSecsSinceEpoch(), values[2].toDouble());
    }
    sunSpots.close();
    //![2]

    //![3]
    auto chart = new QChart;
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Sunspots count (by Space Weather Prediction Center)");
    //![3]

    //![4]
    auto axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Sunspots count");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    createDefaultChartView(chart);
    //![5]

    return true;
}
