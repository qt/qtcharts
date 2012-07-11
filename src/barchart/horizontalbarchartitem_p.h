#ifndef HORIZONTALBARCHARTITEM_H
#define HORIZONTALBARCHARTITEM_H

#include "abstractbarchartitem_p.h"
#include "qstackedbarseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE


class HorizontalBarChartitem : public AbstractBarChartItem
{
    Q_OBJECT
public:
    HorizontalBarChartitem(QAbstractBarSeries *series, ChartPresenter *presenter);

private:
    virtual QVector<QRectF> calculateLayout();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // HORIZONTALBARCHARTITEM_H
