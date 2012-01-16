#include "qseriespointgraphicsitem.h"
#include <QPainter>
#include <QPicture>
#include <QPixmap>
#include <QDebug>

QSeriesPointGraphicsItem::QSeriesPointGraphicsItem(qreal dx, qreal dy, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_dx(dx),
      m_dy(dy)
{
}

QRectF QSeriesPointGraphicsItem::boundingRect() const
{
//    return parentItem()->boundingRect();
    return QRectF(0, 0, 10, 10);
}

void QSeriesPointGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QTransform transform = painter->transform();
    transform.translate(m_dx, m_dy);
    painter->setTransform(transform);

    QPen pen = painter->pen();
    QBrush brush = pen.brush();
    // TODO: The opacity should be user definable...
    brush.setColor(QColor(255, 82, 0, 50));
    pen.setBrush(brush);
    pen.setWidth(4);
    painter->setPen(pen);
    painter->drawArc(0, 0, 4, 4, 0, 5760);

    // TODO: how about using a bitmap?
//    QPixmap pixmap;
//    pixmap.load("scatter.png");
//    painter->drawPixmap(boundingRect().toRect(), pixmap);

//    painter->drawRect(boundingRect());
}
