// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>

class ValueAxis: public Chart
{
public:
    QString name() { return "ValueAxis"; }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return QString(); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Value X , Value Y");

        QString name("Series ");
        int nameIndex = 0;
        foreach (DataList list, table) {
            QLineSeries *series = new QLineSeries(chart);
            foreach (Data data, list)
                series->append(data.first);
            series->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(series);
        }

        chart->createDefaultAxes();
        QValueAxis *axis = new QValueAxis();
        foreach (QAbstractSeries *series, chart->series())
            chart->setAxisX(axis, series);

        return chart;
    }
};

class ValueAxisTitle: public ValueAxis
{
public:
    QString name() { return "ValueAxis Title"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = ValueAxis::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle("Value X , Value Y, title");
        return chart;
    }
};

DECLARE_CHART(ValueAxis);
DECLARE_CHART(ValueAxisTitle);
