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
#include <QDateTime>
#include <QDateTimeAxis>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //![1]
    QLineSeries* series = new QLineSeries();
    //![1]

    //![2]
    QDateTime momentInTime;
    for (int i = 0; i < 100; i++) {
        momentInTime.setDate(QDate(2012, 1 , (1 + i / 9) % 28));
        momentInTime.setTime(QTime(9 + i % 9, 0));
        if (i > 0)
            series->append(momentInTime.toMSecsSinceEpoch(), series->points().at(i - 1).y() *  (0.95 + (qrand() % 11) / 100.0));
        else
            series->append(momentInTime.toMSecsSinceEpoch(), 45);
    }
    //![2]

    //![3]
    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTicksCount(20);
    momentInTime.setDate(QDate(2012,1,1));
    momentInTime.setTime(QTime(6, 0));
    axisX->setMin(momentInTime);
    momentInTime.setDate(QDate(2012,1,7));
    momentInTime.setTime(QTime(18, 0));
    axisX->setMax(momentInTime);
    chart->setAxisX(axisX, series);
    chart->setTitle("Date and Time axis chart example");
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
