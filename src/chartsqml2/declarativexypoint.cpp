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
