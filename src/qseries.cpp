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

#include "qseries.h"

/*!
    \class QSeries
    \brief Base class for all QtCommercial Chart series.
    \mainclass

    Usually you use the series type specific inherited classes instead of the base class.
    \sa QScatterSeries
*/

/*!
    \enum QSeries::QSeriesType

    The type of the series object.

    \value SeriesTypeLine
    \value SeriesTypeArea
    \value SeriesTypeBar
    \value SeriesTypeStackedBar
    \value SeriesTypePercentBar
    \value SeriesTypePie
    \value SeriesTypeScatter
    \value SeriesTypeSpline
*/

/*!
    \fn QSeries::QSeries(QObject *parent)
    \brief Constructs ChartSeries object with \a parent.
*/

/*!
    \fn QSeries::~QSeries()
    \brief Virtual destructor for the chart series.
*/

/*!
    \fn QSeriesType QSeries::type() const
    \brief The type of the series.
*/

/*!
    \fn bool QSeries::setModel(QAbstractItemModel *model)
    \brief Use the \a model to provide data for the series. The model overrides possible user data
    set with QChartSeries type specific data setters. For example if you call both
    QScatterSeries::addData() and QScatterSeries::setModel, only the data provided by the model is
    used by the series. Returns true if the model is valid for the series.
*/

/*!
    \fn void QSeries::setName(QString name)
    \brief Sets a \a name for the series.

    The name of a series is shown in the legend for QXYSeries.
    \sa QChart::setTitle()
    \sa QPieSlice::setName()
    \sa QBarSet::setName()
*/

/*!
    \fn QString QSeries::name()
    \brief Returns the name of the series.
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE
#include "moc_qseries.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
