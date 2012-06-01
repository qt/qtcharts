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

#include <QApplication>
#include <QMainWindow>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLegend>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");

    *set0 << QPointF(0.0, 1) << QPointF(1.0, 2) << QPointF(2.4, 3) << QPointF(3.0, 4) << QPointF(4.0, 5) << QPointF(5.0, 6);
    *set1 << QPointF(0.1, 2) << QPointF(1.2, 3) << QPointF(2.45, 4) << QPointF(3.2, 5) << QPointF(4.2, 6) << QPointF(5.2, 7);
    *set2 << QPointF(0.2, 3) << QPointF(1.4, 4) << QPointF(2.50, 5) << QPointF(3.4, 6) << QPointF(4.4, 7) << QPointF(5.4, 8);
    *set3 << QPointF(0.3, 4) << QPointF(1.6, 5) << QPointF(2.55, 6) << QPointF(3.6, 7) << QPointF(4.6, 8) << QPointF(5.6, 9);
    *set4 << QPointF(0.4, 5) << QPointF(1.8, 6) << QPointF(2.6, 7) << QPointF(3.8, 8) << QPointF(4.8, 9) << QPointF(5.8, 10);
//![1]

//![2]
    QBarSeries* series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
//![2]

//![3]
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
//![3]

//![4]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->axisY()->setNiceNumbersEnabled(true);
//![4]

//![5]
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![5]

//![6]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//![6]

    return a.exec();
}
