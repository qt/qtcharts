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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

/*
    Purpose of this class is to resolve what happens during MousePress - MouseMove - MouseRelease event chain.
    Threre can be many MouseMove events and if they all are below our treshold, the result is clicked call.
    If any move event goes over treshold, result will be many moved(QPointF delta) calls,
    where delta is calculated from original position.

    Reason for this is, that legend marker don't know when it should emit clicked and when it should
    allow legend to scroll. We only get this information when some move goes beyond treshold, but
    then it will be too late to let the scroller handle events, because marker is already handling.

    By handling clicked calls in markers and moved calls in scroller, the problem is solved.
    Derived class descides, should the virtual method be implemented as signal or not.

    This could be implemented in LegendMarkerItem, but this way the code is reusable and in one place only.
*/

#ifndef MOUSEEVENTHANDLER_H
#define MOUSEEVENTHANDLER_H

#include "qchartglobal.h"
#include <QBasicTimer>
#include <QTime>
#include <QPointF>

class QGraphicsSceneMouseEvent;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class MouseEventHandler
{
public:
    enum State {
        Idle,
        Pressed,
        Moved,
        Released
    };

    MouseEventHandler();
    virtual ~MouseEventHandler();

    void setMoveTreshold(qreal treshold);

    virtual void mouseClicked() = 0;
    virtual void mouseMoved(QPointF delta) = 0;
    virtual void mouseReleased(QPointF delta) = 0;

    void handleMousePressEvent(QGraphicsSceneMouseEvent* event);
    void handleMouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void handleMouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    QPointF m_lastPos;
    State m_state;
    qreal m_treshold;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // MOUSEEVENTHANDLER_H
