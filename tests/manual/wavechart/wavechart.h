/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef WAVECHART_H
#define WAVECHART_H

#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtCore/QObject>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

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
