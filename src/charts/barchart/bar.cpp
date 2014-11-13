/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/bar_p.h>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QStyleOptionGraphicsItem>
#include <QtWidgets/QStyle>

QT_CHARTS_BEGIN_NAMESPACE

Bar::Bar(QBarSet *barset, int index, QGraphicsItem *parent) : QGraphicsRectItem(parent),
    m_index(index),
    m_barset(barset),
    m_hovering(false),
    m_mousePressed(false)
{
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

Bar::~Bar()
{
    // End hover event, if bar is deleted during it
    if (m_hovering)
        emit hovered(false, m_index, m_barset);
}

void Bar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressed(m_index, m_barset);
    m_mousePressed = true;
    QGraphicsItem::mousePressEvent(event);
}

void Bar::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_hovering = true;
    emit hovered(true, m_index, m_barset);

}

void Bar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_hovering = false;
    emit hovered(false, m_index, m_barset);
}

void Bar::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit released(m_index, m_barset);
    if (m_mousePressed)
        emit clicked(m_index, m_barset);
    m_mousePressed = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

void Bar::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit doubleClicked(m_index, m_barset);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Remove selection border around bar
    QStyleOptionGraphicsItem barOption(*option);
    barOption.state &= ~QStyle::State_Selected;
    QGraphicsRectItem::paint(painter, &barOption, widget);
}

#include "moc_bar_p.cpp"

QT_CHARTS_END_NAMESPACE
