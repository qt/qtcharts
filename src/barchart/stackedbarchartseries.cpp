#include <limits.h>
#include "stackedbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarChartSeries::StackedBarChartSeries(QObject *parent) :
    QChartSeries(parent)
{
}

bool StackedBarChartSeries::setData(QAbstractItemModel* model)
{
    mModel = model;
}

int StackedBarChartSeries::min()
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

int StackedBarChartSeries::max()
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

int StackedBarChartSeries::maxColumnSum()
{
    Q_ASSERT(mModel->rowCount() > 0);
    Q_ASSERT(mModel->columnCount() > 0);

    int max = INT_MIN;

    for (int col=0; col <mModel->rowCount(); col++) {
        int sum = columnSum(col);
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

int StackedBarChartSeries::countRows()
{
    return mModel->rowCount();
}

int StackedBarChartSeries::countColumns()
{
    return mModel->columnCount();
}

int StackedBarChartSeries::countTotalItems()
{
    return mModel->rowCount() * mModel->columnCount();
}

int StackedBarChartSeries::valueAt(int row, int column)
{
    QModelIndex index = mModel->index(row,column);
    return mModel->data(index).toInt();
}

int StackedBarChartSeries::columnSum(int column)
{
    int sum(0);
    int count = mModel->rowCount();

    for (int row = 0; row < count; row++) {
        sum += mModel->data(mModel->index(row,column)).toInt();
    }
    return sum;
}

#include "moc_stackedbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

