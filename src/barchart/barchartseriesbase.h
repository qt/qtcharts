#ifndef BARCHARTSERIESBASE_H
#define BARCHARTSERIESBASE_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"
#include "qchartglobal.h"

class BarGroupBase;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeriesBase : public QChartSeries
{
    Q_OBJECT
protected:
    BarChartSeriesBase(QObject* parent=0);

public:
    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeInvalid; }

    // TODO: Better data model?
    virtual bool setData(QAbstractItemModel* model);

    // Methods to find out minimum and maximum values of data
    int min();
    int max();
    int maxColumnSum();     // returns maximum sum of items in all columns.

    int countRows();
    int countColumns();     // Count items in one series.
    int countTotalItems();
    int valueAt(int row, int column);

    int columnSum(int column);

public Q_SLOTS:

private:

    QAbstractItemModel* mModel;
    BarGroupBase* mBarGroup;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIESBASE_H
