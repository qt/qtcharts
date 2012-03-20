#ifndef BARCHARTITEM_H
#define BARCHARTITEM_H

#include "chartitem_p.h"
#include "qbarseries.h"
#include <QPen>
#include <QBrush>
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Bar;
class BarValue;
class QChartAxisCategories;
class QChart;

typedef QHash<Bar*, QSizeF> BarLayout;

class BarChartItem : public QObject, public ChartItem
{
    Q_OBJECT
public:
    BarChartItem(QBarSeries *series, ChartPresenter *presenter);
    virtual ~BarChartItem();

// Common implemantation of different presenters. Not to be instantiated.
// TODO: combine this with BarPresenter and derive other presenters from it?

public:
    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    // TODO: Consider the domain for layoutChanged. May be use case, may not be. If it is, then the derived classes need to implement it
    virtual void dataChanged();     // data of series has changed -> need to recalculate bar sizes
private slots:
    virtual void layoutChanged();   // layout has changed -> need to recalculate bar sizes

public:
    BarLayout calculateLayout();
    void applyLayout(const BarLayout &layout);
    void setLayout(const BarLayout &layout);

protected:
    void initAxisLabels();

public slots:
    void handleModelChanged(int index);
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF& size);
    void handleLayoutChanged();

    // Internal slots
    void showToolTip(QPoint pos, QString tip);      // shows tooltip (if enabled)

protected:

    // TODO: consider these.
    int mHeight;        // Layout spesific
    int mWidth;
    qreal mBarWidth;

    qreal mDomainMinX;
    qreal mDomainMaxX;
    qreal mDomainMinY;
    qreal mDomainMaxY;

    bool mLayoutSet;    // True, if component has been laid out.

    // Not owned.
    QBarSeries* mSeries;
    QList<Bar*> mBars;
    QList<BarValue*> mFloatingValues;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTITEM_H
