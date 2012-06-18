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

#include "declarativeareaseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \qmlclass AreaSeries QAreaSeries

    \section1 Example Usage

    \beginfloatleft
    \image demos_qmlchart4.png
    \endfloat
    \clearfloat

    The following QML shows how to create a simple area chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View4.qml 1
*/

DeclarativeAreaSeries::DeclarativeAreaSeries(QObject *parent) :
    QAreaSeries(parent)
{
}

void DeclarativeAreaSeries::setUpperSeries(DeclarativeLineSeries* series)
{
    QAreaSeries::setUpperSeries(series);
}

DeclarativeLineSeries* DeclarativeAreaSeries::upperSeries() const
{
    return qobject_cast<DeclarativeLineSeries *>(QAreaSeries::upperSeries());
}

void DeclarativeAreaSeries::setLowerSeries(DeclarativeLineSeries* series)
{
    QAreaSeries::setLowerSeries(series);
}

DeclarativeLineSeries* DeclarativeAreaSeries::lowerSeries() const
{
    return qobject_cast<DeclarativeLineSeries *>(QAreaSeries::lowerSeries());
}

#include "moc_declarativeareaseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
