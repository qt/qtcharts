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
#include "domain_p.h"
#include "legendmarker_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QXYSeries
    \brief The QXYSeries class is a base class for line, spline and scatter series.
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
    \fn void QXYSeries::clicked(const QPointF& point)
    \brief Signal is emitted when user clicks the \a point on chart.
*/


/*!
    \fn void QXYSeriesPrivate::pointReplaced(int index)
    \brief \internal \a index
*/

/*!
    \fn void QXYSeriesPrivate::pointAdded(int index)
    \brief \internal \a index
*/

/*!
    \fn void QXYSeriesPrivate::pointRemoved(int index)
    \brief \internal \a index
*/

/*!
    \fn void QXYSeriesPrivate::updated()
    \brief \internal
*/

/*!
    \internal

    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance ownerships is transferred.
*/
QXYSeries::QXYSeries(QXYSeriesPrivate &d,QObject *parent) : QAbstractSeries(d, parent)
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
void QXYSeries::append(qreal x,qreal y)
{
    append(QPointF(x,y));
}

/*!
   This is an overloaded function.
   Adds data \a point to the series. Points are connected with lines on the chart.
 */
void QXYSeries::append(const QPointF &point)
{
    Q_D(QXYSeries);
    d->m_points<<point;
    emit d->pointAdded(d->m_points.count()-1);
}

/*!
   This is an overloaded function.
   Adds list of data \a points to the series. Points are connected with lines on the chart.
 */
void QXYSeries::append(const QList<QPointF> &points)
{
    foreach(const QPointF& point , points) {
        append(point);
    }
}


void QXYSeries::replace(qreal oldX,qreal oldY,qreal newX,qreal newY)
{
    replace(QPointF(oldX,oldY),QPointF(newX,newY));
}

void QXYSeries::replace(const QPointF &oldPoint,const QPointF &newPoint)
{
    Q_D(QXYSeries);
    int index = d->m_points.indexOf(oldPoint);
    if(index==-1) return;
    d->m_points[index] = newPoint;
    emit d->pointReplaced(index);
}

/*!
  Removes current \a x and \a y value.
*/
void QXYSeries::remove(qreal x,qreal y)
{
    remove(QPointF(x,y));
}

/*!
  Removes current \a point x value. Note \a point y value is ignored.
*/
void QXYSeries::remove(const QPointF &point)
{
    Q_D(QXYSeries);
    int index = d->m_points.indexOf(point);
    if(index==-1) return;
    d->m_points.remove(index);
    emit d->pointRemoved(index);
}

/*!
   Removes all data points from the series.
*/
void QXYSeries::removeAll()
{
    Q_D(QXYSeries);
    foreach(const QPointF& point, d->m_points) {
        remove(point);
    }
}

void QXYSeries::insert(int index, const QPointF &point)
{
    Q_D(QXYSeries);
    d->m_points.insert(index, point);
    emit d->pointAdded(index);
}

void QXYSeries::clear()
{
    Q_D(QXYSeries);
    for (int i = d->m_points.size() - 1; i >= 0; i--)
        remove(d->m_points.at(i));
}

/*!
    \internal \a pos
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
    if (d->m_pen!=pen) {
        d->m_pen = pen;
        emit d->updated();
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
    if (d->m_brush!=brush) {
        d->m_brush = brush;
        emit d->updated();
    }
}

QBrush QXYSeries::brush() const
{
    Q_D(const QXYSeries);
    return d->m_brush;
}


/*!
    Sets if data points are \a visible and should be drawn on line.
*/
void QXYSeries::setPointsVisible(bool visible)
{
    Q_D(QXYSeries);
    if (d->m_pointsVisible != visible){
        d->m_pointsVisible = visible;
        emit d->updated();
    }
}

/*!
    Returns true if drawing the data points of the series is enabled.
*/
bool QXYSeries::pointsVisible() const
{
    Q_D(const QXYSeries);
    return d->m_pointsVisible;
}


/*!
    Stream operator for adding a data \a point to the series.
    \sa append()
*/
QXYSeries& QXYSeries::operator<< (const QPointF &point)
{
    append(point);
    return *this;
}


/*!
    Stream operator for adding a list of \a points to the series.
    \sa append()
*/

QXYSeries& QXYSeries::operator<< (const QList<QPointF>& points)
{
    append(points);
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


QXYSeriesPrivate::QXYSeriesPrivate(QXYSeries *q) :
    QAbstractSeriesPrivate(q),
    m_pointsVisible(false)
{
}

void QXYSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    Q_Q(QXYSeries);

    const QList<QPointF>& points = q->points();


    if(points.isEmpty()){
        minX=0.0;
        minY=0.0;
        maxX=1.0;
        maxY=1.0;
    }

    for (int i = 0; i < points.count(); i++)
    {
        qreal x = points[i].x();
        qreal y = points[i].y();
        minX = qMin(minX, x);
        minY = qMin(minY, y);
        maxX = qMax(maxX, x);
        maxY = qMax(maxY, y);
    }

    domain.setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
}

QList<LegendMarker*> QXYSeriesPrivate::createLegendMarker(QLegend* legend)
{
    Q_Q(QXYSeries);
    QList<LegendMarker*> list;
    return list << new XYLegendMarker(q,legend);
}

#include "moc_qxyseries.cpp"
#include "moc_qxyseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
