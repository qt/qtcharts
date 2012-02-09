#ifndef BARCHARTSERIES_H
#define BARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "barchartseriesbase.h"

class BarGroup;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeries : public BarChartSeriesBase
{
    Q_OBJECT
public:
    BarChartSeries(QObject* parent=0);

    // from BarChartSeriesBase
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeBar; }

private:

    BarGroup* mBarGroup;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
