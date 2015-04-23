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
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

class BarCategoryAxisY: public Chart
{
public:
    QString name() { return "AxisY"; }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return "BarCategoryAxis"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle(" BarCateogry Y , Value X");

        QString name("Series ");
        QHorizontalBarSeries *series = new QHorizontalBarSeries(chart);
        QValueAxis *valueaxis = new QValueAxis();
        QBarCategoryAxis *barcategory = new QBarCategoryAxis();
        for (int i(0); i < table.count(); i++) {
            QBarSet *set = new QBarSet("Bar set " + QString::number(i));
            foreach(Data data, table[i])
                *set << data.first.y();
            series->append(set);
        }
        chart->addSeries(series);

        int count = series->barSets().first()->count();

        for (int i = 0; i < count; i++) {
            barcategory->append("BarSet " + QString::number(i));
        }

        chart->setAxisX(valueaxis, series);
        chart->setAxisY(barcategory, series);

        return chart;
    }
};

class BarCategoryAxisYTitle: public BarCategoryAxisY
{
public:
    QString name()
    {
        return "AxisY Title";
    }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = BarCategoryAxisY::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle(" BarCateogry Y , Value X, title");
        return chart;
    }
};

DECLARE_CHART(BarCategoryAxisY);
DECLARE_CHART(BarCategoryAxisYTitle);
