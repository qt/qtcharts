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

#include "drilldownchart.h"
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

DrilldownChart::DrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      m_currentSeries(0)
{
}

void DrilldownChart::changeSeries(DrilldownBarSeries *series)
{
    if (m_currentSeries) {
        removeSeries(m_currentSeries);
    }

    m_currentSeries = series;

    // Reset axis
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(m_currentSeries->categories());

    addSeries(series);

    createDefaultAxes();
    setAxisX(axis, series);
    axisY()->setTitleText("Crops");

    setTitle(series->name());
}

void DrilldownChart::handleClicked(int index, QBarSet *barset)
{
    Q_UNUSED(barset)
    DrilldownBarSeries *series = static_cast<DrilldownBarSeries *>(sender());
    changeSeries(series->drilldownSeries(index));
}

#include "moc_drilldownchart.cpp"
