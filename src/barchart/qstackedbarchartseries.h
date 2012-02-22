#ifndef STACKEDBARCHARTSERIES_H
#define STACKEDBARCHARTSERIES_H

#include "qbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarCategory;

class QTCOMMERCIALCHART_EXPORT QStackedBarChartSeries : public QBarChartSeries
{
    Q_OBJECT
public:
    QStackedBarChartSeries(QBarCategory *category, QObject* parent=0);

    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeStackedBar; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARCHARTSERIES_H
