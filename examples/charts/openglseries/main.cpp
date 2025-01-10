// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "datasource.h"

#include <QApplication>
#include <QChartView>
#include <QLabel>
#include <QLineSeries>
#include <QLogValueAxis>
#include <QMainWindow>
#include <QScatterSeries>
#include <QValueAxis>

// Uncomment to use logarithmic axes instead of regular value axes
//#define USE_LOG_AXIS

// Uncomment to use regular series instead of OpenGL accelerated series
//#define DONT_USE_GL_SERIES

// Uncomment to add a simple regular series (thick line) and a matching OpenGL series (thinner line)
// to verify the series have same visible geometry.
//#define ADD_SIMPLE_SERIES

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList colors;
    colors << "red" << "blue" << "green" << "black";

    auto chart = new QChart;
    chart->legend()->hide();

#ifdef USE_LOG_AXIS
    auto axisX = new QLogValueAxis;
    auto axisY = new QLogValueAxis;
#else
    auto axisX = new QValueAxis;
    auto axisY = new QValueAxis;
#endif

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    const int seriesCount = 10;
#ifdef DONT_USE_GL_SERIES
    const int pointCount = 100;
    chart->setTitle("Unaccelerated Series");
#else
    const int pointCount = 10000;
    chart->setTitle("OpenGL Accelerated Series");
#endif

    QList<QXYSeries *> seriesList;
    for (int i = 0; i < seriesCount; i++) {
        QXYSeries *series = 0;
        int colorIndex = i % colors.size();
        if (i % 2) {
            series = new QScatterSeries;
            auto scatter = static_cast<QScatterSeries *>(series);
            scatter->setColor(QColor(colors.at(colorIndex)));
            scatter->setMarkerSize(qreal(colorIndex + 2) / 2.0);
            // Scatter pen doesn't have affect in OpenGL drawing, but if you disable OpenGL drawing
            // this makes the marker border visible and gives comparable marker size to OpenGL
            // scatter points.
            scatter->setPen(QPen("black"));
        } else {
            series = new QLineSeries;
            series->setPen(QPen(QBrush(QColor(colors.at(colorIndex))),
                                qreal(colorIndex + 2) / 2.0));
        }
        seriesList.append(series);
#ifdef DONT_USE_GL_SERIES
        series->setUseOpenGL(false);
#else
        //![1]
        series->setUseOpenGL(true);
        //![1]
#endif
        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    if (axisX->type() == QAbstractAxis::AxisTypeLogValue)
        axisX->setRange(0.1, 20.0);
    else
        axisX->setRange(0, 20.0);

    if (axisY->type() == QAbstractAxis::AxisTypeLogValue)
        axisY->setRange(0.1, 10.0);
    else
        axisY->setRange(0, 10.0);

#ifdef ADD_SIMPLE_SERIES
    QLineSeries *simpleRasterSeries = new QLineSeries;
    *simpleRasterSeries << QPointF(0.001, 0.001)
                 << QPointF(2.5, 8.0)
                 << QPointF(5.0, 4.0)
                 << QPointF(7.5, 9.0)
                 << QPointF(10.0, 0.001)
                 << QPointF(12.5, 2.0)
                 << QPointF(15.0, 1.0)
                 << QPointF(17.5, 6.0)
                 << QPointF(20.0, 10.0);
    simpleRasterSeries->setUseOpenGL(false);
    simpleRasterSeries->setPen(QPen(QBrush("magenta"), 8));
    chart->addSeries(simpleRasterSeries);
    simpleRasterSeries->attachAxis(axisX);
    simpleRasterSeries->attachAxis(axisY);

    QLineSeries *simpleGLSeries = new QLineSeries;
    simpleGLSeries->setUseOpenGL(true);
    simpleGLSeries->setPen(QPen(QBrush("black"), 2));
    simpleGLSeries->replace(simpleRasterSeries->points());
    chart->addSeries(simpleGLSeries);
    simpleGLSeries->attachAxis(axisX);
    simpleGLSeries->attachAxis(axisY);
#endif

    QChartView *chartView = new QChartView(chart);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(600, 400);
    window.show();

    DataSource dataSource;
    dataSource.generateData(seriesCount, 10, pointCount);

    auto fpsLabel = new QLabel(&window);
    auto countLabel = new QLabel(&window);
    QString countText = QStringLiteral("Total point count: %1");
    countLabel->setText(countText.arg(pointCount * seriesCount));
    countLabel->adjustSize();
    fpsLabel->move(10, 2);
    fpsLabel->adjustSize();
    fpsLabel->raise();
    fpsLabel->show();
    countLabel->move(10, fpsLabel->height());
    fpsLabel->raise();
    countLabel->show();

    // We can get more than one changed event per frame, so do async update.
    // This also allows the application to be responsive.
    QObject::connect(chart->scene(), &QGraphicsScene::changed,
                     &dataSource, &DataSource::handleSceneChanged);

    dataSource.startUpdates(seriesList, fpsLabel);

    return a.exec();
}
