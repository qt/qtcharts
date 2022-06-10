// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QCategoryAxis>

class LogValueAxisX: public Chart
{
public:
    QString name() { return "LogValueAxisX"; }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return QObject::tr("Log"); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("LogValue X , Value Y");

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
        QLogValueAxis *axis = new QLogValueAxis();
        axis->setBase(1.2);
        foreach (QAbstractSeries *series, chart->series())
            chart->setAxisX(axis, series);

        return chart;
    }
};

class LogValueAxisTitleX: public LogValueAxisX
{
public:
    QString name() { return "LogValueAxisXTitle"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = LogValueAxisX::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle("Log Value X , Value Y, title");
        return chart;
    }
};

DECLARE_CHART(LogValueAxisX);
DECLARE_CHART(LogValueAxisTitleX);
