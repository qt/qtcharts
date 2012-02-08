#ifndef BARGROUPBASE_H
#define BARGROUPBASE_H

#include "charttheme_p.h"
#include "chartitem_p.h"
//#include "barlabel_p.h"
//#include "bar_p.h"
#include "barchartseriesbase.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Base Class for bar groups. Common implemantation of different groups. Not to be instantiated.

class BarGroupBase : public QObject, public ChartItem
{
    Q_OBJECT
public:
    BarGroupBase(BarChartSeriesBase& series, QGraphicsItem *parent = 0);
    void setSeparatorsVisible(bool visible = true);

public: // From ChartItem
    void setSize(const QSizeF &size){};
    void setPlotDomain(const PlotDomain& data){};

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    // From ChartThemeObserver
    void themeChanged(ChartTheme *theme);

    // TODO: these may change with layout awarness.
    void setBarWidth( int w );
    int addColor( QColor color );
    void resetColors();

    virtual void dataChanged();     // data of series has changed -> need to recalculate bar sizes
    virtual void layoutChanged() = 0;   // layout has changed -> need to recalculate bar sizes

protected slots:
    void handleModelChanged(int index);
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& size);


protected:

    BarChartSeriesBase& mSeries;

    int mMin;                                   // Min and max values of data. (updated when data is changed, used when drawing)
    int mMax;

    int mHeight;        // Layout spesific
    int mWidth;
    int mBarDefaultWidth;

    bool mLayoutSet;    // True, if component has been laid out.
    bool mLayoutDirty;

    QList<QColor> mColors;  // List of colors for series for now

    ChartTheme* mTheme;
    bool mSeparatorsVisible;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARGROUPBASE_H
