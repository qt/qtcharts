#ifndef SCATTERPRESENTER_H
#define SCATTERPRESENTER_H

#include "qchartglobal.h"
#include "chartitem_p.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QScatterSeries;

/*!
 * The "business logic" of scatter series. This is a QObject that does not have a parent QObject.
 * The QGraphicsItem parent owns the object instead.
 */
class ScatterPresenter : public QObject, public ChartItem
{
    Q_OBJECT
public:
    explicit ScatterPresenter(QScatterSeries *series, QGraphicsObject *parent = 0);

public: // from ChartItem
    QRectF boundingRect() const { return m_boundingRect; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

signals:

public Q_SLOTS:
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& rect);
    void handleModelChanged();

public:
    void changeGeometry();

    QScatterSeries *m_series;
    QRectF m_boundingRect;
    QList<qreal> m_scenex;
    QList<qreal> m_sceney;
    QColor m_markerColor;
    Domain m_visibleChartArea;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SCATTERPRESENTER_H
