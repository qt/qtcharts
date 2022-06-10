// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //![1]
    QLineSeries *series = new QLineSeries();
    *series << QPointF(1.0, 1.0) << QPointF(2.0, 73.0) << QPointF(3.0, 268.0) << QPointF(4.0, 17.0)
            << QPointF(5.0, 4325.0) << QPointF(6.0, 723.0);
    //![1]

    //![2]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Logarithmic axis example");
    //![2]

    //![3]
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Data point");
    axisX->setLabelFormat("%i");
    axisX->setTickCount(series->count());
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QLogValueAxis *axisY = new QLogValueAxis();
    axisY->setTitleText("Values");
    axisY->setLabelFormat("%g");
    axisY->setBase(8.0);
    axisY->setMinorTickCount(-1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![3]

    //![4]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![4]

    //![5]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();
    //![5]

    return app.exec();
}
