#include "qchartglobal.h"
#include "qchartseries.h"

#include "barchartseries.h"
#include "qlinechartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartSeries* QChartSeries::create(QChartSeriesType type, QObject* parent)
{
    qDebug() << "QChartSeries::create";
    // TODO: Other types
    switch (type) {
    case QChartSeries::SeriesTypeLine: {
        QLineChartSeries* s = QLineChartSeries::create(parent); // TODO: do we need create method for derived implementations?
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

#include "moc_qchartseries.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
