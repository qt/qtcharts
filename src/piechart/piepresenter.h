#ifndef PIEPRESENTER_H
#define PIEPRESENTER_H

#include "chartitem_p.h"
#include "qpieseries.h"

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

public: // from ChartItem
    void setSize(const QSizeF &size);
    void setPlotDomain(const PlotDomain& data);
    QRectF boundingRect() const { return m_rect; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}

public:
    void seriesChanged();
    void resize();
    QRectF pieRect() const { return m_pieRect; }

public Q_SLOTS:
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& rect);

private:
    friend class PieSlice;
    QList<PieSlice*> m_slices;
    QPieSeries *m_pieSeries;
    QRectF m_rect;
    QRectF m_pieRect;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIEPRESENTER_H
