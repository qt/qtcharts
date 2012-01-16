#ifndef QBARCHARTGRID_H
#define QBARCHARTGRID_H

#include <QGraphicsItem>

class QBarChartGrid : public QGraphicsItem
{

public:
    QBarChartGrid(QGraphicsItem *parent = 0);

    // Data api:
    void setLimits( int min, int max );
    void setHorizontalLineCount( int count );

    // Layout api:
    void setSize( int h, int w );

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:

    int mWidth;
    int mHeight;

    int mMin;
    int mMax;
    int mHorizontalLineCount;      // Draw this many horizontal lines to grid
};

#endif // QBARCHARTGRID_H
