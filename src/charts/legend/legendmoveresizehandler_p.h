// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef LEGENDMOVERESIZEHANDLER_P_H
#define LEGENDMOVERESIZEHANDLER_P_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QPointF>
#include <QtCharts/qlegend.h>
#include <QtCharts/private/qlegend_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;

class Q_CHARTS_EXPORT LegendMoveResizeHandler
{
public:
    LegendMoveResizeHandler(QLegend *legend);
    ~LegendMoveResizeHandler();

    inline bool shouldShowMoveHint() const { return m_mode == MousePosition::Top; }
    void reset();

    void handleMousePressEvent(QGraphicsSceneMouseEvent *event);
    void handleMouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void handleMouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void handleHoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void handleHoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void handleHoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    enum class Action {
        Idle    = 0x00,
        Hovered = 0x01,
        Pressed = 0x02,
        Moving  = 0x04,
        Resizing= 0x08
    };

    enum class MousePosition {
        Nowhere,
        TopLeft,
        BottomRight,
        BottomLeft,
        TopRight,
        Top,
        Bottom,
        Left,
        Right
    };

    void setMouseCursor();
    void setMouseCursor(MousePosition mpos);
    void determineMousePosition(QPointF fromPoint);

    QLegend *m_legend{nullptr};
    QPointF m_moveOffset{0.0,0.0};
    Action m_action{Action::Idle};
    MousePosition m_mode{MousePosition::Nowhere};
    qreal m_reattachThreshold{0.0};
};

QT_END_NAMESPACE

#endif
