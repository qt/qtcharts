#ifndef PERCENTBARGROUP_H
#define PERCENTBARGROUP_H

#include "chartitem_p.h"
#include "bar_p.h"
#include "percentbarchartseries.h"
#include "bargroupbase.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PercentBarGroup : public BarGroupBase
{
public:
    PercentBarGroup(PercentBarChartSeries& series, QGraphicsItem *parent = 0);

private:

    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PERCENTBARGROUP_H
