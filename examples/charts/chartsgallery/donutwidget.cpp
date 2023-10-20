// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "donutwidget.h"

#include <QChart>
#include <QPieSeries>
#include <QPieSlice>

DonutWidget::DonutWidget(QWidget *parent)
    : ContentWidget(parent)
{
    //![1]
    auto series = new QPieSeries;
    series->setHoleSize(0.35);
    series->append("Protein 4.2%", 4.2);
    QPieSlice *slice = series->append("Fat 15.6%", 15.6);
    slice->setExploded();
    slice->setLabelVisible();
    series->append("Other 23.8%", 23.8);
    series->append("Carbs 56.4%", 56.4);
    //![1]

    //![2]
    auto chart = new QChart;
    chart->setTitle("Donut with a lemon glaze (100g)");
    chart->addSeries(series);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->legend()->setFont(QFont("Arial", 7));

    createDefaultChartView(chart);
    //![2]
}
