// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "donutbreakdownchart.h"
#include "donutbreakdownwidget.h"

#include <QChart>
#include <QPieSeries>

DonutBreakdownWidget::DonutBreakdownWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    // Graph is based on data of 'Total consumption of energy increased by 10 per cent in 2010'
    // Statistics Finland, 13 December 2011
    // http://www.stat.fi/til/ekul/2010/ekul_2010_2011-12-13_tie_001_en.html

    auto series1 = new QPieSeries;
    series1->setName("Fossil fuels");
    series1->append("Oil", 353295);
    series1->append("Coal", 188500);
    series1->append("Natural gas", 148680);
    series1->append("Peat", 94545);

    auto series2 = new QPieSeries;
    series2->setName("Renewables");
    series2->append("Wood fuels", 319663);
    series2->append("Hydro power", 45875);
    series2->append("Wind power", 1060);

    auto series3 = new QPieSeries;
    series3->setName("Others");
    series3->append("Nuclear energy", 238789);
    series3->append("Import energy", 37802);
    series3->append("Other", 32441);
    //![1]

    //![2]
    auto donutBreakdown = new DonutBreakdownChart;
    donutBreakdown->setAnimationOptions(QChart::AllAnimations);
    donutBreakdown->setTitle("Total consumption of energy in Finland 2010");
    donutBreakdown->legend()->setAlignment(Qt::AlignRight);
    donutBreakdown->addBreakdownSeries(series1, Qt::red);
    donutBreakdown->addBreakdownSeries(series2, Qt::darkGreen);
    donutBreakdown->addBreakdownSeries(series3, Qt::darkBlue);
    //![2]

    //![3]
    createDefaultChartView(donutBreakdown);
    //![3]
}
