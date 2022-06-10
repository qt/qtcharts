// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "chart.h"
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    Chart *chart = new Chart;
    chart->setTitle("Dynamic spline chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView chartView(chart);
    chartView.setRenderHint(QPainter::Antialiasing);
    window.setCentralWidget(&chartView);
    window.resize(400, 300);
    window.show();
    return a.exec();
}
