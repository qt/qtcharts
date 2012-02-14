#ifndef BARGROUPBASE_H
#define BARGROUPBASE_H

#include "chartitem_p.h"
#include "barchartmodel_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Base Class for bar groups. Common implemantation of different groups. Not to be instantiated.
class BarGroupBase : public QObject, public ChartItem
{
    Q_OBJECT
public:
    BarGroupBase(BarChartModel& model, QGraphicsItem *parent = 0);
    void setSeparatorsVisible(bool visible = true);

public: // From ChartItem
//    void setSize(const QSizeF &size){};

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    // TODO: these may change with layout awarness.
    void setBarWidth( int w );
    int addColor( QColor color );
    void resetColors();

    // TODO: Consider the domain for layoutChanged. May be use case, may not be. If it is, then the derived classes need to implement it
    virtual void dataChanged();     // data of series has changed -> need to recalculate bar sizes
    virtual void layoutChanged() = 0;   // layout has changed -> need to recalculate bar sizes

protected slots:
    void handleModelChanged(int index);
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& size);

protected:

    // TODO: consider these.
    //int mMin;           // Min and max values of data. (updated when data is changed, used when drawing)
    //int mMax;

    int mHeight;        // Layout spesific
    int mWidth;
    int mBarDefaultWidth;

    bool mLayoutSet;    // True, if component has been laid out.
    bool mLayoutDirty;

    QList<QColor> mColors;  // List of colors for series for now
    bool mSeparatorsVisible;
    BarChartModel& mModel;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARGROUPBASE_H
