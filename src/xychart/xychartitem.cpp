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

#include "xychartitem_p.h"
#include "qxyseries.h"
#include "qxyseries_p.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QAbstractItemModel>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

XYChartItem::XYChartItem(QXYSeries *series, ChartPresenter *presenter):ChartItem(presenter),
    m_minX(0),
    m_maxX(0),
    m_minY(0),
    m_maxY(0),
    m_series(series)
{
    connect(series->d_func(),SIGNAL(pointReplaced(int)),this,SLOT(handlePointReplaced(int)));
    connect(series->d_func(),SIGNAL(pointAdded(int)),this,SLOT(handlePointAdded(int)));
    connect(series->d_func(),SIGNAL(pointsAdded(int, int)),this,SLOT(handlePointsAdded(int, int)));
    connect(series->d_func(),SIGNAL(pointRemoved(int)),this,SLOT(handlePointRemoved(int)));
    connect(series->d_func(),SIGNAL(pointsRemoved(int, int)),this,SLOT(handlePointsRemoved(int, int)));
    connect(this,SIGNAL(clicked(QPointF)),series,SIGNAL(clicked(QPointF)));
}

QPointF XYChartItem::calculateGeometryPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);
    qreal x = (point.x() - m_minX)* deltaX;
    qreal y = (point.y() - m_minY)*-deltaY + m_size.height();
    return QPointF(x,y);
}


QPointF XYChartItem::calculateGeometryPoint(int index) const
{
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);
    qreal x = (m_series->x(index) - m_minX)* deltaX;
    qreal y = (m_series->y(index) - m_minY)*-deltaY + m_size.height();
    return QPointF(x,y);
}

QVector<QPointF> XYChartItem::calculateGeometryPoints() const
{
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);

    QVector<QPointF> points;
    points.reserve(m_series->count());
    for (int i = 0; i < m_series->count(); ++i) {
        qreal x = (m_series->x(i) - m_minX)* deltaX;
        qreal y = (m_series->y(i) - m_minY)*-deltaY + m_size.height();
        points << QPointF(x,y);
    }
    return points;
}

QPointF XYChartItem::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width()/(m_maxX-m_minX);
    const qreal deltaY = m_size.height()/(m_maxY-m_minY);
    qreal x = point.x()/deltaX +m_minX;
    qreal y = (point.y()-m_size.height())/(-deltaY)+ m_minY;
    return QPointF(x,y);
}

void XYChartItem::updateLayout(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints,int index)
{
    if (animator()) {
        animator()->updateLayout(this,oldPoints,newPoints,index);
    } else {
        setLayout(newPoints);
    }
}

void XYChartItem::setLayout(QVector<QPointF> &points)
{
    m_points = points;
    update();
}

//handlers

void XYChartItem::handlePointAdded(int index)
{
    if (m_series->model() == 0) {
        Q_ASSERT(index<m_series->count());
        Q_ASSERT(index>=0);
    }
    QVector<QPointF> points = m_points;
    QPointF point;
    point = calculateGeometryPoint(index);
    points.insert(index, point);
    updateLayout(m_points, points, index);
    update();
}

void XYChartItem::handlePointsAdded(int start, int end)
{
    if (m_series->model() == 0) {
        for (int i = start; i <= end; i++)
            handlePointAdded(i);
    } else {
        // series uses model as a data source
        int first = m_series->mapFirst();
        int count = m_series->mapCount();
        int addedCount = end - start + 1;
        if (count != -1 && start >= first + count) {
            return;
        }

        // adding items to unlimited map
        else if (count == -1 && start >= first) {
            for (int i = start; i <= end; i++)
                handlePointAdded(i - first);
        } else if (count == - 1 && start < first) {
            // not all newly added items
            for (int i = first; i < first + addedCount; i++)
                handlePointAdded(i - first);
        }
        // commented out code below does the same thing, but its more confusing.
        //        } else if (count == -1) {
        //            int begin = qMax(start, first);
        //            for (int i = begin; i < begin + (end - start + 1); i++)
        //                handlePointAdded(i - first);
        //        }

        // adding items to limited map
        else if (start >= first) {
            // remove the items that will no longer fit into the map
            // int toRemove = addedCount - (count - points().size());
            for (int i = start; i <= end; i++) {
                handlePointAdded(i - first);
            }
            if (m_points.size() > count)
                for (int i = m_points.size() - 1; i >= count; i--)
                    handlePointRemoved(i);
            //            update();
        } else {
            //
            for (int i = first; i < first + addedCount; i++) {
                handlePointAdded(i - first);
            }
            if (m_points.size() > count)
                for (int i = m_points.size() - 1; i >= count; i--)
                    handlePointRemoved(i);
        }
    }
}

void XYChartItem::handlePointRemoved(int index)
{
    if (m_series->model() == 0) {
        Q_ASSERT(index<m_series->count() + 1);
        Q_ASSERT(index>=0);
    }
    QVector<QPointF> points = m_points;
    points.remove(index);
    updateLayout(m_points, points, index);
    update();
}

void XYChartItem::handlePointsRemoved(int start, int end)
{
    Q_UNUSED(start)
    Q_UNUSED(end)
    if (m_series->model() == 0) {
        for (int i = end; i >= start; i--)
            handlePointRemoved(i);
    } else {
        // series uses model as a data source
        int first = m_series->mapFirst();
        int count = m_series->mapCount();
        int removedCount = end - start + 1;
        if (count != -1 && start >= first + count) {
            return;
        }

        // removing items from unlimited map
        else if (count == -1 && start >= first) {
            for (int i = end; i >= start; i--)
                handlePointRemoved(i - first);
        } else if (count == - 1 && start < first) {
            // not all removed items
            for (int i = first + removedCount - 1; i >= first; i--)
                handlePointRemoved(i - first);
        }

        // removing items from limited map
        else if (start >= first) {
            //
            int lastExisting = qMin(first + m_points.size() - 1, end);
            for (int i = lastExisting; i >= start; i--) {
                handlePointRemoved(i - first);
            }

            // the map is limited, so after removing the items some new items may have fall within the mapped area
            int itemsAvailable;
            if (m_series->mapOrientation() == Qt::Vertical)
                itemsAvailable = m_series->model()->rowCount() - first - m_points.size();
            else
                itemsAvailable = m_series->model()->columnCount() - first - m_points.size();
            int toBeAdded = qMin(itemsAvailable, count - m_points.size());
            int currentSize = m_points.size();
            if (itemsAvailable > 0)
                for (int i = m_points.size(); i < currentSize + toBeAdded; i++)
                    handlePointAdded(i);
        } else {
            // first removed item lays before the mapped area
            int toRemove = qMin(m_points.size() - 1, removedCount);
            for (int i = first; i < first + toRemove; i++)
                handlePointRemoved(0);

            // the map is limited, so after removing the items some new items may have fall into the map
            int itemsAvailable;
            if (m_series->mapOrientation() == Qt::Vertical)
                itemsAvailable = m_series->model()->rowCount() - first - m_points.size();
            else
                itemsAvailable = m_series->model()->columnCount() - first - m_points.size();
            int toBeAdded = qMin(itemsAvailable, count - m_points.size());
            int currentSize = m_points.size();
            if (itemsAvailable > 0)
                for (int i = m_points.size(); i < currentSize + toBeAdded; i++)
                    handlePointAdded(i);
        }
    }

}

void XYChartItem::handlePointReplaced(int index)
{
    Q_ASSERT(index<m_series->count());
    Q_ASSERT(index>=0);
    QPointF point = calculateGeometryPoint(index);
    QVector<QPointF> points = m_points;
    points.replace(index,point);
    updateLayout(m_points,points,index);
    update();
}

void XYChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    m_minX=minX;
    m_maxX=maxX;
    m_minY=minY;
    m_maxY=maxY;

    if (isEmpty()) return;
    QVector<QPointF> points = calculateGeometryPoints();
    updateLayout(m_points,points);
    update();
}

void XYChartItem::handleGeometryChanged(const QRectF &rect)
{
    Q_ASSERT(rect.isValid());
    m_size=rect.size();
    m_clipRect=rect.translated(-rect.topLeft());
    setPos(rect.topLeft());

    if (isEmpty()) return;
    QVector<QPointF> points = calculateGeometryPoints();
    updateLayout(m_points,points);
    update();
}


bool XYChartItem::isEmpty()
{
    return !m_clipRect.isValid() || qFuzzyIsNull(m_maxX - m_minX) || qFuzzyIsNull(m_maxY - m_minY);
}

void XYChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(calculateDomainPoint(event->pos()));
}

#include "moc_xychartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
