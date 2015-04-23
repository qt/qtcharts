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

class MultiValueAxis2: public Chart
{
public:
    QString name()
    {
        return "AxisSet 2";
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

        chart->setTitle("MultiValueAxis2");

        QString name("Series");
        int nameIndex = 1;
        foreach (DataList list, table) {
            QLineSeries *series = new QLineSeries(chart);
            foreach (Data data, list)
                series->append(data.first);
            series->setName(name + QString::number(nameIndex));

            chart->addSeries(series);
            axisX = new QValueAxis();
            axisX->setLinePenColor(series->pen().color());

            axisY = new QValueAxis();
            axisY->setLinePenColor(series->pen().color());

            chart->addAxis(axisX, nameIndex % 2?Qt::AlignTop:Qt::AlignBottom);
            chart->addAxis(axisY, nameIndex % 2?Qt::AlignRight:Qt::AlignLeft);
            series->attachAxis(axisX);
            series->attachAxis(axisY);
            nameIndex++;
        }

        return chart;
    }
};

DECLARE_CHART(MultiValueAxis2);
