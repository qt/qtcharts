/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include "declarativexypoint.h"
#include <QtCore/QDataStream>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \qmltype XYPoint
    \inqmlmodule QtCharts

    \brief Type is used to initialize XY-series coordinate data.

    XYPoint is a convenience element for initializing XY-series with static coordinate data. To
    manipulate an XY-series dynamically, use it's data manipulation functions instead.
    \sa LineSeries, AreaSeries, ScatterSeries, SplineSeries
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

#include "moc_declarativexypoint.cpp"

QT_CHARTS_END_NAMESPACE
