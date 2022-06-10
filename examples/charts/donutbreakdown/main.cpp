// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtCharts/QChartView>
#include "donutbreakdownchart.h"

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //![1]
    // Graph is based on data of 'Total consumption of energy increased by 10 per cent in 2010'
    // Statistics Finland, 13 December 2011
    // http://www.stat.fi/til/ekul/2010/ekul_2010_2011-12-13_tie_001_en.html

    QPieSeries *series1 = new QPieSeries();
    series1->setName("Fossil fuels");
    series1->append("Oil", 353295);
    series1->append("Coal", 188500);
    series1->append("Natural gas", 148680);
    series1->append("Peat", 94545);

    QPieSeries *series2 = new QPieSeries();
    series2->setName("Renewables");
    series2->append("Wood fuels", 319663);
    series2->append("Hydro power", 45875);
    series2->append("Wind power", 1060);

    QPieSeries *series3 = new QPieSeries();
    series3->setName("Others");
    series3->append("Nuclear energy", 238789);
    series3->append("Import energy", 37802);
    series3->append("Other", 32441);
    //![1]

    //![2]
    DonutBreakdownChart *donutBreakdown = new DonutBreakdownChart();
    donutBreakdown->setAnimationOptions(QChart::AllAnimations);
    donutBreakdown->setTitle("Total consumption of energy in Finland 2010");
    donutBreakdown->legend()->setAlignment(Qt::AlignRight);
    donutBreakdown->addBreakdownSeries(series1, Qt::red);
    donutBreakdown->addBreakdownSeries(series2, Qt::darkGreen);
    donutBreakdown->addBreakdownSeries(series3, Qt::darkBlue);
    //![2]

    //![3]
    QMainWindow window;
    QChartView *chartView = new QChartView(donutBreakdown);
    chartView->setRenderHint(QPainter::Antialiasing);
    window.setCentralWidget(chartView);
    window.resize(800, 500);
    window.show();
    //![3]

    return a.exec();
}
