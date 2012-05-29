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

#include "piesliceitem_p.h"
#include "piechartitem_p.h"
#include "qpieseries.h"
#include "qpieslice.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <qmath.h>
#include <QGraphicsSceneEvent>
#include <QTime>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#define PI 3.14159265 // TODO: is this defined in some header?

QPointF offset(qreal angle, qreal length)
{
    qreal dx = qSin(angle*(PI/180)) * length;
    qreal dy = qCos(angle*(PI/180)) * length;
    return QPointF(dx, -dy);
}

PieSliceItem::PieSliceItem(QGraphicsItem* parent)
    :QGraphicsObject(parent),
    m_hovered(false)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButtonMask);
    setZValue(ChartPresenter::PieSeriesZValue);
}

PieSliceItem::~PieSliceItem()
{
    // If user is hovering over the slice and it gets destroyed we do
    // not get a hover leave event. So we must emit the signal here.
    if (m_hovered)
        emit hovered(false);
}

QRectF PieSliceItem::boundingRect() const
{
    return m_boundingRect;
}

QPainterPath PieSliceItem::shape() const
{
    // Don't include the label and label arm.
    // This is used to detect a mouse clicks. We do not want clicks from label.
    return m_slicePath;
}

void PieSliceItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->save();
    painter->setClipRect(parentItem()->boundingRect());
    painter->setPen(m_data.m_slicePen);
    painter->setBrush(m_data.m_sliceBrush);
    painter->drawPath(m_slicePath);
    painter->restore();

    if (m_data.m_isLabelVisible) {
        painter->setClipRect(parentItem()->boundingRect());
        painter->setPen(m_data.m_labelPen);
        painter->drawPath(m_labelArmPath);
		// the pen color will affect the font color as well
        painter->setFont(m_data.m_labelFont);
        painter->drawText(m_labelTextRect.bottomLeft(), m_data.m_labelText);
    }
}

void PieSliceItem::hoverEnterEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    m_hovered = true;
    emit hovered(true);
}

void PieSliceItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    m_hovered = false;
    emit hovered(false);
}

void PieSliceItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(event->buttons());
}

void PieSliceItem::setLayout(const PieSliceData &sliceData)
{
    m_data = sliceData;
    updateGeometry();
    update();
}

void PieSliceItem::updateGeometry()
{
    if (m_data.m_radius <= 0)
        return;

    prepareGeometryChange();

    // update slice path
    qreal centerAngle;
    QPointF armStart;
    m_slicePath = slicePath(m_data.m_center, m_data.m_radius, m_data.m_startAngle, m_data.m_angleSpan, &centerAngle, &armStart);

    // update text rect
    m_labelTextRect = labelTextRect(m_data.m_labelFont, m_data.m_labelText);

    // update label arm path
    QPointF labelTextStart;
    m_labelArmPath = labelArmPath(armStart, centerAngle, m_data.m_radius * m_data.m_labelArmLengthFactor, m_labelTextRect.width(), &labelTextStart);

    // update text position
    m_labelTextRect.moveBottomLeft(labelTextStart);

    // update bounding rect
    if (m_data.m_isLabelVisible)
        m_boundingRect = m_slicePath.boundingRect().united(m_labelArmPath.boundingRect()).united(m_labelTextRect);
    else
        m_boundingRect = m_slicePath.boundingRect();
}

QPointF PieSliceItem::sliceCenter(QPointF point, qreal radius, QPieSlice *slice)
{
    if (slice->isExploded()) {
        qreal centerAngle = slice->startAngle() + (slice->angleSpan()/2);
        qreal len = radius * slice->explodeDistanceFactor();
        qreal dx = qSin(centerAngle*(PI/180)) * len;
        qreal dy = -qCos(centerAngle*(PI/180)) * len;
        point += QPointF(dx, dy);
    }
    return point;
}

QPainterPath PieSliceItem::slicePath(QPointF center, qreal radius, qreal startAngle, qreal angleSpan, qreal *centerAngle, QPointF* armStart)
{
    // calculate center angle
    *centerAngle = startAngle + (angleSpan/2);

    // calculate slice rectangle
    QRectF rect(center.x()-radius, center.y()-radius, radius*2, radius*2);

    // slice path
    // TODO: draw the shape so that it might have a hole in the center
    QPainterPath path;
    path.moveTo(rect.center());
    path.arcTo(rect, -startAngle + 90, -angleSpan);
    path.closeSubpath();

    // calculate label arm start point
    *armStart = center;
    *armStart += offset(*centerAngle, radius + PIESLICE_LABEL_GAP);

    return path;
}

QPainterPath PieSliceItem::labelArmPath(QPointF start, qreal angle, qreal length, qreal textWidth, QPointF *textStart)
{
    // prevent label arm pointing straight down because it will look bad
    if (angle < 180 && angle > 170)
        angle = 170;
    if (angle > 180 && angle < 190)
        angle = 190;

    // line from slice to label
    qreal dx = qSin(angle*(PI/180)) * length;
    qreal dy = -qCos(angle*(PI/180)) * length;
    QPointF parm1 = start + QPointF(dx, dy);

    // line to underline the label
    QPointF parm2 = parm1;
    if (angle < 180) { // arm swings the other way on the left side
         parm2 += QPointF(textWidth, 0);
         *textStart = parm1;
    }
    else {
         parm2 += QPointF(-textWidth,0);
         *textStart = parm2;
    }

    // elevate the text position a bit so that it does not hit the line
    *textStart += QPointF(0, -3);

    QPainterPath path;
    path.moveTo(start);
    path.lineTo(parm1);
    path.lineTo(parm2);

    return path;
}

QRectF PieSliceItem::labelTextRect(QFont font, QString text)
{
    QFontMetricsF fm(font);
    return fm.boundingRect(text);
}

#include "moc_piesliceitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
