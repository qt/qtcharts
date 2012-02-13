#include <limits.h>
#include <QDebug>
#include "stackedbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarChartSeries::StackedBarChartSeries(QBarCategory &category, QObject *parent) :
    BarChartSeriesBase(category, parent)
{
}

#include "moc_stackedbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

