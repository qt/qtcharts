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

#include "qxyseries.h"
#include "qxyseries_p.h"
#include "abstractdomain_p.h"
#include "qvalueaxis.h"
#include "xychart_p.h"
#include "qxylegendmarker.h"
#include "charthelpers_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QXYSeries
    \brief The QXYSeries class is a base class for line, spline and scatter series.
*/
/*!
    \qmlclass XYSeries
    \inherits AbstractSeries
    The XYSeries class is a base class for line, spline and scatter series.

    The class cannot be instantiated directly.
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisX
    The x axis used for the series. If you leave both axisX and axisXTop undefined, a ValueAxis is created for
    the series.
    \sa axisXTop
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisY
    The y axis used for the series. If you leave both axisY and axisYRight undefined, a ValueAxis is created for
    the series.
    \sa axisYRight
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisXTop
    The x axis used for the series, drawn on top of the chart view. Note that you can only provide either axisX or
    axisXTop, but not both.
    \sa axisX
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisYRight
    The y axis used for the series, drawn to the right on the chart view. Note that you can only provide either axisY
    or axisYRight, but not both.
    \sa axisY
*/

/*!
    \property QXYSeries::pointsVisible
    Controls if the data points are visible and should be drawn.
*/
/*!
    \qmlproperty bool XYSeries::pointsVisible
    Controls if the data points are visible and should be drawn.
*/

/*!
   \fn QPen QXYSeries::pen() const
   \brief  Returns pen used to draw points for series.
    \sa setPen()
*/

/*!
   \fn QBrush QXYSeries::brush() const
   \brief  Returns brush used to draw points for series.
    \sa setBrush()
*/

/*!
    \property QXYSeries::color
    The color of the series. This is line (pen) color in case of QLineSeries or QSplineSeries and
    fill (brush) color in case of QScatterSeries or QAreaSeries.
    \sa QXYSeries::pen(), QXYSeries::brush()
*/
/*!
    \qmlproperty color XYSeries::color
    The color of the series. This is line (pen) color in case of LineSeries or SplineSeries and
    fill (brush) color in case of ScatterSeries or AreaSeries.
*/

/*!
    \fn void QXYSeries::clicked(const QPointF& point)
    \brief Signal is emitted when user clicks the \a point on chart.
*/
/*!
    \qmlsignal XYSeries::onClicked(QPointF point)
    Signal is emitted when user clicks the \a point on chart. For example:
    \code
    LineSeries {
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        onClicked: console.log("onClicked: " + point.x + ", " + point.y);
    }
    \endcode
*/

/*!
    \fn void QXYSeries::hovered(const QPointF &point, bool state)
    This signal is emitted when user has hovered over or away from the series. \a point shows the origin (coordinate)
    of the hover event. \a state is true when user has hovered over the series and false when hover has moved away from
    the series.
*/
/*!
    \qmlsignal XYSeries::onHovered(point point, bool state)
    This signal is emitted when user has hovered over or away from the series. \a point shows the origin (coordinate)
    of the hover event. \a state is true when user has hovered over the series and false when hover has moved away from
    the series.
*/

/*!
    \fn void QXYSeries::pointReplaced(int index)
    Signal is emitted when a point has been replaced at \a index.
    \sa replace()
*/
/*!
    \qmlsignal XYSeries::onPointReplaced(int index)
    Signal is emitted when a point has been replaced at \a index.
*/

/*!
    \fn void QXYSeries::pointsReplaced()
    Signal is emitted when all points have been replaced with another points.
    \sa replace()
*/
/*!
    \qmlsignal XYSeries::onPointsReplaced()
*/

/*!
    \fn void QXYSeries::pointAdded(int index)
    Signal is emitted when a point has been added at \a index.
    \sa append(), insert()
*/
/*!
    \qmlsignal XYSeries::onPointAdded(int index)
    Signal is emitted when a point has been added at \a index.
*/

/*!
    \fn void QXYSeries::pointRemoved(int index)
    Signal is emitted when a point has been removed from \a index.
    \sa remove()
*/
/*!
    \qmlsignal XYSeries::onPointRemoved(int index)
    Signal is emitted when a point has been removed from \a index.
*/

/*!
    \fn void QXYSeries::colorChanged(QColor color)
    \brief Signal is emitted when the line (pen) color has changed to \a color.
*/
/*!
    \qmlsignal XYSeries::onColorChanged(color color)
    Signal is emitted when the line (pen) color has changed to \a color.
*/

/*!
    \fn void QXYSeriesPrivate::updated()
    \brief \internal
*/

/*!
    \qmlmethod XYSeries::append(real x, real y)
    Append point (\a x, \a y) to the series
*/

/*!
    \qmlmethod XYSeries::replace(real oldX, real oldY, real newX, real newY)
    Replaces point (\a oldX, \a oldY) with point (\a newX, \a newY). Does nothing, if point (oldX, oldY) does not
    exist.
*/

/*!
    \qmlmethod XYSeries::remove(real x, real y)
    Removes point (\a x, \a y) from the series. Does nothing, if point (x, y) does not exist.
*/

/*!
    \qmlmethod XYSeries::insert(int index, real x, real y)
    Inserts point (\a x, \a y) to the \a index. If index is 0 or smaller than 0 the point is prepended to the list of
    points. If index is the same as or bigger than count, the point is appended to the list of points.
*/

/*!
    \qmlmethod QPointF XYSeries::at(int index)
    Returns point at \a index. Returns (0, 0) if the index is not valid.
*/

/*!
    \internal

    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance ownerships is transferred.
*/
QXYSeries::QXYSeries(QXYSeriesPrivate &d, QObject *parent)
    : QAbstractSeries(d, parent)
{
}

/*!
    Destroys the object. Series added to QChartView or QChart instances are owned by those,
    and are deleted when mentioned object are destroyed.
*/
QXYSeries::~QXYSeries()
{
}

/*!
    Adds data point \a x \a y to the series. Points are connected with lines on the chart.
 */
void QXYSeries::append(qreal x, qreal y)
{
    append(QPointF(x, y));
}

/*!
   This is an overloaded function.
   Adds data \a point to the series. Points are connected with lines on the chart.
 */
void QXYSeries::append(const QPointF &point)
{
    Q_D(QXYSeries);

    if (isValidValue(point)) {
        d->m_points << point;
        emit pointAdded(d->m_points.count() - 1);
    }
}

/*!
   This is an overloaded function.
   Adds list of data \a points to the series. Points are connected with lines on the chart.
 */
void QXYSeries::append(const QList<QPointF> &points)
{
    foreach (const QPointF &point , points)
        append(point);
}

/*!
  Replaces data point \a oldX \a oldY with data point \a newX \a newY.
  \sa QXYSeries::pointReplaced()
*/
void QXYSeries::replace(qreal oldX, qreal oldY, qreal newX, qreal newY)
{
    replace(QPointF(oldX, oldY), QPointF(newX, newY));
}

/*!
  Replaces \a oldPoint with \a newPoint.
  \sa QXYSeries::pointReplaced()
*/
void QXYSeries::replace(const QPointF &oldPoint, const QPointF &newPoint)
{
    Q_D(QXYSeries);
    int index = d->m_points.indexOf(oldPoint);
    if (index == -1)
        return;
    if (isValidValue(newPoint)) {
        d->m_points[index] = newPoint;
        emit pointReplaced(index);
    }
}

/*!
  Replaces the current points with \a points. This is faster than replacing data points one by one,
  or first clearing all data, and then appending the new data. Emits QXYSeries::pointsReplaced()
  when the points have been replaced.
  \sa QXYSeries::pointsReplaced()
*/
void QXYSeries::replace(QList<QPointF> points)
{
    Q_D(QXYSeries);
    d->m_points = points.toVector();
    emit pointsReplaced();
}

/*!
  Removes current \a x and \a y value.
*/
void QXYSeries::remove(qreal x, qreal y)
{
    remove(QPointF(x, y));
}

/*!
  Removes current \a point x value.

  Note: point y value is ignored.
*/
void QXYSeries::remove(const QPointF &point)
{
    Q_D(QXYSeries);
    int index = d->m_points.indexOf(point);
    if (index == -1)
        return;
    d->m_points.remove(index);
    emit pointRemoved(index);
}

/*!
   Inserts a \a point in the series at \a index position.
*/
void QXYSeries::insert(int index, const QPointF &point)
{
    Q_D(QXYSeries);
    if (isValidValue(point)) {
        d->m_points.insert(index, point);
        emit pointAdded(index);
    }
}

/*!
    Removes all points from the series.
*/
void QXYSeries::clear()
{
    Q_D(QXYSeries);
    for (int i = d->m_points.size() - 1; i >= 0; i--)
        remove(d->m_points.at(i));
}

/*!
    Returns list of points in the series.
*/
QList<QPointF> QXYSeries::points() const
{
    Q_D(const QXYSeries);
    return d->m_points.toList();
}

/*!
    Returns number of data points within series.
*/
int QXYSeries::count() const
{
    Q_D(const QXYSeries);
    return d->m_points.count();
}


/*!
    Sets \a pen used for drawing points on the chart. If the pen is not defined, the
    pen from chart theme is used.
    \sa QChart::setTheme()
*/
void QXYSeries::setPen(const QPen &pen)
{
    Q_D(QXYSeries);
    if (d->m_pen != pen) {
        bool emitColorChanged = d->m_pen.color() != pen.color();
        d->m_pen = pen;
        emit d->updated();
        if (emitColorChanged)
            emit colorChanged(pen.color());
    }
}

QPen QXYSeries::pen() const
{
    Q_D(const QXYSeries);
    return d->m_pen;
}

/*!
    Sets \a brush used for drawing points on the chart. If the brush is not defined, brush
    from chart theme setting is used.
    \sa QChart::setTheme()
*/
void QXYSeries::setBrush(const QBrush &brush)
{
    Q_D(QXYSeries);
    if (d->m_brush != brush) {
        d->m_brush = brush;
        emit d->updated();
    }
}

QBrush QXYSeries::brush() const
{
    Q_D(const QXYSeries);
    return d->m_brush;
}

void QXYSeries::setColor(const QColor &color)
{
    QPen p = pen();
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
    }
}

QColor QXYSeries::color() const
{
    return pen().color();
}

void QXYSeries::setPointsVisible(bool visible)
{
    Q_D(QXYSeries);
    if (d->m_pointsVisible != visible) {
        d->m_pointsVisible = visible;
        emit d->updated();
    }
}

bool QXYSeries::pointsVisible() const
{
    Q_D(const QXYSeries);
    return d->m_pointsVisible;
}


/*!
    Stream operator for adding a data \a point to the series.
    \sa append()
*/
QXYSeries &QXYSeries::operator<< (const QPointF &point)
{
    append(point);
    return *this;
}


/*!
    Stream operator for adding a list of \a points to the series.
    \sa append()
*/

QXYSeries &QXYSeries::operator<< (const QList<QPointF>& points)
{
    append(points);
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


QXYSeriesPrivate::QXYSeriesPrivate(QXYSeries *q)
    : QAbstractSeriesPrivate(q),
      m_pointsVisible(false)
{
}

void QXYSeriesPrivate::initializeDomain()
{
    qreal minX(0);
    qreal minY(0);
    qreal maxX(1);
    qreal maxY(1);

    Q_Q(QXYSeries);

    const QList<QPointF>& points = q->points();

    if (!points.isEmpty()) {
        minX = points[0].x();
        minY = points[0].y();
        maxX = minX;
        maxY = minY;

        for (int i = 0; i < points.count(); i++) {
            qreal x = points[i].x();
            qreal y = points[i].y();
            minX = qMin(minX, x);
            minY = qMin(minY, y);
            maxX = qMax(maxX, x);
            maxY = qMax(maxY, y);
        }
    }

    domain()->setRange(minX, maxX, minY, maxY);
}

QList<QLegendMarker*> QXYSeriesPrivate::createLegendMarkers(QLegend* legend)
{
    Q_Q(QXYSeries);
    QList<QLegendMarker*> list;
    return list << new QXYLegendMarker(q,legend);
}

void QXYSeriesPrivate::initializeAxes()
{

}

QAbstractAxis::AxisType QXYSeriesPrivate::defaultAxisType(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return QAbstractAxis::AxisTypeValue;
}

QAbstractAxis* QXYSeriesPrivate::createDefaultAxis(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return 0;
}

void QXYSeriesPrivate::initializeAnimations(QtCommercialChart::QChart::AnimationOptions options)
{
    XYChart *item = static_cast<XYChart *>(m_item.data());
    Q_ASSERT(item);
    if (options.testFlag(QChart::SeriesAnimations)) {
        item->setAnimation(new XYAnimation(item));
    }else{
        item->setAnimation(0);
    }
    QAbstractSeriesPrivate::initializeAnimations(options);
}

#include "moc_qxyseries.cpp"
#include "moc_qxyseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
