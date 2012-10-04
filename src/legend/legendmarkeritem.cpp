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

#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QGraphicsSimpleTextItem>
#include <QDebug>

#include "qlegend.h"
#include "qlegend_p.h"
#include "qlegendmarker.h"
#include "qlegendmarker_p.h"
#include "legendmarkeritem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LegendMarkerItem::LegendMarkerItem(QLegendMarkerPrivate *marker, QGraphicsObject *parent) :
    QGraphicsObject(parent),
    m_marker(marker),
    m_markerRect(0,0,10.0,10.0),
    m_boundingRect(0,0,0,0),
    m_textItem(new QGraphicsSimpleTextItem(this)),
    m_rectItem(new QGraphicsRectItem(this)),
    m_margin(4),
    m_space(4)
{
    m_rectItem->setRect(m_markerRect);
}

void LegendMarkerItem::setPen(const QPen &pen)
{
    m_rectItem->setPen(pen);
}

QPen LegendMarkerItem::pen() const
{
    return m_rectItem->pen();
}

void LegendMarkerItem::setBrush(const QBrush &brush)
{
    m_rectItem->setBrush(brush);
}

QBrush LegendMarkerItem::brush() const
{
    return m_rectItem->brush();
}

void LegendMarkerItem::setFont(const QFont &font)
{
    m_textItem->setFont(font);
    QFontMetrics fn(font);
    m_markerRect = QRectF(0,0,fn.height()/2,fn.height()/2);
    updateGeometry();
}

QFont LegendMarkerItem::font() const
{
    return m_textItem->font();
}

void LegendMarkerItem::setLabel(const QString label)
{
    m_label = label;
    updateGeometry();
}

QString LegendMarkerItem::label() const
{
    return m_label;
}

void LegendMarkerItem::setLabelBrush(const QBrush &brush)
{
    m_textItem->setBrush(brush);
}

QBrush LegendMarkerItem::labelBrush() const
{
    return m_textItem->brush();
}

void LegendMarkerItem::setGeometry(const QRectF& rect)
{
    QFontMetrics fn (m_font);

    int width = rect.width();
    qreal x = m_margin + m_markerRect.width() +  m_space + m_margin;
    qreal y = qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin);

    if (fn.boundingRect(m_label).width() + x > width)
    {
        QString string = m_label + "...";
        while(fn.boundingRect(string).width() + x > width && string.length() > 3)
            string.remove(string.length() - 4, 1);
        m_textItem->setText(string);
    }
    else
        m_textItem->setText(m_label);

    const QRectF& textRect = m_textItem->boundingRect();


    m_textItem->setPos(x-m_margin,y/2 - textRect.height()/2);
    m_rectItem->setRect(m_markerRect);
    m_rectItem->setPos(m_margin,y/2  - m_markerRect.height()/2);

    prepareGeometryChange();
    m_boundingRect = QRectF(0,0,x+textRect.width()+m_margin,y);
}

QRectF LegendMarkerItem::boundingRect() const
{
    return m_boundingRect;
}

void LegendMarkerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    Q_UNUSED(painter)
}

QSizeF LegendMarkerItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(m_textItem->font());
    QSizeF sh;

      switch (which) {
        case Qt::MinimumSize:
            sh = QSizeF(fn.boundingRect("...").width() + 2*m_margin + m_space +m_markerRect.width(),qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin));
            break;
        case Qt::PreferredSize:
            sh = QSizeF(fn.boundingRect(m_label).width() + 2*m_margin + m_space +m_markerRect.width(),qMax(m_markerRect.height()+2*m_margin,fn.height()+2*m_margin));
            break;
        default:
          break;
      }

      return sh;
}

void LegendMarkerItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    MouseEventHandler::handleMousePressEvent(event);
}

void LegendMarkerItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    MouseEventHandler::handleMouseMoveEvent(event);
}

void LegendMarkerItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    MouseEventHandler::handleMouseReleaseEvent(event);
}

void LegendMarkerItem::mouseClicked()
{
    emit m_marker->q_func()->clicked();
}

void LegendMarkerItem::mouseMoved(QPointF delta)
{
    qreal dx = m_marker->m_legend->d_ptr->offset().x() - delta.x();
    qreal dy = m_marker->m_legend->d_ptr->offset().y() - delta.y();
    m_marker->m_legend->d_ptr->setOffset(dx, dy);
}

void LegendMarkerItem::mouseReleased(QPointF delta)
{
    qreal dx = m_marker->m_legend->d_ptr->offset().x() - delta.x();
    qreal dy = m_marker->m_legend->d_ptr->offset().y() - delta.y();
    m_marker->m_legend->d_ptr->setOffset(dx, dy);
}

#include "moc_legendmarkeritem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
