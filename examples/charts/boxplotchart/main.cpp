// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBoxPlotSeries>
#include <QtCharts/QBoxSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCore/QFile>

#include "boxdatareader.h"

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! [1]
    QBoxPlotSeries *acmeSeries = new QBoxPlotSeries();
    acmeSeries->setName("Acme Ltd");

    QBoxPlotSeries *boxWhiskSeries = new QBoxPlotSeries();
    boxWhiskSeries->setName("BoxWhisk Inc");
    //! [1]

    //! [2]
    QFile acmeData(":acme");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    BoxDataReader dataReader(&acmeData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set)
            acmeSeries->append(set);
    }
    //! [2]

    //! [3]
    QFile boxwhiskData(":boxwhisk");
    if (!boxwhiskData.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    dataReader.readFile(&boxwhiskData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set)
            boxWhiskSeries->append(set);
    }
    //! [3]

    //! [4]
    QChart *chart = new QChart();
    chart->addSeries(acmeSeries);
    chart->addSeries(boxWhiskSeries);
    chart->setTitle("Acme Ltd and BoxWhisk Inc share deviation in 2012");
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
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //! [7]

    //! [8]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();
    //! [8]

    return a.exec();
}

