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
    StackedBarChartItem(QBarSeries *series, ChartPresenter *presenter);
    ~StackedBarChartItem();

private:
    // From BarChartItem
    virtual QVector<QRectF> calculateLayout();

private:

    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARCHARTITEM_H
