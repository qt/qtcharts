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
#include "qpieseries.h"

class PieChart: public Chart
{
public:
    QString name() { return QObject::tr("PieChart"); }
    QString category()  { return QObject::tr("PieSeries"); }
    QString subCategory() { return QString::null; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Pie chart");
        qreal pieSize = 1.0 / table.count();
        for (int i = 0; i < table.count(); i++) {
            QPieSeries *series = new QPieSeries(chart);
            foreach (Data data, table[i]) {
                QPieSlice *slice = series->append(data.second, data.first.y());
                if (data == table[i].first()) {
                    slice->setLabelVisible();
                    slice->setExploded();
                }
            }
            qreal hPos = (pieSize / 2) + (i / (qreal) table.count());
            series->setPieSize(pieSize);
            series->setHorizontalPosition(hPos);
            series->setVerticalPosition(0.5);
            chart->addSeries(series);
        }
        return chart;
    }
};

DECLARE_CHART(PieChart)

