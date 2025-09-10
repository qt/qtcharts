// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "declarativexypoint_p.h"
#include <QtCore/QDataStream>

QT_BEGIN_NAMESPACE

/*!
    \qmltype XYPoint
    \inqmlmodule QtCharts

    \brief Initializes XY-series coordinate data.

    The XYPoint type is a convenience type for initializing line, spline, and
    scatter series with static coordinate data. To manipulate a series
    dynamically, use the data manipulation functions it inherits from the
    XYSeries type, instead.
    \sa XYSeries, LineSeries, AreaSeries, ScatterSeries, SplineSeries
*/

/*!
    \qmlproperty real XYPoint::x
    The x-coordinate of the point.
*/

/*!
    \qmlproperty real XYPoint::y
    The y-coordinate of the point.
*/

DeclarativeXYPoint::DeclarativeXYPoint(QObject *parent) :
    QObject(parent)
{
    setX(0.0);
    setY(0.0);
}

QT_END_NAMESPACE

#include "moc_declarativexypoint_p.cpp"
