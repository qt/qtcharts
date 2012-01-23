#include "barchartseries.h"
QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartSeries::BarChartSeries(QList<int> data, QObject *parent)
    : QChartSeries(parent)
    , mData(data)
{
}

int BarChartSeries::min()
{
    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    int min = mData.at(0);

    for (int i=0; i <mData.count(); i++) {
        if (mData.at(i) < min) {
            min = mData.at(i);
        }
    }
    return min;
}

int BarChartSeries::max()
{
    int max = mData.at(0);

    for (int i=0; i <mData.count(); i++) {
        if (mData.at(i) > max) {
            max = mData.at(i);
        }
    }
    return max;
}

int BarChartSeries::count()
{
    return mData.count();
}

int BarChartSeries::valueAt(int i)
{
    return mData.at(i);
}

QTCOMMERCIALCHART_END_NAMESPACE
