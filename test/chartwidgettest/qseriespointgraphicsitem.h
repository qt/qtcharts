#ifndef QSERIESPOINTGRAPHICSITEM_H
#define QSERIESPOINTGRAPHICSITEM_H

#include <QGraphicsItem>

class QSeriesPointGraphicsItem : public QGraphicsItem
{
public:
    QSeriesPointGraphicsItem(qreal dx, qreal dy, QGraphicsItem *parent = 0);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    qreal m_dx;
    qreal m_dy;
};

#endif // QSERIESPOINTGRAPHICSITEM_H
