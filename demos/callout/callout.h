#ifndef CALLOUT_H
#define CALLOUT_H

#include <QGraphicsItem>
#include <QFont>

class QGraphicsSceneMouseEvent;

class Callout : public QGraphicsItem
{
public:
    Callout(QGraphicsItem * parent = 0);

    void setText(const QString &text);
    void setAnchor(QPointF point);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QString m_text;
    QRectF m_textRect;
    QRectF m_rect;
    QPointF m_anchor;
    QFont m_font;
    QPointF m_clickOffset;
};

#endif // CALLOUT_H
