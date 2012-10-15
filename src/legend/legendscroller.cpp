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

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QLegendMarker>
#include "qlegendmarker_p.h"
#include "legendmarkeritem_p.h"
#include "legendscroller_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendScroller::LegendScroller(QChart *chart) : QLegend(chart),
    m_lastPos(0, 0),
    m_state(Idle),
    m_treshold(10)
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

void LegendScroller::setMoveTreshold(qreal treshold)
{
    m_treshold = treshold;
}

void LegendScroller::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_pressPos = event->screenPos();
    m_lastPos = m_pressPos;
    m_state = Pressed;
    event->accept();
}

void LegendScroller::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF delta = event->screenPos() - m_lastPos;

    switch (m_state) {
    case Pressed: {
        // calculate treshold. If enough, change to move state and send out move deltas.
        if (qAbs(delta.x()) > m_treshold || qAbs(delta.y()) > m_treshold) {
            m_state = Moved;
            m_lastPos = event->screenPos();
            move(delta);
        }
        event->accept();
        break;
    }
    case Moved: {
        m_lastPos = event->screenPos();
        move(delta);
        event->accept();
        break;
    }
    case Idle:
    default: {
        event->ignore();
        break;
    }
    }
}

void LegendScroller::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastPos = event->screenPos();

    switch (m_state) {
    case Pressed:
    {
        m_state = Idle;
        QList<QGraphicsItem *> items = scene()->items(event->scenePos());

        foreach (QGraphicsItem *i, items) {
            if (d_ptr->m_markerHash.contains(i)) {
                QLegendMarker *marker = d_ptr->m_markerHash.value(i);
                emit marker->clicked();
            }
        }

        event->accept();
        break;
    }
    case Moved:
    {
        scrollTo(m_lastPos - m_pressPos);
        event->accept();
        break;
    }
    default:
    {
        m_state = Idle;
        event->ignore();
        break;
    }
    }
}


#include "moc_legendscroller_p.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
