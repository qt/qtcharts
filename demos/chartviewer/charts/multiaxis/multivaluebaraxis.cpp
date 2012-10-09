/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
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
#include "qvalueaxis.h"
#include "qcategoryaxis.h"
#include "qbarseries.h"
#include "qbarset.h"
#include "qbarcategoryaxis.h"

class MultiValueBarAxis: public Chart
{
public:
    QString name()
    {
        return "Axis";
    }
    QString category()
    {
        return QObject::tr("MultiAxis");
    }
    QString subCategory()
    {
        return "MultiBarAxis";
    }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        QValueAxis *axisX;
        QValueAxis *axisY;
        QBarSeries *series = new QBarSeries();
        QBarCategoryAxis *barcategory = new QBarCategoryAxis();

        chart->setTitle("MultiBarAxis");

        QString name("Series");
        int nameIndex = 1;
        for (int i(0); i < 2; i++) {
            QLineSeries *series = new QLineSeries(chart);
            foreach (Data data, table.at(i))
                series->append(data.first);
            series->setName(name + QString::number(nameIndex));

            chart->addSeries(series);
            axisX = new QValueAxis();
            axisX->setLinePenColor(series->pen().color());
            axisX->setTitle("ValueAxis for series" + QString::number(nameIndex));
            if (nameIndex % 2)
                axisX->setAlignment(Qt::AlignTop);
            else
                axisX->setAlignment(Qt::AlignBottom);
            axisY = new QValueAxis();
            axisY->setLinePenColor(series->pen().color());
            axisY->setTitle("ValueAxis for series" + QString::number(nameIndex));

            if (nameIndex % 2)
                axisY->setAlignment(Qt::AlignRight);
            else
                axisY->setAlignment(Qt::AlignLeft);

            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            nameIndex++;
        }

        QBarSet *set = new QBarSet("Bar set ");
        foreach (Data data, table.at(2))
            *set << data.first.y();

        int count = set->count();
        for (int i = 0; i < count; i++) {
            barcategory->append("BarSet " + QString::number(i));
        }
        series->append(set);
        chart->addSeries(series);

        barcategory->setLinePen(set->brush().color());
        barcategory->setGridLinePen(set->brush().color());
        barcategory->setTitle("BarCategoryAxis Title");

        chart->setAxisX(barcategory, series);

        return chart;
    }
};


DECLARE_CHART(MultiValueBarAxis);
