#ifndef CHARTITEM_H_
#define CHARTITEM_H_

#include "domain_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartAnimator;

class ChartItem : public QGraphicsItem
{
    enum ChartItemTypes{ AXIS_ITEM = UserType+1, XYLINE_ITEM};
public:
    ChartItem(QGraphicsItem* parent = 0):QGraphicsItem(parent),
    m_animator(0){};
    //TODO make pure
    virtual void handleGeometryChanged(const QRectF&){};
    virtual void handleDomainChanged(const Domain& domain){};

    void setAnimator(ChartAnimator* animator){
        m_animator=animator;
    }

    virtual ~ChartItem(){};

protected:
    ChartAnimator* m_animator;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTITEM_H_ */
