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

#include "qgroupedbarseries.h"
#include "qgroupedbarseries_p.h"
#include "groupedbarchartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"
#include "qcategoriesaxis.h"
#include "qvaluesaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QGroupedBarSeries
    \brief Series for creating grouped bar chart
    \mainclass

    QGroupedBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as groups, where bars in same category are grouped next to each other. QGroupedBarSeries groups the data
    from sets to categories, which are defined by a QStringList.

    See the \l {GroupedbarChart Example} {grouped bar chart example} to learn how to create a grouped bar chart.
    \image examples_groupedbarchart.png

    \sa QBarSet, QPercentBarSeries, QBarSeries, QStackedBarSeries
*/
/*!
    \qmlclass GroupedBarSeries QGroupedBarSeries
    \inherits BarSeries

    The following QML shows how to create a simple grouped bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View8.qml 1
    \beginfloatleft
    \image demos_qmlchart7.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs empty QGroupedBarSeries.
    QGroupedBarSeries is QObject which is a child of a \a parent.
*/
QGroupedBarSeries::QGroupedBarSeries(QObject *parent)
    : QBarSeries(*new QGroupedBarSeriesPrivate(this), parent)
{
}

/*!
    Returns QChartSeries::SeriesTypeGroupedBar.
*/
QAbstractSeries::SeriesType QGroupedBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeGroupedBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QGroupedBarSeriesPrivate::QGroupedBarSeriesPrivate(QGroupedBarSeries *q) : QBarSeriesPrivate(q)
{

}

void QGroupedBarSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    qreal x = categoryCount();
    qreal y = max();
    minX = qMin(minX, -0.5);
    minY = qMin(minY, y);
    maxX = qMax(maxX, x - 0.5);
    maxY = qMax(maxY, y);
    tickXCount = x+1;

    domain.setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
}


Chart* QGroupedBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QGroupedBarSeries);

    GroupedBarChartItem* bar = new GroupedBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        presenter->animator()->addAnimation(bar);
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}


#include "moc_qgroupedbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

