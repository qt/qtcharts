#ifndef PIECHARTITEM_H
#define PIECHARTITEM_H

#include "qpieseries.h"
#include "chartitem_p.h"
#include "piesliceitem_p.h"

class QGraphicsItem;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QPieSlice;
class ChartPresenter;

typedef QHash<QPieSlice*, PieSliceData> PieLayout;

class PieChartItem : public QObject, public ChartItem
{
    Q_OBJECT

public:
    // TODO: use a generic data class instead of x and y
    PieChartItem(QPieSeries *series, ChartPresenter *presenter, QGraphicsItem *parent);
    ~PieChartItem();

public: // from QGraphicsItem
    QRectF boundingRect() const { return m_rect; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

public Q_SLOTS:
    void initialize();
    void handleSlicesAdded(QList<QPieSlice*> slices);
    void handleSlicesRemoved(QList<QPieSlice*> slices);
    void handlePieLayoutChanged();
    void handleSliceChanged();
    void handleDomainChanged(qreal, qreal, qreal, qreal);
    void handleGeometryChanged(const QRectF& rect);

public:
    void calculatePieLayout();
    PieSliceData sliceData(QPieSlice *slice);
    PieLayout calculateLayout();
    void applyLayout(const PieLayout &layout);
    void updateLayout(QPieSlice *slice, const PieSliceData &sliceData);
    void setLayout(const PieLayout &layout);
    void setLayout(QPieSlice *slice, const PieSliceData &sliceData);
    void destroySlice(QPieSlice *slice);

private:
    friend class PieSliceItem;
    QHash<QPieSlice*, PieSliceItem*> m_slices;
    QPieSeries *m_series;
    QRectF m_rect;
    QPointF m_pieCenter;
    qreal m_pieRadius;
    ChartPresenter *m_presenter;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIECHARTITEM_H
