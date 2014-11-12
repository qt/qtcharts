/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "wavechart.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtOpenGL/QGLWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    QChart *chart = new QChart();
    WaveChart *waveChart = new WaveChart(chart,&window);

    waveChart->setViewport( new QGLWidget() );
    waveChart->setRenderHint(QPainter::Antialiasing);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTitle("This is wave generator.");

    window.setCentralWidget(waveChart);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
