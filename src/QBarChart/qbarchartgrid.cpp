#include "qbarchartgrid.h"
#include <QDebug>
#include <QPainter>

QBarChartGrid::QBarChartGrid(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}


void QBarChartGrid::setLimits( int min, int max )
{
    mMin = min;
    mMax = max;
}

void QBarChartGrid::setHorizontalLineCount(int count)
{
    mHorizontalLineCount = count;
}

void QBarChartGrid::setSize( int h, int w )
{
    mHeight = h;
    mWidth = w;
}

void QBarChartGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "QBarChartGrid::paint w =" << mWidth << "h =" << mHeight;

    QPen p = painter->pen();
    p.setColor( QColor(0,255,0) );
    p.setWidth( 1 );
    painter->setPen(p);

    // Draw horizontal lines
    if ( mHorizontalLineCount >0 ) {
        int step = mHeight / mHorizontalLineCount;
        if (step > 0) {
            for (int y=0; y<mHeight; y+=step) {
                painter->drawLine(0,y,mWidth,y);
            }
        }
    }
}

QRectF QBarChartGrid::boundingRect() const
{
    QRectF r(scenePos().x(), scenePos().y(), scenePos().x() + mWidth, scenePos().y() + mHeight );
    return r;
}
