#ifndef BARPRESENTERBASE_H
#define BARPRESENTERBASE_H

#include "chartitem_p.h"
#include "qbarseries.h"
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Bar;
class BarLabel;
class Separator;
class BarValue;

// Common implemantation of different presenters. Not to be instantiated.
// TODO: combine this with BarPresenter and derive other presenters from it?
class BarPresenterBase : public QObject, public ChartItem
{
    Q_OBJECT
public:
    BarPresenterBase(QBarSeries *series, QGraphicsItem *parent = 0);
    virtual ~BarPresenterBase();

public:
    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    // TODO: these may change with layout awarness.
    void setBarWidth( int w );

    // TODO: Consider the domain for layoutChanged. May be use case, may not be. If it is, then the derived classes need to implement it
    virtual void dataChanged();     // data of series has changed -> need to recalculate bar sizes
    virtual void layoutChanged() = 0;   // layout has changed -> need to recalculate bar sizes

public slots:
    void handleModelChanged(int index);
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& size);

    // Internal slots
    void showToolTip(QPoint pos, QString tip);      // shows tooltip (if enabled)
    void enableSeparators(bool enabled);

protected:

    // TODO: consider these.
    int mHeight;        // Layout spesific
    int mWidth;
    int mBarDefaultWidth;

    bool mLayoutSet;    // True, if component has been laid out.
    bool mLayoutDirty;

    bool mSeparatorsEnabled;

    // Owned
    QBarSeries* mSeries;

    // Not owned.
    QList<Bar*> mBars;
    QList<BarLabel*> mLabels;
    QList<Separator*> mSeparators;
    QList<BarValue*> mFloatingValues;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARPRESENTERBASE_H
