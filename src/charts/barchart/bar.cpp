// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/bar_p.h>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QStyleOptionGraphicsItem>
#include <QtWidgets/QStyle>

QT_BEGIN_NAMESPACE

Bar::Bar(QBarSet *barset, QGraphicsItem *parent) : QGraphicsRectItem(parent),
    m_index(-255),
    m_layoutIndex(-255),
    m_barset(barset),
    m_labelItem(nullptr),
    m_hovering(false),
    m_mousePressed(false),
    m_visualsDirty(true),
    m_labelDirty(true)
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
    delete m_labelItem;
}

void Bar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressed(m_index, m_barset);
    m_mousePressed = true;
    QGraphicsItem::mousePressEvent(event);
}

void Bar::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovering = true;
    emit hovered(true, m_index, m_barset);

}

void Bar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
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

QT_END_NAMESPACE

#include "moc_bar_p.cpp"
