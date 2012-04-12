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
    *series << QPointF(0, 6) << QPointF(2, 4) << QPointF(3, 8) << QPointF(7, 4) << QPointF(10,5);
    QChart* chart = new QChart();
    chart->addSeries(series);
//![1]

//![2]
    // Customize series
    QPen pen(QRgb(0xfdb157));
    pen.setWidth(5);
    series->setPen(pen);

    // Customize chart title
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitle("Customchart example");

    // Customize chart background
    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0,0));
    backgroundGradient.setFinalStop(QPointF(0,1));
    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
    backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setBackgroundBrush(backgroundGradient);
//![2]

//![3]
    QAxis* axisX = chart->axisX();
    QAxis* axisY = chart->axisY();

    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis colors
    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(2);
    axisX->setAxisPen(axisPen);
    axisY->setAxisPen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(Qt::white);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    // Customize grid lines and shades
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);
    axisY->setShadesPen(Qt::NoPen);
    axisY->setShadesBrush(QBrush(QRgb(0xa5a2a3)));
    axisY->setShadesVisible(true);
//![3]

//![4]
    QChartAxisCategories* categoriesX = chart->axisX()->categories();
    categoriesX->insert(1,"low");
    categoriesX->insert(5,"optimal");
    categoriesX->insert(10,"high");

    QChartAxisCategories* categoriesY = chart->axisY()->categories();
    categoriesY->insert(1,"slow");
    categoriesY->insert(5,"med");
    categoriesY->insert(10,"fast");

    axisX->setRange(0,10);
    axisX->setTicksCount(4);
    axisY->setRange(0,10);
    axisY->setTicksCount(4);
//![4]

//![5]
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![5]

//![6]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//![6]

    return a.exec();
}
