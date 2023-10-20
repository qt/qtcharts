// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "dynamicsplinewidget.h"

#include <QChart>
#include <QChartView>
#include <QRandomGenerator>
#include <QSplineSeries>
#include <QValueAxis>

DynamicSplineWidget::DynamicSplineWidget(QWidget *parent)
    : ContentWidget(parent)
{
    auto chart = new QChart;
    chart->setTitle("Dynamic Spline Chart");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);

    m_axisX = new QValueAxis;
    m_axisY = new QValueAxis;

    QObject::connect(&m_timer, &QTimer::timeout, this, &DynamicSplineWidget::handleTimeout);
    m_timer.setInterval(1000);

    m_series = new QSplineSeries;
    QPen green(Qt::red);
    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x, m_y);

    chart->addSeries(m_series);

    chart->addAxis(m_axisX,Qt::AlignBottom);
    chart->addAxis(m_axisY,Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
    m_axisX->setTickCount(5);
    m_axisX->setRange(0, 10);
    m_axisY->setRange(-5, 10);

    createDefaultChartView(chart);

    m_timer.start();
}

void DynamicSplineWidget::handleTimeout()
{
    qreal x = defaultChartView()->chart()->plotArea().width() / m_axisX->tickCount();
    qreal y = (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount();
    m_x += y;
    m_y = QRandomGenerator::global()->bounded(5) - 2.5;
    m_series->append(m_x, m_y);
    defaultChartView()->chart()->scroll(x, 0);
    if (m_x >= 100)
        m_timer.stop();
}
