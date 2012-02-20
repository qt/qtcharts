#ifndef QBARGROUP_H
#define QBARGROUP_H

#include "barpresenterbase.h"
#include "qbarchartseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Base class for bar groups

class BarPresenter : public BarPresenterBase
{
public:
    explicit BarPresenter(BarChartModel& model, QGraphicsItem *parent = 0);

private:

    // From BarGroupBase
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:
    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARGROUP_H
