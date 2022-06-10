// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "wavechart.h"
#include <qmath.h>
#include <qrandom.h>

QT_USE_NAMESPACE

static const int numPoints =100;

WaveChart::WaveChart(QChart* chart, QWidget* parent) :
    QChartView(chart, parent),
    m_series(new QLineSeries()),
    m_wave(0),
    m_step(2 * M_PI / numPoints)
{
    QPen blue(Qt::blue);
    blue.setWidth(3);
    m_series->setPen(blue);

    chart->legend()->setVisible(false);

    int fluctuate = 100;

    for (qreal x = 0; x <= 2 * M_PI; x += m_step) {
        m_series->append(x, fabs(sin(x) * fluctuate));
    }

    chart->addSeries(m_series);
    chart->createDefaultAxes();

    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.setInterval(5000);
    m_timer.start();
}

void WaveChart::update()
{

    int fluctuate;
    const QList<QPointF>& points = m_series->points();
    for (qreal i = 0, x = 0; x <= 2 * M_PI; x += m_step, i++) {
        fluctuate = QRandomGenerator::global()->bounded(100);
        m_series->replace(x,points[i].y(),x,fabs(sin(x) * fluctuate));

    }

}
