/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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
#include "qchart.h"
#include "qlineseries.h"
#include "qlogvalueaxis.h"
#include "qcategoryaxis.h"

class LogValueAxisY: public Chart
{
public:
    QString name() { return "LogValueAxisY"; }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return QObject::tr("Log"); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Value X , LogValue Y");

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
        QLogValueAxis *axis = new QLogValueAxis();
        axis->setBase(2);
        foreach (QAbstractSeries *series, chart->series())
            chart->setAxisY(axis, series);

        return chart;
    }
};

class LogValueAxisTitleY: public LogValueAxisY
{
public:
    QString name() { return "LogValueAxisYTitle"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = LogValueAxisY::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle("Value X , Log Value Y, title");
        return chart;
    }
};

DECLARE_CHART(LogValueAxisY);
DECLARE_CHART(LogValueAxisTitleY);
