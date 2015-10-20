/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>

class CategoryLineChart: public Chart
{
public:
    QString name() { return QObject::tr("CategoryAxis"); }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return QString::null; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Category X , Category Y ");

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

        QCategoryAxis *axisX = new QCategoryAxis;
        axisX->append("low", 5);
        axisX->append("avg.", 12);
        axisX->append("high", 19);
        axisX->setRange(0, 20);
        chart->setAxisX(axisX, chart->series().at(0));

        QCategoryAxis *axisY = new QCategoryAxis;
        axisY->append("cheap", 5);
        axisY->append("fair", 12);
        axisY->append("pricy", 20);
        axisY->setRange(0, 20);
        chart->setAxisY(axisY, chart->series().at(0));

        return chart;
    }
};

class CategoryLineChartTitle: public CategoryLineChart
{
public:
    QString name() { return QObject::tr("CategoryAxis, Title"); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = CategoryLineChart::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle("Category X , Category Y,title  ");
        return chart;
    }
};

DECLARE_CHART(CategoryLineChart)
DECLARE_CHART(CategoryLineChartTitle)
