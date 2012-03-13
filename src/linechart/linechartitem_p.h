#ifndef LINECHARTITEM_H
#define LINECHARTITEM_H

#include "qchartglobal.h"
#include "xychartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QLineSeries;

class LineChartItem :  public XYChartItem
{
     Q_OBJECT
public:
     explicit LineChartItem(QLineSeries* series,QGraphicsItem *parent = 0);
    ~ LineChartItem(){};

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

public slots:
    void handleUpdated();

signals:
    void clicked(const QPointF& point);

protected:
    virtual void setGeometry(QVector<QPointF>& points);
    void mousePressEvent( QGraphicsSceneMouseEvent * event );

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
