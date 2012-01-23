#ifndef BAR_H
#define BAR_H

#include <QGraphicsItem>
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Single bar item of chart
class Bar : public QGraphicsItem
{
public:
    Bar(QGraphicsItem *parent=0);

    // Layout Stuff
    void resize( int w, int h );       // Size of bar. in screen coordinates.
    void setColor( QColor col );       // Color of bar
    void setPos(qreal x, qreal y);

public:
    // From QGraphicsItem

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

private:

    int mHeight;
    int mWidth;
    qreal mXpos;
    qreal mYpos;
    QColor mColor;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BAR_H
