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
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QStackedBarSeries>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QBarSet *low = new QBarSet("Min");
    QBarSet *high = new QBarSet("Max");

    *low << -52 << -50 << -45.3 << -37.0 << -25.6 << -8.0 << -6.0 << -11.8 << -19.7 << -32.8 << -43.0 << -48.0;
    *high << 11.9 << 12.8 << 18.5 << 26.5 << 32.0 << 34.8 << 38.2 << 34.8 << 29.8 << 20.4 << 15.1 << 11.8;
//![1]

//![2]
    QStackedBarSeries *series = new QStackedBarSeries();
    series->append(low);
    series->append(high);
//![2]

//![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Temperature records in celcius");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    axis->setTitleText("Month");
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->axisY(series)->setRange(-52, 52);
    chart->axisY(series)->setTitleText("Temperature [&deg;C]");
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
    window.resize(600, 300);
    window.show();
//![7]

    return a.exec();
}
