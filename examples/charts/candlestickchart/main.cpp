// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "candlestickdatareader.h"

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! [1]
    QCandlestickSeries *acmeSeries = new QCandlestickSeries();
    acmeSeries->setName("Acme Ltd");
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));
    //! [1]

    //! [2]
    QFile acmeData(":acme");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    QStringList categories;

    CandlestickDataReader dataReader(&acmeData);
    while (!dataReader.atEnd()) {
        QCandlestickSet *set = dataReader.readCandlestickSet();
        if (set) {
            acmeSeries->append(set);
            categories << QDateTime::fromMSecsSinceEpoch(set->timestamp()).toString("dd");
        }
    }
    //! [2]

    //! [3]
    QChart *chart = new QChart();
    chart->addSeries(acmeSeries);
    chart->setTitle("Acme Ltd Historical Data (July 2015)");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //! [3]

    //! [4]
    chart->createDefaultAxes();

    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);
    //! [4]

    //! [5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //! [5]

    //! [6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //! [6]

    //! [7]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();
    //! [7]

    return a.exec();
}
