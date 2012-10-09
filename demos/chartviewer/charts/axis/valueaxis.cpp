/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "charts.h"
#include "qchart.h"
#include "qlineseries.h"
#include "qvalueaxis.h"
#include "qcategoryaxis.h"

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
        chart->axisX()->setTitle("Axis X");
        chart->axisY()->setTitle("Axis Y");
        chart->setTitle("Value X , Value Y, title");
        return chart;
    }
};

DECLARE_CHART(ValueAxis);
DECLARE_CHART(ValueAxisTitle);
