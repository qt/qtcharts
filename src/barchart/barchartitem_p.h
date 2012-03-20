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

// Common implemantation of different presenters.
class BarChartItem : public QObject, public ChartItem
{
    Q_OBJECT
public:
    BarChartItem(QBarSeries *series, QChart *parent = 0);
    virtual ~BarChartItem();

public:
    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    // TODO: Consider the domain for layoutChanged. May be use case, may not be. If it is, then the derived classes need to implement it
    virtual void dataChanged();     // data of series has changed -> need to recalculate bar sizes
private slots:
    virtual void layoutChanged();   // layout has changed -> need to recalculate bar sizes

protected:
    void initAxisLabels();

public slots:
    void handleModelChanged(int index);
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF& size);

    // Internal slots
    void showToolTip(QPoint pos, QString tip);      // shows tooltip (if enabled)

protected:

    // TODO: consider these.
    int mHeight;        // Layout spesific
    int mWidth;
    qreal mBarWidth;

    bool mLayoutSet;    // True, if component has been laid out.

    // Not owned.
    QBarSeries* mSeries;
    QList<Bar*> mBars;
    QList<BarValue*> mFloatingValues;
    QChart* mChart;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTITEM_H
