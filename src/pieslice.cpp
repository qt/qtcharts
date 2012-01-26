#include "pieslice.h"
#include <QPainter>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PieSlice::PieSlice(const QColor& color, qreal startAngle, qreal span, QRectF rect)
    : m_color(color),
    m_startAngle(startAngle),
    m_span(span),
    m_rect(rect)
{
    setAcceptHoverEvents(true);
}

PieSlice::~PieSlice()
{
}

QRectF PieSlice::boundingRect() const
{
    return m_rect;
}

QPainterPath PieSlice::shape() const
{
    qreal angle = (-m_startAngle) + (90);
    qreal span = -m_span;

    QPainterPath path;
    path.moveTo(boundingRect().center());
    path.arcTo(boundingRect(), angle, span);

    // TODO: draw the shape so that it might have a hole in the center
    // - Sin & Cos will be needed to find inner/outer arc endpoints

    // dx, dy are offsets from the center
    //qreal l = boundingRect().height();
    //qreal dx = qSin(angle*(M_PI/180)) * l;
    //qreal dy = qCos(angle*(M_PI/180)) * l;

    // TODO: exploded slice?

    return path;
}

void PieSlice::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Setup painter
    painter->setBrush(m_color);
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen;
    //pen.setColor(m_color.darker());
    pen.setColor(Qt::gray);
    pen.setWidth(1);
    painter->setPen(pen);

    // From Qt docs:
    // The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).
    // Positive values for the angles mean counter-clockwise while negative values mean the clockwise direction.
    // Zero degrees is at the 3 o'clock position.
    //
    // For sake of simplicity convert this so that zero degrees is at 12 o'clock and full circle is 360.
    //qreal angle = (-m_startAngle*16) + (90*16);
    //qreal span = -m_span*16;
    //painter->drawPie(boundingRect(), angle, span);

    painter->drawPath(shape());
}

void PieSlice::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    QGraphicsItem::hoverEnterEvent(event);
    qDebug() << "hover" << m_color << m_startAngle << m_span;
}

QTCOMMERCIALCHART_END_NAMESPACE
