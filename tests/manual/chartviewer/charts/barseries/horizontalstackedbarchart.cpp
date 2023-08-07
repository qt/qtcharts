// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QBarSet>

class HorizontalStackedBarChart: public Chart
{
public:
    QString name() { return QObject::tr("HorizontalStackedBarChart"); }
    QString category()  { return QObject::tr("BarSeries"); }
    QString subCategory() { return QObject::tr("Horizontal"); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Horizontal stacked chart");
        QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries(chart);
        for (int i(0); i < table.count(); i++) {
            QBarSet *set = new QBarSet("Bar set " + QString::number(i));
            foreach (Data data, table[i])
                *set << data.first.y();
            series->append(set);
        }
        chart->addSeries(series);
        chart->createDefaultAxes();
        return chart;
    }
};

DECLARE_CHART(HorizontalStackedBarChart)

