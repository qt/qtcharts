#ifndef BAR_H
#define BAR_H

#include "qchartglobal.h"
#include <QGraphicsObject>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Single visual bar item of chart
class Bar : public QGraphicsObject
{
    Q_OBJECT
public:
    Bar(QGraphicsItem *parent=0);

public: // from ChartItem
    void setSize(const QSizeF &size);

    // Layout Stuff
    void resize(qreal w, qreal h);
    void setPos(qreal x, qreal y);
    void setPen(QPen pen);
    void setBrush(QBrush brush);

public:
    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

Q_SIGNALS:
    void clicked();
    void hoverEntered(QPoint pos);
    void hoverLeaved();

private:

    qreal mHeight;
    qreal mWidth;
    qreal mXpos;
    qreal mYpos;
    QColor mColor;

    QBrush mBrush;
    QPen mPen;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BAR_H
