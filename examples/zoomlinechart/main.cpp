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

#include "chart.h"
#include "chartview.h"
#include <QApplication>
#include <QMainWindow>
#include <QLineSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QLineSeries* series = new QLineSeries();
    series->setName("line");
    qreal yValue = 0.0;
    for (int i(0); i < 500; i++) {
        yValue = yValue + (qreal) (qrand() % 10) / 500.0;
        QPointF value((i + (qreal) rand() / (qreal) RAND_MAX) * (10.0 / 500.0), yValue);
        *series << value;
    }
//![1]

    Chart* chart = new Chart();
    chart->addSeries(series);
    chart->setTitle("Zoom in/out example");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    ChartView* chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.grabGesture(Qt::PanGesture);
    window.grabGesture(Qt::PinchGesture);
    window.show();

    return a.exec();
}
