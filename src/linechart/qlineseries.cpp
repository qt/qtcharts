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

#include "qlineseries.h"
#include "qlineseries_p.h"
#include "linechartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QLineSeries
    \brief The QLineSeries class is used for making line charts.

    \mainclass

	A line chart is used to show information as a series of data points
	connected by straight lines.

    \image examples_linechart.png

	Creating basic line chart is simple:
	\code
    QLineSeries* series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    ...
    chart->addSeries(series);
    \endcode
*/
/*!
    \qmlclass LineSeries QLineSeries
    \inherits XYSeries

    The following QML shows how to create a simple line chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View2.qml 1
    \beginfloatleft
    \image demos_qmlchart2.png
    \endfloat
    \clearfloat
*/

/*!
    \fn virtual SeriesType QLineSeries::type() const
    \brief Returns type of series.
    \sa QAbstractSeries, SeriesType
*/

/*!
    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance ownerships is transferred.
*/
QLineSeries::QLineSeries(QObject *parent) : QXYSeries(*new QLineSeriesPrivate(this),parent)
{

}

/*!
    \internal
*/
QLineSeries::QLineSeries(QLineSeriesPrivate &d,QObject *parent) : QXYSeries (d,parent)
{

}
/*!
    Destroys the object. Series added to QChartView or QChart instances are owned by those,
    and are deleted when mentioned object are destroyed.
*/
QLineSeries::~QLineSeries()
{
    Q_D(QLineSeries);
    if(d->m_dataset){
           d->m_dataset->removeSeries(this);
    }
}

QAbstractSeries::SeriesType QLineSeries::type() const
{
    return QAbstractSeries::SeriesTypeLine;
}

/*
QDebug operator<< (QDebug debug, const QLineSeries series)
{
    Q_ASSERT(series.d_func()->m_x.size() == series.d_func()->m_y.size());
    int size = series.d_func()->m_x.size();
    for (int i=0; i<size; i++) {
        debug.nospace() << "(" << series.d_func()->m_x.at(i) << ','<< series.d_func()->m_y.at(i) << ") ";
    }
    return debug.space();
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QLineSeriesPrivate::QLineSeriesPrivate(QLineSeries* q):QXYSeriesPrivate(q)
{

};

ChartElement* QLineSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QLineSeries);
    LineChartItem* line = new LineChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        line->setAnimation(new XYAnimation(line));
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return line;
}

#include "moc_qlineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
