#include <limits.h>
#include <QDebug>
#include "stackedbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarChartSeries::StackedBarChartSeries(QBarCategory &category, QObject *parent) :
    BarChartSeriesBase(category, parent)
{
}

void StackedBarChartSeries::addBarSet(QBarSet &set)
{
    BarChartSeriesBase::addBarSet(set);
}

void StackedBarChartSeries::removeBarSet(QBarSet &set)
{
    BarChartSeriesBase::removeBarSet(set);
}

#include "moc_stackedbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

