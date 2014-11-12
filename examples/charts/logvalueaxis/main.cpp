/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //![1]
    QLineSeries *series = new QLineSeries();
    *series << QPointF(1, 1) << QPointF(2, 73) << QPointF(3, 268) << QPointF(4, 17) << QPointF(5, 4325) << QPointF(6, 723);
    //![1]

    //![2]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Logarithmic axis example");
    //![2]

    //![3]
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Data point");
    axisX->setTickCount(6);
    axisX->setLabelFormat("%i");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QLogValueAxis *axisY = new QLogValueAxis;
    axisY->setLabelFormat("%g");
    axisY->setTitleText("Values");
    axisY->setBase(8);
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
    window.resize(400, 300);
    window.show();

    //![5]

    return a.exec();
}
