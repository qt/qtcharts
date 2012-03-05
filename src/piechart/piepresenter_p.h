#ifndef PIEPRESENTER_H
#define PIEPRESENTER_H

#include "chartitem_p.h"
#include "qpieseries.h"
#include <QSignalMapper>

class QGraphicsItem;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PieSlice;

class PiePresenter : public QObject, public ChartItem
{
    Q_OBJECT

public:
    // TODO: use a generic data class instead of x and y
    PiePresenter(QGraphicsItem *parent, QPieSeries *series);
    ~PiePresenter();

public: // from QGraphicsItem
    QRectF boundingRect() const { return m_rect; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

public Q_SLOTS:
    void handleSeriesChanged(const QPieSeries::ChangeSet& changeSet);
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& rect);
    void updateGeometry();

private:
    void addSlice(QPieSlice* sliceData);
    void updateSlice(QPieSlice* sliceData);
    void deleteSlice(QPieSlice* sliceData);

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

#endif // PIEPRESENTER_H
