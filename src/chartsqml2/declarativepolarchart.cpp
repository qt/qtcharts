/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include "declarativepolarchart_p.h"
#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \qmltype PolarChartView
    \inherits ChartView
    \instantiates DeclarativePolarChart
    \inqmlmodule QtCharts

    \brief Presents data in polar charts.

    Polar charts present data in a circular graph, where the placement of data
    is based on the angle and distance from the center of the graph, the
    \e pole.

    \image examples_qmlpolarchart1.png

    A polar chart is a specialization of the ChartView type. It supports line,
    spline, area, and scatter series, and all axis types supported by them. Each
    axis can be used either as a radial or an angular axis.

    The first and last tick mark on an angular ValueAxis are co-located at a
    0/360 degree angle.

    If the angular distance between two consecutive points in a series is more
    than 180 degrees, any direct line connecting the two points becomes
    meaningless, and will not be drawn. Instead, a line will be drawn to and
    from the center of the chart. Therefore, the axis ranges must be chosen
    accordingly when displaying line, spline, or area series.

    Polar charts draw all axes of the same orientation in the same position, so
    using multiple axes of the same orientation can be confusing, unless the
    extra axes are only used to customize the grid. For example, you can display
    a highlighted range with a secondary shaded CategoryAxis or provide
    unlabeled subticks with a secondary ValueAxis thas has hidden labels.

    The following QML code shows how to create a polar chart with a spline and
    scatter series and two value axes:
    \snippet qmlpolarchart/qml/qmlpolarchart/View1.qml 1
*/

DeclarativePolarChart::DeclarativePolarChart(QQuickItem *parent)
    : DeclarativeChart(QChart::ChartTypePolar, parent)
{
}

DeclarativePolarChart::~DeclarativePolarChart()
{
}

QT_CHARTS_END_NAMESPACE

#include "moc_declarativepolarchart_p.cpp"
