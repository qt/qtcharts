#ifndef PERCENTBARSERIES_H
#define PERCENTBARSERIES_H

#include "qbarseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QPercentBarSeries : public QBarSeries
{
    Q_OBJECT
public:
    QPercentBarSeries(QBarCategory *category, QObject* parent=0);

    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypePercentBar; }
};

QTCOMMERCIALCHART_END_NAMESPACE


#endif // PERCENTBARSERIES_H
