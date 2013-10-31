/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
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
#include "qchart_p.h"
QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QLineSeries
    \inmodule Qt Charts
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
#ifdef QDOC_QT5
/*!
    \qmltype LineSeries
    \instantiates QLineSeries
    \inqmlmodule QtCommercial.Chart

    \include doc/src/lineseries.qdocinc
*/
#else
/*!
    \qmlclass LineSeries QLineSeries

    \include ../doc/src/lineseries.qdocinc
*/
#endif

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

};

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
}

#include "moc_qlineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
