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

#include "qhorizontalbarseries.h"
#include "qhorizontalbarseries_p.h"
#include "horizontalbarchartitem_p.h"
#include "horizontalbaranimation_p.h"
#include "qbarcategoryaxis.h"

#include "chartdataset_p.h"
#include "charttheme_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHorizontalBarSeries
    \brief Series for creating horizontal bar chart
    \mainclass

    QHorizontalBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as groups, where bars in same category are grouped next to each other. QHorizontalBarSeries groups the data
    from sets to categories, which are defined by a QStringList.

    See the \l {HorizontalBarChart Example} {horizontal bar chart example} to learn how to create a horizontal bar chart.
    \image examples_horizontalbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries, QHorizontalStackedBarSeries, QHorizontalPercentBarSeries
*/
/*!
    \qmlclass HorizontalBarSeries QHorizontalBarSeries
    \inherits AbstractBarSeries

    The following QML shows how to create a simple horizontal bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View9.qml 1
    \beginfloatleft
    \image demos_qmlchart9.png
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
    Destructor
    Removes series from chart.
*/
QHorizontalBarSeries::~QHorizontalBarSeries()
{
    Q_D(QHorizontalBarSeries);
    if (d->m_dataset)
        d->m_dataset->removeSeries(this);
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

void QHorizontalBarSeriesPrivate::scaleDomain(Domain &domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());

    qreal y = categoryCount();
    minX = qMin(minX, min());
    minY = qMin(minY, - (qreal)0.5);
    maxX = qMax(maxX, max());
    maxY = qMax(maxY, y - (qreal)0.5);

    domain.setRange(minX, maxX, minY, maxY);
}

ChartElement *QHorizontalBarSeriesPrivate::createGraphics(ChartPresenter *presenter)
{
    Q_Q(QHorizontalBarSeries);

    HorizontalBarChartItem *bar = new HorizontalBarChartItem(q, presenter);
    if (presenter->animationOptions().testFlag(QChart::SeriesAnimations))
        bar->setAnimation(new HorizontalBarAnimation(bar));
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

#include "moc_qhorizontalbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
