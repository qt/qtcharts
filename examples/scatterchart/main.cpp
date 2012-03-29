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

#include <QtGui/QApplication>
#include <QMainWindow>
#include <QChartView>
#include <QScatterSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//![1]
    QPen pen(Qt::black);
    pen.setWidth(2);
    QBrush blue(Qt::blue);
    QBrush red(Qt::red);

    QScatterSeries *series0 = new QScatterSeries();
    series0->setPen(pen);
    series0->setBrush(blue);
    series0->setShape(QScatterSeries::MarkerShapeCircle);
    series0->setSize(15.0);

    QScatterSeries *series1 = new QScatterSeries();
    series1->setPen(pen);
    series1->setBrush(red);
    series1->setShape(QScatterSeries::MarkerShapeCircle);
    series1->setSize(15.0);
//![1]

//![2]
    series0->add(0, 6);
    series0->add(2, 4);
    series0->add(3, 8);
    series0->add(7, 4);
    series0->add(10, 5);

    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10, 2);
//![2]
//![3]
    QChart* chart = new QChart();

    chart->addSeries(series0);
    chart->addSeries(series1);
    chart->setTitle("Simple scatterchart example");
//![3]
//![4]
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![4]
//![5]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//![5]
    return a.exec();
}
