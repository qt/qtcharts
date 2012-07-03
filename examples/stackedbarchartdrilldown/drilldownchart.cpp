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
#include <QCategoriesAxis>

QTCOMMERCIALCHART_USE_NAMESPACE

DrilldownChart::DrilldownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(parent, wFlags)
    ,m_currentSeries(0)
{
}

void DrilldownChart::changeSeries(DrilldownBarSeries *series)
{
    if (m_currentSeries) {
        removeSeries(m_currentSeries);
    }

    m_currentSeries = series;

    // Reset axis
    QCategoriesAxis* axis = new QCategoriesAxis();
    axis->append(m_currentSeries->categories());

    addSeries(series);

    createDefaultAxes();
    setAxisX(axis,series);

    setTitle(series->name());
}

void DrilldownChart::handleClicked(int index, QBarSet *barset)
{
    Q_UNUSED(barset)
    DrilldownBarSeries* series = static_cast<DrilldownBarSeries*> (sender());
    changeSeries(series->drilldownSeries(index));
}

#include "moc_drilldownchart.cpp"
