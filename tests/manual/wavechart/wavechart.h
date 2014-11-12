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
