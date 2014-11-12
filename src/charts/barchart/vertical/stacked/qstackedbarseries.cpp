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

#include <QtCharts/QStackedBarSeries>
#include <private/qstackedbarseries_p.h>
#include <private/stackedbarchartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QStackedBarSeries
    \inmodule Qt Charts
    \brief Series for creating stacked bar chart.
    \mainclass

    QStackedBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as stacks, where bars in same category are stacked on top of each other.
    QStackedBarSeries groups the data from sets to categories, which are defined by QStringList.

    See the \l {StackedbarChart Example} {stacked bar chart example} to learn how to create a stacked bar chart.
    \image examples_stackedbarchart.png

    \sa QBarSet, QPercentBarSeries, QAbstractBarSeries
*/

/*!
    \qmltype StackedBarSeries
    \instantiates QStackedBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Series for creating stacked bar chart.

    The following QML shows how to create a simple stacked bar chart:
    \snippet qmlchart/qml/qmlchart/View7.qml 1
    \beginfloatleft
    \image examples_qmlchart7.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs empty QStackedBarSeries.
    QStackedBarSeries is QObject which is a child of a \a parent.
*/
QStackedBarSeries::QStackedBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QStackedBarSeriesPrivate(this), parent)
{
}

/*!
    Destructor. Removes series from chart.
*/
QStackedBarSeries::~QStackedBarSeries()
{
    Q_D(QStackedBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}
/*!
    Returns QAbstractSeries::SeriesTypeStackedBar.
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

#include "moc_qstackedbarseries.cpp"

QT_CHARTS_END_NAMESPACE

