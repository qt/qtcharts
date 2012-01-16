#ifndef XYGRID_H_
#define XYGRID_H_

#include <qchartconfig.h>
#include <QGraphicsItem>

QCHART_BEGIN_NAMESPACE

class XYPlotData;
class XYLineChart;

class XYGrid : public QGraphicsItem
{
public:
    XYGrid(const XYLineChart* const chart,QGraphicsItem* parent = 0);
    virtual ~XYGrid();

    //from QGraphicsItem
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setSize(const QSizeF& rect);

private:
    QRectF m_rect;
    const XYLineChart* const m_chart;
};

QCHART_END_NAMESPACE

#endif /* XYGRID_H_ */
