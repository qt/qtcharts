// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "modeldatawidget.h"
#include "modeldatamodel.h"

#include <QChart>
#include <QChartView>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLineSeries>
#include <QTableView>
#include <QVXYModelMapper>

QT_USE_NAMESPACE

ModelDataWidget::ModelDataWidget(QWidget *parent)
    : ContentWidget(parent)
{
    // create simple model for storing user's data
    //! [1]
    auto *model = new ModelDataModel;
    //! [1]

    //! [2]
    // create table view and add model to it
    auto tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //! [2]

    //! [3]
    auto chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);
    //! [3]

    // series 1
    //! [4]
    auto series = new QLineSeries;
    series->setName("Line 1");
    auto mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);
    //! [4]

    //! [5]
    // for storing color hex from the series
    QString seriesColorHex = "#000000";

    // get the color of the series and use it for showing the mapped area
    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(0, 0, 2, model->rowCount()));
    //! [5]

    // series 2
    //! [6]
    series = new QLineSeries;
    series->setName("Line 2");

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(2);
    mapper->setYColumn(3);
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);
    //! [6]

    //! [7]
    // get the color of the series and use it for showing the mapped area
    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(2, 0, 2, model->rowCount()));
    //! [7]

    //! [8]
    chart->createDefaultAxes();
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    auto chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    //! [8]

    //! [9]
    // create main layout
    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(chartView, 1, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 0);
    setLayout(mainLayout);
    //! [9]
}
