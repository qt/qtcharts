#ifndef XYGRID_H_
#define XYGRID_H_

#include <qchartconfig.h>
#include <xyplotdata_p.h>
#include <QGraphicsItem>

QCHART_BEGIN_NAMESPACE

class XYGrid : public QGraphicsItem
{
public:
    XYGrid(QGraphicsItem* parent = 0);
    virtual ~XYGrid();

    //from QGraphicsItem
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //TODO: this is just temporary interface
    void setXYPlotData(const XYPlotData& xyPlotData);
    void setSize(const QSizeF& rect);

private:
    QRectF m_rect;
    XYPlotData m_xyPlotData;
};

QCHART_END_NAMESPACE

#endif /* XYGRID_H_ */
