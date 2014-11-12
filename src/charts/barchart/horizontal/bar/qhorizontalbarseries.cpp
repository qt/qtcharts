/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <QtCharts/QHorizontalBarSeries>
#include <private/qhorizontalbarseries_p.h>
#include <private/horizontalbarchartitem_p.h>
#include <QtCharts/QBarCategoryAxis>

#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>


QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QHorizontalBarSeries
    \inmodule Qt Charts
    \brief Series for creating horizontal bar chart.
    \mainclass

    QHorizontalBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as groups, where bars in same category are grouped next to each other. QHorizontalBarSeries groups the data
    from sets to categories, which are defined by a QStringList.

    See the \l {HorizontalBarChart Example} {horizontal bar chart example} to learn how to create a horizontal bar chart.
    \image examples_horizontalbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries, QHorizontalStackedBarSeries, QHorizontalPercentBarSeries
*/
/*!
    \qmltype HorizontalBarSeries
    \instantiates QHorizontalBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Series type for creating horizontal bar chart.

    The following QML shows how to create a simple horizontal bar chart:
    \snippet qmlchart/qml/qmlchart/View9.qml 1
    \beginfloatleft
    \image examples_qmlchart9.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs empty QHorizontalBarSeries.
    QHorizontalBarSeries is QObject which is a child of a \a parent.
*/
QHorizontalBarSeries::QHorizontalBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QHorizontalBarSeriesPrivate(this), parent)
{
}

/*!
    Destructor.
    Removes series from chart.
*/
QHorizontalBarSeries::~QHorizontalBarSeries()
{
    Q_D(QHorizontalBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Returns QChartSeries::SeriesTypeHorizontalBar.
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

#include "moc_qhorizontalbarseries.cpp"

QT_CHARTS_END_NAMESPACE
