/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "wavechart.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QOpenGLWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    QChart *chart = new QChart();
    WaveChart *waveChart = new WaveChart(chart,&window);

    waveChart->setViewport( new QOpenGLWidget() );
    waveChart->setRenderHint(QPainter::Antialiasing);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTitle("This is wave generator.");

    window.setCentralWidget(waveChart);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
