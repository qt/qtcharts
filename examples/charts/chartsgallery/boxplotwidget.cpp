// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "boxplotdatareader.h"
#include "boxplotwidget.h"

#include <QBarCategoryAxis>
#include <QBoxPlotSeries>
#include <QBoxSet>
#include <QChart>
#include <QFile>
#include <QLegend>

BoxPlotWidget::BoxPlotWidget(QWidget *parent)
    : ContentWidget(parent)
{
}

bool BoxPlotWidget::doLoad()
{
    //! [1]
    auto acmeSeries = new QBoxPlotSeries;
    acmeSeries->setName("Acme Ltd");

    auto boxWhiskSeries = new QBoxPlotSeries;
    boxWhiskSeries->setName("BoxWhisk Inc");
    //! [1]

    //! [2]
    QFile acmeData(":boxplot_a");
    const QString errorTemplate = QStringLiteral("Failed to load '%1' file.");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_loadError = errorTemplate.arg(acmeData.fileName());
        return false;
    }

    BoxPlotDataReader dataReader(&acmeData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set)
            acmeSeries->append(set);
    }
    //! [2]

    //! [3]
    QFile boxwhiskData(":boxplot_b");
    if (!boxwhiskData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_loadError = errorTemplate.arg(acmeData.fileName());
        return false;
    }

    dataReader.readFile(&boxwhiskData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set)
            boxWhiskSeries->append(set);
    }
    //! [3]

    //! [4]
    auto chart = new QChart;
    chart->addSeries(acmeSeries);
    chart->addSeries(boxWhiskSeries);
    chart->setTitle("Acme Ltd. and BoxWhisk Inc. share deviation in 2012");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //! [4]

    //! [5]
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setMin(15.0);
    chart->axes(Qt::Horizontal).first()->setMax(34.0);
    //! [5]

    //! [6]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //! [6]

    //! [7]
    createDefaultChartView(chart);
    //! [7]

    return true;
}
