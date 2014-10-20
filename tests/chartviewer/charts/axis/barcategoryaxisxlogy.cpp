/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QBarCategoryAxis>

class BarCategoryAxisXLogY: public Chart
{
public:
    QString name() { return "AxisX"; }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return "BarCategoryAxis"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle(" BarCateogry X , LogValue Y");

        QString name("Series ");
        QBarSeries *series = new QBarSeries(chart);
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

        chart->setAxisY(logvalueaxis, series);
        chart->setAxisX(barcategory, series);

        return chart;
    }
};

class BarCategoryAxisXLogYTitle: public BarCategoryAxisXLogY
{
    QString name() { return "AxisX Title"; }
    QChart *createChart(const DataTable &table)
    {
        QChart *chart = BarCategoryAxisXLogY::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle(" BarCateogry X , LogValue Y, title");
        return chart;
    }
};

DECLARE_CHART(BarCategoryAxisXLogY);
DECLARE_CHART(BarCategoryAxisXLogYTitle);
