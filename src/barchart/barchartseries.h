#ifndef BARCHARTSERIES_H
#define BARCHARTSERIES_H

#include <QList>
#include "qchartseries.h"
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeries : public QChartSeries
{

public:
    BarChartSeries(QList<int> data, QObject* parent=0);

    // from QChartSeries
    static QChartSeries* create(QObject* parent = 0 );
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeBar; }

    // Methods to find out minimum and maximum values of data
    int min();
    int max();
    int count();
    int valueAt(int i);

private:

    QList<int> mData;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
