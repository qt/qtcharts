#ifndef AREACHARTITEM_H
#define AREACHARTITEM_H

#include "qchartglobal.h"
#include "linechartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class QAreaSeries;
class AreaChartItem;

class AreaChartItem :  public QObject ,public ChartItem
{
    Q_OBJECT
public:
    AreaChartItem(ChartPresenter* presenter, QAreaSeries* areaSeries, QGraphicsItem *parent = 0);
    ~ AreaChartItem();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    void setPen(const QPen& pen);
    void setBrush(const QBrush& brush);
    void setPointsVisible(bool visible);
    void updatePath();
public slots:
    void handleUpdated();
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& size);

private:
    ChartPresenter* m_presenter;
    QPainterPath m_path;
    QAreaSeries* m_series;
    LineChartItem* m_upper;
    LineChartItem* m_lower;
    QRectF m_rect;
    QRectF m_clipRect;
    QPen m_pen;
    QBrush m_brush;
};

class AreaBoundItem : public LineChartItem
{
public:
    AreaBoundItem(AreaChartItem* item,ChartPresenter* presenter, QLineSeries* lineSeries):LineChartItem(presenter,lineSeries),
    m_item(item){};

    ~AreaBoundItem(){};

    void applyGeometry(QVector<QPointF>& points){
        LineChartItem::applyGeometry(points);
        m_item->updatePath();
    }

private:
    AreaChartItem* m_item;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
