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

#include "multichartwidget.h"
#include <QVBoxLayout>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qscatterseries.h>
#include <qpieseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

MultiChartWidget::MultiChartWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);

    // Create chart 1 and add a simple pie series onto it
    QChartView *chartView1 = new QChartView();
    l->addWidget(chartView1);
    QPieSeries *pie = new QPieSeries();
    pie->append(1.1, "label1");
    pie->append(1.2, "label2");
    chartView1->addSeries(pie);

    // Create chart 2 and add a simple scatter series onto it
    QChartView *chartView2 = new QChartView();
    l->addWidget(chartView2);
    QScatterSeries *scatter = new QScatterSeries();
    *scatter << QPointF(0.5, 5.0)
             << QPointF(1.0, 4.5)
             << QPointF(1.0, 5.5)
             << QPointF(1.5, 5.0)
             << QPointF(2.0, 4.5)
             << QPointF(2.0, 5.5)
             << QPointF(2.5, 5.0);
    chartView2->addSeries(scatter);
}
