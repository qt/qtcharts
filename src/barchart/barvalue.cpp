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

#include "barvalue_p.h"
#include <QPainter>
#include <QPen>
#include <QGraphicsSimpleTextItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarValue::BarValue(QBarSet &set, QGraphicsItem *parent) : QGraphicsObject(parent),
    m_barSet(set),
    m_textItem(new QGraphicsSimpleTextItem(this))
{
    setVisible(false);
}

void BarValue::setText(QString str)
{
    m_textItem->setText(str);
}

QString BarValue::text() const
{
    return m_textItem->text();
}

void BarValue::setPen(const QPen &pen)
{
    m_textItem->setPen(pen);
}

QPen BarValue::pen() const
{
    return m_textItem->pen();
}

void BarValue::setFont(const QFont &font)
{
    m_textItem->setFont(font);
}

QFont BarValue::font() const
{
    return m_textItem->font();
}

void BarValue::setPos(qreal x, qreal y)
{
    m_textItem->setPos(x,y);
}

void BarValue::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF BarValue::boundingRect() const
{
    return m_textItem->boundingRect();
}

void BarValue::toggleVisible()
{
    qDebug() << "toggle visible";
    setVisible(!isVisible());
}

#include "moc_barvalue_p.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
