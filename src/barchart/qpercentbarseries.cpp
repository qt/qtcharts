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

#include "qpercentbarseries.h"
#include "qpercentbarseries_p.h"
#include "percentbarchartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QPercentBarSeries
    \brief part of QtCommercial chart API.
    \mainclass

    QPercentBarSeries represents a series of data shown as bars. Each bar of QBarSet is shown as percentage
    of all bars in category. One QPercentBarSeries can contain multiple QBarSet data sets.
    QBarSeries groups the data from sets to categories, which are defined by QStringList.

    See the \l {PercentbarChart Example} {percent bar chart example} to learn how to create a percent bar chart.
    \image examples_percentbarchart.png

    \sa QBarSet, QStackedBarSeries, QBarSeries
*/

/*!
    \fn virtual QSeriesType QPercentBarSeries::type() const
    \brief Returns type of series.
    \sa QAbstractSeries, QSeriesType
*/

/*!
    Constructs empty QPercentBarSeries. Parameter \a categories defines the categories for chart.
    QPercentBarSeries is QObject which is a child of a \a parent.
*/
QPercentBarSeries::QPercentBarSeries(/*QBarCategories categories,*/ QObject *parent)
    : QBarSeries(*new QPercentBarSeriesPrivate(/*categories,*/this), parent)
{
}

QAbstractSeries::SeriesType QPercentBarSeries::type() const
{
    return QAbstractSeries::SeriesTypePercentBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPercentBarSeriesPrivate::QPercentBarSeriesPrivate(/*QBarCategories categories,*/ QPercentBarSeries *q) : QBarSeriesPrivate(/*categories,*/q)
{

}

void QPercentBarSeriesPrivate::scaleDomain(Domain& domain)
{
    Q_Q(QPercentBarSeries);
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    qreal x = q->categoryCount();
    minX = qMin(minX, x);
    maxX = qMax(maxX, x);
    minY = 0;
    maxY = 100;
    tickXCount = x+1;

    domain.setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
}


Chart* QPercentBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QPercentBarSeries);

    PercentBarChartItem* bar = new PercentBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        presenter->animator()->addAnimation(bar);
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

#include "moc_qpercentbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

