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

#include "legendlayout_p.h"
#include "chartpresenter_p.h"
#include "legendmarker_p.h"
#include "qlegend_p.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendLayout::LegendLayout(QLegend* legend)
    : m_legend(legend)
{

}

LegendLayout::~LegendLayout()
{

}

void LegendLayout::setOffset(qreal x, qreal y)
{
    bool scrollHorizontal = true;
    switch (m_legend->alignment()) {
    case Qt::AlignTop:
    case Qt::AlignBottom:
        scrollHorizontal = true;
        break;
    case Qt::AlignLeft:
    case Qt::AlignRight:
        scrollHorizontal = false;
        break;
    }

    // If detached, the scrolling direction is vertical instead of horizontal and vice versa.
    if (!m_legend->isAttachedToChart())
        scrollHorizontal = !scrollHorizontal;

    QRectF boundingRect = geometry();
    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    boundingRect.adjust(left, top, -right, -bottom);

    // Limit offset between m_minOffset and m_maxOffset
    if (scrollHorizontal) {
        if (m_width <= boundingRect.width())
            return;

        if (x != m_offsetX) {
            m_offsetX = qBound(m_minOffsetX, x, m_maxOffsetX);
            m_legend->d_ptr->items()->setPos(-m_offsetX, boundingRect.top());
        }
    } else {
        if (m_height <= boundingRect.height())
            return;

        if (y != m_offsetY) {
            m_offsetY = qBound(m_minOffsetY, y, m_maxOffsetY);
            m_legend->d_ptr->items()->setPos(boundingRect.left(), -m_offsetY);
        }
    }
}

QPointF LegendLayout::offset() const
{
    return QPointF(m_offsetX, m_offsetY);
}

void LegendLayout::invalidate()
{
    QGraphicsLayout::invalidate();
    if (m_legend->isAttachedToChart())
        m_legend->d_ptr->m_presenter->layout()->invalidate();
}

void LegendLayout::setGeometry(const QRectF& rect)
{
    m_legend->d_ptr->items()->setVisible(m_legend->isVisible());

    QGraphicsLayout::setGeometry(rect);

    if (m_legend->isAttachedToChart())
        setAttachedGeometry(rect);
    else
        setDettachedGeometry(rect);
}

void LegendLayout::setAttachedGeometry(const QRectF& rect)
{
    if (!rect.isValid())
        return;

    m_offsetX = 0;
    m_offsetY = 0;

    QSizeF size(0, 0);

    if (m_legend->d_ptr->markers().isEmpty())
        return;

    m_width = 0;
    m_height = 0;

    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);

    QRectF geometry = rect.adjusted(left, top, -right, -bottom);

    switch (m_legend->alignment()) {
    case Qt::AlignTop:
    case Qt::AlignBottom: {
            QPointF point(0, 0);
            foreach (LegendMarker *marker, m_legend->d_ptr->markers()) {
                if (marker->isVisible()) {
                    marker->setGeometry(geometry);
                    marker->setPos(point.x(), geometry.height() / 2 - marker->boundingRect().height() / 2);
                    const QRectF& rect = marker->boundingRect();
                    size = size.expandedTo(rect.size());
                    qreal w = rect.width();
                    m_width += w;
                    point.setX(point.x() + w);
                }
            }
            if (m_width < geometry.width())
                m_legend->d_ptr->items()->setPos(geometry.width() / 2 - m_width / 2, geometry.top());
            else
                m_legend->d_ptr->items()->setPos(geometry.topLeft());
            m_height = size.height();
        }
        break;
    case Qt::AlignLeft:
    case Qt::AlignRight: {
        QPointF point(0, 0);
        foreach (LegendMarker *marker, m_legend->d_ptr->markers()) {
            if (marker->isVisible()) {
                marker->setGeometry(geometry);
                marker->setPos(point);
                const QRectF& rect = marker->boundingRect();
                qreal h = rect.height();
                size = size.expandedTo(rect.size());
                m_height += h;
                point.setY(point.y() + h);
            }
        }

        if (m_height < geometry.height())
            m_legend->d_ptr->items()->setPos(geometry.left(), geometry.height() / 2 - m_height / 2);
        else
            m_legend->d_ptr->items()->setPos(geometry.topLeft());
        m_width = size.width();
        break;
        }
    }

    m_minOffsetX = -left;
    m_minOffsetY = - top;
    m_maxOffsetX = m_width - geometry.width() - right;
    m_maxOffsetY = m_height - geometry.height() - bottom;
}

void LegendLayout::setDettachedGeometry(const QRectF& rect)
{
    if (!rect.isValid())
        return;

    // Detached layout is different.
    // In detached mode legend may have multiple rows and columns, so layout calculations
    // differ a log from attached mode.
    // Also the scrolling logic is bit different.

    m_offsetX = 0;
    m_offsetY = 0;

    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRectF geometry = rect.adjusted(left, top, -right, -bottom);

    QSizeF size(0, 0);

    QList<LegendMarker *> markers = m_legend->d_ptr->markers();

    if (markers.isEmpty())
        return;

    switch (m_legend->alignment()) {
    case Qt::AlignTop: {
            QPointF point(0, 0);
            m_width = 0;
            m_height = 0;
            for (int i = 0; i < markers.count(); i++) {
                LegendMarker *marker = markers.at(i);
                if (marker->isVisible()) {
                    marker->setGeometry(geometry);
                    marker->setPos(point.x(), point.y());
                    const QRectF& boundingRect = marker->boundingRect();
                    qreal w = boundingRect.width();
                    qreal h = boundingRect.height();
                    m_width = qMax(m_width, w);
                    m_height = qMax(m_height, h);
                    point.setX(point.x() + w);
                    if (point.x() + w > geometry.left() + geometry.width() - right) {
                        // Next item would go off rect.
                        point.setX(0);
                        point.setY(point.y() + h);
                        if (i + 1 < markers.count()) {
                            m_height += h;
                        }
                    }
                }
            }
            m_legend->d_ptr->items()->setPos(geometry.topLeft());

            m_minOffsetX = -left;
            m_minOffsetY = -top;
            m_maxOffsetX = m_width - geometry.width() - right;
            m_maxOffsetY = m_height - geometry.height() - bottom;
        }
        break;
    case Qt::AlignBottom: {
            QPointF point(0, geometry.height());
            m_width = 0;
            m_height = 0;
            for (int i = 0; i < markers.count(); i++) {
                LegendMarker *marker = markers.at(i);
                if (marker->isVisible()) {
                    marker->setGeometry(geometry);
                    const QRectF& boundingRect = marker->boundingRect();
                    qreal w = boundingRect.width();
                    qreal h = boundingRect.height();
                    m_width = qMax(m_width, w);
                    m_height = qMax(m_height, h);
                    marker->setPos(point.x(), point.y() - h);
                    point.setX(point.x() + w);
                    if (point.x() + w > geometry.left() + geometry.width() - right) {
                        // Next item would go off rect.
                        point.setX(0);
                        point.setY(point.y() - h);
                        if (i + 1 < markers.count()) {
                            m_height += h;
                        }
                    }
                }
            }
            m_legend->d_ptr->items()->setPos(geometry.topLeft());

            m_minOffsetX = -left;
            m_minOffsetY = -m_height + geometry.height() - top;
            m_maxOffsetX = m_width - geometry.width() - right;
            m_maxOffsetY = -bottom;
        }
        break;
    case Qt::AlignLeft: {
            QPointF point(0, 0);
            m_width = 0;
            m_height = 0;
            qreal maxWidth = 0;
            for (int i = 0; i < markers.count(); i++) {
                LegendMarker *marker = markers.at(i);
                if (marker->isVisible()) {
                    marker->setGeometry(geometry);
                    const QRectF& boundingRect = marker->boundingRect();
                    qreal w = boundingRect.width();
                    qreal h = boundingRect.height();
                    m_height = qMax(m_height, h);
                    maxWidth = qMax(maxWidth, w);
                    marker->setPos(point.x(), point.y());
                    point.setY(point.y() + h);
                    if (point.y() + h > geometry.bottom() - bottom) {
                        // Next item would go off rect.
                        point.setX(point.x() + maxWidth);
                        point.setY(0);
                        if (i + 1 < markers.count()) {
                            m_width += maxWidth;
                            maxWidth = 0;
                        }
                    }
                }
            }
            m_width += maxWidth;
            m_legend->d_ptr->items()->setPos(geometry.topLeft());

            m_minOffsetX = -left;
            m_minOffsetY = -top;
            m_maxOffsetX = m_width - geometry.width() - right;
            m_maxOffsetY = m_height - geometry.height() - bottom;
        }
        break;
    case Qt::AlignRight: {
            QPointF point(geometry.width(), 0);
            m_width = 0;
            m_height = 0;
            qreal maxWidth = 0;
            for (int i = 0; i < markers.count(); i++) {
                LegendMarker *marker = markers.at(i);
                if (marker->isVisible()) {
                    marker->setGeometry(geometry);
                    const QRectF& boundingRect = marker->boundingRect();
                    qreal w = boundingRect.width();
                    qreal h = boundingRect.height();
                    m_height = qMax(m_height, h);
                    maxWidth = qMax(maxWidth, w);
                    marker->setPos(point.x() - w, point.y());
                    point.setY(point.y() + h);
                    if (point.y() + h > geometry.bottom() - bottom) {
                        // Next item would go off rect.
                        point.setX(point.x() - maxWidth);
                        point.setY(0);
                        if (i + 1 < markers.count()) {
                            m_width += maxWidth;
                            maxWidth = 0;
                        }
                    }
                }
            }
            m_width += maxWidth;
            m_legend->d_ptr->items()->setPos(geometry.topLeft());

            m_minOffsetX = - m_width + geometry.width() - left;
            m_minOffsetY = -top;
            m_maxOffsetX = - right;
            m_maxOffsetY = m_height - geometry.height() - bottom;
        }
        break;
    default:
        break;
    }

}

QSizeF LegendLayout::sizeHint(Qt::SizeHint which, const QSizeF & constraint) const
{
    QSizeF size(0, 0);
    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);

    if (constraint.isValid()) {
        foreach (LegendMarker *marker, m_legend->d_ptr->markers())
            size = size.expandedTo(marker->effectiveSizeHint(which));
        size = size.boundedTo(constraint);
    } else if (constraint.width() >= 0) {
        qreal width = 0;
        qreal height = 0;
        foreach (LegendMarker *marker, m_legend->d_ptr->markers()) {
            width += marker->effectiveSizeHint(which).width();
            height = qMax(height, marker->effectiveSizeHint(which).height());
        }

        size = QSizeF(qMin(constraint.width(), width), height);
    } else if (constraint.height() >= 0) {
        qreal width = 0;
        qreal height = 0;
        foreach (LegendMarker *marker, m_legend->d_ptr->markers()) {
            width = qMax(width, marker->effectiveSizeHint(which).width());
            height += height, marker->effectiveSizeHint(which).height();
        }
        size = QSizeF(width, qMin(constraint.height(), height));
    } else {
        foreach (LegendMarker *marker, m_legend->d_ptr->markers())
            size = size.expandedTo(marker->effectiveSizeHint(which));
    }
    size += QSize(left + right, top + bottom);
    return size;
}

QTCOMMERCIALCHART_END_NAMESPACE
