// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "barmodelmappermodel.h"
#include "barmodelmapperwidget.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QChartView>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLineSeries>
#include <QTableView>
#include <QValueAxis>
#include <QVBarModelMapper>
#include <QVXYModelMapper>

BarModelMapperWidget::BarModelMapperWidget(QWidget *parent)
    : ContentWidget(parent)
{
    // create simple model for storing user's data
    //! [1]
    auto model = new BarModelMapperModel(this);
    //! [1]

    //! [2]
    // create table view and add model to it
    auto tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->setMinimumWidth(300);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model->setParent(tableView);
    //! [2]

    //! [3]
    auto chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);
    //! [3]

    chart->layout()->setContentsMargins(0, 0, 0, 0);

    // series 1
    //! [4]
    auto series = new QBarSeries;

    int first = 3;
    int count = 5;
    auto mapper = new QVBarModelMapper(this);
    mapper->setFirstBarSetColumn(1);
    mapper->setLastBarSetColumn(4);
    mapper->setFirstRow(first);
    mapper->setRowCount(count);
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);
    //! [4]

    //! [5]
    // for storing color hex from the series
    QString seriesColorHex = "#000000";

    // get the color of the series and use it for showing the mapped area
    QList<QBarSet *> barsets = series->barSets();
    for (int i = 0; i < barsets.count(); i++) {
        seriesColorHex = "#" + QString::number(barsets.at(i)->brush().color().rgb(), 16).right(6).toUpper();
        model->addMapping(seriesColorHex, QRect(1 + i, first, 1, barsets.at(i)->count()));
    }
    //! [5]

    //! [6]
    QStringList categories {"April",  "May", "June", "July", "August"};
    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    auto axisY = new QValueAxis;
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //! [6]

    //! [7]
    auto chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    //! [7]

    //! [8]
    // create main layout
    auto mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(10);
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(chartView, 1, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 0);
    setLayout(mainLayout);
    //! [8]
}
