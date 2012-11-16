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
#include "qhorizontalstackedbarseries.h"
#include "qhorizontalstackedbarseries_p.h"
#include "horizontalstackedbarchartitem_p.h"
#include "horizontalstackedbaranimation_p.h"

#include "chartdataset_p.h"
#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QHorizontalStackedBarSeries
    \brief Series for creating horizontal stacked bar chart
    \mainclass

    QHorizontalStackedBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as groups, where bars in same category are grouped next to each other. QHorizontalStackedBarSeries groups the data
    from sets to categories, which are defined by a QStringList.

    See the \l {HorizontalStackedBarChart Example} {horizontal stacked bar chart example} to learn how to create a horizontal stacked bar chart.
    \image examples_horizontalstackedbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries, QHorizontalPercentBarSeries, QHorizontalBarSeries
*/
/*!
    \qmlclass HorizontalStackedBarSeries QHorizontalStackedBarSeries
    \inherits QAbstractBarSeries

    The following QML shows how to create a simple horizontal stacked bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View10.qml 1
    \beginfloatleft
    \image demos_qmlchart10.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs empty QHorizontalStackedBarSeries.
    QHorizontalStackedBarSeries is QObject which is a child of a \a parent.
*/
QHorizontalStackedBarSeries::QHorizontalStackedBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QHorizontalStackedBarSeriesPrivate(this), parent)
{
}

/*!
    Destructor
    Removes series from chart.
*/
QHorizontalStackedBarSeries::~QHorizontalStackedBarSeries()
{
    Q_D(QHorizontalStackedBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Returns QChartSeries::SeriesTypeHorizontalStackedBar.
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

void QHorizontalStackedBarSeriesPrivate::initializeAnimations(QtCommercialChart::QChart::AnimationOptions options)
{
    HorizontalStackedBarChartItem *bar = static_cast<HorizontalStackedBarChartItem *>(m_item.data());
    Q_ASSERT(bar);
    if (options.testFlag(QChart::SeriesAnimations)) {
        bar->setAnimation(new HorizontalStackedBarAnimation(bar));
    }else{
        bar->setAnimation(0);
    }
    QAbstractSeriesPrivate::initializeAnimations(options);
}
#include "moc_qhorizontalstackedbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
