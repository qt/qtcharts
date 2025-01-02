// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QLineSeries>
#include <private/qlineseries_p.h>
#include <private/linechartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <private/qchart_p.h>
QT_BEGIN_NAMESPACE

/*!
    \class QLineSeries
    \inmodule QtCharts
    \brief The QLineSeries class presents data in line charts.

    A line chart is used to show information as a series of data points
    connected by straight lines.

    \image examples_linechart.png

    Creating a basic line chart is simple:
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

    \brief Presents data in line charts.

    A line chart is used to show information as a series of data points
    connected by straight lines.

    The following QML example shows how to create a simple line chart:
    \snippet qmlchartsgallery/qml/LineSeries.qml 1
    \beginfloatleft
    \image examples_qmlchart2.png
    \endfloat
    \clearfloat
*/

/*!
    \qmlproperty int LineSeries::count
    The number of data points in the series.
*/

/*!
    \qmlproperty real LineSeries::width
    The width of the line. By default, the width is 2.0.
*/

/*!
    \qmlproperty Qt::PenStyle LineSeries::style
    Controls the style of the line. Set to one of \l{Qt::NoPen}{Qt.NoPen},
    \l{Qt::SolidLine}{Qt.SolidLine}, \l{Qt::DashLine}{Qt.DashLine}, \l{Qt::DotLine}{Qt.DotLine},
    \l{Qt::DashDotLine}{Qt.DashDotLine}, or \l{Qt::DashDotDotLine}{Qt.DashDotDotLine}.
    Using \l{Qt::CustomDashLine}{Qt.CustomDashLine} is not supported in the QML API.
    By default, the style is Qt.SolidLine.

    \sa Qt::PenStyle
*/

/*!
    \qmlproperty Qt::PenCapStyle LineSeries::capStyle
    Controls the cap style of the line. Set to one of \l{Qt::FlatCap}{Qt.FlatCap},
    \l{Qt::SquareCap}{Qt.SquareCap} or \l{Qt::RoundCap}{Qt.RoundCap}. By
    default the cap style is Qt.SquareCap.

    \sa Qt::PenCapStyle
*/

/*!
    Constructs an empty series object that is a child of \a parent.
    When the series object is added to a QChartView or QChart instance, the ownership
    is transferred.
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
    Destroys the object. Series added to QChartView or QChart instances are owned by the
    instances and deleted when the instances are destroyed.
*/
QLineSeries::~QLineSeries()
{
    Q_D(QLineSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    \reimp
*/
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
        debug.nospace() << "(" << series.d_func()->m_x.at(i) << ',' << series.d_func()->m_y.at(i) << ") ";
    }
    return debug.space();
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QLineSeriesPrivate::QLineSeriesPrivate(QLineSeries *q)
    : QXYSeriesPrivate(q)
{
    m_markerSize = m_pen.widthF() * 1.5;
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

QT_END_NAMESPACE

#include "moc_qlineseries.cpp"
