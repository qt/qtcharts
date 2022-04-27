/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include <QtCharts/QPercentBarSeries>
#include <private/qpercentbarseries_p.h>
#include <private/percentbarchartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE

/*!
    \class QPercentBarSeries
    \inmodule QtCharts
    \brief The QPercentBarSeries class presents a series of categorized data as
    a percentage of each category.

    This class draws data as a series of uniformly sized vertically stacked bars, with one
    bar per category. Each bar set added to the series contributes a single segment to each
    stacked bar. The segment size corresponds to the percentage of the segment value compared
    with the total value of all segments in the stack.
    Bars with zero value are not drawn.

    See the \l {PercentbarChart Example} {percent bar chart example} to learn how to create a
    percent bar chart.
    \image examples_percentbarchart.png

    \sa QBarSet, QStackedBarSeries, QAbstractBarSeries
*/
/*!
    \qmltype PercentBarSeries
    \instantiates QPercentBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Presents a series of categorized data as a percentage of each category.

    The data is drawn as a series of uniformly sized vertically stacked bars, with one
    bar per category. Each bar set added to the series contributes a single segment to each
    stacked bar. The segment size corresponds to the percentage of the segment value compared
    with the total value of all segments in the stack.
    Bars with zero value are not drawn.

    The following QML code snippet shows how to create a simple percent bar chart:
    \snippet qmlchart/qml/qmlchart/View8.qml 1
    \beginfloatleft
    \image examples_qmlchart8.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs an empty vertical percent bar series that is a QObject and a child of \a parent.
*/
QPercentBarSeries::QPercentBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QPercentBarSeriesPrivate(this), parent)
{
}

/*!
    Removes the bar series from the chart.
*/
QPercentBarSeries::~QPercentBarSeries()
{
    Q_D(QPercentBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Returns the vertical percent bar series.
*/
QAbstractSeries::SeriesType QPercentBarSeries::type() const
{
    return QAbstractSeries::SeriesTypePercentBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPercentBarSeriesPrivate::QPercentBarSeriesPrivate(QPercentBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QPercentBarSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal x = categoryCount();
    minX = qMin(minX, - (qreal)0.5);
    maxX = qMax(maxX, x - (qreal)0.5);
    minY = 0;
    maxY = 100;

    domain()->setRange(minX, maxX, minY, maxY);
}


void QPercentBarSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QPercentBarSeries);
    PercentBarChartItem *bar = new PercentBarChartItem(q,parent);
    m_item.reset(bar);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

QT_END_NAMESPACE

#include "moc_qpercentbarseries.cpp"
