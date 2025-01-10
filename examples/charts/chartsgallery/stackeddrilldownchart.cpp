// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "stackeddrilldownchart.h"

#include <QBarCategoryAxis>
#include <QValueAxis>

StackedDrilldownChart::StackedDrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      m_axisX(new QBarCategoryAxis),
      m_axisY(new QValueAxis)
{
    addAxis(m_axisY, Qt::AlignLeft);
    addAxis(m_axisX, Qt::AlignBottom);
}

void StackedDrilldownChart::changeSeries(StackedDrilldownSeries *series)
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

void StackedDrilldownChart::handleClicked(int index, QBarSet *)
{
    auto series = static_cast<StackedDrilldownSeries *>(sender());
    changeSeries(series->drilldownSeries(index));
}
