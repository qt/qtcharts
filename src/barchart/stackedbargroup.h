#ifndef STACKEDBARGROUP_H
#define STACKEDBARGROUP_H

#include "bargroupbase.h"
#include "stackedbarchartseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class StackedBarGroup : public BarGroupBase
{
public:
    StackedBarGroup(BarChartModel& model, QGraphicsItem *parent = 0);

private:
    // From BarGroupBase
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARGROUP_H
