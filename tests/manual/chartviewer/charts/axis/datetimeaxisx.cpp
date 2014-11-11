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
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>

class DateTimeAxisX: public Chart
{
public:
    QString name() { return "AxisX"; }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return "DateTimeAxis"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("DateTime X , Value Y");
        QValueAxis *valueaxis = new QValueAxis();
        QDateTimeAxis *datetimeaxis = new QDateTimeAxis();
        datetimeaxis->setTickCount(10);
        datetimeaxis->setFormat("yyyy");

        qreal day = 1000l * 60l * 60l * 24l;

        QString name("Series ");
        int nameIndex = 0;
        foreach (DataList list, table) {
            QLineSeries *series = new QLineSeries(chart);
            foreach (Data data, list) {
                QPointF point = data.first;
                series->append(day * 365l * 30l + point.x() * day * 365l, point.y());
            }
            series->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(series);
            chart->setAxisX(datetimeaxis, series);
            chart->setAxisY(valueaxis, series);
        }

        return chart;
    }
};

class DateTimeAxisXTitle: public DateTimeAxisX
{
public:
    QString name() { return "AxisX Title"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = DateTimeAxisX::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle("DateTime X , Value Y, Title");
        return chart;
    }
};


DECLARE_CHART(DateTimeAxisX);
DECLARE_CHART(DateTimeAxisXTitle);
