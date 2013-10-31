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
#include "qhorizontalpercentbarseries.h"
#include "qhorizontalpercentbarseries_p.h"
#include "horizontalpercentbarchartitem_p.h"

#include "chartdataset_p.h"
#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHorizontalPercentBarSeries
    \inmodule Qt Charts
    \brief Series for creating horizontal percent bar chart.
    \mainclass

    QHorizontalPercentBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as groups, where bars in same category are grouped next to each other. QHorizontalPercentBarSeries groups the data
    from sets to categories, which are defined by a QStringList.

    See the \l {HorizontalPercentBarChart Example} {horizontal percent bar chart example} to learn how to create a horizontal percent bar chart.
    \image examples_horizontalpercentbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries, QHorizontalStackedBarSeries, QHorizontalBarSeries
*/
#ifdef QDOC_QT5
/*!
    \qmltype HorizontalPercentBarSeries
    \instantiates QHorizontalPercentBarSeries
    \inqmlmodule QtCommercial.Chart

    \include doc/src/horizontalpercentbarseries.qdocinc
*/
#else
/*!
    \qmlclass HorizontalPercentBarSeries QHorizontalPercentBarSeries

    \include ../doc/src/horizontalpercentbarseries.qdocinc
*/
#endif

/*!
    Constructs empty QHorizontalPercentBarSeries.
    QHorizontalPercentBarSeries is QObject which is a child of a \a parent.
*/
QHorizontalPercentBarSeries::QHorizontalPercentBarSeries(QObject *parent) :
    QAbstractBarSeries(*new QHorizontalPercentBarSeriesPrivate(this), parent)
{
}

/*!
    Returns QAbstractSeries::SeriesTypeHorizontalPercentBar.
*/
QAbstractSeries::SeriesType QHorizontalPercentBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeHorizontalPercentBar;
}

/*!
    Destructor.
    Removes series from chart.
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

#include "moc_qhorizontalpercentbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
