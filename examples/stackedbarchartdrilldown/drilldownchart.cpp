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
#include <QChartAxis>

QTCOMMERCIALCHART_USE_NAMESPACE

DrilldownChart::DrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(parent, wFlags)
    ,m_currentSeries(0)
{
}

void DrilldownChart::changeSeries(QAbstractSeries *series)
{
    if (m_currentSeries)
        removeSeries(m_currentSeries);
    m_currentSeries = series;
    addSeries(series);
    setTitle(series->name());
    axisY()->setNiceNumbersEnabled(true);
}

void DrilldownChart::handleClicked(QBarSet *barset, QString category, Qt::MouseButtons button)
{
    Q_UNUSED(barset)
    Q_UNUSED(button)
    DrilldownBarSeries* series = static_cast<DrilldownBarSeries*> (sender());
    changeSeries(series->drilldownSeries(category));
}

#include "moc_drilldownchart.cpp"
