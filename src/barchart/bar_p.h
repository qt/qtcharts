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
    Bar(QString category, QGraphicsItem *parent=0);

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
    void clicked(QString category);
    void rightClicked(QString category);
    void hoverEntered(QPoint pos);
    void hoverLeaved();

private:

    qreal mXpos;
    qreal mYpos;
    qreal mWidth;
    qreal mHeight;

    QBrush mBrush;
    QPen mPen;

    QString mCategory;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BAR_H
