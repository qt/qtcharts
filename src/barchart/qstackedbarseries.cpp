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
#include "barchartmodel_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QStackedBarSeries
    \brief part of QtCommercial chart API.
    \mainclass

    QStackedBarSeries represents a series of data shown as bars. All bars in same category are
    stacked on top of each other. One QStackedBarSeries can contain multiple QBarSet data sets.
    QStackedBarSeries groups the data from sets to categories, which are defined by QStringList.

    See the \l {StackedbarChart Example} {stacked bar chart example} to learn how to create a stacked bar chart.
    \image examples_stackedbarchart.png

    \sa QBarSet, QPercentBarSeries, QBarSeries
*/

/*!
    \fn virtual QSeriesType QStackedBarSeries::type() const
    \brief Returns type of series.
    \sa QSeriesType
*/

/*!
    Constructs empty QStackedBarSeries. Parameter \a categories defines the categories for chart.
    QStackedBarSeries is QObject which is a child of a \a parent.
*/
QStackedBarSeries::QStackedBarSeries(QBarCategories categories, QObject *parent)
    : QBarSeries(*new QStackedBarSeriesPrivate(categories,this), parent)
{
}

QAbstractSeries::QSeriesType QStackedBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeStackedBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QStackedBarSeriesPrivate::QStackedBarSeriesPrivate(QBarCategories categories, QStackedBarSeries *q) : QBarSeriesPrivate(categories,q)
{

}

void QStackedBarSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    qreal x = m_internalModel->categoryCount();
    qreal y = maxCategorySum();
    minX = qMin(minX, x);
    minY = qMin(minY, y);
    maxX = qMax(maxX, x);
    maxY = qMax(maxY, y);
    tickXCount = x+1;

    domain.setRangeX(minX,maxX,tickXCount);
    domain.setRangeY(minY,maxY,tickYCount);
}


Chart* QStackedBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QStackedBarSeries);

    StackedBarChartItem* bar = new StackedBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        presenter->animator()->addAnimation(bar);
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

#include "moc_qstackedbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

