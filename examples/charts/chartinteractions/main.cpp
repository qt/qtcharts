/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QLineSeries>

#include <QtCharts/QValueAxis>

#include "chart.h"
#include "chartview.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineSeries *series = new QLineSeries();

    series->append(0, 6);
    series->append(1, 3);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 13);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    Chart *chart = new Chart(0, 0, series);
    chart->legend()->hide();
    chart->addSeries(series);
    QPen p = series->pen();
    p.setWidth(5);
    series->setPen(p);
    chart->createDefaultAxes();
    chart->setTitle("Drag'n drop to move data points");

    QValueAxis *axisX = new QValueAxis();
    chart->setAxisX(axisX, series);
    axisX->setRange(0, 20);

    QValueAxis *axisY = new QValueAxis();
    chart->setAxisY(axisY, series);
    axisY->setRange(0, 13);

    QObject::connect(series, SIGNAL(pressed(QPointF)), chart, SLOT(clickPoint(QPointF)));

    ChartView *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
