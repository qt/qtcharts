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

#include "qstackedbarseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QStackedBarSeries
    \brief part of QtCommercial chart API.

    QStackedBarSeries represents a series of data shown as bars. All bars in same category are
    stacked on top of each other. One QStackedBarSeries can contain multible QBarSet data sets.
    QStackedBarSeries groups the data from sets to categories, which are defined by QStringList.

    \mainclass

    \sa QBarSet, QPercentBarSeries, QBarSeries
*/

/*!
    \fn virtual QSeriesType QStackedBarSeries::type() const
    \brief Returns type of series.
    \sa QSeries, QSeriesType
*/

/*!
    Constructs empty QStackedBarSeries. Parameter \a categories defines the categories for chart.
    QStackedBarSeries is QObject which is a child of a \a parent.
*/
QStackedBarSeries::QStackedBarSeries(QStringList categories, QObject *parent)
    : QBarSeries(categories, parent)
{
}

#include "moc_qstackedbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

