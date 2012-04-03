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

#include <QtGui/QApplication>
#include <QMainWindow>
#include <QChartView>
#include <QScatterSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//![1]
    QPen pen(Qt::black);
    pen.setWidth(2);
    QBrush blue(Qt::blue);
    QBrush red(Qt::red);

    QScatterSeries *series0 = new QScatterSeries();
    series0->setPen(pen);
    series0->setBrush(blue);
    series0->setShape(QScatterSeries::MarkerShapeCircle);
    series0->setSize(15.0);

    QScatterSeries *series1 = new QScatterSeries();
    series1->setPen(pen);
    series1->setBrush(red);
    series1->setShape(QScatterSeries::MarkerShapeCircle);
    series1->setSize(15.0);
//![1]

//![2]
    series0->append(0, 6);
    series0->append(2, 4);
    series0->append(3, 8);
    series0->append(7, 4);
    series0->append(10, 5);

    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10, 2);
//![2]
//![3]
    QChart* chart = new QChart();

    chart->addSeries(series0);
    chart->addSeries(series1);
    chart->setTitle("Simple scatterchart example");
//![3]
//![4]
    QChartView* chartView = new QChartView(chart);
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
