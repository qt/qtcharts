#ifndef QBARCHARTXAXIS_H
#define QBARCHARTXAXIS_H

#include <QGraphicsItem>

class QBarChartXAxis : public QGraphicsItem
{

public:
    QBarChartXAxis(QGraphicsItem *parent = 0);

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:

    int mWidth;
    int mHeight;
};

#endif // QBARCHARTXAXIS_H
