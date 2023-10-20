// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "interactionschart.h"
#include "interactionsview.h"
#include "interactionswidget.h"

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>

InteractionsWidget::InteractionsWidget(QWidget *parent)
    : ContentWidget(parent)
{
    auto series = new QLineSeries;

    series->append(0, 6);
    series->append(1, 3);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 13);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    auto chart = new InteractionsChart(0, {}, series);
    chart->legend()->hide();
    chart->addSeries(series);
    QPen p = series->pen();
    p.setWidth(5);
    series->setPen(p);
    chart->setTitle("Drag and drop data points to move them");

    auto axisX = new QValueAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setRange(0, 20);
    series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    chart->addAxis(axisY, Qt::AlignLeft);
    axisY->setRange(0, 13);
    series->attachAxis(axisY);

    QObject::connect(series, &QLineSeries::pressed, chart, &InteractionsChart::clickPoint);

    auto view = new InteractionsView(chart, this);
    setDefaultChartView(view);
}
