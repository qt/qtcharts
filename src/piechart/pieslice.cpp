#include "pieslice_p.h"
#include "piepresenter_p.h"
#include "qpieseries.h"
#include "qpieslice.h"
#include <QPainter>
#include <QDebug>
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

PieSlice::PieSlice(QGraphicsItem* parent)
    :QGraphicsObject(parent),
    m_pieRadius(0),
    m_startAngle(0),
    m_angleSpan(0),
    m_isExploded(false),
    m_explodeDistanceFactor(0),
    m_labelVisible(false),
    m_labelArmLengthFactor(0)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

PieSlice::~PieSlice()
{

}

QRectF PieSlice::boundingRect() const
{
    return m_slicePath.boundingRect();
}

QPainterPath PieSlice::shape() const
{
    // Don't include the label and label arm.
    // This is used to detect a mouse clicks. We do not want clicks from label.
    return m_slicePath;
}

void PieSlice::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setClipRect(parentItem()->boundingRect());

    painter->save();
    painter->setPen(m_slicePen);
    painter->setBrush(m_sliceBrush);
    painter->drawPath(m_slicePath);
    painter->restore();

    if (m_labelVisible) {
        painter->save();
        painter->setPen(m_labelArmPen);
        painter->drawPath(m_labelArmPath);
        painter->restore();

        painter->setFont(m_labelFont);
        painter->drawText(m_labelTextRect.bottomLeft(), m_labelText);
    }
}

void PieSlice::hoverEnterEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    emit hoverEnter();
}

void PieSlice::hoverLeaveEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    emit hoverLeave();
}

void PieSlice::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    emit clicked();
}

void PieSlice::setPieCenterAndRadius(QPointF center, qreal radius)
{
    m_pieCenter = center;
    m_pieRadius = radius;
}

void PieSlice::updateGeometry()
{
    if (m_pieRadius <= 0)
        return;

    prepareGeometryChange();

    // update slice path
    qreal centerAngle;
    QPointF armStart;
    m_slicePath = slicePath(m_pieCenter, m_pieRadius, m_startAngle, m_angleSpan, m_isExploded, m_pieRadius * m_explodeDistanceFactor, &centerAngle, &armStart);

    // update text rect
    m_labelTextRect = labelTextRect(m_labelFont, m_labelText);

    // update label arm path
    QPointF labelTextStart;
    m_labelArmPath = labelArmPath(armStart, centerAngle, m_pieRadius * m_labelArmLengthFactor, m_labelTextRect.width(), &labelTextStart);

    // update text position
    m_labelTextRect.moveBottomLeft(labelTextStart);

    //qDebug() << "PieSlice::updateGeometry" << m_labelText << boundingRect() << m_startAngle << m_startAngle + m_angleSpan;
}

void PieSlice::updateData(const QPieSlice* sliceData)
{
    // TODO: compare what has changes to avoid unneccesary geometry updates

    m_startAngle = sliceData->startAngle();
    m_angleSpan = sliceData->m_angleSpan;
    m_isExploded = sliceData->isExploded();
    m_explodeDistanceFactor = sliceData->explodeDistanceFactor();
    m_slicePen = sliceData->slicePen();
    m_sliceBrush = sliceData->sliceBrush();

    m_labelVisible = sliceData->isLabelVisible();
    m_labelText = sliceData->label();
    m_labelFont = sliceData->labelFont();
    m_labelArmLengthFactor = sliceData->labelArmLengthFactor();
    m_labelArmPen = sliceData->labelArmPen();

    updateGeometry();
    update();
}

QPainterPath PieSlice::slicePath(QPointF center, qreal radius, qreal startAngle, qreal angleSpan, bool exploded, qreal explodeDistance, qreal* centerAngle, QPointF* armStart)
{
    // calculate center angle
    *centerAngle = startAngle + (angleSpan/2);

    // calculate slice rectangle
    QRectF rect(center.x()-radius, center.y()-radius, radius*2, radius*2);

    // adjust rect for exploding
    if (exploded) {
        qreal dx = qSin(*centerAngle*(PI/180)) * explodeDistance;
        qreal dy = -qCos(*centerAngle*(PI/180)) * explodeDistance;
        rect.translate(dx, dy);
    }

    // slice path
    // TODO: draw the shape so that it might have a hole in the center
    QPainterPath path;
    path.moveTo(rect.center());
    path.arcTo(rect, -startAngle + 90, -angleSpan);
    path.closeSubpath();

    // calculate label arm start point
    *armStart = center;
    if (exploded)
        *armStart += offset(*centerAngle, explodeDistance + radius + PIESLICE_LABEL_GAP);
    else
        *armStart += offset(*centerAngle, radius + PIESLICE_LABEL_GAP);

    return path;
}

QPainterPath PieSlice::labelArmPath(QPointF start, qreal angle, qreal length, qreal textWidth, QPointF* textStart)
{
    qreal dx = qSin(angle*(PI/180)) * length;
    qreal dy = -qCos(angle*(PI/180)) * length;
    QPointF parm1 = start + QPointF(dx, dy);

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
    *textStart += QPointF(0, -5);

    QPainterPath path;
    path.moveTo(start);
    path.lineTo(parm1);
    path.lineTo(parm2);

    return path;
}

QRectF PieSlice::labelTextRect(QFont font, QString text)
{
    QFontMetricsF fm(font);
    return fm.boundingRect(text);
}

#include "moc_pieslice_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
