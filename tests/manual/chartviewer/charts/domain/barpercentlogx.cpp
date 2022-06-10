// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QHorizontalPercentBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QBarCategoryAxis>

class BarPercentLogX: public Chart
{
public:
    QString name() { return "Horizontal PercentBar"; }
    QString category()  { return QObject::tr("Domain"); }
    QString subCategory() { return "Horizontal Log"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("PercentBar: Log X, BarCateogry Y");

        QString name("Series ");
        QHorizontalPercentBarSeries *series = new QHorizontalPercentBarSeries(chart);
        QLogValueAxis *logvalueaxis = new QLogValueAxis();
        logvalueaxis->setBase(2);
        QBarCategoryAxis *barcategory = new QBarCategoryAxis();
        for (int i(0); i < table.count(); i++) {
            QBarSet *set = new QBarSet("Bar set " + QString::number(i));
            foreach (Data data, table[i])
                *set << data.first.y();
            series->append(set);
        }
        chart->addSeries(series);

        int count = series->barSets().first()->count();


        for (int i = 0; i < count; i++) {
            barcategory->append("BarSet " + QString::number(i));
        }

        chart->setAxisX(logvalueaxis, series);
        chart->setAxisY(barcategory, series);

        return chart;
    }
};

DECLARE_CHART(BarPercentLogX);
