#include "qscatterseries.h"
#include <QPainter>

QScatterSeries::QScatterSeries(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}

QRectF QScatterSeries::boundingRect() const
{
//    qreal penWidth = 1;
//    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
//                  20 + penWidth, 20 + penWidth);
    return QRectF(0, 0, 100, 100);
}

void QScatterSeries::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen = painter->pen();
    QBrush brush = pen.brush();
    brush.setColor(Qt::darkRed);
    pen.setBrush(brush);
    painter->setPen(pen);
    painter->drawRoundedRect(0, 0, 10, 10, 5, 5);
    painter->drawRoundedRect(5, 5, 10, 10, 5, 5);
    painter->drawRoundedRect(54, 25, 10, 10, 5, 5);
    painter->drawRoundedRect(34, 35, 10, 10, 5, 5);
    //painter->drawEllipse(QPoint(10, 10), 100, 100);
}
