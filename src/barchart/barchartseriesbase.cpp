#include <limits.h>
#include <QDebug>
#include "barchartseriesbase.h"
#include "bargroup.h"
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartSeriesBase::BarChartSeriesBase(QObject *parent)
    : QChartSeries(parent)
    ,mModel(*(new BarChartModel(this))) // TODO: is this ok?
{
    qDebug() << "BarChartSeriesBase::BarChartSeriesBase";
}
/*
bool BarChartSeriesBase::setModel(QAbstractItemModel* model)
{
    mModel = model;
    return true;
}
*/
/*
bool BarChartSeriesBase::setData(QList<qreal>& data)
{
    mData = &data;
    return true;
}
*/
/*
int BarChartSeriesBase::min()
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

int BarChartSeriesBase::max()
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

int BarChartSeriesBase::maxColumnSum()
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

int BarChartSeriesBase::countRows()
{
    return mModel->rowCount();
}

int BarChartSeriesBase::countColumns()
{
    return mModel->columnCount();
}

int BarChartSeriesBase::countTotalItems()
{
    return mModel->rowCount() * mModel->columnCount();
}

int BarChartSeriesBase::valueAt(int row, int column)
{
    QModelIndex index = mModel->index(row,column);
    return mModel->data(index).toInt();
}

int BarChartSeriesBase::columnSum(int column)
{
    int sum(0);
    int count = mModel->rowCount();

    for (int row = 0; row < count; row++) {
        sum += mModel->data(mModel->index(row,column)).toInt();
    }
    return sum;
}
*/

int BarChartSeriesBase::addData(QList<qreal> data)
{
    qDebug() << "BarChartSeriesBase::addData";
    return mModel.addData(data);
}

void BarChartSeriesBase::removeData(int id)
{
    mModel.removeData(id);
}

qreal BarChartSeriesBase::min()
{
    return mModel.min();
    /* Delegated to model
    int count = mData->count();
    int min = INT_MAX;

    for (int i=0; i<count; i++) {
        if (mData->at(i) < min) {
            min = mData->at(i);
        }
    }
    return min;
    */
}

qreal BarChartSeriesBase::max()
{
    return mModel.max();
    /* Delegated to model
    int count = mData->count();
    int max = INT_MIN;

    for (int i=0; i<count; i++) {
        if (mData->at(i) > max) {
            max = mData->at(i);
        }
    }
    return max;
    */
}

int BarChartSeriesBase::countColumns()
{
    return mModel.countColumns();
//    return mData->count();
}

qreal BarChartSeriesBase::valueAt(int series, int item)
{
    return mModel.valueAt(series,item);
//    return mData->at(item);
}

qreal BarChartSeriesBase::maxColumnSum()
{
    qDebug() << "BarChartSeriesBase::maxColumnSum" << mModel.maxColumnSum();
    return mModel.maxColumnSum();
}

BarChartModel& BarChartSeriesBase::model()
{
    return mModel;
}

#include "moc_barchartseriesbase.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
