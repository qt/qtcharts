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

#include "mouseeventhandler_p.h"
#include <QGraphicsSceneMouseEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

MouseEventHandler::MouseEventHandler() :
    m_lastPos(0, 0),
    m_state(Idle),
    m_treshold(10)
{
}

MouseEventHandler::~MouseEventHandler()
{
}

void MouseEventHandler::setMoveTreshold(qreal treshold)
{
    m_treshold = treshold;
}

void MouseEventHandler::handleMousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_lastPos = event->screenPos();
    m_state = Pressed;
    event->accept();
}

void MouseEventHandler::handleMouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF delta = event->screenPos() - m_lastPos;

    switch (m_state) {
    case Pressed: {
        // calculate treshold. If enough, change to move state and send out move deltas.
        if (qAbs(delta.x()) > m_treshold || qAbs(delta.y()) > m_treshold) {
            m_state = Moved;
            m_lastPos = event->screenPos();
            mouseMoved(delta);
        }
        event->accept();
        break;
    }
    case Moved: {
        m_lastPos = event->screenPos();
        mouseMoved(delta);
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

void MouseEventHandler::handleMouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    m_lastPos = event->screenPos();

    switch (m_state) {
    case Pressed:
    {
        m_state = Idle;
        mouseClicked();
        event->accept();
        break;
    }
    case Moved:
    {
        m_state = Idle;
        mouseReleased(m_lastPos);
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

QTCOMMERCIALCHART_END_NAMESPACE
