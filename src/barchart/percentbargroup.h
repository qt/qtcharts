#ifndef PERCENTBARGROUP_H
#define PERCENTBARGROUP_H

#include "chartitem_p.h"
#include "bar.h"
#include "percentbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PercentBarGroup : public ChartItem
{
public:
    PercentBarGroup(PercentBarChartSeries& series, QGraphicsItem *parent = 0);

    // From ChartItem
    virtual void setSize(const QSize& size);
    virtual void setPlotDomain(const PlotDomain& data);

    // Layout "api"
    void setPos(qreal x, qreal y);
    void setBarWidth( int w );          // Default width for each bar

    int addColor( QColor color );
    void resetColors();

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:

    void dataChanged();     // data of series has changed -> need to recalculate bar sizes
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
    PercentBarChartSeries& mSeries;
    int mMin;                                   // Min and max values of data. (updated when data is changed, used when drawing)
    int mMax;

    int mHeight;        // Layout spesific
    int mWidth;
    int mBarDefaultWidth;

    bool mLayoutSet;    // True, if component has been laid out.
    bool mLayoutDirty;

    QList<QColor> mColors;  // List of colors for series for now

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PERCENTBARGROUP_H
