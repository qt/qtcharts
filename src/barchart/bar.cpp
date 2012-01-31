#include "bar.h"
#include <QDebug>
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Bar::Bar(QGraphicsItem *parent)
    : ChartItem(parent)
{
}

void Bar::setSize(const QSize& size)
{
    mWidth = size.width();
    mHeight = size.height();
}

void Bar::setPlotDomain(const PlotDomain& data)
{
    mPlotDomain = data;
}

void Bar::setTheme(ChartTheme *theme)
{
    // TODO
}

void Bar::resize( int w, int h )
{
//    qDebug() << "bar::resize" << w << h;
    mWidth = w;
    mHeight = h;
}

void Bar::setColor( QColor col )
{
    mColor = col;
}
void Bar::setPos(qreal x, qreal y)
{
 //   qDebug() << "Bar::setpos" << x << y;
    mXpos = x;
    mYpos = y;
}

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (0 == mHeight) {
        return;
    }
    // TODO: accept brush instead of color
    QBrush brush(mColor);
    painter->setBrush(brush);
    painter->drawRect(mXpos-mWidth, mYpos-mHeight ,mWidth ,mHeight); // Evil inverse rect, because we want bars to grow from bottom to top :)
}

QRectF Bar::boundingRect() const
{
    QRectF r(mXpos, mYpos, mXpos + mWidth, mYpos + mHeight);
    return r;
}

QTCOMMERCIALCHART_END_NAMESPACE
