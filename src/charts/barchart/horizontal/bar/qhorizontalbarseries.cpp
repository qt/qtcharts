// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QHorizontalBarSeries>
#include <private/qhorizontalbarseries_p.h>
#include <private/horizontalbarchartitem_p.h>
#include <QtCharts/QBarCategoryAxis>

#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>


QT_BEGIN_NAMESPACE

/*!
    \class QHorizontalBarSeries
    \inmodule QtCharts
    \brief The QHorizontalBarSeries class presents a series of data as horizontal bars grouped by
    category.

    This class draws data as a series of horizontal bars grouped by category, with one bar per
    category from each bar set added to the series.

    See the \l {Charts with Widgets Gallery} to learn how to create a horizontal bar chart.
    \image examples_horizontalbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries, QHorizontalStackedBarSeries, QHorizontalPercentBarSeries
*/
/*!
    \qmltype HorizontalBarSeries
    \instantiates QHorizontalBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Presents a series of data as horizontal bars grouped by category.

    The data is drawn as a series of horizontal bars grouped by category, with one bar per
    category from each bar set added to the series.

    The following QML code snippet shows how to create a simple horizontal bar chart:
    \snippet qmlchartsgallery/qml/BarSeriesHorizontal.qml 1
    \beginfloatleft
    \image examples_qmlchart9.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs an empty horizontal bar series that is a QObject and a child of \a parent.
*/
QHorizontalBarSeries::QHorizontalBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QHorizontalBarSeriesPrivate(this), parent)
{
}

/*!
    Removes the horizontal bar series from the chart.
*/
QHorizontalBarSeries::~QHorizontalBarSeries()
{
    Q_D(QHorizontalBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Returns the horizontal bar series.
*/
QAbstractSeries::SeriesType QHorizontalBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeHorizontalBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QHorizontalBarSeriesPrivate::QHorizontalBarSeriesPrivate(QHorizontalBarSeries *q)
    : QAbstractBarSeriesPrivate(q)
{

}

void QHorizontalBarSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal y = categoryCount();
    minX = qMin(minX, min());
    minY = qMin(minY, - (qreal)0.5);
    maxX = qMax(maxX, max());
    maxY = qMax(maxY, y - (qreal)0.5);

    domain()->setRange(minX, maxX, minY, maxY);
}

void QHorizontalBarSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QHorizontalBarSeries);
    HorizontalBarChartItem *bar = new HorizontalBarChartItem(q,parent);
    m_item.reset(bar);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

QT_END_NAMESPACE

#include "moc_qhorizontalbarseries.cpp"
