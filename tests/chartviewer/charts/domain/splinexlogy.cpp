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
#include "qsplineseries.h"
#include "qlogvalueaxis.h"
#include "qvalueaxis.h"

class SplineXLogY: public Chart
{
public:
    QString name() { return "Spline X LogY"; }
    QString category()  { return QObject::tr("Domain"); }
    QString subCategory() { return QObject::tr("Both Log"); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Spline: X, Log Y");

        QString name("Series ");
        int nameIndex = 0;
        foreach (DataList list, table) {
            QSplineSeries *series = new QSplineSeries(chart);
            foreach (Data data, list)
                series->append(data.first);
            series->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(series);
        }

        QValueAxis *axisX= new QValueAxis();
        QLogValueAxis *axisY= new QLogValueAxis();
        axisY->setBase(2);
        foreach (QAbstractSeries *series, chart->series()) {
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
        }

        return chart;
    }
};

DECLARE_CHART(SplineXLogY);
