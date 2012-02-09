#ifndef PERCENTBARCHARTSERIES_H
#define PERCENTBARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "barchartseriesbase.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PercentBarGroup;

class QTCOMMERCIALCHART_EXPORT PercentBarChartSeries : public BarChartSeriesBase
{
    Q_OBJECT
public:
    PercentBarChartSeries(QObject* parent=0);

    // from BarChartSeriesBase
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypePercentBar; }

public Q_SLOTS:

private:

    PercentBarGroup* mPercentBarGroup;
};

QTCOMMERCIALCHART_END_NAMESPACE


#endif // PERCENTBARCHARTSERIES_H
