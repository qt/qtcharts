// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QScatterSeries>

class ScatterChart: public Chart
{
public:
    QString name() { return QObject::tr("ScatterChart"); }
    QString category()  { return QObject::tr("XYSeries"); }
    QString subCategory() { return QString(); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Scatter chart");
        QString name("Series ");
        int nameIndex = 0;
        foreach (DataList list, table) {
            QScatterSeries *series = new QScatterSeries(chart);
            foreach (Data data, list)
                series->append(data.first);
            series->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(series);
        }
        chart->createDefaultAxes();
        return chart;
    }
};

DECLARE_CHART(ScatterChart)
