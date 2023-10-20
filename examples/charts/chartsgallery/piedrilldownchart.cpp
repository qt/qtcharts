// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "piedrilldownchart.h"
#include "piedrilldownslice.h"

PieDrilldownChart::PieDrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
}

void PieDrilldownChart::changeSeries(QAbstractSeries *series)
{
    if (m_currentSeries)
        removeSeries(m_currentSeries);
    m_currentSeries = series;
    addSeries(series);
    setTitle(series->name());
}

void PieDrilldownChart::handleSliceClicked(QPieSlice *slice)
{
    auto *drilldownSlice = static_cast<PieDrilldownSlice *>(slice);
    changeSeries(drilldownSlice->drilldownSeries());
}
