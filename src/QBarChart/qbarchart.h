#ifndef QBARCHART_H
#define QBARCHART_H

#include <QGraphicsItem>

#include "qbarchartbar.h"
#include "qbarchartcontrol.h"
#include "qbarchartview.h"
#include "qbarchartgrid.h"

class QBarChart : public QGraphicsItem
{

public:
    explicit QBarChart(QGraphicsItem *parent = 0);

    // Data "api"
    void addSeries(QList<int> data);     // TODO: maybe some better structure

    // Layout "api"
    void setSize( int h, int w );
    void setPos(qreal x, qreal y);
    void setBarWidth( int w );

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:

    void dataChanged();
    void gridChanged();

private:

    // Data
    QList<int> mData;      // use ints for now..
    int mMin;              // Min and max values of data. (updated when data is changed, used when drawing)
    int mMax;

    // View components
    QList<QBarChartBar> mItems;     // 2 first items in list are x and y axis, in that order
    QBarChartGrid *mGrid;

    int mHeight;        // Layout spesific
    int mWidth;
    int mBarDefaultWidth;

    // Controll stuff
    QBarChartControl mBarControl;



};

#endif // QBARCHART_H
