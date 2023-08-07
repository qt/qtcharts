// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QCategoryAxis>

class LogValueAxisY: public Chart
{
public:
    QString name() { return "LogValueAxisY"; }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return QObject::tr("Log"); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Value X , LogValue Y");

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
        axis->setBase(2);
        foreach (QAbstractSeries *series, chart->series())
            chart->setAxisY(axis, series);

        return chart;
    }
};

class LogValueAxisTitleY: public LogValueAxisY
{
public:
    QString name() { return "LogValueAxisYTitle"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = LogValueAxisY::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle("Value X , Log Value Y, title");
        return chart;
    }
};

DECLARE_CHART(LogValueAxisY);
DECLARE_CHART(LogValueAxisTitleY);
