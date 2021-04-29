/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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

class Q_CHARTS_PRIVATE_EXPORT LegendMoveResizeHandler
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
