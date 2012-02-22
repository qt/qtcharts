#ifndef PERCENTBARCHARTSERIES_H
#define PERCENTBARCHARTSERIES_H

#include "qbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QPercentBarChartSeries : public QBarChartSeries
{
    Q_OBJECT
public:
    QPercentBarChartSeries(QBarCategory *category, QObject* parent=0);

    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypePercentBar; }
};

QTCOMMERCIALCHART_END_NAMESPACE


#endif // PERCENTBARCHARTSERIES_H
