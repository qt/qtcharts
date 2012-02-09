#ifndef AXISITEM_H_
#define AXISITEM_H_

#include "domain_p.h"
#include "chartitem_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxis;

class AxisItem : public QObject, public ChartItem
{
    Q_OBJECT
public:
    enum AxisType{X_AXIS,Y_AXIS};

    AxisItem(QChartAxis* axis,AxisType type = X_AXIS,QGraphicsItem* parent = 0);
    ~AxisItem();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};

protected slots:
    void handleAxisChanged();
    void handleDomainChanged(const Domain& domain);
    void handleGeometryChanged(const QRectF& size);

protected:
    void updateDomain();

private:
    void clear();

public:
    AxisType axisType() const {return m_type;};

protected:


private:
    void createItems();
private:

    QChartAxis* m_axis;
    AxisType m_type;
    int m_ticks;
    Domain m_domain;
    QRectF m_rect;

    QPainterPath m_path;


    QList<QGraphicsLineItem*> m_grid;
    QList<QGraphicsRectItem*> m_shades;
    QList<QGraphicsSimpleTextItem*> m_labels;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* AXISITEM_H_ */
