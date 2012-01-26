#ifndef QBARCHART_H
#define QBARCHART_H

#include "chartitem_p.h"
#include "bar.h"
#include "barchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// TODO: Better name for this? The function of this class is to know where each bar in series is laid out.
//class BarGroup : public QGraphicsItemGroup

class BarGroup : public ChartItem
{
/* // TODO: implement as singleton?
private:
    static BarGroup* mBarGroupInstance;

public:
    static BarGroup* instance()
    {
        if (mBarGroupInstance == NULL) {
            mBarGroupInstance = new BarGroup();
        }
        return mBarGroupInstance;
    }
private:
*/
public:
    explicit BarGroup(BarChartSeries& series, QGraphicsItem *parent = 0);

    // From ChartItem
    virtual void setSize(const QSize& size);
    virtual void setPlotDomain(const PlotDomain& data);

    // Layout "api"
    void resize( int w, int h );        // Size for whole series. Single bars are drawn inside this area
    void setPos(qreal x, qreal y);
    void setBarWidth( int w );          // Default width for each bar
    void setColor( QColor color );      // Default color for each bar

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:

    void dataChanged();     // data of series has changed -> need to recalculate bar sizes
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
    BarChartSeries& mSeries;
    int mMin;                                   // Min and max values of data. (updated when data is changed, used when drawing)
    int mMax;

    int mHeight;        // Layout spesific
    int mWidth;
    int mBarDefaultWidth;

    QColor mColor;

    bool mLayoutSet;    // True, if component has been laid out.
    bool mLayoutDirty;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARCHART_H
