#ifndef BAR_H
#define BAR_H

//#include "chartitem_p.h"
#include "qchartglobal.h"
#include <QGraphicsObject>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Single bar item of chart
class Bar : public QGraphicsObject
{
    Q_OBJECT

public:
    Bar(QGraphicsItem *parent=0);

public:

    // Layout Stuff
    void resize(qreal w, qreal h);   // Size of bar.
    void setPos(qreal x, qreal y);
    void setPen(QPen pen);
    void setBrush(QBrush brush);

public:

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
    void clicked();
    void hoverEnter();
    void hoverLeave();

private:

    qreal mHeight;
    qreal mWidth;
    qreal mXpos;
    qreal mYpos;

    QBrush mBrush;
    QPen mPen;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BAR_H
