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

#include "qabstractseries.h"
#include "qabstractseries_p.h"
#include "chartdataset_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QAbstractSeries
    \brief Base class for all QtCommercial Chart series.
    \mainclass

    Usually you use the series type specific inherited classes instead of the base class.
    \sa QXYSeries, QLineSeries, QSplineSeries, QScatterSeries, QAreaSeries, QBarSeries, QStackedBarSeries,
    QPercentBarSeries, QPieSeries
*/

/*!
    \enum QAbstractSeries::SeriesType

    The type of the series object.

    \value SeriesTypeLine
    \value SeriesTypeArea
    \value SeriesTypeBar
    \value SeriesTypeStackedBar
    \value SeriesTypePercentBar
    \value SeriesTypeGroupedBar
    \value SeriesTypePie
    \value SeriesTypeScatter
    \value SeriesTypeSpline
*/

/*!
    \fn QSeriesType QAbstractSeries::type() const
    \brief The type of the series.
*/

/*!
    \fn bool QAbstractSeries::setModel(QAbstractItemModel *model)
    \brief Use the \a model to provide data for the series. The model overrides possible user data
    set with QChartSeries type specific data setters. For example if you call both
    QScatterSeries::addData() and QScatterSeries::setModel, only the data provided by the model is
    used by the series. Returns true if the model is valid for the series.
*/

/*!
    \property QAbstractSeries::name
    \brief name of the series property
*/

/*!
    \fn void QAbstractSeries::setName(const QString& name)
    \brief Sets a \a name for the series.

    The name of a series is shown in the legend for QXYSeries.
    \sa QChart::setTitle()
    \sa QPieSlice::setLabel()
    \sa QBarSet::setName()
*/

/*!
    \internal
    \brief Constructs ChartSeries object with \a parent.
*/
QAbstractSeries::QAbstractSeries(QAbstractSeriesPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

/*!
    \brief Virtual destructor for the chart series.
*/
QAbstractSeries::~QAbstractSeries()
{
    if(d_ptr->m_dataset) qFatal("Still binded series detected !");
}

void QAbstractSeries::setName(const QString& name)
{
    d_ptr->m_name = name;
}

/*!
    \brief Returns the name of the series.
    \sa setName()
*/
QString QAbstractSeries::name() const
{
    return d_ptr->m_name;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

QAbstractSeriesPrivate::QAbstractSeriesPrivate(QAbstractSeries* q):
    q_ptr(q),
    m_dataset(0)
{
}

QAbstractSeriesPrivate::~QAbstractSeriesPrivate()
{
}

#include "moc_qabstractseries.cpp"
#include "moc_qabstractseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE


