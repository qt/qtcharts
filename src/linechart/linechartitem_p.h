#ifndef LINECHARTITEM_H
#define LINECHARTITEM_H

#include "qchartglobal.h"
#include "xychartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLineSeries;
class ChartPresenter;

class LineChartItem :  public XYChartItem
{
     Q_OBJECT
public:
     explicit LineChartItem(QLineSeries *series,ChartPresenter *presenter);
    ~LineChartItem() {};

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

public Q_SLOTS:
    void handleUpdated();

protected:
    void setLayout(QVector<QPointF>& points);

private:
    QLineSeries* m_series;
    QGraphicsItemGroup m_items;
    QPainterPath m_path;
    QRectF m_rect;
    QPen m_linePen;
    QPen m_pointPen;
    bool m_pointsVisible;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
