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

#include "qbarseries.h"
#include "qbarseries_p.h"
#include "barchartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "baranimation_p.h"
#include "qvalueaxis.h"
#include "qbarcategoryaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarSeries
    \brief Series for creating bar chart
    \mainclass

    QBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as groups, where bars in same category are grouped next to each other. QBarSeries groups the data
    from sets to categories, which are defined by a QStringList.

    See the \l {BarChart Example} {bar chart example} to learn how to create a grouped bar chart.
    \image examples_barchart.png

    \sa QBarSet, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries
*/
/*!
    \qmlclass BarSeries QBarSeries
    \inherits AbstractBarSeries

    The following QML shows how to create a simple grouped bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View6.qml 1
    \beginfloatleft
    \image demos_qmlchart6.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs empty QBarSeries.
    QBarSeries is QObject which is a child of a \a parent.
*/
QBarSeries::QBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QBarSeriesPrivate(this), parent)
{

}

/*!
    Returns QChartSeries::SeriesTypeBar.
*/
QAbstractSeries::SeriesType QBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeBar;
}

/*!
    Destructor. Removes series from chart.
*/
QBarSeries::~QBarSeries()
{
    Q_D(QBarSeries);
    if(d->m_dataset) {
        d->m_dataset->removeSeries(this);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarSeriesPrivate::QBarSeriesPrivate(QBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QBarSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());

    qreal x = categoryCount();
    minX = qMin(minX, - (qreal)0.5);
    minY = qMin(minY, min());
    maxX = qMax(maxX, x - (qreal)0.5);
    maxY = qMax(maxY, max());

    domain.setRange(minX,maxX,minY,maxY);
}


ChartElement* QBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QBarSeries);

    BarChartItem* bar = new BarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        bar->setAnimation(new BarAnimation(bar));
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

#include "moc_qbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

