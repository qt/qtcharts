#ifndef BAR_H
#define BAR_H

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

public: // from ChartItem
    void setSize(const QSizeF &size);

    // Layout Stuff
    void resize(qreal w, qreal h);   // Size of bar.
    void setPos(qreal x, qreal y);
    void setPen(QPen pen);
    void setBrush(QBrush brush);
    void setColor( QColor col);     // deprecated

public:
    // From QGraphicsItem

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
    void clicked();

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
