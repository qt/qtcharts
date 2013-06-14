/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "declarativepolarchart.h"
#include "qchart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \qmlclass PolarChartView DeclarativePolarChart

    PolarChartView element is the parent that is responsible for showing different chart series types
    in a polar chart.

    Polar charts support line, spline, area, and scatter series, and all axis types
    supported by those series.

    \note When setting ticks to an angular ValueAxis, keep in mind that the first and last tick
    are co-located at 0/360 degree angle.

    \note If the angular distance between two consecutive points in a series is more than 180 degrees,
    any line connecting the two points becomes meaningless, so choose the axis ranges accordingly
    when displaying line, spline, or area series.

    The following QML shows how to create a polar chart with two series:
    \snippet ../demos/qmlpolarchart/qml/qmlpolarchart/View1.qml 1

    \beginfloatleft
    \image demos_qmlpolarchart1.png
    \endfloat
    \clearfloat
*/

DeclarativePolarChart::DeclarativePolarChart(QDECLARATIVE_ITEM *parent)
    : DeclarativeChart(QChart::ChartTypePolar, parent)
{
}

DeclarativePolarChart::~DeclarativePolarChart()
{
}

#include "moc_declarativepolarchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
