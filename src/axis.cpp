#include "axis_p.h"
#include <QPainter>
#include <QDebug>

QCHART_BEGIN_NAMESPACE

Axis::Axis(QGraphicsItem* parent): QGraphicsItem(parent)
{
}

Axis::~Axis()
{
}

void Axis::setLength(int length)
{
    QPainterPath path;
    path.moveTo(QPointF(0,0));
    path.lineTo(length,0);
   // path.lineTo(length-4,0);
   // path.lineTo(length,3);
   // path.lineTo(length-4,6);
   // path.lineTo(length-4,4);
   // path.lineTo(0,4);
   // path.lineTo(0,2);
    m_path=path;
    update();
}

QRectF Axis::boundingRect() const
{
    return m_path.boundingRect();
}

QPainterPath Axis::shape() const
{
    return m_path;
}

void Axis::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->save();
    QPen pen(Qt::black);
    //pen.setWidth(10);
    painter->setPen(pen);
    painter->drawPath(m_path);
    painter->restore();
}

QCHART_END_NAMESPACE
