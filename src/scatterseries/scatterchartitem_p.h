#ifndef SCATTERPRESENTER_H
#define SCATTERPRESENTER_H

#include "qchartglobal.h"
#include "xychartitem_p.h"
#include <QGraphicsItem>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QScatterSeries;

class ScatterChartItem : public XYChartItem
{
    Q_OBJECT
public:
    explicit ScatterChartItem(QScatterSeries *series, QGraphicsItem *parent = 0);

public:
    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setPen(const QPen& pen);
    void setBrush(const QBrush& brush);

signals:
    void clicked(QPointF coordinates);

public slots:
    void handleUpdated();

private:
    void createPoints(int count);
    void deletePoints(int count);

protected:
    virtual void setGeometry(QVector<QPointF>& points);

private:
    QScatterSeries *m_series;
    QGraphicsItemGroup m_items;
    int m_shape;
    int m_size;
    QRectF m_rect;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SCATTERPRESENTER_H
