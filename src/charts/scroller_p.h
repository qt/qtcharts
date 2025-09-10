// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef SCROLLER_P_H
#define SCROLLER_P_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>
#include <QtCore/QBasicTimer>
#include <QtCore/QElapsedTimer>
#include <QtCore/QPointF>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class Scroller;
class QLegend;

class Q_CHARTS_EXPORT ScrollTicker : public QObject
{
    Q_OBJECT
public:
    explicit ScrollTicker(Scroller *scroller, QObject *parent = 0);
    void start(int interval);
    void stop();
protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QBasicTimer m_timer;
    Scroller *m_scroller;
};

class Q_CHARTS_EXPORT Scroller
{
public:
    enum State {
        Idle,
        Pressed,
        Move,
        Scroll
    };

    Scroller();
    virtual ~Scroller();

    virtual void setOffset(const QPointF &point) = 0;
    virtual QPointF offset() const = 0;

    void move(const QPointF &delta);
    void scrollTo(const QPointF &delta);

    void handleMousePressEvent(QGraphicsSceneMouseEvent *event);
    void handleMouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void handleMouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void scrollTick();

private:
    void startTicker(int interval);
    void stopTicker();

private:
    void calculateSpeed(const QPointF &position);
    void lowerSpeed(QPointF &speed, qreal maxSpeed = 100);

private:
    ScrollTicker m_ticker;
    QElapsedTimer m_timeStamp;
    QPointF m_speed;
    QPointF m_fraction;
    int m_timeTresholdMin;
    int m_timeTresholdMax;

    State m_state;
    QPointF m_pressPos;
    QPointF m_lastPos;
    qreal m_treshold;
};

QT_END_NAMESPACE

#endif /* SCROLLER_P_H */
