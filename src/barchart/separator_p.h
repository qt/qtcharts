#ifndef SEPARATOR_H
#define SEPARATOR_H

#include "chartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Separator : public ChartItem
{
public:
    Separator(QGraphicsItem *parent = 0);

    void setPos(qreal x, qreal y);
    void setColor(QColor color);

    // From ChartItem
    void setSize(const QSizeF &size);

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

private:

    QColor mColor;
    qreal mXpos;
    qreal mYpos;
    qreal mHeight;
    qreal mWidth;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SEPARATOR_H
