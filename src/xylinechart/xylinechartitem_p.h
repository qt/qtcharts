#ifndef XYLINECHARTITEM_H
#define XYLINECHARTITEM_H

#include "qchartglobal.h"
#include "chartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class QXYChartSeries;
class LineChartAnimationItem;

class XYLineChartItem :  public QObject , public ChartItem
{
     Q_OBJECT
public:
    XYLineChartItem(ChartPresenter* presenter, QXYChartSeries* series,QGraphicsItem *parent = 0);
    ~ XYLineChartItem(){};

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
    //from ChartItem
    void setSize(const QSizeF& size);
    void setPlotDomain(const PlotDomain& data){};
    void setDomain(const Domain& data);
    void setSeries(QXYChartSeries* series);
    const Domain& domain() const { return m_domain;}
    //ChartAnimationManager* animationManager();

    void updateItem();

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
    void calculatePoint(QPointF& point, int index, const QXYChartSeries* series,const QSizeF& size, const Domain& domain) const;
    void calculatePoints(QVector<QPointF>& points,QHash<int,int>& hash,const QXYChartSeries* series, const QSizeF& size, const Domain& domain) const;

private slots:
    void handleSeriesChanged(int index);

private:
    ChartPresenter* m_presenter;
    QPainterPath m_path;
    QSizeF m_size;
    QRectF m_rect;
    Domain m_domain;
    QList<QGraphicsItem*> m_points;
    QVector<QPointF> m_data;
    QHash<int,int> m_hash;
    QXYChartSeries* m_series;
    bool m_dirtyData;
    bool m_dirtyGeometry;
    bool m_dirtyDomain;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
