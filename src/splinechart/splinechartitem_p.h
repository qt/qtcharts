#ifndef SPLINECHARTITEM_P_H
#define SPLINECHARTITEM_P_H

#include "qsplineseries.h"
#include "xychartitem_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplineChartItem : public XYChartItem
{
    Q_OBJECT
public:
    SplineChartItem(QSplineSeries* series, QGraphicsItem *parent = 0);

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

public slots:
    void handleUpdated();

protected:
    void setLayout(QVector<QPointF>& points);

private:
    QPointF calculateGeometryControlPoint(int index) const;

private:
    QSplineSeries* m_series;
    QPainterPath m_path;
    QRectF m_rect;
    QPen m_linePen;
    QPen m_pointPen;
    bool m_pointsVisible;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SPLINECHARTITEM_P_H
