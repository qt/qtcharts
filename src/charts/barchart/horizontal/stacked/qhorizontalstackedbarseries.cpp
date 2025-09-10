// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#include <QtCharts/QHorizontalStackedBarSeries>
#include <private/qhorizontalstackedbarseries_p.h>
#include <private/horizontalstackedbarchartitem_p.h>

#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>

QT_BEGIN_NAMESPACE
/*!
    \class QHorizontalStackedBarSeries
    \inmodule QtCharts
    \brief The QHorizontalStackedBarSeries class presents a series of data as horizontally
    stacked bars, with one bar per category.

    Each bar set added to the series contributes a single segment to each stacked bar.

    See the \l {Charts with Widgets Gallery} to learn how to create a horizontal stacked bar chart.
    \image examples_horizontalstackedbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries, QHorizontalPercentBarSeries, QHorizontalBarSeries
*/
/*!
    \qmltype HorizontalStackedBarSeries
    \nativetype QHorizontalStackedBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Presents a series of data as stacked horizontal bars, with one bar per category.

    Each bar set added to the series contributes a single segment to each stacked bar.

    The following QML code snippet shows how to create a simple horizontal stacked bar chart:
    \snippet qmlchartsgallery/qml/BarSeriesStackedHorizontal.qml 1
    \beginfloatleft
    \image examples_qmlchart10.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs an empty horizontal stacked bar series that is a QObject and a child of \a parent.
*/
QHorizontalStackedBarSeries::QHorizontalStackedBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QHorizontalStackedBarSeriesPrivate(this), parent)
{
}

/*!
    Removes the bar series from the chart.
*/
QHorizontalStackedBarSeries::~QHorizontalStackedBarSeries()
{
    Q_D(QHorizontalStackedBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Returns the horizontal stacked bar series.
*/
QAbstractSeries::SeriesType QHorizontalStackedBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeHorizontalStackedBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QHorizontalStackedBarSeriesPrivate::QHorizontalStackedBarSeriesPrivate(QHorizontalStackedBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QHorizontalStackedBarSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal y = categoryCount();
    minX = qMin(minX, bottom());
    minY = qMin(minY, - (qreal)0.5);
    maxX = qMax(maxX, top());
    maxY = qMax(maxY, y - (qreal)0.5);

    domain()->setRange(minX, maxX, minY, maxY);
}

void QHorizontalStackedBarSeriesPrivate::initializeGraphics(QGraphicsItem *parent)
{
    Q_Q(QHorizontalStackedBarSeries);
    HorizontalStackedBarChartItem *bar = new HorizontalStackedBarChartItem(q,parent);
    m_item.reset(bar);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

QT_END_NAMESPACE

#include "moc_qhorizontalstackedbarseries.cpp"
