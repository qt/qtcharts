/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/
#include "drilldownchart.h"
#include "drilldownslice.h"

QTCOMMERCIALCHART_USE_NAMESPACE

DrilldownChart::DrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    :QChart(parent, wFlags),
    m_currentSeries(0)
{

}

DrilldownChart::~DrilldownChart()
{

}

void DrilldownChart::changeSeries(QSeries* series)
{
    // NOTE: if the series is owned by the chart it will be deleted
    // here the "window" owns the series...
    if (m_currentSeries)
        removeSeries(m_currentSeries);
    m_currentSeries = series;
    addSeries(series);
    setTitle(series->name());
}

void DrilldownChart::handleSliceClicked(QPieSlice* slice)
{
    DrilldownSlice* drilldownSlice = static_cast<DrilldownSlice*>(slice);
    changeSeries(drilldownSlice->drilldownSeries());
}

#include "moc_drilldownchart.cpp"
