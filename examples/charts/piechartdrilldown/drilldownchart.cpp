/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/
#include "drilldownchart.h"
#include "drilldownslice.h"

QT_CHARTS_USE_NAMESPACE

DrilldownChart::DrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      m_currentSeries(0)
{

}

DrilldownChart::~DrilldownChart()
{

}

void DrilldownChart::changeSeries(QAbstractSeries *series)
{
    // NOTE: if the series is owned by the chart it will be deleted
    // here the "window" owns the series...
    if (m_currentSeries)
        removeSeries(m_currentSeries);
    m_currentSeries = series;
    addSeries(series);
    setTitle(series->name());
}

void DrilldownChart::handleSliceClicked(QPieSlice *slice)
{
    DrilldownSlice *drilldownSlice = static_cast<DrilldownSlice *>(slice);
    changeSeries(drilldownSlice->drilldownSeries());
}

#include "moc_drilldownchart.cpp"
