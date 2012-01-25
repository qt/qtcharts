#ifndef BARCHARTSERIES_H
#define BARCHARTSERIES_H

#include <QList>
#include <QRectF>
#include <QAbstractItemModel>
#include "qchartseries.h"
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Container for series
class QTCOMMERCIALCHART_EXPORT BarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    BarChartSeries(QObject* parent=0);

    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeBar; }

    // TODO: This as dataModel instead of n different setters. (data model itself can accept lists and whatnot)
    virtual bool setData(QAbstractItemModel* model);

    // Methods to find out minimum and maximum values of data
    int min();
    int max();
    int countSeries();
    int countItemsInSeries();     // Count items in one series.
    int countTotalItems();
    int valueAt(int series, int item);

public Q_SLOTS:

    void chartSizeChanged(QRectF rect);

private:

    //QList<int> mData;
    QAbstractItemModel* mModel;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARCHARTSERIES_H
