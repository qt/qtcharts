#ifndef CHARTITEM_H_
#define CHARTITEM_H_

#include "chart_p.h"
#include "chartpresenter_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem : public QGraphicsItem, public Chart
{
    enum ChartItemTypes{ AXIS_ITEM = UserType+1, XYLINE_ITEM};
public:
    ChartItem(ChartPresenter *presenter):QGraphicsItem(presenter->rootItem()),Chart(presenter){};
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTITEM_H_ */
