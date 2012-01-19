#ifndef CHART_H
#define CHART_H

#include <qchartconfig.h>
#include <QGraphicsItem>

QCHART_BEGIN_NAMESPACE

class Axis;
class XYGrid;
class QChartSeries;
class XYPlotDomain;

class QCHART_EXPORT QChart : public QGraphicsItem
{

public:
    QChart(QGraphicsItem* parent = 0);
    virtual ~QChart();

    //from QGraphicsItem
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};

    void addSeries(QChartSeries* series);

    virtual void setSize(const QSizeF& rect);
    void setMargin(int margin);
    int margin() const { return m_marginSize;}

private:
    QRect m_rect;
    QList<const QChartSeries*> m_series;
    Axis* m_axisX;
    Axis* m_axisY;
    XYGrid* m_grid;
    QList<XYPlotDomain*> m_plotDataList;
    QList<QGraphicsItem*> m_items;
    int m_plotDataIndex;
    int m_marginSize;
};

QCHART_END_NAMESPACE

#endif
