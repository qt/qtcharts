/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <QtCharts/QPolarChart>
#include <QtCharts/QAbstractAxis>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \enum QPolarChart::PolarOrientation

   This type is used to specify the polar orientation of an axis.

    \value PolarOrientationRadial
    \value PolarOrientationAngular
*/

/*!
 \class QPolarChart
 \inmodule Qt Charts
 \brief Polar chart API for Qt Charts.

 QPolarChart is a specialization of QChart to show a polar chart.

 Polar charts support line, spline, area, and scatter series, and all axis types
 supported by those series.

 \note When setting ticks to an angular QValueAxis, keep in mind that the first and last tick
 are co-located at 0/360 degree angle.

 \note If the angular distance between two consecutive points in a series is more than 180 degrees,
 any line connecting the two points becomes meaningless, so choose the axis ranges accordingly
 when displaying line, spline, or area series. In such case series don't draw a direct line between
 the two points, but instead draw a line to and from the center of the chart.

 \note Polar charts draw all axes of same orientation in the same position, so using multiple
 axes of same orientation can be confusing, unless the extra axes are only used to customize the
 grid (e.g. you can display a highlighted range with a secondary shaded QCategoryAxis or provide
 unlabeled subticks with a secondary QValueAxis that has its labels hidden).

 \sa QChart
 */

/*!
 Constructs a polar chart as a child of the \a parent.
 Parameter \a wFlags is passed to the QChart constructor.
 */
QPolarChart::QPolarChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypePolar, parent, wFlags)
{
}

/*!
 Destroys the polar chart object and its children, like series and axis objects added to it.
 */
QPolarChart::~QPolarChart()
{
}

/*!
 Returns the axes added for the \a series with \a polarOrientation. If no series is provided, then any axis with the
 specified polar orientation is returned.

 \sa addAxis()
 */
QList<QAbstractAxis *> QPolarChart::axes(PolarOrientations polarOrientation, QAbstractSeries *series) const
{
    Qt::Orientations orientation(0);
    if (polarOrientation.testFlag(PolarOrientationAngular))
        orientation |= Qt::Horizontal;
    if (polarOrientation.testFlag(PolarOrientationRadial))
        orientation |= Qt::Vertical;

    return QChart::axes(orientation, series);
}

/*!
  This convenience method adds \a axis to the polar chart with \a polarOrientation.
  The chart takes the ownership of the axis.

  \note Axes can be added to a polar chart also with QChart::addAxis() instead of this method.
  The specified alignment determines the polar orientation: horizontal alignments indicate angular
  axis and vertical alignments indicate radial axis.

  \sa QChart::removeAxis(), QChart::createDefaultAxes(), QAbstractSeries::attachAxis(), QChart::addAxis()
*/
void QPolarChart::addAxis(QAbstractAxis *axis, PolarOrientation polarOrientation)
{
    if (!axis || axis->type() == QAbstractAxis::AxisTypeBarCategory) {
        qWarning("QAbstractAxis::AxisTypeBarCategory is not a supported axis type for polar charts.");
    } else {
        Qt::Alignment alignment = Qt::AlignLeft;
        if (polarOrientation == PolarOrientationAngular)
            alignment = Qt::AlignBottom;
        QChart::addAxis(axis, alignment);
    }
}

/*!
  Angular axes of a polar chart report horizontal orientation and radial axes report
  vertical orientation.
  This function is a convenience function for converting the orientation of an \a axis to
  corresponding polar orientation. If the \a axis is NULL or not added to a polar chart,
  the return value is meaningless.
*/
QPolarChart::PolarOrientation QPolarChart::axisPolarOrientation(QAbstractAxis *axis)
{
    if (axis && axis->orientation() == Qt::Horizontal)
        return PolarOrientationAngular;
    else
        return PolarOrientationRadial;
}

#include "moc_qpolarchart.cpp"

QT_CHARTS_END_NAMESPACE
