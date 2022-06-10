// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //![1]
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("Multiaxis chart example");
    //![1]

    //![2]
    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);
    //![2]

    //![3]
    QSplineSeries *series = new QSplineSeries;
    *series << QPointF(1, 5) << QPointF(3.5, 18) << QPointF(4.8, 7.5) << QPointF(10, 2.5);
    chart->addSeries(series);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLinePenColor(series->pen().color());

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    //![3]

    //![4]
    series = new QSplineSeries;
    *series << QPointF(1, 0.5) << QPointF(1.5, 4.5) << QPointF(2.4, 2.5) << QPointF(4.3, 12.5)
            << QPointF(5.2, 3.5) << QPointF(7.4, 16.5) << QPointF(8.3, 7.5) << QPointF(10, 17);
    chart->addSeries(series);

    QCategoryAxis *axisY3 = new QCategoryAxis;
    axisY3->append("Low", 5);
    axisY3->append("Medium", 12);
    axisY3->append("High", 17);
    axisY3->setLinePenColor(series->pen().color());
    axisY3->setGridLinePen((series->pen()));

    chart->addAxis(axisY3, Qt::AlignRight);
    series->attachAxis(axisX);
    series->attachAxis(axisY3);
    //![4]

    //![5]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![5]

    //![6]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();
    //![6]

    return a.exec();
}

