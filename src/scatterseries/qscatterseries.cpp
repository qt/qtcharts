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

#include "qscatterseries.h"
#include "qchart.h"

/*!
    \class QScatterSeries
    \brief The QScatterSeries class is used for making scatter charts.

    \mainclass

    The scatter data is displayed as a collection of points on the chart. Each point determines the position on the horizontal axis
    and the vertical axis.

    \image scatterchart.png

    Creating basic scatter chart is simple:
    \code
    QScatterSeries* series = new QScatterSeries();
    series->append(0, 6);
    series->append(2, 4);
    ...
    chartView->addSeries(series);
    \endcode
*/

/*!
    \enum QScatterSeries::MarkerShape

    This enum describes the shape used when rendering marker items.

    \value MarkerShapeCircle
    \value MarkerShapeRectangle
*/

/*!
    \fn QChartSeriesType QScatterSeries::type() const
    \brief Returns QChartSeries::SeriesTypeScatter.
    \sa QSeries, QSeriesType
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs a series object which is a child of \a parent.
*/
QScatterSeries::QScatterSeries(QObject *parent) :
    QXYSeries(parent),
    m_shape(QScatterSeries::MarkerShapeCircle),
    m_size(15.0)
{
}

/*!
    Destroys the object. Note that adding series to QChart transfers the ownership to the chart.
*/
QScatterSeries::~QScatterSeries()
{
}

/*!
    Returns the shape used for drawing markers.
*/
QScatterSeries::MarkerShape QScatterSeries::shape() const
{
    return m_shape;
}

/*!
    Overrides the default shape of the marker items with a user defined \a shape. The default shape
    is defined by chart theme setting.
*/
void QScatterSeries::setShape(MarkerShape shape)
{
    if (m_shape != shape) {
        m_shape = shape;
        emit QXYSeries::updated();
    }
}

/*!
    Returns the size of the marker items.
*/
qreal QScatterSeries::size() const
{
    return m_size;
}

/*!
    Set the \a size of the marker items. The default size is 9.0.
*/
void QScatterSeries::setSize(qreal size)
{
    if (!qFuzzyIsNull(m_size - size)) {
        m_size = size;
        emit updated();
    }
}

QTCOMMERCIALCHART_END_NAMESPACE
