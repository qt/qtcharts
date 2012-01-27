#ifndef STACKEDBARCHARTSERIES_H
#define STACKEDBARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class StackedBarGroup;

class QTCOMMERCIALCHART_EXPORT StackedBarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    StackedBarChartSeries(QObject* parent=0);

    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeStackedBar; }

    // TODO: Better data model?
    virtual bool setData(QAbstractItemModel* model);

    // Methods to find out minimum and maximum values of data
    int min();
    int max();
    int maxColumnSum();     // returns maximum sum of items in all columns.

    int countRows();
    int countColumns();
    int countTotalItems();
    int valueAt(int row, int column);

private:
    int columnSum(int column);

public Q_SLOTS:

private:

    QAbstractItemModel* mModel;
    StackedBarGroup* mStackedBarGroup;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARCHARTSERIES_H
