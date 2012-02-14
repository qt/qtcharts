#ifndef QBARGROUP_H
#define QBARGROUP_H

#include "bargroupbase.h"
#include "barchartseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Base class for bar groups

class BarGroup : public BarGroupBase
{
public:
    explicit BarGroup(BarChartModel& model, QGraphicsItem *parent = 0);

private:

    // From BarGroupBase
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:
    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARGROUP_H
