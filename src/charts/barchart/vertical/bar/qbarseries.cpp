// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QBarSeries>
#include <private/qbarseries_p.h>
#include <private/barchartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

QT_BEGIN_NAMESPACE

/*!
    \class QBarSeries
    \inmodule QtCharts
    \brief The QBarSeries class presents a series of data as vertical bars grouped by category.

    This class draws data as a series of vertical bars grouped by category, with one bar per
    category from each bar set added to the series.

    See the \l {Creating Bar Charts} {bar chart example} to learn how to create
    a grouped bar chart.
    \image examples_barchart.png

    \sa QBarSet, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries
*/
/*!
    \qmltype BarSeries
    \nativetype QBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Presents a series of data as vertical bars grouped by category.

    The data is drawn as a series of vertical bars grouped by category, with one bar per
    category from each bar set added to the series.

    The following QML code snippet shows how to create a simple grouped bar
    chart:
    \snippet qmlchartsgallery/qml/BarSeries.qml 1
    \image examples_qmlchart6.png
*/

/*!
    Constructs an empty bar series that is a QObject and a child of \a parent.
*/
QBarSeries::QBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QBarSeriesPrivate(this), parent)
{

}

/*!
    Returns the bar series.
*/
QAbstractSeries::SeriesType QBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeBar;
}

/*!
    Removes the bar series from the chart.
*/
QBarSeries::~QBarSeries()
{
    Q_D(QBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarSeriesPrivate::QBarSeriesPrivate(QBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QBarSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal x = categoryCount();
    minX = qMin(minX, - (qreal)0.5);
    minY = qMin(minY, min());
    maxX = qMax(maxX, x - (qreal)0.5);
    maxY = qMax(maxY, max());

    domain()->setRange(minX, maxX, minY, maxY);
}


void QBarSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QBarSeries);
    BarChartItem *bar = new BarChartItem(q,parent);
    m_item.reset(bar);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

QT_END_NAMESPACE

#include "moc_qbarseries.cpp"
