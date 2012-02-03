#include "percentbarchartseries.h"

#include <limits.h>
#include <QDebug>
#include "percentbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PercentBarChartSeries::PercentBarChartSeries(QObject *parent) :
    QChartSeries(parent)
{
}

bool PercentBarChartSeries::setData(QAbstractItemModel* model)
{
    mModel = model;
    return true;
}

int PercentBarChartSeries::min()
{
    Q_ASSERT(mModel->rowCount() > 0);
    Q_ASSERT(mModel->columnCount() > 0);

    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    int min = INT_MAX;

    for (int i=0; i <mModel->rowCount(); i++) {
        for(int j=0; j<mModel->columnCount(); j++) {
            int temp = mModel->data(mModel->index(i,j)).toInt();
            if (temp < min) {
                min = temp;
            }
        }
    }
    return min;
}

int PercentBarChartSeries::max()
{
    Q_ASSERT(mModel->rowCount() > 0);
    Q_ASSERT(mModel->columnCount() > 0);

    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    int max = INT_MIN;

    for (int i=0; i <mModel->rowCount(); i++) {
        for(int j=0; j<mModel->columnCount(); j++) {
            int temp = mModel->data(mModel->index(i,j)).toInt();
            if (temp > max) {
                max = temp;
            }
        }
    }
    return max;
}

int PercentBarChartSeries::maxColumnSum()
{
    Q_ASSERT(mModel->rowCount() > 0);
    Q_ASSERT(mModel->columnCount() > 0);

    int max = INT_MIN;

    for (int col=0; col <mModel->columnCount(); col++) {
        int sum = columnSum(col);
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

int PercentBarChartSeries::countRows()
{
    return mModel->rowCount();
}

int PercentBarChartSeries::countColumns()
{
    return mModel->columnCount();
}

int PercentBarChartSeries::countTotalItems()
{
    return mModel->rowCount() * mModel->columnCount();
}

int PercentBarChartSeries::valueAt(int row, int column)
{
    QModelIndex index = mModel->index(row,column);
    return mModel->data(index).toInt();
}

int PercentBarChartSeries::columnSum(int column)
{
    int sum(0);
    int count = mModel->rowCount();

    for (int row = 0; row < count; row++) {
        sum += mModel->data(mModel->index(row,column)).toInt();
    }
    return sum;
}

#include "moc_percentbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

