/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtCharts/QHorizontalPercentBarSeries>
#include <private/qhorizontalpercentbarseries_p.h>
#include <private/horizontalpercentbarchartitem_p.h>

#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QHorizontalPercentBarSeries
    \inmodule Qt Charts
    \brief Series for creating horizontal percent bar chart.

    QHorizontalPercentBarSeries represents a series of data shown as bars. The purpose of this
    class is to draw bars as groups, where bars in same category are grouped next to each other.
    QHorizontalPercentBarSeries groups the data from sets to categories, which are defined by a
    QStringList. Bars with zero value are not drawn.

    See the \l {HorizontalPercentBarChart Example} {horizontal percent bar chart example} to learn
    how to create a horizontal percent bar chart.
    \image examples_horizontalpercentbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries,
    QHorizontalStackedBarSeries, QHorizontalBarSeries
*/
/*!
    \qmltype HorizontalPercentBarSeries
    \instantiates QHorizontalPercentBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Series type for creating horizontal precent bar chart.

    The following QML shows how to create a simple horizontal percent bar chart:
    \snippet qmlchart/qml/qmlchart/View11.qml 1
    \beginfloatleft
    \image examples_qmlchart11.png
    \endfloat
    \clearfloat
*/

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

QT_CHARTS_END_NAMESPACE
