#ifndef STACKEDBARSERIES_H
#define STACKEDBARSERIES_H

#include "qbarseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarCategory;

class QTCOMMERCIALCHART_EXPORT QStackedBarSeries : public QBarSeries
{
    Q_OBJECT
public:
    QStackedBarSeries(QBarCategory *category, QObject* parent=0);

    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeStackedBar; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARSERIES_H
