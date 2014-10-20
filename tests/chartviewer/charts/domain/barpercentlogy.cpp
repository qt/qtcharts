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
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QBarCategoryAxis>

class BarPercentLogY: public Chart
{
public:
    QString name() { return "PercentBar"; }
    QString category()  { return QObject::tr("Domain"); }
    QString subCategory() { return "Vertical Log"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("PercentBar: BarCateogry X, Log Y");

        QString name("Series ");
        QPercentBarSeries *series = new QPercentBarSeries(chart);
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

DECLARE_CHART(BarPercentLogY);
