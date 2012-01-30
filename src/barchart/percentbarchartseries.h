#ifndef PERCENTBARCHARTSERIES_H
#define PERCENTBARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PercentBarGroup;

class QTCOMMERCIALCHART_EXPORT PercentBarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    PercentBarChartSeries(QObject* parent=0);

    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypePercentBar; }

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

    int columnSum(int column);

public Q_SLOTS:

private:

    QAbstractItemModel* mModel;
    PercentBarGroup* mPercentBarGroup;
};

QTCOMMERCIALCHART_END_NAMESPACE


#endif // PERCENTBARCHARTSERIES_H
