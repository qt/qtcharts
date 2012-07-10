#ifndef HORIZONTALBARCHARTITEM_H
#define HORIZONTALBARCHARTITEM_H

#include "barchartitem_p.h"
#include "qstackedbarseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE


class HorizontalBarChartitem : public BarChartItem
{
    Q_OBJECT
public:
    HorizontalBarChartitem(QAbstractBarSeries *series, ChartPresenter *presenter);

private:
    virtual QVector<QRectF> calculateLayout();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // HORIZONTALBARCHARTITEM_H
