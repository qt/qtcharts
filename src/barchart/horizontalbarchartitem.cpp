#include "horizontalbarchartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

HorizontalBarChartitem::HorizontalBarChartitem(QAbstractBarSeries *series, ChartPresenter *presenter) :
    BarChartItem(series, presenter)
{
}

QVector<QRectF> HorizontalBarChartitem::calculateLayout()
{
    // TODO:
    QVector<QRectF> layout;
    return layout;
}

#include "moc_horizontalbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
