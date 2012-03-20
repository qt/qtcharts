#ifndef STACKEDBARCHARTITEM_H
#define STACKEDBARCHARTITEM_H

#include "barchartitem_p.h"
#include "qstackedbarseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class StackedBarChartItem : public BarChartItem
{
    Q_OBJECT
public:
    StackedBarChartItem(QBarSeries *series, QChart *parent = 0);
    ~StackedBarChartItem();

private:
    // From BarChartItem
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARCHARTITEM_H
