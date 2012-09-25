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

#ifndef SCROLLER_P_H
#define SCROLLER_P_H

#include "qchartglobal.h"
#include <QBasicTimer>
#include <QTime>
#include <QPointF>

class QGraphicsSceneMouseEvent;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Scroller;
class QLegend;

class ScrollTicker : public QObject
{
    Q_OBJECT
public:
    explicit ScrollTicker(Scroller *scroller, QObject *parent = 0);
    void start(int interval);
    void stop();
protected:
    void timerEvent(QTimerEvent *event);

private:
    QBasicTimer m_timer;
    Scroller *m_scroller;
};

class Scroller
{
public:
    enum State {
        Idle,
        Pressed,
        Move,
        Scroll,
        Stop
    };

    Scroller();
    virtual ~Scroller();

    virtual void setOffset(const QPointF &point) = 0;
    virtual QPointF offset() const = 0;

public:
    void scrollTick();

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void calculateSpeed(const QPointF &position);
    void lowerSpeed(QPointF &speed, qreal maxSpeed = 100);

private:
    ScrollTicker m_ticker;
    State m_state;
    QTime m_timeStamp;
    QPointF m_press;
    QPointF m_offset;
    QPointF m_speed;
    QPointF m_distance;
    QPointF m_fraction;
    int m_moveThreshold;
    int m_timeTreshold;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* SCROLLER_P_H */
