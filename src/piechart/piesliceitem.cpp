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
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPointF offset(qreal angle, qreal length)
{
    qreal dx = qSin(angle*(M_PI/180)) * length;
    qreal dy = qCos(angle*(M_PI/180)) * length;
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
        painter->save();

        // Pen for label arm not defined in the QPieSeries api, let's use brush's color instead
        // Also, the drawText actually uses the pen color for the text color (unlike QGraphicsSimpleTextItem)
        painter->setPen(m_data.m_labelBrush.color());
        painter->setBrush(m_data.m_labelBrush);
        painter->setFont(m_data.m_labelFont);
        if (m_data.m_labelPosition == QPieSlice::LabelOutside) {
            painter->setClipRect(parentItem()->boundingRect());
            painter->strokePath(m_labelArmPath, m_data.m_labelBrush.color());
        } else { // QPieSlice::LabelInside
            painter->setClipPath(m_slicePath);
        }
        painter->drawText(m_labelTextRect, Qt::AlignCenter, m_data.m_labelText);

        painter->restore();
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

    // slice path
    qreal centerAngle;
    QPointF armStart;
    m_slicePath = slicePath(m_data.m_center, m_data.m_radius, m_data.m_startAngle, m_data.m_angleSpan, &centerAngle, &armStart);

    // text rect
    QFontMetricsF fm(m_data.m_labelFont);
    m_labelTextRect = QRectF(0, 0, fm.width(m_data.m_labelText), fm.height());

    // label arm path
    QPointF labelTextStart;
    m_labelArmPath = labelArmPath(armStart, centerAngle, m_data.m_radius * m_data.m_labelArmLengthFactor, m_labelTextRect.width(), &labelTextStart);

    // text position
    if (m_data.m_labelPosition == QPieSlice::LabelOutside)
        m_labelTextRect.moveBottomLeft(labelTextStart);
    else {// QPieSlice::LabelInside
        QPointF sliceCenter = m_data.m_center + offset(centerAngle, m_data.m_radius / 2);
        m_labelTextRect.moveCenter(sliceCenter);
    }

    //  bounding rect
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
        point += offset(centerAngle, len);
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
    // Normalize the angle to 0-360 range
    // NOTE: We are using int here on purpose. Depenging on platform and hardware
    // qreal can be a double, float or something the user gives to the Qt configure
    // (QT_COORD_TYPE). Compilers do not seem to support modulo for double or float
    // but there are fmod() and fmodf() functions for that. So instead of some #ifdef
    // that might break we just use int. Precision for this is just fine for our needs.
    int normalized = angle * 10.0;
    normalized = normalized % 3600;
    if (normalized < 0)
        normalized += 3600;
    angle = (qreal) normalized / 10.0;

    // prevent label arm pointing straight down because it will look bad
    if (angle < 180 && angle > 170)
        angle = 170;
    if (angle > 180 && angle < 190)
        angle = 190;

    // line from slice to label
    QPointF parm1 = start + offset(angle, length);

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

    QPainterPath path;
    path.moveTo(start);
    path.lineTo(parm1);
    path.lineTo(parm2);

    return path;
}

#include "moc_piesliceitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
