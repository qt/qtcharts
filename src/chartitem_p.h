#ifndef CHARTITEM_H_
#define CHARTITEM_H_

#include "plotdomain_p.h"
#include "domain_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartAnimationManager;

class ChartItem : public QGraphicsItem
{
    enum ChartItemTypes{ AXIS_ITEM = UserType+1, XYLINE_ITEM};
public:
    ChartItem(QGraphicsItem* parent = 0):QGraphicsItem(parent){};
    virtual ~ChartItem(){};

    virtual void setSize(const QSizeF& size) = 0;
    virtual void setPlotDomain(const PlotDomain& data) = 0;

    //future interface
    virtual void setDomain(const Domain& data){};
    virtual void updateItem(){};
    virtual ChartAnimationManager* animationManager(){ return 0;};
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTITEM_H_ */
