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
#include <QAbstractItemModel>

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

/*!
    \internal \a pos
*/
QList<QPointF> QXYSeries::points() const
{
    //    Q_ASSERT(false);
    Q_D(const QXYSeries);
    if (d->m_model) {
        QList<QPointF> result;
        if (d->m_mapOrientation == Qt::Vertical){
            // consecutive data is read from model's column

            for(int i = d->m_mapFirst; i< d->m_mapFirst + count(); ++i) {
                qreal x =  d->m_model->data(d->m_model->index(i, d->m_mapX), Qt::DisplayRole).toReal();
                qreal y =  d->m_model->data(d->m_model->index(i, d->m_mapY), Qt::DisplayRole).toReal();
                result << QPointF(x,y);
            }
            return result;
        }
        else{
            // consecutive data is read from model's row
            for(int i = d->m_mapFirst; i<  d->m_mapFirst + count(); ++i) {
                qreal x =  d->m_model->data(d->m_model->index(d->m_mapX, i), Qt::DisplayRole).toReal();
                qreal y =  d->m_model->data(d->m_model->index(d->m_mapY, i), Qt::DisplayRole).toReal();
                result << QPointF(x,y);
            }
            return result;
        }
    } else {
        // model is not specified, return the data from series' internal data store
        return d->m_points.toList();
    }
}

/*!
    Returns number of data points within series.
*/
int QXYSeries::count() const
{
    Q_D(const QXYSeries);

    if (d->m_model) {
        if (d->m_mapOrientation == Qt::Vertical) {
            // data is in a column. Return the number of mapped items if the model's column have enough items
            // or the number of items that can be mapped
            if (d->m_mapCount != -1)
                return qMin(d->m_mapCount, qMax(d->m_model->rowCount() - d->m_mapFirst, 0));
            else
                return qMax(d->m_model->rowCount() - d->m_mapFirst, 0);
        } else {
            // data is in a row. Return the number of mapped items if the model's row have enough items
            // or the number of items that can be mapped
            if (d->m_mapCount != -1)
                return qMin(d->m_mapCount, qMax(d->m_model->columnCount() - d->m_mapFirst, 0));
            else
                return qMax(d->m_model->columnCount() - d->m_mapFirst, 0);
        }
    }

    // model is not specified, return the number of points in the series internal data store
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

/*!
     \fn bool QXYSeries::setModel(QAbstractItemModel *model)
     Sets the \a model to be used as a data source
     \sa setModelMapping()
 */
bool QXYSeries::setModel(QAbstractItemModel *model)
{
    Q_D(QXYSeries);
    // disconnect signals from old model
    if (d->m_model) {
        QObject::disconnect(d->m_model, 0, this, 0);
        d->m_mapX = -1;
        d->m_mapY = -1;
        d->m_mapOrientation = Qt::Vertical;
    }

    // set new model
    if (model) {
        d->m_model = model;
        return true;
    } else {
        d->m_model = 0;
        return false;
    }
}

/*!
     Sets the \a modelX to be used as a data source for x coordinate and \a modelY to be used
     as a data source for y coordinate. The \a orientation parameter specifies whether the data
     is in columns or in rows.
     \sa setModel()
 */
void QXYSeries::setModelMapping(int modelX, int modelY, Qt::Orientation orientation)
{
    Q_D(QXYSeries);
    if (d->m_model == 0)
        return;
    d->m_mapX = modelX;
    d->m_mapY = modelY;
    d->m_mapOrientation = orientation;

    // connect the signals from the model
    connect(d->m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(modelUpdated(QModelIndex,QModelIndex)));
    if (d->m_mapOrientation == Qt::Vertical) {
        connect(d->m_model,SIGNAL(rowsInserted(QModelIndex,int,int)), d, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(d->m_model,SIGNAL(rowsRemoved(QModelIndex,int,int)), d, SLOT(modelDataRemoved(QModelIndex,int,int)));
    } else {
        connect(d->m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), d, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(d->m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), d, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }
}

void QXYSeries::setModelMappingRange(int first, int count)
{
    Q_D(QXYSeries);
    d->m_mapFirst = qMax(first, 0);
    d->m_mapCount = qMax(count, -1);
}

int QXYSeries::mapX() const
{
    Q_D(const QXYSeries);
    return d->m_mapX;
}

int QXYSeries::mapY() const
{
    Q_D(const QXYSeries);
    return d->m_mapY;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


QXYSeriesPrivate::QXYSeriesPrivate(QXYSeries *q) : QAbstractSeriesPrivate(q),
    m_mapX(-1),
    m_mapY(-1),
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

    domain.setRangeX(minX,maxX,tickXCount);
    domain.setRangeY(minY,maxY,tickYCount);
}

QList<LegendMarker*> QXYSeriesPrivate::createLegendMarker(QLegend* legend)
{
    Q_Q(QXYSeries);
    QList<LegendMarker*> list;
    return list << new XYLegendMarker(q,legend);
}

void QXYSeriesPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    for (int row = topLeft.row(); row <= bottomRight.row(); row++) {
        for (int column = topLeft.column(); column <= bottomRight.column(); column++) {
            if (m_mapOrientation == Qt::Vertical) {
                if ((column == m_mapX || column == m_mapY)                          // modified item is in a mapped column
                        && row >= m_mapFirst                                        // modfied item in not before first item
                        && (m_mapCount == -1 || row < m_mapFirst + m_mapCount))     // map is not limited or item lays before the end of map
                    emit pointReplaced(row - m_mapFirst);
            } else {
                if ((row == m_mapX || row == m_mapY)                                // modified item is in a mapped row
                        && column >= m_mapFirst                                     // modfied item in not before first item
                        && (m_mapCount == -1 || column < m_mapFirst + m_mapCount))  // map is not limited or item lays before the end of map
                    emit pointReplaced(column - m_mapFirst);
            }
        }
    }
}


void QXYSeriesPrivate::modelDataAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    emit pointsAdded(start, end);
}

void QXYSeriesPrivate::modelDataRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    emit pointsRemoved(start, end);
}

#include "moc_qxyseries.cpp"
#include "moc_qxyseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
