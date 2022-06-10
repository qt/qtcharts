// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "wavechart.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtOpenGLWidgets/QOpenGLWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    QChart *chart = new QChart();
    WaveChart *waveChart = new WaveChart(chart,&window);

    waveChart->setViewport(new QOpenGLWidget());
    waveChart->setRenderHint(QPainter::Antialiasing);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTitle("This is wave generator.");

    window.setCentralWidget(waveChart);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
