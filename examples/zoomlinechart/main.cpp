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

#include "chartview.h"
#include <QApplication>
#include <QMainWindow>
#include <QLineSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QLineSeries* series0 = new QLineSeries();
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);

    QLineSeries* series1 = new QLineSeries();
    QPen red(Qt::red);
    red.setWidth(3);
    series1->setPen(red);
//![1]

//![2]
    *series0 << QPointF(0, 6) << QPointF(2, 4) << QPointF(3, 8) << QPointF(7, 4) << QPointF(10, 5);
    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10, 2);
//![2]

//![3]
    QChart* chart = new QChart();

    chart->addSeries(series0);
    chart->addSeries(series1);
    chart->setTitle("Zoom in/out chart example");
    chart->setAnimationOptions(QChart::AllAnimations);
//![3]

//![4]
     ChartView* chartView = new ChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);
//![4]

//![5]
     QMainWindow window;
     window.setCentralWidget(chartView);
     window.resize(400, 300);
     window.show();
//![5]

    return a.exec();
}
