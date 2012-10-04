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

#include "scroller_p.h"
#include "qlegend.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Scroller::Scroller()
    : m_ticker(this),
      m_timeTresholdMin(50),
      m_timeTresholdMax(300),
      m_state(Idle)
{

}

Scroller::~Scroller()
{
}

void Scroller::move(const QPointF &delta)
{
    switch (m_state) {
    case Idle:
        m_timeStamp = QTime::currentTime();
        m_state = Move;
        break;
    case Scroll:
        stopTicker();
        m_timeStamp = QTime::currentTime();
        m_state = Move;
        break;
    default:
        break;
    }
    setOffset(offset() - delta);
}

void Scroller::release(const QPointF &delta)
{
    // Starts scrolling, if at least m_timeTresholdMin msecs has gone since timestamp
    // current time is no more than m_timeTresholdMax from timestamp

    if ((m_timeStamp.elapsed() > m_timeTresholdMin) && (m_timeStamp.msecsTo(QTime::currentTime()) < m_timeTresholdMax)) {
        // Release was quick enough. Start scrolling.
        // Magic number is to make scroll bit slower (the resolution of screen may affect this)
        m_speed = delta / 5;

        qreal fraction = qMax(qAbs(m_speed.x()), qAbs(m_speed.y()));

        if (!qFuzzyIsNull(fraction)) {
            m_fraction.setX(qAbs(m_speed.x() / fraction));
            m_fraction.setY(qAbs(m_speed.y() / fraction));
        } else {
            m_fraction.setX(1);
            m_fraction.setY(1);
        }
        startTicker(25);
        m_state = Scroll;
    } else {
        stopTicker();   // Stop ticker, if one is running.
        m_state = Idle;
    }
}

void Scroller::startTicker(int interval)
{
    m_state = Scroll;
    m_ticker.start(interval);
}

void Scroller::stopTicker()
{
    m_state = Idle;
    m_ticker.stop();
}

void Scroller::scrollTick()
{
    switch (m_state) {
    case Scroll:
        lowerSpeed(m_speed);
        setOffset(offset() - m_speed);
        if (m_speed == QPointF(0, 0)) {
            m_state = Idle;
            m_ticker.stop();
        }
        break;
    case Idle:
    case Move:
        qWarning() << __FUNCTION__ << "Scroller unexpected state" << m_state;
        m_ticker.stop();
        m_state = Idle;
        break;
    }
}

void Scroller::lowerSpeed(QPointF &speed, qreal maxSpeed)
{
    qreal x = qBound(-maxSpeed, speed.x(), maxSpeed);
    qreal y = qBound(-maxSpeed, speed.y(), maxSpeed);

    x = (x == 0) ? x :
        (x > 0) ? qMax(qreal(0), x - m_fraction.x()) : qMin(qreal(0), x + m_fraction.x());
    y = (y == 0) ? y :
        (y > 0) ? qMax(qreal(0), y - m_fraction.y()) : qMin(qreal(0), y + m_fraction.y());
    speed.setX(x);
    speed.setY(y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ScrollTicker::ScrollTicker(Scroller *scroller, QObject *parent)
    : QObject(parent),
      m_scroller(scroller)
{

}

void ScrollTicker::start(int interval)
{
    if (!m_timer.isActive())
        m_timer.start(interval, this);
}

void ScrollTicker::stop()
{
    m_timer.stop();
}

void ScrollTicker::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    m_scroller->scrollTick();
}

#include "moc_scroller_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
