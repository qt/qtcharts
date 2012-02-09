#ifndef BAR_H
#define BAR_H

#include "chartitem_p.h"
#include "qchartglobal.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Single bar item of chart
class Bar : public ChartItem
{
public:
    Bar(QGraphicsItem *parent=0);

public: // from ChartItem
    void setSize(const QSizeF &size);

    // Layout Stuff
    void resize( qreal w, qreal h );   // Size of bar.
    void setColor( QColor col );       // Color of bar
    void setPos(qreal x, qreal y);

public:
    // From QGraphicsItem

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

private:

    qreal mHeight;
    qreal mWidth;
    qreal mXpos;
    qreal mYpos;
    QColor mColor;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BAR_H
