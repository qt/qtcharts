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
    \property QAbstractSeries::name
    \brief name of the series property
*/

/*!
    \fn void QAbstractSeries::nameChanged()

    This signal is emitted when the series name changes.

    \sa name
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
    if (name != d_ptr->m_name) {
        d_ptr->m_name = name;
        emit nameChanged();
    }
}

/*!
    \brief Returns the name of the series.
    \sa setName()
*/
QString QAbstractSeries::name() const
{
    return d_ptr->m_name;
}

/*!
    Sets the visibility of series to \a visible
*/
void QAbstractSeries::setVisible(bool visible)
{
    if (visible != d_ptr->m_visible) {
        d_ptr->m_visible = visible;
        emit visibleChanged();
    }
}

/*!
    Returns the visibility of series
*/
bool QAbstractSeries::isVisible() const
{
    return d_ptr->m_visible;
}

/*!
    \brief Returns the chart where series belongs to.

    Set automatically when the series is added to the chart
    and unset when the series is removed from the chart.
*/
QChart* QAbstractSeries::chart() const
{
    return d_ptr->m_chart;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

QAbstractSeriesPrivate::QAbstractSeriesPrivate(QAbstractSeries* q):
    q_ptr(q),
    m_chart(0),
    m_dataset(0),
    m_visible(true)
{
}

QAbstractSeriesPrivate::~QAbstractSeriesPrivate()
{
}

#include "moc_qabstractseries.cpp"
#include "moc_qabstractseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE


