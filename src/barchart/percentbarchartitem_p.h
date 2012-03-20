#ifndef PERCENTBARCHARTITEM_H
#define PERCENTBARCHARTITEM_H

#include "barchartitem_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSeries;

class PercentBarChartItem : public BarChartItem
{
    Q_OBJECT
public:
    PercentBarChartItem(QBarSeries *series, QChart *parent = 0);

private:

    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PERCENTBARCHARTITEM_H
