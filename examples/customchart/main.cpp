/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia nor the names of its contributors
**     may be used to endorse or promote products derived from this
**     software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
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
