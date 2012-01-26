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
    qDebug() << "bar::resize" << w << h;
    mWidth = w;
    mHeight = h;
}

void Bar::setColor( QColor col )
{
    mColor = col;
}
void Bar::setPos(qreal x, qreal y)
{
    qDebug() << "Bar::setpos" << x << y;
    mXpos = x;
    mYpos = y;
}

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (0 == mHeight) {
        return;
    }
    // Set color for bar. TODO: gradients, textures etc
    QPen pen = painter->pen();
    pen.setColor( mColor );
    pen.setWidth( mWidth );
    painter->setPen(pen);

    // Draw bar
    painter->drawLine(mXpos, mYpos,
                      mXpos, mYpos - mHeight);
}

QRectF Bar::boundingRect() const
{
    QRectF r(mXpos, mYpos, mXpos + mWidth, mYpos + mHeight);
    return r;
}

QTCOMMERCIALCHART_END_NAMESPACE
