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
#include <QtCharts/QLogValueAxis>

class LineLogXLogY: public Chart
{
public:
    QString name() { return "Line LogX LogY"; }
    QString category()  { return QObject::tr("Domain"); }
    QString subCategory() { return QObject::tr("Both Log"); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Line: Log X, Log Y");

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

        QLogValueAxis *axisX= new QLogValueAxis();
        axisX->setBase(2);
        QLogValueAxis *axisY= new QLogValueAxis();
        axisY->setBase(2);
        foreach (QAbstractSeries *series, chart->series()) {
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
        }

        return chart;
    }
};

DECLARE_CHART(LineLogXLogY);
