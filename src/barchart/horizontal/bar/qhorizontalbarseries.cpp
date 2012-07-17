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
#include "qbarcategoriesaxis.h"

#include "chartdataset_p.h"
#include "charttheme_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

QHorizontalBarSeries::QHorizontalBarSeries(QObject *parent) :
    QAbstractBarSeries(*new QHorizontalBarSeriesPrivate(this), parent)
{
}

QAbstractSeries::SeriesType QHorizontalBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeHorizontalBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QHorizontalBarSeriesPrivate::QHorizontalBarSeriesPrivate(QHorizontalBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QHorizontalBarSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());

    qreal y = categoryCount();
    qreal x = max();
    minX = qMin(minX, x);
    minY = qMin(minY, - (qreal)0.5);
    maxX = qMax(maxX, x);
    maxY = qMax(maxY, y - (qreal)0.5);

    domain.setRange(minX,maxX,minY,maxY);
}

Chart* QHorizontalBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QHorizontalBarSeries);

    HorizontalBarChartItem* bar = new HorizontalBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        bar->setAnimator(presenter->animator());
        bar->setAnimation(new HorizontalBarAnimation(bar));
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

#include "moc_qhorizontalbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
