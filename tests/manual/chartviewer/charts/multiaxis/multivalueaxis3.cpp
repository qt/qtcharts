// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>

class MultiValueAxis3: public Chart
{
public:
    QString name()
    {
        return "AxisSet 3";
    }
    QString category()
    {
        return QObject::tr("MultiAxis");
    }
    QString subCategory()
    {
        return "MultiValueAxis";
    }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        QValueAxis *axisX;
        QValueAxis *axisY;

        chart->setTitle("MultiValueAxis3");

        QString name("Series");
        int nameIndex = 0;
        foreach (DataList list, table) {
            QLineSeries *series = new QLineSeries(chart);
            foreach (Data data, list)
                series->append(data.first);
            series->setName(name + QString::number(nameIndex));

            chart->addSeries(series);
            axisX = new QValueAxis();
            axisX->setLinePenColor(series->pen().color());
            axisX->setTitleText("ValueAxis for series" + QString::number(nameIndex));

            axisY = new QValueAxis();
            axisY->setLinePenColor(series->pen().color());
            axisY->setTitleText("ValueAxis for series" + QString::number(nameIndex));

            chart->addAxis(axisX, nameIndex % 2?Qt::AlignTop:Qt::AlignBottom);
            chart->addAxis(axisY, nameIndex % 2?Qt::AlignRight:Qt::AlignLeft);
            series->attachAxis(axisX);
            series->attachAxis(axisY);
            nameIndex++;
        }

        return chart;
    }
};

DECLARE_CHART(MultiValueAxis3);
