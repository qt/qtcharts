/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
