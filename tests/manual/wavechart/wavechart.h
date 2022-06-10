// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef WAVECHART_H
#define WAVECHART_H

#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtCore/QObject>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

QT_USE_NAMESPACE

class WaveChart: public QChartView
{
    Q_OBJECT

public:
    WaveChart(QChart* chart, QWidget* parent);

private slots:
    void update();

private:
    QLineSeries* m_series;
    int m_wave;
    qreal m_step;
    QTimer m_timer;
};

#endif
