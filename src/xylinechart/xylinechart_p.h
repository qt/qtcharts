#ifndef XYLINECHART_H
#define XYLINECHART_H

#include "qchartconfig.h"
#include "qchart.h"
#include "qxyseries.h"
#include "xyplotdata_p.h"

QCHART_BEGIN_NAMESPACE

class Axis;
class XYGrid;

class XYLineChart : public QChart
{

public:
    XYLineChart(QGraphicsItem *parent = 0);
    virtual ~XYLineChart(){};

    //from QGraphicsItem
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //from QChart
    virtual void setSize(const QSizeF& size);

    void addXYSeries(const QXYSeries* series);

    const XYPlotData& xyPlotData() const { return m_plotDataList.at(m_plotDataIndex); }

private:
    void updateGeometry();
    void drawData(QPainter *painter);

private:
    QRect m_rect;
    QList<const QXYSeries*> m_series;
    Axis* m_axisX;
    Axis* m_axisY;
    XYGrid* m_grid;
    QPointF* m_origin;
    QMap<int, QVector<QPointF> > curveMap;
    QList<XYPlotData> m_plotDataList;
    int m_plotDataIndex;


};

QCHART_END_NAMESPACE

#endif
