/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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
#include <QBoxSet>
#include <QLegend>
#include <QBarCategoryAxis>

#include "boxdatareader.h"

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! [1]
    QBoxPlotSeries *acmeSeries = new QBoxPlotSeries();
    acmeSeries->setName("Acme Ltd");

    QBoxPlotSeries *boxWhiskSeries = new QBoxPlotSeries();
    boxWhiskSeries->setName("BoxWhisk Inc");
    //! [1]

    //! [2]
    QFile acmeData(":acme");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    BoxDataReader dataReader(&acmeData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set)
            acmeSeries->append(set);
    }
    //! [2]

    //! [3]
    QFile boxwhiskData(":boxwhisk");
    if (!boxwhiskData.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    dataReader.readFile(&boxwhiskData);
    while (!dataReader.atEnd()) {
        QBoxSet *set = dataReader.readBox();
        if (set)
            boxWhiskSeries->append(set);
    }
    //! [3]

    //! [4]
    QChart *chart = new QChart();
    chart->addSeries(acmeSeries);
    chart->addSeries(boxWhiskSeries);
    chart->setTitle("Acme Ltd and BoxWhisk Inc share deviation in 2012");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //! [4]

    //! [5]
    chart->createDefaultAxes();
    chart->axisY()->setMin(15.0);
    chart->axisY()->setMax(34.0);
    //! [5]

    //! [6]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //! [6]

    //! [7]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //! [7]

    //! [8]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();
    //! [8]

    return a.exec();
}

