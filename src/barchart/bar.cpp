#include "bar.h"
#include <QDebug>
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Bar::Bar(ChartItem *parent)
    : ChartItem(parent)
{
}

void Bar::setSize(const QSize& size)
{
    //mSize = size;
    mWidth = size.width();
    mHeight = size.height();
}

void Bar::setPlotDomain(const PlotDomain& data)
{
    mPlotDomain = data;
}

void Bar::resize( int w, int h )
{
    mWidth = w;
    mHeight = h;
}

void Bar::setColor( QColor col )
{
    mColor = col;
}
void Bar::setPos(qreal x, qreal y)
{
    mXpos = x;
    mYpos = y;
}

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Set color for bar. TODO: gradients, textures etc
    QPen pen = painter->pen();
    pen.setColor( mColor );
    pen.setWidth( mWidth );
    painter->setPen(pen);

    // Draw bar
    // TODO: Pen width affects bar height for now. This should be rect
    painter->drawLine(scenePos().x() + mXpos, scenePos().y() + mYpos + parentItem()->boundingRect().height() - mHeight - mWidth,
                      scenePos().x() + mXpos, scenePos().y() + mYpos + parentItem()->boundingRect().height() - mWidth);
}

QRectF Bar::boundingRect() const
{
    // TODO: check validity of this (I suppose there is easier way, and currently this bit incorrect :)
//    QRectF r(scenePos().x()+mXpos, scenePos().y()+mYpos, scenePos().x() + mWidth, scenePos().y() + mHeight );
    QRectF r(mXpos, mYpos, mXpos + mWidth, mYpos + mHeight);
    return r;
}

QTCOMMERCIALCHART_END_NAMESPACE
