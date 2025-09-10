// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#include <QtCharts/QHorizontalPercentBarSeries>
#include <private/qhorizontalpercentbarseries_p.h>
#include <private/horizontalpercentbarchartitem_p.h>

#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>

QT_BEGIN_NAMESPACE

/*!
    \class QHorizontalPercentBarSeries
    \inmodule QtCharts
    \brief The QHorizontalPercentBarSeries class presents a series of categorized data as
    a percentage of each category.

    This class draws data as a series of uniformly sized horizontally stacked bars, with one
    bar per category. Each bar set added to the series contributes a single segment to each
    stacked bar. The segment size corresponds to the percentage of the segment value compared
    with the total value of all segments in the stack.
    Bars with zero value are not drawn.

    See the \l {Charts with Widgets Gallery} to learn
    how to create a horizontal percent bar chart.
    \image examples_horizontalpercentbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries,
    QHorizontalStackedBarSeries, QHorizontalBarSeries
*/
/*!
    \qmltype HorizontalPercentBarSeries
    \nativetype QHorizontalPercentBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Presents a series of categorized data as a percentage of each category.

    The data is drawn as a series of uniformly sized horizontally stacked bars, with one
    bar per category. Each bar set added to the series contributes a single segment to each
    stacked bar. The segment size corresponds to the percentage of the segment value compared
    with the total value of all segments in the stack.
    Bars with zero value are not drawn.

    The following QML code snippet shows how to create a simple horizontal percent bar chart:
    \snippet qmlchartsgallery/qml/BarSeriesPercentHorizontal.qml 1
    \beginfloatleft
    \image examples_qmlchart11.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs an empty horizontal percent bar series that is a QObject and a child of \a parent.
*/
QHorizontalPercentBarSeries::QHorizontalPercentBarSeries(QObject *parent) :
    QAbstractBarSeries(*new QHorizontalPercentBarSeriesPrivate(this), parent)
{
}

/*!
    Returns the horizontal percent bar series.
*/
QAbstractSeries::SeriesType QHorizontalPercentBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeHorizontalPercentBar;
}

/*!
    Removes the bar series from the chart.

*/
QHorizontalPercentBarSeries::~QHorizontalPercentBarSeries()
{
    Q_D(QHorizontalPercentBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QHorizontalPercentBarSeriesPrivate::QHorizontalPercentBarSeriesPrivate(QHorizontalPercentBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QHorizontalPercentBarSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal y = categoryCount();
    minX = 0;
    maxX = 100;
    minY = qMin(minY, - (qreal)0.5);
    maxY = qMax(maxY, y - (qreal)0.5);

    domain()->setRange(minX, maxX, minY, maxY);
}

void QHorizontalPercentBarSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QHorizontalPercentBarSeries);
    HorizontalPercentBarChartItem *bar = new HorizontalPercentBarChartItem(q,parent);
    m_item.reset(bar);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

QT_END_NAMESPACE

#include "moc_qhorizontalpercentbarseries.cpp"
