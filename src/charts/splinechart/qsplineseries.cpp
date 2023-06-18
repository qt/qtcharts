// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QSplineSeries>
#include <private/qsplineseries_p.h>
#include <private/splinechartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <private/splineanimation_p.h>
#include <private/qchart_p.h>

/*!
    \class QSplineSeries
    \inmodule QtCharts
    \brief The QSplineSeries class presents data as spline charts.

    A spline series stores the data points and the segment control points needed
    by QPainterPath to draw a spline. The control points are automatically
    calculated when the data changes. The algorithm computes the points so that
    the normal spline can be drawn.

    \image examples_splinechart.png

    The following code snippet illustrates how to create a basic spline chart:
    \code
    QSplineSeries* series = new QSplineSeries();
    series->append(0, 6);
    series->append(2, 4);
    ...
    chart->addSeries(series);
    \endcode
*/
/*!
    \qmltype SplineSeries
    \instantiates QSplineSeries
    \inqmlmodule QtCharts

    \inherits XYSeries

    \brief Presents data as spline charts.

    A spline series stores the data points and the segment control points needed
    by QPainterPath to draw a spline. The control points are automatically
    calculated when the data changes. The algorithm computes the points so that
    the normal spline can be drawn.

    \image examples_qmlchart3.png

    The following QML code shows how to create a simple spline chart:
    \snippet qmlchartsgallery/qml/SplineSeries.qml 1
*/

/*!
    \qmlproperty real SplineSeries::width
    The width of the line. By default, the width is 2.0.
*/

/*!
    \qmlproperty Qt::PenStyle SplineSeries::style
    Controls the style of the line. Set to one of \l{Qt::NoPen}{Qt.NoPen},
    \l{Qt::SolidLine}{Qt.SolidLine}, \l{Qt::DashLine}{Qt.DashLine}, \l{Qt::DotLine}{Qt.DotLine},
    \l{Qt::DashDotLine}{Qt.DashDotLine}, or \l{Qt::DashDotDotLine}{Qt.DashDotDotLine}.
    Using \l{Qt::CustomDashLine}{Qt.CustomDashLine} is not supported in the QML API.
    By default, the style is Qt.SolidLine.

    \sa Qt::PenStyle
*/

/*!
    \qmlproperty Qt::PenCapStyle SplineSeries::capStyle
    Controls the cap style of the line. Set to one of \l{Qt::FlatCap}{Qt.FlatCap},
    \l{Qt::SquareCap}{Qt.SquareCap} or \l{Qt::RoundCap}{Qt.RoundCap}. By
    default, the cap style is Qt.SquareCap.

    \sa Qt::PenCapStyle
*/

/*!
    \qmlproperty int SplineSeries::count
    The number of data points in the series.
*/

QT_BEGIN_NAMESPACE

/*!
    Constructs an empty series object that is a child of \a parent.
    When the series object is added to a QChart instance, the ownerships is
    transferred.
  */

QSplineSeries::QSplineSeries(QObject *parent)
    : QLineSeries(*new QSplineSeriesPrivate(this), parent)
{
}

/*!
  Deletes the spline series.
*/
QSplineSeries::~QSplineSeries()
{
    Q_D(QSplineSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    \reimp
*/
QAbstractSeries::SeriesType QSplineSeries::type() const
{
    return QAbstractSeries::SeriesTypeSpline;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSplineSeriesPrivate::QSplineSeriesPrivate(QSplineSeries *q)
    : QLineSeriesPrivate(q)
{
}

void QSplineSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QSplineSeries);
    SplineChartItem *spline = new SplineChartItem(q,parent);
    m_item.reset(spline);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

void QSplineSeriesPrivate::initializeTheme(int index, ChartTheme* theme, bool forced)
{
    Q_Q(QSplineSeries);
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

void QSplineSeriesPrivate::initializeAnimations(QChart::AnimationOptions options,
                                                int duration, QEasingCurve &curve)
{
    SplineChartItem *item = static_cast<SplineChartItem *>(m_item.get());
    Q_ASSERT(item);
    if (item->animation())
        item->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::SeriesAnimations))
        item->setAnimation(new SplineAnimation(item, duration, curve));
    else
        item->setAnimation(0);
    QAbstractSeriesPrivate::initializeAnimations(options, duration, curve);
}

QT_END_NAMESPACE

#include "moc_qsplineseries.cpp"
#include "moc_qsplineseries_p.cpp"
