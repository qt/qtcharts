/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

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
    QString subCategory() { return QString::null; }

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
