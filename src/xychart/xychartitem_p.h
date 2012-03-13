#ifndef XYCHARTITEM_H
#define XYCHARTITEM_H

#include "qchartglobal.h"
#include "chartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class QXYSeries;

class XYChartItem :  public QObject , public ChartItem
{
     Q_OBJECT
public:
     explicit XYChartItem(QXYSeries* series, QGraphicsItem *parent = 0);
    ~ XYChartItem(){};

    QVector<QPointF> points() const {return m_points;}
    QRectF clipRect() const { return m_clipRect;}

public slots:
    void handlePointAdded(int index);
    void handlePointRemoved(int index);
    void handlePointReplaced(int index);
    void handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY);
    void handleGeometryChanged(const QRectF& size);

protected:
    virtual void setGeometry(QVector<QPointF>& points);
    QPointF calculateGeometryPoint(const QPointF& point) const;
    QPointF calculateGeometryPoint(int index) const;
    QPointF calculateDomainPoint(const QPointF& point) const;
    QVector<QPointF> calculateGeometryPoints() const;

private:
    void updatePoints(QVector<QPointF>& points);
    void updatePoint(QVector<QPointF>& points);
    inline bool isEmpty();

private:
    qreal m_minX;
    qreal m_maxX;
    qreal m_minY;
    qreal m_maxY;
    QXYSeries* m_series;
    QSizeF m_size;
    QRectF m_clipRect;
    QVector<QPointF> m_points;

    friend class XYAnimation;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
