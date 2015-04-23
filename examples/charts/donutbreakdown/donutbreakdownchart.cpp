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
#include "donutbreakdownchart.h"
#include "mainslice.h"
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieLegendMarker>

QT_CHARTS_USE_NAMESPACE

//![1]
DonutBreakdownChart::DonutBreakdownChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
    // create the series for main center pie
    m_mainSeries = new QPieSeries();
    m_mainSeries->setPieSize(0.7);
    QChart::addSeries(m_mainSeries);
}
//![1]

//![2]
void DonutBreakdownChart::addBreakdownSeries(QPieSeries *breakdownSeries, QColor color)
{
    QFont font("Arial", 8);

    // add breakdown series as a slice to center pie
    MainSlice *mainSlice = new MainSlice(breakdownSeries);
    mainSlice->setName(breakdownSeries->name());
    mainSlice->setValue(breakdownSeries->sum());
    m_mainSeries->append(mainSlice);

    // customize the slice
    mainSlice->setBrush(color);
    mainSlice->setLabelVisible();
    mainSlice->setLabelColor(Qt::white);
    mainSlice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
    mainSlice->setLabelFont(font);

    // position and customize the breakdown series
    breakdownSeries->setPieSize(0.8);
    breakdownSeries->setHoleSize(0.7);
    breakdownSeries->setLabelsVisible();
    foreach (QPieSlice *slice, breakdownSeries->slices()) {
        color = color.lighter(115);
        slice->setBrush(color);
        slice->setLabelFont(font);
    }

    // add the series to the chart
    QChart::addSeries(breakdownSeries);

    // recalculate breakdown donut segments
    recalculateAngles();

    // update customize legend markers
    updateLegendMarkers();
}
//![2]

//![3]
void DonutBreakdownChart::recalculateAngles()
{
    qreal angle = 0;
    foreach (QPieSlice *slice, m_mainSeries->slices()) {
        QPieSeries *breakdownSeries = qobject_cast<MainSlice *>(slice)->breakdownSeries();
        breakdownSeries->setPieStartAngle(angle);
        angle += slice->percentage() * 360.0; // full pie is 360.0
        breakdownSeries->setPieEndAngle(angle);
    }
}
//![3]

//![4]
void DonutBreakdownChart::updateLegendMarkers()
{
    // go through all markers
    foreach (QAbstractSeries *series, series()) {
        foreach (QLegendMarker *marker, legend()->markers(series)) {
            QPieLegendMarker *pieMarker = qobject_cast<QPieLegendMarker *>(marker);
            if (series == m_mainSeries) {
                // hide markers from main series
                pieMarker->setVisible(false);
            } else {
                // modify markers from breakdown series
                pieMarker->setLabel(QString("%1 %2%")
                                    .arg(pieMarker->slice()->label())
                                    .arg(pieMarker->slice()->percentage() * 100, 0, 'f', 2));
                pieMarker->setFont(QFont("Arial", 8));
            }
        }
    }
}
//![4]
