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

//typedef QVector<QRectF> BarLayout;

class BarChartItem : public ChartItem
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

    virtual QVector<QRectF> calculateLayout();
    void applyLayout(const QVector<QRectF> &layout);
    void setLayout(const QVector<QRectF> &layout);
    void updateLayout(const QVector<QRectF> &layout);

    QRectF geometry() const { return m_rect;}

public Q_SLOTS:
    void handleModelChanged(int index);
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF &size);
    void handleLayoutChanged();

    // Internal slots
    void showToolTip(QPoint pos, QString tip);      // shows tooltip (if enabled)

protected:

    // TODO: consider these.
    qreal m_domainMinX;
    qreal m_domainMaxX;
    qreal m_domainMinY;
    qreal m_domainMaxY;

    QRectF m_rect;
    bool m_layoutSet;    // True, if component has been laid out.
    QVector<QRectF> m_layout;

    // Not owned.
    QBarSeries *m_series;
    QList<Bar *> m_bars;
    QList<BarValue *> m_floatingValues;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTITEM_H
