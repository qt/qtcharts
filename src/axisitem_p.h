#ifndef AXISITEM_H_
#define AXISITEM_H_

#include "plotdomain_p.h"
#include "chartitemcontrol.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class AxisItem: public QGraphicsItem, public ChartItemControl
{
public:
    enum AxisType{X_AXIS,Y_AXIS};

    AxisItem(AxisType type = X_AXIS,QGraphicsItem* parent = 0);
    ~AxisItem();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};

public: // from ChartItemControl
    void setPos (const QPointF & pos);
    void resize(const QSize &size);
    void setTheme(ChartTheme *theme);
    void setPlotDomain(const PlotDomain& data);

public:
    void setLength(int length);
    void setWidth(int width);
    AxisType axisType() const {return m_type;};

private:
    void createItems();
private:
    QRectF m_rect;
    int m_ticks;
    PlotDomain m_plotDomain;
    QPainterPath m_path;

    QList<QGraphicsLineItem*> m_grid;
    QList<QGraphicsRectItem*> m_shades;
    QList<QGraphicsSimpleTextItem*> m_labels;
    AxisType m_type;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* AXISITEM_H_ */
