#include "percentbarchartseries.h"

#include <limits.h>
#include <QDebug>
#include "percentbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PercentBarChartSeries::PercentBarChartSeries(QBarCategory &category, QObject *parent) :
    BarChartSeriesBase(category, parent)
{
}

void PercentBarChartSeries::addBarSet(QBarSet &set)
{
    BarChartSeriesBase::addBarSet(set);
}

void PercentBarChartSeries::removeBarSet(QBarSet &set)
{
    BarChartSeriesBase::removeBarSet(set);
}

#include "moc_percentbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

