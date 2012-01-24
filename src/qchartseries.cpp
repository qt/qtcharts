#include "qchartglobal.h"
#include "qchartseries.h"

#include "barchartseries.h"
#include "qxychartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartSeries* QChartSeries::create(QChartSeriesType type, QObject* parent)
{
    // TODO: Other types
    switch (type) {
    case QChartSeries::SeriesTypeLine: {
        QXYChartSeries* s = QXYChartSeries::create(parent); // TODO: do we need create method for derived implementations?
        return s;
    }
    case QChartSeries::SeriesTypePie: {
       return 0;
    }
    case QChartSeries::SeriesTypeScatter: {
       return 0;
    }
    case QChartSeries::SeriesTypeBar: {
        BarChartSeries* s = new BarChartSeries(parent);
        return s;
    }
    default:
        return 0;
    }
}

QTCOMMERCIALCHART_END_NAMESPACE
