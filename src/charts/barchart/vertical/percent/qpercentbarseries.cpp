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

#include <QtCharts/QPercentBarSeries>
#include <private/qpercentbarseries_p.h>
#include <private/percentbarchartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QPercentBarSeries
    \inmodule Qt Charts
    \brief Series for creating percent bar chart.

    QPercentBarSeries represents a series of data shown as bars. The purpose of this class is to
    draw bars as stacks, where each bar is shown as percentage of all bars in that category.
    QPercentBarSeries groups the data from sets to categories, which are defined by a QStringList.
    Bars with zero value are not drawn.

    See the \l {PercentbarChart Example} {percent bar chart example} to learn how to create a
    percent bar chart.
    \image examples_percentbarchart.png

    \sa QBarSet, QStackedBarSeries, QAbstractBarSeries
*/
/*!
    \qmltype PercentBarSeries
    \instantiates QPercentBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractBarSeries

    \brief Series for creating persent bar chart.

    The following QML shows how to create a simple percent bar chart:
    \snippet qmlchart/qml/qmlchart/View8.qml 1
    \beginfloatleft
    \image examples_qmlchart8.png
    \endfloat
    \clearfloat
*/

/*!
    Constructs empty QPercentBarSeries.
    QPercentBarSeries is QObject which is a child of a \a parent.
*/
QPercentBarSeries::QPercentBarSeries(QObject *parent)
    : QAbstractBarSeries(*new QPercentBarSeriesPrivate(this), parent)
{
}

/*!
    Destructor. Removes series from chart.
*/
QPercentBarSeries::~QPercentBarSeries()
{
    Q_D(QPercentBarSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Returns QAbstractSeries::SeriesTypePercentBar.
*/
QAbstractSeries::SeriesType QPercentBarSeries::type() const
{
    return QAbstractSeries::SeriesTypePercentBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPercentBarSeriesPrivate::QPercentBarSeriesPrivate(QPercentBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QPercentBarSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal x = categoryCount();
    minX = qMin(minX, - (qreal)0.5);
    maxX = qMax(maxX, x - (qreal)0.5);
    minY = 0;
    maxY = 100;

    domain()->setRange(minX, maxX, minY, maxY);
}


void QPercentBarSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QPercentBarSeries);
    PercentBarChartItem *bar = new PercentBarChartItem(q,parent);
    m_item.reset(bar);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

#include "moc_qpercentbarseries.cpp"

QT_CHARTS_END_NAMESPACE

