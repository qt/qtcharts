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

#include "qstackedbarseries.h"
#include "qstackedbarseries_p.h"
#include "stackedbarchartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "qvalueaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QStackedBarSeries
    \brief Series for creating stacked bar chart
    \mainclass

    QStackedBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as stacks, where bars in same category are stacked on top of each other.
    QStackedBarSeries groups the data from sets to categories, which are defined by QStringList.

    See the \l {StackedbarChart Example} {stacked bar chart example} to learn how to create a stacked bar chart.
    \image examples_stackedbarchart.png

    \sa QBarSet, QPercentBarSeries, QAbstractBarSeries
*/

/*!
    \qmlclass StackedBarSeries QStackedBarSeries
    \inherits AbstractBarSeries

    The following QML shows how to create a simple stacked bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View7.qml 1
    \beginfloatleft
    \image demos_qmlchart7.png
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
    Returns QChartSeries::SeriesTypeStackedBar.
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

QTCOMMERCIALCHART_END_NAMESPACE

