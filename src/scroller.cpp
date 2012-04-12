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

Scroller::Scroller():
m_ticker(this),
m_state(Idle),
m_moveThreshold(10),
m_timeTreshold(50)
{

}

Scroller::~Scroller()
{
}

void Scroller::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {

        switch (m_state) {
        case Idle:
        {
            m_state = Pressed;
            m_offset = offset();
            m_press = event->pos();
            m_timeStamp = QTime::currentTime();
            event->accept();
            break;
        }
        case Scroll:
        {
            m_state = Stop;
            m_speed = QPoint(0, 0);
            m_offset = offset();
            m_press = event->pos();
            event->accept();
            break;
        }
        case Pressed:
        case Move:
        case Stop:
            qWarning() << __FUNCTION__<<"Scroller unexpected state" << m_state;
            event->ignore();
            break;
        }
    }
}

void Scroller::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF delta = event->pos() - m_press;

    switch (m_state) {
    case Pressed:
    case Stop:
    {
        if (qAbs(delta.x()) > m_moveThreshold || qAbs(delta.y()) > m_moveThreshold) {
            m_state = Move;
            m_timeStamp = QTime::currentTime();
            m_distance = QPointF(0, 0);
            m_press = event->pos();
            event->accept();
            break;
        }
        else {
            event->ignore();
            break;
        }
    }
    case Move:
    {
        setOffset(m_offset - delta);
        calculateSpeed(event->pos());
        event->accept();
        break;
    }
    case Idle:
    case Scroll:
        qWarning() << __FUNCTION__<<"Scroller unexpected state" << m_state;
        event->ignore();
        break;
    }

}

void Scroller::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {

        switch (m_state) {

        case Scroll:
            m_state = Stop;
            m_speed = QPointF(0, 0);
            m_offset = offset();
            event->accept();
            break;
        case Pressed:
        {
            m_state = Idle;
            //if (m_timeStamp.elapsed() < m_clickedPressDelay) {

            //emit clicked(m_offset.toPoint());
            //}
            event->accept();
            break;
        }
        case Move:
        {
            calculateSpeed(event->pos());
            m_offset = offset();
            m_press = event->pos();
            if (m_speed == QPointF(0, 0)) {
                m_state = Idle;
            }
            else {
                m_speed /= 4;
                m_state = Scroll;
                m_ticker.start(20);
            }
            event->accept();
            break;
        }

        case Stop:
        case Idle:
            qWarning() << __FUNCTION__<<"Scroller unexpected state" << m_state;
            event->ignore();
            break;

        }
    }
}

void Scroller::scrollTick()
{
    switch (m_state) {
        case Scroll:
        {
            lowerSpeed(m_speed);
            setOffset(m_offset - m_speed);
            m_offset = offset();
            if (m_speed == QPointF(0, 0)) {
                m_state = Idle;
                m_ticker.stop();
            }
            break;
        }
        case Stop:
            m_ticker.stop();
            break;
        case Idle:
        case Move:
        case Pressed:
            qWarning() << __FUNCTION__<<"Scroller unexpected state" << m_state;
            m_ticker.stop();
        break;

    }
}

void Scroller::lowerSpeed(QPointF& speed, qreal maxSpeed)
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

void Scroller::calculateSpeed(const QPointF& position)
{
    if (m_timeStamp.elapsed() > m_timeTreshold) {

        QPointF distance = position - m_press;

        m_timeStamp = QTime::currentTime();
        m_speed = distance -  m_distance;
        m_distance = distance;

        qreal fraction = qMax(qAbs(m_speed.x()), qAbs(m_speed.y()));

        if (fraction != 0) {
            m_fraction.setX(qAbs(m_speed.x() / fraction));
            m_fraction.setY(qAbs(m_speed.y() / fraction));
        }
        else {
            m_fraction.setX(1);
            m_fraction.setY(1);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ScrollTicker::ScrollTicker(Scroller *scroller,QObject* parent):QObject(parent),
    m_scroller(scroller)
{

}

void ScrollTicker::start(int interval)
{
    if (!m_timer.isActive()){
        m_timer.start(interval, this);
    }
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
