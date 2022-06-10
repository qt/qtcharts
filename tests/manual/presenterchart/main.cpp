// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "chartview.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    QChart *chart = new QChart();
    ChartView chartView(chart, &window);
    chartView.setRenderHint(QPainter::Antialiasing);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    window.setCentralWidget(&chartView);
    window.resize(400, 300);
    window.show();
    return a.exec();
}
