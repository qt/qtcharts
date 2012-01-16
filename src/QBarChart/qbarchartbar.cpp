#include "qbarchartbar.h"
#include <QDebug>
#include <Qpainter>

QBarChartBar::QBarChartBar(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
}

void QBarChartBar::setSize( int h, int w )
{
    mHeight = h;
    mWidth = w;
}

void QBarChartBar::setColor( QColor col )
{
    mColor = col;
}

void QBarChartBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "QBarChartBar::paint" << scenePos();
    // Set color for bar. TODO: gradients, textures etc
    QPen pen = painter->pen();
    pen.setColor( mColor );
    pen.setWidth( mWidth );
    painter->setPen(pen);

    // Draw bar
    painter->drawLine(scenePos().x(), scenePos().y() + parentItem()->boundingRect().height(),
                      scenePos().x(), scenePos().y() + parentItem()->boundingRect().height() - mHeight );
}

QRectF QBarChartBar::boundingRect() const
{
    QRectF r(scenePos().x(), scenePos().y(), scenePos().x() + mWidth, scenePos().y() + mHeight );
    return r;
}
