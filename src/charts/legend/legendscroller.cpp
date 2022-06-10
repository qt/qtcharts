// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtWidgets/QGraphicsSceneHoverEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QStylePainter>
#include <QtWidgets/QStyleOption>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QChart>
#include <private/qlegendmarker_p.h>
#include <private/legendlayout_p.h>
#include <private/legendmarkeritem_p.h>
#include <private/legendscroller_p.h>
#include <private/legendmoveresizehandler_p.h>
#include <private/legendlayout_p.h>

QT_BEGIN_NAMESPACE

LegendScroller::LegendScroller(QChart *chart) : QLegend(chart)
{
    connect(this, &QLegend::interactiveChanged, this, &LegendScroller::handleInteractiveChanged);
    connect(this, &QLegend::attachedToChartChanged, this, &LegendScroller::handleDetached);
}

void LegendScroller::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLegend::paint(painter, option, widget);

    if (!isInteractive())
        return;

    if (!isAttachedToChart() && d_ptr->m_resizer->shouldShowMoveHint()) {
        QStyle *s = this->style();
        QStylePainter stylePainter;
        QStyleOptionRubberBand rubberBandOption;
        QRectF rubberBandRectF(0, 0, geometry().width(), d_ptr->m_layout->contentsRect().y());
        rubberBandOption.rect = rubberBandRectF.toRect();
        s->drawControl(QStyle::CE_RubberBand, &rubberBandOption, painter);
    }
}

void LegendScroller::setOffset(const QPointF &point)
{
    d_ptr->setOffset(point);
}

QPointF LegendScroller::offset() const
{
    return d_ptr->offset();
}

void LegendScroller::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!isInteractive() || isAttachedToChart()) {
        Scroller::handleMousePressEvent(event);
        return;
    }

    m_forwardMouseEvents = false;
    m_forwardHoverEvents = false;

    QRectF contentRect = geometry();
    qreal left, top, right, bottom;
    d_ptr->m_layout->getContentsMargins(&left, &top, &right, &bottom);
    contentRect.adjust(left, top, -right, -bottom);
    contentRect.moveTo(left, top);
    QPointF pt = event->pos();

    if (contentRect.contains(pt)) {
        Scroller::handleMousePressEvent(event);
    } else {
        d_ptr->m_resizer->handleMousePressEvent(event);
        updateForResizerChange();
        m_forwardMouseEvents = event->isAccepted();
    }
}

void LegendScroller::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_forwardMouseEvents) {
        d_ptr->m_resizer->handleMouseMoveEvent(event);
        updateForResizerChange();
    } else {
        Scroller::handleMouseMoveEvent(event);
    }
}

void LegendScroller::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_forwardMouseEvents) {
        d_ptr->m_resizer->handleMouseReleaseEvent(event);
        updateForResizerChange();
        m_forwardMouseEvents = false;
    } else {
        Scroller::handleMouseReleaseEvent(event);

        if (!event->isAccepted()) {
            const QList<QGraphicsItem *> items = scene()->items(event->scenePos());

            for (const auto i : items) {
                if (d_ptr->m_markerHash.contains(i)) {
                    QLegendMarker *marker = d_ptr->m_markerHash.value(i);
                    emit marker->clicked();
                }
            }
            event->accept();
        }
    }
}

void LegendScroller::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    if (isInteractive() && isAttachedToChart())
        detachFromChart();
}

void LegendScroller::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (isInteractive() && !isAttachedToChart()) {
        m_forwardHoverEvents = true;
        d_ptr->m_resizer->handleHoverEnterEvent(event);
        updateForResizerChange();
    } else {
        QLegend::hoverEnterEvent(event);
    }
}

void LegendScroller::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isInteractive() || isAttachedToChart()) {
        QLegend::hoverMoveEvent(event);
        return;
    }

    bool stopForwarding = d_ptr->m_layout->contentsRect().contains(event->pos());
    if (stopForwarding) {
        if (m_forwardHoverEvents) {
            // the event position is no longer over the border
            // frame, so send a leave. This will set the
            // mouse cursor back to an arrow.
            m_forwardHoverEvents = false;
            d_ptr->m_resizer->handleHoverLeaveEvent(event);
            updateForResizerChange();
        }
    } else {
        if (!m_forwardHoverEvents) {
            // if we're not already forwarding events, and we
            // shouldn't stop forwarding, then we should
            // start forwarding. This would happen if the event
            // position was inside the layout's content rect
            // on the _previous_ move event, and now the position
            // is on the border frame. So, this fakes a hover
            // enter from the _inside_ (which we otherwise
            // would not get).
            m_forwardHoverEvents = true;
            d_ptr->m_resizer->handleHoverEnterEvent(event);
            updateForResizerChange();
        }
    }

    if (m_forwardHoverEvents) {
        d_ptr->m_resizer->handleHoverMoveEvent(event);
        updateForResizerChange();
    } else {
        QLegend::hoverMoveEvent(event);
    }
}

void LegendScroller::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (m_forwardHoverEvents) {
        m_forwardHoverEvents = false;
        d_ptr->m_resizer->handleHoverLeaveEvent(event);
        updateForResizerChange();
    } else {
        QLegend::hoverLeaveEvent(event);
    }
}

void LegendScroller::handleInteractiveChanged(bool interactive)
{
    setAcceptHoverEvents(interactive);
    m_cachedShouldShowMoveEvents = d_ptr->m_resizer->shouldShowMoveHint();
    m_forwardMouseEvents = false;
    m_forwardHoverEvents = false;
    d_ptr->m_resizer->reset();
    update();
}

void LegendScroller::updateForResizerChange()
{
    LegendMoveResizeHandler* resizer = d_ptr->m_resizer;
    if (resizer->shouldShowMoveHint() != m_cachedShouldShowMoveEvents) {
        m_cachedShouldShowMoveEvents = resizer->shouldShowMoveHint();
        update();
    }
}

void LegendScroller::handleDetached(bool attached)
{
    if (attached)
        return;

    qreal left, top, right, bottom;
    d_ptr->m_layout->getContentsMargins(&left, &top, &right, &bottom);
    QSizeF newSize = QSizeF(left + right, top + bottom);
    qreal width = 0;
    qreal height = 0;

    for (auto marker : d_ptr->markers()) {
        LegendMarkerItem *item = marker->d_ptr->item();
        QSizeF itemESizeHint = item->effectiveSizeHint(Qt::PreferredSize);

        switch (alignment()) {
        case Qt::AlignTop:
        case Qt::AlignBottom:
            // + 3 accounts for the margin which is not an accessible member.
            width += itemESizeHint.width() + 3;
            height = qMax(height, itemESizeHint.height());
            break;
        case Qt::AlignLeft:
        case Qt::AlignRight:
            width = qMax(width, itemESizeHint.width());
            height += itemESizeHint.height();
            break;
        default:
            break;
        }
    }

    newSize += QSizeF(width, height);

    QRectF newGeom = QRectF(geometry().topLeft(), newSize);
    setGeometry(newGeom.intersected(QRectF(QPoint(0,0), d_ptr->m_chart->size())));
}

QT_END_NAMESPACE

#include "moc_legendscroller_p.cpp"
