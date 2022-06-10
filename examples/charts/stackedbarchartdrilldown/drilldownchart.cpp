// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "drilldownchart.h"
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_USE_NAMESPACE

DrilldownChart::DrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      m_currentSeries(0),
      m_axisX(new QBarCategoryAxis()),
      m_axisY(new QValueAxis())
{
      addAxis(m_axisY, Qt::AlignLeft);
      addAxis(m_axisX, Qt::AlignBottom);
}

void DrilldownChart::changeSeries(DrilldownBarSeries *series)
{
    if (m_currentSeries)
        removeSeries(m_currentSeries);

    m_currentSeries = series;

    // Reset axis
    m_axisX->setCategories(m_currentSeries->categories());
    addSeries(series);
    series->attachAxis(m_axisX);
    series->attachAxis(m_axisY);
    m_axisY->setRange(0,m_currentSeries->maxValue());
    setTitle(series->name());
}

void DrilldownChart::handleClicked(int index, QBarSet *barset)
{
    Q_UNUSED(barset);
    DrilldownBarSeries *series = static_cast<DrilldownBarSeries *>(sender());
    changeSeries(series->drilldownSeries(index));
}

#include "moc_drilldownchart.cpp"
