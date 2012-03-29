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

#include "qpercentbarseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QPercentBarSeries
    \brief part of QtCommercial chart API.

    QPercentBarSeries represents a series of data shown as bars. Each bar of QBarSet is shown as percentage
    of all bars in category. One QPercentBarSeries can contain multible QBarSet data sets.
    QBarSeries groups the data from sets to categories, which are defined by QStringList.

    \mainclass

    \sa QBarSet, QStackedBarSeries, QBarSeries
*/

/*!
    \fn virtual QSeriesType QPercentBarSeries::type() const
    \brief Returns type of series.
    \sa QSeries, QSeriesType
*/

/*!
    Constructs empty QPercentBarSeries. Parameter \a categories defines the categories for chart.
    QPercentBarSeries is QObject which is a child of a \a parent.
*/
QPercentBarSeries::QPercentBarSeries(QStringList categories, QObject *parent)
    : QBarSeries(categories, parent)
{
}

#include "moc_qpercentbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

