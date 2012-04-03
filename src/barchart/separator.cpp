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

#include "separator_p.h"
#include <QDebug>
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Separator::Separator(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
}

void Separator::setPos(qreal x, qreal y)
{
    mXpos = x;
    mYpos = y;
}

void Separator::setColor(QColor color)
{
    mColor = color;
}

void Separator::setSize(const QSizeF &size)
{
    mWidth = size.width();
    mHeight = size.height();
}

void Separator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (isVisible()) {
        QPen pen(mColor);
        painter->setPen(pen);
        painter->drawLine(mXpos,mYpos,mXpos,mHeight);
    }
}

QRectF Separator::boundingRect() const
{
    QRectF r(mXpos,mYpos,mWidth,mHeight);
    return r;
}


QTCOMMERCIALCHART_END_NAMESPACE
