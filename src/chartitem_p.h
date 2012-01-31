#ifndef CHARTITEM_H_
#define CHARTITEM_H_

#include "plotdomain_p.h"
#include "chartobjectinterface_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
// TODO: setSize and set plotDomain back here. Derive this only from QGraphicsItem
// class ChartItem : public QGraphicsItem
class ChartItem : public QGraphicsItem, public ChartObjectInterface
{
    enum ChartItemTypes{ AXIS_ITEM = UserType+1, XYLINE_ITEM};
public:
    ChartItem(QGraphicsItem* parent = 0):QGraphicsItem(parent){};
    virtual ~ChartItem(){};
    // TODO: this is a hack; integration ongoing:
    QGraphicsItem *graphicsItem() { return this; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTITEM_H_ */
