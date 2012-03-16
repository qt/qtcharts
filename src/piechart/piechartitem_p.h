#ifndef PIECHARTITEM_H
#define PIECHARTITEM_H

#include "qpieseries.h"
#include "chartitem_p.h"
#include "pieslice_p.h"

class QGraphicsItem;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QPieSlice;

class PieChartItem : public QObject, public ChartItem
{
    Q_OBJECT

public:
    // TODO: use a generic data class instead of x and y
    PieChartItem(QGraphicsItem *parent, QPieSeries *series);
    ~PieChartItem();

public: // from QGraphicsItem
    QRectF boundingRect() const { return m_rect; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

public Q_SLOTS:
    void handleSeriesChanged();
    void handleSliceChanged();
    void handleDomainChanged(qreal, qreal, qreal, qreal);
    void handleGeometryChanged(const QRectF& rect);

public:
    QVector<PieSliceLayout> calculateLayout();
    void applyLayout(QVector<PieSliceLayout> &layout);
    void updateLayout(PieSliceLayout &layout);
    void setLayout(QVector<PieSliceLayout> &layout);
    void setLayout(PieSliceLayout &layout);
    void destroySlice(QPieSlice *slice);

private:
    friend class PieSlice;
    QHash<QPieSlice*, PieSlice*> m_slices;
    QPieSeries *m_series;
    QRectF m_rect;
    QPointF m_pieCenter;
    qreal m_pieRadius;
    QRectF m_debugRect;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIECHARTITEM_H
