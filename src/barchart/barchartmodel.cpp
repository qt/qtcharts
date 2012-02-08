#include <limits.h>
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartModel::BarChartModel(QObject *parent) :
    QObject(parent)
{
}

void BarChartModel::addSeries(BarChartSeriesBase& series)
{
    mSeries.append(&series);
    emit modelUpdated();
}

void BarChartModel::removeSeries(BarChartSeriesBase& series)
{
    int i = mSeries.indexOf(&series);
    if (-1 == i) {
        return;
    }
    mSeries.removeAt(i);
    emit modelUpdated();
}

int BarChartModel::countSeries()
{
    return mSeries.count();
}

int BarChartModel::countItemsInSeries()
{
    int count(0);
    for (int i=0; i<mSeries.count(); i++){
        // TODO: can we assume that all series have same number of values? If not. then which values are empty?
        int temp = mSeries.at(i)->countValues();
        if (temp > count) {
            count = temp;
        }
    }
    return count;
}

int BarChartModel::countTotalItems()
{
    int total = mSeries.count() * countItemsInSeries();
    return total;
}

int BarChartModel::min()
{
    Q_ASSERT(mSeries.count() > 0);
    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    int min = INT_MAX;

    for (int i=0; i <mSeries.count(); i++) {
        int temp = mSeries.at(i)->min();
        if (temp < min) {
            min = temp;
        }
    }
    return min;
}

int BarChartModel::max()
{
    Q_ASSERT(mSeries.count() > 0);

    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    int max = INT_MIN;

    for (int i=0; i <mSeries.count(); i++) {
        int temp = mSeries.at(i)->min();
        if (temp > max) {
            max = temp;
        }
    }
    return max;
}

qreal BarChartModel::valueAt(int series, int item)
{
    if ((series < 0) || (series >= mSeries.count())) {
        // No series, no value.
        return 0;
    } else if ((item < 0) || (item >= mSeries.at(series)->countValues())) {
        // No item, no value.
        return 0;
    }

    return mSeries.at(series)->valueAt(item);
}

#include "moc_barchartmodel_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
