#ifndef SCATTERPRESENTER_H
#define SCATTERPRESENTER_H

#include "qchartglobal.h"
#include "chartitem_p.h"
#include <QObject>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QScatterSeries;

class ScatterPresenter : public QObject, public ChartItem
{
    Q_OBJECT
public:
    explicit ScatterPresenter(QScatterSeries *series, QGraphicsObject *parent = 0);

public: // from ChartItem
    QRectF boundingRect() const { return m_path.controlPointRect(); }
    QPainterPath shape() const { return m_path; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent (QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
    void clicked(QPointF coordinates);

public Q_SLOTS:
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF& rect);
    void handleModelChanged();

public:
    void changeGeometry();

    qreal m_minX;
    qreal m_maxX;
    qreal m_minY;
    qreal m_maxY;
    QScatterSeries *m_series;
    QRectF m_boundingRect;
    QPen m_markerPen;
    QBrush m_markerBrush;
    QPainterPath m_path;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SCATTERPRESENTER_H
