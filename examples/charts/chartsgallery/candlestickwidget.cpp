// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "candlestickdatareader.h"
#include "candlestickwidget.h"

#include <QBarCategoryAxis>
#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QChart>
#include <QDateTime>
#include <QFile>
#include <QLegend>
#include <QValueAxis>

CandleStickWidget::CandleStickWidget(QWidget *parent)
    : ContentWidget(parent)
{
}

bool CandleStickWidget::doLoad()
{
    //! [1]
    auto acmeSeries = new QCandlestickSeries;
    acmeSeries->setName("Acme Ltd");
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));
    //! [1]

    //! [2]
    QFile acmeData(":candlestick");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_loadError = QStringLiteral("Failed to load '%1' file.").arg(acmeData.fileName());
        return false;
    }

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
    auto chart = new QChart;
    chart->addSeries(acmeSeries);
    chart->setTitle("Acme Ltd. Historical Data (July 2015)");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //! [3]

    //! [4]
    chart->createDefaultAxes();

    auto axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
    axisX->setCategories(categories);

    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);
    //! [4]

    //! [5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //! [5]

    //! [6]
    createDefaultChartView(chart);
    //! [6]

    return true;
}
