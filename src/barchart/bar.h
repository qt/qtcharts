#ifndef BAR_H
#define BAR_H

#include "chartitem_p.h"
#include "qchartglobal.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Single bar item of chart
class Bar : public ChartItem
{
public:
    Bar(QGraphicsItem *parent=0);

public: // from ChartItemControl
    void setSize(const QSize &size);
    void setTheme(ChartTheme *theme);
    void setPlotDomain(const PlotDomain& data);

    // Layout Stuff
    void resize( int w, int h );       // Size of bar. in screen coordinates.
    void setColor( QColor col );       // Color of bar
    void setPos(qreal x, qreal y);

public:
    // From QGraphicsItem

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

private:

    int mHeight;
    int mWidth;
    qreal mXpos;
    qreal mYpos;
    QColor mColor;

    PlotDomain mPlotDomain;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BAR_H
