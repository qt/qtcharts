// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>

class PieChart: public Chart
{
public:
    QString name() { return QObject::tr("PieChart"); }
    QString category()  { return QObject::tr("PieSeries"); }
    QString subCategory() { return QString(); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Pie chart");
        qreal pieSize = 1.0 / table.count();
        for (int i = 0; i < table.count(); i++) {
            QPieSeries *series = new QPieSeries(chart);
            foreach (Data data, table[i]) {
                QPieSlice *slice = series->append(data.second, data.first.y());
                if (data == table[i].first()) {
                    slice->setLabelVisible();
                    slice->setExploded();
                }
            }
            qreal hPos = (pieSize / 2) + (i / (qreal) table.count());
            series->setPieSize(pieSize);
            series->setHorizontalPosition(hPos);
            series->setVerticalPosition(0.5);
            chart->addSeries(series);
        }
        return chart;
    }
};

DECLARE_CHART(PieChart)

