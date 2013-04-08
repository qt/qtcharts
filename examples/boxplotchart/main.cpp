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

    //      low  bot   med   top  upp
    *set0 << 3 << 4 << 4.4 << 6 << 7;
    *set1 << 5 << 6 << 7.5 << 8 << 12;
    *set2 << 3 << 5 << 5.7 << 8 << 9;
    *set3 << 5 << 6 << 6.8 << 7 << 8;
    *set4 << 4 << 5 << 5.2 << 6 << 7;
    *set5 << 4 << 7 << 8.2 << 9 << 10;

    set0->setBrush(QBrush(QColor(Qt::yellow)));

    //set0->setColor(QColor(Qt::darkRed));
//![1]

//![2]
    QBoxPlotSeries *series = new QBoxPlotSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);
    series->type();
    series->setName("Box & Whiskers");
    //series->setBrush(QBrush(QColor(Qt::yellow)));
//![2]

//![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple boxplotchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
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

