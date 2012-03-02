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

QPointF offset(qreal angle, qreal length)
{
    qreal dx = qSin(angle*(PI/180)) * length;
    qreal dy = qCos(angle*(PI/180)) * length;
    return QPointF(dx, -dy);
}

PieSlice::PieSlice(QGraphicsItem* parent)
    :QGraphicsObject(parent),
    m_startAngle(0),
    m_angleSpan(0),
    m_isExploded(false),
    m_explodeDistance(0),
    m_labelVisible(false)
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
    return m_slicePath;
}

void PieSlice::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->save();
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
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

void PieSlice::setPieRect(QRectF rect)
{
    m_pieRect = rect;
}

void PieSlice::updateGeometry()
{
    if (!m_pieRect.isValid() || m_pieRect.isEmpty())
        return;

    prepareGeometryChange();

    // update slice path
    QPointF center = m_pieRect.center();
    qreal radius = m_pieRect.height() / 2;
    qreal centerAngle;
    QPointF armStart;
    m_slicePath = slicePath(center, radius, m_startAngle, m_angleSpan, m_isExploded, m_explodeDistance, &centerAngle, &armStart);

    // update text rect
    m_labelTextRect = labelTextRect(m_labelFont, m_labelText);

    // update label arm path
    QPointF labelTextStart;
    m_labelArmPath = labelArmPath(armStart, centerAngle, m_labelArmLength, m_labelTextRect.width(), &labelTextStart);

    // update text position
    m_labelTextRect.moveBottomLeft(labelTextStart);

    //qDebug() << "PieSlice::updateGeometry" << m_slicelabel->text() << boundingRect() << m_angle << m_span;
}

void PieSlice::updateData(const QPieSlice* sliceData)
{
    // TODO: compare what has changes to avoid unneccesary geometry updates

    m_startAngle = sliceData->startAngle();
    m_angleSpan = sliceData->m_angleSpan;
    m_isExploded = sliceData->isExploded();
    m_explodeDistance = sliceData->explodeDistance();
    m_pen = sliceData->pen();
    m_brush = sliceData->brush();

    m_labelVisible = sliceData->isLabelVisible();
    m_labelText = sliceData->label();
    m_labelFont = sliceData->labelFont();
    m_labelArmLength = sliceData->labelArmLength();
    m_labelArmPen = sliceData->labelPen();

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
