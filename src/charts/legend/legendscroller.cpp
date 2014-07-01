/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QLegendMarker>
#include "qlegendmarker_p.h"
#include "legendmarkeritem_p.h"
#include "legendscroller_p.h"

QT_CHARTS_BEGIN_NAMESPACE

LegendScroller::LegendScroller(QChart *chart) : QLegend(chart)
{
}

void LegendScroller::setOffset(const QPointF &point)
{
    d_ptr->setOffset(point);
}

QPointF LegendScroller::offset() const
{
    return d_ptr->offset();
}

void LegendScroller::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Scroller::handleMousePressEvent(event);
}

void LegendScroller::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Scroller::handleMouseMoveEvent(event);
}

void LegendScroller::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Scroller::handleMouseReleaseEvent(event);

    if (!event->isAccepted()) {
        QList<QGraphicsItem *> items = scene()->items(event->scenePos());

        foreach (QGraphicsItem *i, items) {
            if (d_ptr->m_markerHash.contains(i)) {
                QLegendMarker *marker = d_ptr->m_markerHash.value(i);
                emit marker->clicked();
            }
        }
    event->accept();
    }
}


#include "moc_legendscroller_p.cpp"
QT_CHARTS_END_NAMESPACE
