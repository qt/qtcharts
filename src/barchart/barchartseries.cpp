#include <QDebug>
#include "barchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartSeries::BarChartSeries(QBarCategory &category, QObject *parent)
    : BarChartSeriesBase(category, parent)
{
}

void BarChartSeries::addBarSet(QBarSet &set)
{
    BarChartSeriesBase::addBarSet(set);
}

void BarChartSeries::removeBarSet(QBarSet &set)
{
    BarChartSeriesBase::removeBarSet(set);
}

#include "moc_barchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
