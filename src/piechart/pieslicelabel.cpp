#include "pieslicelabel.h"
#include <QPainter>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#define PI 3.14159265

PieSliceLabel::PieSliceLabel(QGraphicsItem* parent)
    :QGraphicsItem(parent)
{
    m_pen = QPen(Qt::black);
}

PieSliceLabel::~PieSliceLabel()
{

}

QRectF PieSliceLabel::boundingRect() const
{
    return m_rect;
}

QPainterPath PieSliceLabel::shape() const
{
    return m_path;
}

void PieSliceLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pen);
    painter->drawPath(m_path);
}

void PieSliceLabel::updateGeometry(const QPointF& startPoint, qreal armAngle, qreal armLength)
{
    prepareGeometryChange();

    QPainterPath path;
    path.moveTo(startPoint);

    // draw arm
    qreal dx = qSin(armAngle*(PI/180)) * armLength;
    qreal dy = -qCos(armAngle*(PI/180)) * armLength;
    QPointF p1 = startPoint + QPointF(dx, dy);
    path.lineTo(p1);

    QPointF p2 = p1;
    QPointF pt = p1;
    if (armAngle < 180) {
         p2 += QPointF(50, 0);
    } else {
         p2 += QPointF(-50,0);
         pt = p2;
    }
    path.lineTo(p2);

    QFont font;
    pt += QPointF(0,-2);
    path.addText(pt, font, m_label);

    m_path = path;
    m_rect = path.boundingRect();
}

void PieSliceLabel::setLabel(QString label)
{
    m_label = label;
    // TODO: animation?
}



QTCOMMERCIALCHART_END_NAMESPACE
