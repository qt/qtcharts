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

#include <QtCharts/QLineSeries>
#include <private/qlineseries_p.h>
#include <private/linechartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <private/qchart_p.h>
QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QLineSeries
    \inmodule Qt Charts
    \brief The QLineSeries class is used for making line charts.

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
    \qmltype LineSeries
    \instantiates QLineSeries
    \inqmlmodule QtCharts

    \inherits XYSeries

    \brief The LineSeries type is used for making line charts.

    The following QML shows how to create a simple line chart:
    \snippet qmlchart/qml/qmlchart/View2.qml 1
    \beginfloatleft
    \image examples_qmlchart2.png
    \endfloat
    \clearfloat
*/

/*!
    \fn virtual SeriesType QLineSeries::type() const
    \brief Returns type of series.
    \sa QAbstractSeries, SeriesType
*/

/*!
    \qmlproperty real LineSeries::width
    The width of the line. By default the width is 2.0.
*/

/*!
    \qmlproperty Qt::PenStyle LineSeries::style
    Controls the style of the line. Set to one of Qt.NoPen, Qt.SolidLine, Qt.DashLine, Qt.DotLine,
    Qt.DashDotLine or Qt.DashDotDotLine. Using Qt.CustomDashLine is not supported in the QML API.
    By default the style is Qt.SolidLine.
*/

/*!
    \qmlproperty Qt::PenCapStyle LineSeries::capStyle
    Controls the cap style of the line. Set to one of Qt.FlatCap, Qt.SquareCap or Qt.RoundCap. By
    default the cap style is Qt.SquareCap.
*/

/*!
    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance ownerships is transferred.
*/
QLineSeries::QLineSeries(QObject *parent)
    : QXYSeries(*new QLineSeriesPrivate(this), parent)
{

}

/*!
    \internal
*/
QLineSeries::QLineSeries(QLineSeriesPrivate &d, QObject *parent)
    : QXYSeries(d, parent)
{

}
/*!
    Destroys the object. Series added to QChartView or QChart instances are owned by those,
    and are deleted when mentioned object are destroyed.
*/
QLineSeries::~QLineSeries()
{
    Q_D(QLineSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
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

QLineSeriesPrivate::QLineSeriesPrivate(QLineSeries *q)
    : QXYSeriesPrivate(q)
{

}

void QLineSeriesPrivate::initializeGraphics(QGraphicsItem *parent)
{
    Q_Q(QLineSeries);
    LineChartItem *line = new LineChartItem(q,parent);
    m_item.reset(line);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

void QLineSeriesPrivate::initializeTheme(int index, ChartTheme* theme, bool forced)
{
    Q_Q(QLineSeries);
    const QList<QColor> colors = theme->seriesColors();

    if (forced || QChartPrivate::defaultPen() == m_pen) {
        QPen pen;
        pen.setColor(colors.at(index % colors.size()));
        pen.setWidthF(2);
        q->setPen(pen);
    }

    if (forced || QChartPrivate::defaultPen().color() == m_pointLabelsColor) {
        QColor color = theme->labelBrush().color();
        q->setPointLabelsColor(color);
    }
}

#include "moc_qlineseries.cpp"

QT_CHARTS_END_NAMESPACE
