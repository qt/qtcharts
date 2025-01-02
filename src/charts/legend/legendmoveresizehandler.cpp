// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtGui/QCursor>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtWidgets/QGraphicsSceneHoverEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QChart>
#include <private/legendlayout_p.h>
#include <private/legendmoveresizehandler_p.h>

QT_BEGIN_NAMESPACE

LegendMoveResizeHandler::LegendMoveResizeHandler(QLegend *legend) :
    m_legend(legend)
{
    m_legend->setAcceptHoverEvents(true);
    m_legend->setCursor(Qt::ArrowCursor);
}

LegendMoveResizeHandler::~LegendMoveResizeHandler()
{
}

void LegendMoveResizeHandler::reset()
{
    m_action = Action::Idle;
    setMouseCursor(MousePosition::Nowhere);
}

void LegendMoveResizeHandler::handleMousePressEvent(QGraphicsSceneMouseEvent *event)
{
    determineMousePosition(event->pos());
    m_moveOffset = event->pos();
    m_action = Action::Pressed;

    // Since the legend does not have a proper frame,
    // with a title bar, we have replaced the "top" from
    // being a resize bar to being a move area. This
    // is evident to the user as the mouse cursor
    // changes to an open hand while over the top
    // in hover mode, and a closed hand when the mouse
    // button is pressed.
    if (m_legend->isAttachedToChart()) {
        m_action = Action::Idle;
    } else if (m_mode == MousePosition::Top) {
        m_action = Action::Moving;
        setMouseCursor();
    } else if (m_mode != MousePosition::Nowhere) {
        m_action = Action::Resizing;
    }
}

void LegendMoveResizeHandler::handleMouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF geom = m_legend->geometry();
    QMarginsF reattachMargins{m_reattachThreshold, m_reattachThreshold, m_reattachThreshold, m_reattachThreshold};
    QRectF dragArea = m_legend->parentWidget()->geometry() - reattachMargins;

    if (m_action == Action::Moving) {
        bool reattach = true;
        QPointF toPoint = event->scenePos() - m_moveOffset;

        if (event->scenePos().x() <= dragArea.left())
            m_legend->setAlignment(Qt::AlignLeft);
        else if (event->scenePos().x() >= dragArea.right())
            m_legend->setAlignment(Qt::AlignRight);
        else if (event->scenePos().y() <= dragArea.top())
            m_legend->setAlignment(Qt::AlignTop);
        else if (event->scenePos().y() >= dragArea.bottom())
            m_legend->setAlignment(Qt::AlignBottom);
        else
            reattach = false;

        QRectF potentialGeom(geom);
        potentialGeom.moveTopLeft(toPoint);
        if (potentialGeom.left() <= dragArea.left())
            toPoint.setX(dragArea.left());
        else if (potentialGeom.right() >= dragArea.right())
            toPoint.setX(dragArea.right() - geom.width());

        if (potentialGeom.top() <= dragArea.top())
            toPoint.setY(dragArea.top());
        else if (potentialGeom.bottom() >= dragArea.bottom())
            toPoint.setY(dragArea.bottom() - geom.height());

        // Set the geometry to be the new desired position corrected to
        // be within the bounds of the dragArea.
        geom.moveTopLeft(toPoint);
        if (geom != m_legend->geometry())
            m_legend->setGeometry(geom);

        if (reattach && !m_legend->isAttachedToChart()) {
            m_action = Action::Idle;
            m_mode = MousePosition::Nowhere;
            setMouseCursor();
            m_legend->attachToChart();
        }
    } else if (m_action == Action::Resizing) {
        QPointF trackPoint = event->scenePos();
        QRectF boundRect = m_legend->parentWidget()->geometry();

        if (trackPoint.x() <= boundRect.left())
            trackPoint.rx() = boundRect.left() + 1;
        else if (trackPoint.x() >= boundRect.right())
            trackPoint.rx() = boundRect.right() - 1;

        if (trackPoint.y() <= boundRect.top())
            trackPoint.ry() = boundRect.top() + 1;
        else if (trackPoint.y() >= boundRect.bottom())
            trackPoint.ry() = boundRect.bottom();

        switch (m_mode) {
        case MousePosition::TopLeft:
            geom = QRectF(trackPoint, geom.bottomRight());
            break;
        case MousePosition::BottomRight:
            geom = QRectF(geom.topLeft(), trackPoint);
            break;
        case MousePosition::BottomLeft:
            geom = QRectF(QPointF(trackPoint.x(), geom.y()), QPointF(geom.right(), trackPoint.y()));
            break;
        case MousePosition::TopRight:
            geom = QRectF(QPointF(geom.x(), trackPoint.y()), QPoint(trackPoint.x(), geom.bottom()));
            break;
        case MousePosition::Bottom:
            geom = QRectF(geom.topLeft(), QPointF(geom.right(), trackPoint.y()));
            break;
        case MousePosition::Left:
            geom = QRectF(QPointF(trackPoint.x(), geom.top()), geom.bottomRight());
            break;
        case MousePosition::Right:
            geom = QRectF(geom.topLeft(), QPointF(trackPoint.x(), geom.bottom()));
            break;
        default:
            break;
        }

        geom = QRectF(geom.topLeft(),
                      geom.size().expandedTo(m_legend->d_ptr->m_layout->minimumSize())
                      .boundedTo((boundRect & geom).size()));

        if (geom.size() != m_legend->geometry().size())
            m_legend->setGeometry(geom);
    }
}

void LegendMoveResizeHandler::handleMouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_action = Action::Idle;
    determineMousePosition(event->pos());
    setMouseCursor();
}

void LegendMoveResizeHandler::handleHoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!m_legend->isAttachedToChart()) {
        determineMousePosition(event->pos());
        setMouseCursor();
    }
    m_action = Action::Hovered;
}

void LegendMoveResizeHandler::handleHoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!m_legend->isAttachedToChart()) {
        determineMousePosition(event->pos());
        setMouseCursor();
    }
    m_action = Action::Hovered;
}

void LegendMoveResizeHandler::handleHoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    if (!m_legend->isAttachedToChart()) {
        m_mode = MousePosition::Nowhere;
        setMouseCursor();
    }
    m_action = Action::Idle;
}

void LegendMoveResizeHandler::setMouseCursor()
{
    setMouseCursor(m_mode);
}

void LegendMoveResizeHandler::setMouseCursor(MousePosition mpos)
{
#ifdef QT_NO_CURSOR
    Q_UNUSED(mpos);
    return;
#else
    const QList<QGraphicsItem*> items = m_legend->d_ptr->m_items->childItems();
    for (const auto item : items) {
        if (!item->hasCursor())
            item->setCursor(Qt::ArrowCursor);
    }

    switch (mpos) {
    case MousePosition::TopLeft:
    case MousePosition::BottomRight:
        m_legend->setCursor(Qt::SizeFDiagCursor);
        break;
    case MousePosition::BottomLeft:
    case MousePosition::TopRight:
        m_legend->setCursor(Qt::SizeBDiagCursor);
        break;
    case MousePosition::Top:
        if (m_action == Action::Moving)
            m_legend->setCursor(Qt::ClosedHandCursor);
        else
            m_legend->setCursor(Qt::OpenHandCursor);
        break;
    case MousePosition::Bottom:
        m_legend->setCursor(Qt::SizeVerCursor);
        break;
    case MousePosition::Left:
    case MousePosition::Right:
        m_legend->setCursor(Qt::SizeHorCursor);
        break;
    case MousePosition::Nowhere:
        m_legend->setCursor(Qt::ArrowCursor);
        break;
    }
#endif
}

void LegendMoveResizeHandler::determineMousePosition(QPointF fromPoint)
{
    QRectF contentRect = m_legend->d_ptr->m_layout->contentsRect();

    if (fromPoint.x() <= contentRect.left()) {
        if (fromPoint.y() <= contentRect.top())
            m_mode = MousePosition::TopLeft;
        else if (fromPoint.y() >= contentRect.bottom())
            m_mode = MousePosition::BottomLeft;
        else
            m_mode = MousePosition::Left;
    } else if (fromPoint.x() > contentRect.left() && fromPoint.x() < contentRect.right()) {
        if (fromPoint.y() <= contentRect.top())
            m_mode = MousePosition::Top;
        else if (fromPoint.y() >= contentRect.bottom())
            m_mode = MousePosition::Bottom;
        else
            // This catches a corner case where the mouse
            // position y is inside of the content rect
            m_mode = MousePosition::Nowhere;
    } else if (fromPoint.x() >= contentRect.left()) {
        if (fromPoint.y() <= contentRect.top())
            m_mode = MousePosition::TopRight;
        else if (fromPoint.y() >= contentRect.bottom())
            m_mode = MousePosition::BottomRight;
        else
            m_mode = MousePosition::Right;
    } else {
        m_mode = MousePosition::Nowhere;
    }
}

QT_END_NAMESPACE
