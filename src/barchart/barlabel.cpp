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

#include "barlabel_p.h"
#include "chartpresenter_p.h"
#include <QBarSet>
#include <QPainter>
#include <QPen>
#include <QGraphicsSimpleTextItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarLabel::BarLabel(QBarSet &barSet, QGraphicsItem *parent) : QGraphicsObject(parent),
    m_barSet(barSet),
    m_textItem(new QGraphicsSimpleTextItem(this))
{
//    connect(&set,SIGNAL(labelsVisibleChanged(bool)),value,SLOT(labelsVisibleChanged(bool)));
    setZValue(ChartPresenter::BarSeriesZValue + 1);
    setVisible(barSet.labelsVisible());
    setPen(Qt::NoPen);
    setBrush(Qt::SolidPattern);
}

void BarLabel::setText(QString str)
{
    m_textItem->setText(str);
}

QString BarLabel::text() const
{
    return m_textItem->text();
}

void BarLabel::setPen(const QPen &pen)
{
    m_textItem->setPen(pen);
}

QPen BarLabel::pen() const
{
    return m_textItem->pen();
}

void BarLabel::setBrush(const QBrush &brush)
{
    m_textItem->setBrush(brush);
}

QBrush BarLabel::brush() const
{
    return m_textItem->brush();
}

void BarLabel::setFont(const QFont &font)
{
    m_textItem->setFont(font);
}

QFont BarLabel::font() const
{
    return m_textItem->font();
}

void BarLabel::setPos(qreal x, qreal y)
{
    m_textItem->setPos(x,y);
}

void BarLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF BarLabel::boundingRect() const
{
    return m_textItem->boundingRect();
}

void BarLabel::labelsVisibleChanged(bool visible)
{
    setVisible(visible);
}

#include "moc_barlabel_p.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
