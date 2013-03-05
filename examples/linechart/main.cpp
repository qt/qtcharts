/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include <QApplication>
#include <QMainWindow>
#include <QChartView>
#include <QLineSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QLineSeries *series = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
//![1]

//![2]
    *series << QPointF(0.06197, 0.16)
            << QPointF(0.18694, 0.16)
            << QPointF(0.3119, 0.16)
            << QPointF(0.43687, 0.16)
            << QPointF(0.56183, 0.16)
            << QPointF(0.68678, 0.16)
            << QPointF(0.81173, 0.16)
            << QPointF(0.93667, 0.16);

   *series2 << QPointF(0.06197, 0.16)
            << QPointF(0.18694, 0.16)
            << QPointF(0.3119, 0.16)
            << QPointF(0.43687, 0.16)
            << QPointF(0.56183, 0.16)
            << QPointF(0.68678, 0.16)
            << QPointF(0.81173, 0.16)
            << QPointF(0.93667, 0.16);
//![2]

//![3]
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
//![3]

//![4]
    QChartView *chartView = new QChartView(chart);
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
