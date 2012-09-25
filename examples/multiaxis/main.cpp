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
#include <QLineSeries>
#include <QValueAxis>
#include <QTime>
#include <QValueAxis>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    //![1]
    QLineSeries* series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QChart* chart = new QChart();
    for (int i = 0; i < 5; i++) {
        series = new QLineSeries;
        for (int k(0); k < 8; k++)
            series->append(i + k, qrand() % 20);
        chart->addSeries(series);

        axisX = new QValueAxis;
        axisX->setTickCount(7 + i);
        axisX->setLinePenColor(series->pen().color());
        if (i % 2)
            axisX->setAlternativePlacement(true);
        axisY = new QValueAxis;
        axisY->setTickCount(7 + i);
        axisY->setLinePenColor(series->pen().color());
        if (i % 2)
            axisY->setAlternativePlacement(true);

        chart->setAxisX(axisX, series);
        chart->setAxisY(axisY, series);
    }
    //![2]

    //![3]
    chart->legend()->hide();

    chart->setTitle("Simple line chart example");
    //![3]

    //![4]
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![4]


    //![5]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();
    //![5]

    return a.exec();
}
