#include <QDebug>
#include "barchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartSeries::BarChartSeries(QBarCategory &category, QObject *parent)
    : BarChartSeriesBase(category, parent)
{
}

#include "moc_barchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
