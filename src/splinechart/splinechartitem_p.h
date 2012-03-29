#ifndef SPLINECHARTITEM_P_H
#define SPLINECHARTITEM_P_H

#include "qsplineseries.h"
#include "xychartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplineChartItem : public XYChartItem
{
    Q_OBJECT
public:
    SplineChartItem(QSplineSeries *series, ChartPresenter *presenter);

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

public Q_SLOTS:
    void handleUpdated();

protected:
    void setLayout(QVector<QPointF> &points,QVector<QPointF> &controlPoints);
    void updateLayout(QVector<QPointF> &oldPoints,QVector<QPointF> &newPoints,int index);

private:
    QPointF calculateGeometryControlPoint(int index) const;

private:
    QSplineSeries* m_series;
    QPainterPath m_path;
    QRectF m_rect;
    QPen m_linePen;
    QPen m_pointPen;
    bool m_pointsVisible;
    QVector<QPointF> m_controlPoints;

    friend class SplineAnimation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SPLINECHARTITEM_P_H
