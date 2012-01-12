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
    brush.setColor(Qt::darkRed);
    pen.setBrush(brush);
    painter->setPen(pen);

    QPixmap pixmap;
    pixmap.load("scatter.png");
    painter->drawPixmap(boundingRect().toRect(), pixmap);

//    painter->drawRect(boundingRect());
}
