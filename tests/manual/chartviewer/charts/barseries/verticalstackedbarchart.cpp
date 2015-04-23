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
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>

class VerticalStackedBarChart: public Chart
{
public:
    QString name() { return QObject::tr("VerticalStackedBarChart"); }
    QString category()  { return QObject::tr("BarSeries"); }
    QString subCategory() { return QObject::tr("Vertical"); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Stacked bar chart");
        QStackedBarSeries *series = new QStackedBarSeries(chart);
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

DECLARE_CHART(VerticalStackedBarChart)

