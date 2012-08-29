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
#include <QBarCategoryAxis>
#include <QStackedBarSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QBarSet *low = new QBarSet("Min");
    QBarSet *high = new QBarSet("Max");

    *low << -51.5 << -49 << -44.3 << -36.0 << -24.6 << -7.0 << -5.0 << -10.8 << -18.7 << -31.8 << -42.0 << -47.0;
    *high << 10.9 << 11.8 << 17.5 << 25.5 << 31.0 << 33.8 << 37.2 << 33.8 << 28.8 << 19.4 << 14.1 << 10.8;
//![1]

//![2]
    QStackedBarSeries *series = new QStackedBarSeries();
    series->append(low);
    series->append(high);
//![2]

//![3]
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Temperature records in Finland in Celcius");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

    QBarCategoryAxis* axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->axisY(series)->setRange(-52,52);
//![4]

//![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
//![5]

//![6]
    QChartView* chartView = new QChartView(chart);
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
