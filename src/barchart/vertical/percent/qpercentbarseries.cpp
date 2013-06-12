/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qpercentbarseries.h"
#include "qpercentbarseries_p.h"
#include "percentbarchartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "qvalueaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QPercentBarSeries
    \brief Series for creating percent bar chart.
    \mainclass

    QPercentBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as stacks, where each bar is shown as percentage of all bars in that category.
    QPercentBarSeries groups the data from sets to categories, which are defined by a QStringList.

    See the \l {PercentbarChart Example} {percent bar chart example} to learn how to create a percent bar chart.
    \image examples_percentbarchart.png

    \sa QBarSet, QStackedBarSeries, QAbstractBarSeries
*/
/*!
    \qmlclass PercentBarSeries QPercentBarSeries
    \inherits QAbstractBarSeries

    The following QML shows how to create a simple percent bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View8.qml 1
    \beginfloatleft
    \image demos_qmlchart8.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs empty QPercentBarSeries.
    QPercentBarSeries is QObject which is a child of a \a parent.
*/
QPercentBarSeries::QPercentBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QPercentBarSeriesPrivate(this), parent)
{
}

/*!
    Destructor. Removes series from chart.
*/
QPercentBarSeries::~QPercentBarSeries()
{
    Q_D(QPercentBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Returns QAbstractSeries::SeriesTypePercentBar.
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

#include "moc_qpercentbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

