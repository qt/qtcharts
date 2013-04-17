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
#include <QBoxPlotSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QLineSeries>

#include <QBrush>
#include <QColor>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QBarSet *set0 = new QBarSet("Jan");
    QBarSet *set1 = new QBarSet("Feb");
    QBarSet *set2 = new QBarSet("Mar");
    QBarSet *set3 = new QBarSet("Apr");
    QBarSet *set4 = new QBarSet("May");
    QBarSet *set5 = new QBarSet("Jun");
    QBarSet *set6 = new QBarSet("Jul");
    QBarSet *set7 = new QBarSet("Aug");
    QBarSet *set8 = new QBarSet("Sep");
    QBarSet *set9 = new QBarSet("Oct");
    QBarSet *set10 = new QBarSet("Nov");
    QBarSet *set11 = new QBarSet("Dec");

    //      low  bot   med   top  upp
    *set0 << 3 << 4 << 4.4 << 6 << 7;
    *set1 << 5 << 6 << 7.5 << 8 << 12;
    *set2 << 3 << 5 << 5.7 << 8 << 9;
    *set3 << 5 << 6 << 6.8 << 7 << 8;
    *set4 << 4 << 5 << 5.2 << 6 << 7;
    *set5 << 4 << 7 << 8.2 << 9 << 10;
    *set6 << 2.5 << 5 << 5.4 << 6 << 7;
    *set7 << 5 << 6.3 << 7.5 << 8 << 12;
    *set8 << 2.6 << 5.1 << 5.7 << 8 << 9;
    *set9 << 3.1 << 5.8 << 6.8 << 7 << 8;
    *set10 << 4.2 << 5 << 5.8 << 6 << 7;
    *set11 << 4.7 << 7 << 8.2 << 9 << 10;

//![1]

//![2]
    QBoxPlotSeries *series = new QBoxPlotSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);
    series->append(set6);
    series->append(set7);
    series->append(set8);
    series->append(set9);
    series->append(set10);
    series->append(set11);
    series->setName("Box & Whiskers");
//![2]

    QLineSeries *lineSeries = new QLineSeries();
    lineSeries->append(0, 4.4);
    lineSeries->append(1, 7.5);
    lineSeries->append(2, 5.7);
    lineSeries->append(3, 6.8);
    lineSeries->append(4, 5.2);
    lineSeries->append(5, 8.2);
    lineSeries->append(6, 5.4);
    lineSeries->append(7, 7.5);
    lineSeries->append(8, 5.7);
    lineSeries->append(9, 6.8);
    lineSeries->append(10, 5.2);
    lineSeries->append(11, 8.2);
    lineSeries->setName("Medians");

//![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->addSeries(lineSeries);
    chart->setTitle("Simple boxplotchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
//![4]

//![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
//![5]

//![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![6]

//![7]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//![7]

    return a.exec();
}

