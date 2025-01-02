// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QStackedBarSeries>
#include <private/qstackedbarseries_p.h>
#include <private/stackedbarchartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE

/*!
    \class QStackedBarSeries
    \inmodule QtCharts
    \brief The QStackedBarSeries class presents a series of data as vertically stacked bars,
    with one bar per category.

    Each bar set added to the series contributes a single segment to each stacked bar.

    See the \l {Charts with Widgets Gallery} to learn how to create a stacked bar chart.
    \image examples_stackedbarchart.png

    \sa QBarSet, QPercentBarSeries, QAbstractBarSeries
*/

/*!
    \qmltype StackedBarSeries
    \instantiates QStackedBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Presents a series of data as vertically stacked bars, with one bar per category.

    Each bar set added to the series contributes a single segment to each stacked bar.

    The following QML shows how to create a simple stacked bar chart:
    \snippet qmlchartsgallery/qml/BarSeriesStacked.qml 1
    \beginfloatleft
    \image examples_qmlchart7.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs an empty bar series that is a QObject and a child of \a parent.
*/
QStackedBarSeries::QStackedBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QStackedBarSeriesPrivate(this), parent)
{
}

/*!
    Removes the bar series from the chart.
*/
QStackedBarSeries::~QStackedBarSeries()
{
    Q_D(QStackedBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}
/*!
    Returns the stacked bar series.
*/
QAbstractSeries::SeriesType QStackedBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeStackedBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QStackedBarSeriesPrivate::QStackedBarSeriesPrivate(QStackedBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QStackedBarSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal x = categoryCount();
    minX = qMin(minX, - (qreal)0.5);
    minY = qMin(minY, bottom());
    maxX = qMax(maxX, x - (qreal)0.5);
    maxY = qMax(maxY, top());

    domain()->setRange(minX, maxX, minY, maxY);
}

void QStackedBarSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QStackedBarSeries);
    StackedBarChartItem *bar = new StackedBarChartItem(q,parent);
    m_item.reset(bar);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

QT_END_NAMESPACE

#include "moc_qstackedbarseries.cpp"
