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
#include "qhorizontalpercentbarseries.h"
#include "qbarset.h"

class HorizontalPercentBarChart: public Chart
{
public:
    QString name() { return QObject::tr("HorizontalPercentBarChart"); }
    QString category()  { return QObject::tr("BarSeries"); }
    QString subCategory() { return QObject::tr("Horizontal"); }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Horizontal percent chart");
        QHorizontalPercentBarSeries *series = new QHorizontalPercentBarSeries(chart);
        for (int i(0); i < table.count(); i++) {
            QBarSet *set = new QBarSet("Bar set " + QString::number(i));
            foreach (Data data, table[i])
                *set << data.first.y();
            series->append(set);
        }
        chart->addSeries(series);
        chart->createDefaultAxes();
        return chart;
    }
};

DECLARE_CHART(HorizontalPercentBarChart)

