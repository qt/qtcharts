// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

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
