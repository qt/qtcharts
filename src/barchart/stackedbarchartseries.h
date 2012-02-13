#ifndef STACKEDBARCHARTSERIES_H
#define STACKEDBARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "barchartseriesbase.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class StackedBarGroup;

class QTCOMMERCIALCHART_EXPORT StackedBarChartSeries : public BarChartSeriesBase
{
    Q_OBJECT
public:
    StackedBarChartSeries(QBarCategory &category, QObject* parent=0);

    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeStackedBar; }

public Q_SLOTS:

private:

    StackedBarGroup* mStackedBarGroup;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARCHARTSERIES_H
