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
#include <QBarCategoriesAxis>
#include <QHorizontalBarSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QBarSet *male = new QBarSet("Male");
    QBarSet *female = new QBarSet("Female");

    // From wikipedia
    *male << -145596 << -149894 << -167327 << -164118 << -170710 << -169408 << -158395 << -176975 << -191803 << -191198 << -196815
          << -207826 << -145517 << -113204 << -90986 << -70909 << -40013 << -15887 << -5769;

    *female << 139353 << 143522 << 161212 << 156824 << 163226 << 161766 << 150595 << 170779 << 185979 << 187897 << 196158
            << 209062 << 152460 << 129230 << 114778 << 109611 << 83845 << 44605 << 22328;

//![1]

//![2]
    QHorizontalBarSeries *series = new QHorizontalBarSeries();
    series->append(male);
    series->append(female);
    series->setBarWidth(0.5);
    series->setGrouping(false);
//![2]

//![3]
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Population of Finland in 2005 by age group");
    chart->createDefaultAxes();
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    QStringList categories;
    categories << "0-4" << "5-9" << "10-14" << "15-19" << "20-24" << "25-29" << "30-34" << "35-39" << "40-44" << "45-49"
               << "50-54" << "55-59" << "60-64" << "65-69" << "70-74" << "75-79" << "80-84" << "85-89" << "90-";

    QBarCategoryAxis* axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->setAxisY(axis,series);
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
    window.resize(400, 800);
    window.show();
//![7]

    return a.exec();
}
