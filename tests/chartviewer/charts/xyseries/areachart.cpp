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
#include "qchart.h"
#include "qareaseries.h"
#include "qlineseries.h"

class AreaChart: public Chart
{
public:
    QString name() { return QObject::tr("AreaChart"); }
    QString category()  { return QObject::tr("XYSeries"); }
    QString subCategory() { return QString::null; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Area chart");

        // The lower series initialized to zero values
        QLineSeries *lowerSeries = 0;
        QString name("Series ");
        int nameIndex = 0;
        for (int i(0); i < table.count(); i++) {
            QLineSeries *upperSeries = new QLineSeries(chart);
            for (int j(0); j < table[i].count(); j++) {
                Data data = table[i].at(j);
                if (lowerSeries) {
                    const QList<QPointF>& points = lowerSeries->points();
                    upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
                } else {
                    upperSeries->append(QPointF(j, data.first.y()));
                }
            }
            QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
            area->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(area);
            chart->createDefaultAxes();
            lowerSeries = upperSeries;
        }
        return chart;
    }
};

DECLARE_CHART(AreaChart)

