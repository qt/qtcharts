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

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QLineSeries* series = new QLineSeries();
    QPen blue(Qt::yellow);
    blue.setWidth(3);
    series->setPen(blue);
//![1]
//![2]
    *series << QPointF(0, 6) << QPointF(2, 4) << QPointF(3, 8) << QPointF(7, 4) << QPointF(10,5);
//![2]
//![3]
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple customchart example");
//![3]
//![4]
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(Qt::yellow);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0,0));
    backgroundGradient.setFinalStop(QPointF(0,1));
    backgroundGradient.setColorAt(0.0, 0x3cc63c);
    backgroundGradient.setColorAt(1.0, 0x26f626);
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setBackgroundBrush(backgroundGradient);
//![4]
//![5]
    QPen black(Qt::black);
    QChartAxis* axisX = chart->axisX();
    QChartAxis* axisY = chart->axisY();

    axisX->setAxisPen(black);
    axisY->setAxisPen(black);
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);

    axisY->setShadesPen(Qt::NoPen);
    axisY->setShadesOpacity(0.5);
    axisY->setShadesBrush(Qt::white);
    axisY->setShadesVisible(true);
//![5]
//![6]
    QChartAxisCategories* categoriesX = chart->axisX()->categories();
    categoriesX->insert(1,"low");
    categoriesX->insert(5,"optimal");
    categoriesX->insert(10,"high");

    QChartAxisCategories* categoriesY = chart->axisY()->categories();
    categoriesY->insert(1,"slow");
    categoriesY->insert(5,"med");
    categoriesY->insert(10,"fast");
//![6]
//![7]
    axisX->setRange(0,10);
    axisX->setTicksCount(4);
    axisY->setRange(0,10);
    axisY->setTicksCount(4);
//![7]
//![8]
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![8]
//![9]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//![9]
    return a.exec();
}
