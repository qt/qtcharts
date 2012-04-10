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

#include "bar_p.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Bar::Bar(QBarSet *barset, QString category, QGraphicsItem *parent) : QGraphicsRectItem(parent),
    m_category(category),
    m_barset(barset)
{
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    setAcceptHoverEvents(true);
}

void Bar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(m_category, event->button());
    emit clicked(m_barset, m_category, event->button());
}

void Bar::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverEntered(event->lastScreenPos());
}

void Bar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    emit hoverLeaved();
}

#include "moc_bar_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
