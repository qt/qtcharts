#include <QDebug>
#include "barchartseries.h"
#include "bargroup.h"
QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartSeries::BarChartSeries(QObject *parent)
    : QChartSeries(parent)
{
}

bool BarChartSeries::setData(QAbstractItemModel* model)
{
    mModel = model;
}

int BarChartSeries::min()
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

int BarChartSeries::max()
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


int BarChartSeries::countRows()
{
    return mModel->rowCount();
}

int BarChartSeries::countColumns()
{
    return mModel->columnCount();
}

int BarChartSeries::countTotalItems()
{
    return mModel->rowCount() * mModel->columnCount();
}

int BarChartSeries::valueAt(int row, int column)
{
    return mModel->data(mModel->index(row,column)).toInt();
}

#include "moc_barchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
