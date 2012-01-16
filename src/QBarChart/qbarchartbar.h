#ifndef QBARCHARTBAR_H
#define QBARCHARTBAR_H

#include <QGraphicsItem>

// Single bar item of chart

class QBarChartBar : public QGraphicsItem
{
public:
    QBarChartBar(QGraphicsItem *parent=0);

    // Layout Stuff
    void setSize( int h, int w );       // Size of bar. in screen coordinates.
    void setColor( QColor col );        // Color of bar

public:
    // From QGraphicsItem

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

private:

    int mHeight;
    int mWidth;
    QPointF mPos;
    QColor mColor;
};

#endif // QBARCHARTBAR_H
