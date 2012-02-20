#ifndef STACKEDBARGROUP_H
#define STACKEDBARGROUP_H

#include "barpresenterbase.h"
#include "qstackedbarchartseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class StackedBarPresenter : public BarPresenterBase
{
public:
    StackedBarPresenter(BarChartModel& model, QGraphicsItem *parent = 0);

private:
    // From BarGroupBase
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARGROUP_H
