#ifndef LINECHARTITEM_H
#define LINECHARTITEM_H

#include "qchartglobal.h"
#include "chartitem_p.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class QLineChartSeries;
class LineChartAnimationItem;

class LineChartItem :  public QObject , public ChartItem
{
     Q_OBJECT
public:
    LineChartItem(ChartPresenter* presenter, QLineChartSeries* series,QGraphicsItem *parent = 0);
    ~ LineChartItem(){};

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    void setPen(const QPen& pen);
    const Domain& domain() const { return m_domain;}

    virtual void addPoint(const QPointF& );
    virtual void addPoints(const QVector<QPointF>& points);
    virtual void removePoint(const QPointF& point);
    virtual void setPoint(const QPointF& oldPoint, const QPointF& newPoint);
    virtual void setPoint(int index,const QPointF& point);
    void clear();
    void clearView();
    int count() const { return m_data.size();}

    const QVector<QPointF>& points(){ return m_data;}

protected:
    virtual void updateGeometry();
    virtual void updateData();
    virtual void updateDomain();
    //refactor
    void calculatePoint(QPointF& point, int index, const QLineChartSeries* series,const QSizeF& size, const Domain& domain) const;
    void calculatePoints(QVector<QPointF>& points,QHash<int,int>& hash,const QLineChartSeries* series, const QSizeF& size, const Domain& domain) const;

protected slots:
    void handleModelChanged(int index);
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& size);

private:
    ChartPresenter* m_presenter;
    QPainterPath m_path;
    QSizeF m_size;
    QRectF m_rect;
    Domain m_domain;
    QList<QGraphicsItem*> m_points;
    QVector<QPointF> m_data;
    QHash<int,int> m_hash;
    QLineChartSeries* m_series;
    QPen m_pen;
    bool m_dirtyData;
    bool m_dirtyGeometry;
    bool m_dirtyDomain;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
