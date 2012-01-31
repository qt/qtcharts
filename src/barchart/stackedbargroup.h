#ifndef STACKEDBARGROUP_H
#define STACKEDBARGROUP_H

#include "chartitem_p.h"
#include "bar.h"
#include "stackedbarchartseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// TODO: derive this from ChartObjectInterface, when setSize is back in ChartItem
class StackedBarGroup : public ChartItem
{
public:
    StackedBarGroup(StackedBarChartSeries& series, QGraphicsItem *parent = 0);

public: // From ChartObjectInterface
    void setSize(const QSize &size);
    void setTheme(ChartTheme *theme);
    void setPlotDomain(const PlotDomain& data);

public: // Layout "api"
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
    StackedBarChartSeries& mSeries;
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

#endif // STACKEDBARGROUP_H
