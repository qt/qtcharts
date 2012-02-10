#include <limits.h>
#include <QVector>
#include <QDebug>
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartModel::BarChartModel(QObject *parent) :
    QObject(parent)
    ,mRunningId(1)
{
}

BarChartModel::~BarChartModel()
{
//    qDebug() << "BarChartModel::~BarChartModel";
    foreach (DataContainer* c, mDataModel) {
        delete c;
    }
}

int BarChartModel::addData(QList<qreal> data)
{
//    qDebug() << "BarChartModel::addData" << data.count();
    DataContainer* c = new DataContainer(data,mRunningId);
    mDataModel.append(c);
    mRunningId++;
    emit modelUpdated();
    return mRunningId-1;
}

void BarChartModel::removeData(int id)
{
//    qDebug() << "BarChartModel::removeData";
    foreach(DataContainer* c, mDataModel) {
        if (c->mId == id) {
            mDataModel.removeOne(c);
            delete c;
        }
    }
    emit modelUpdated();
}

int BarChartModel::countRows()
{
//    qDebug() << "BarChartModel::countRows";
    return mDataModel.count();
}

int BarChartModel::countColumns()
{
//    qDebug() << "BarChartModel::countColumns";
    int count(0);
    for (int i=0; i<mDataModel.count(); i++){
        // TODO: can we assume that all series have same number of values? If not. then which values are empty?
        int temp = mDataModel.at(i)->countColumns();
        if (temp > count) {
            count = temp;
        }
    }
    return count;
}

int BarChartModel::countTotalItems()
{
//    qDebug() << "BarChartModel::countTotalItems";
    int total = mDataModel.count() * countColumns();
    return total;
}

qreal BarChartModel::min()
{
 //   qDebug() << "BarChartModel::min";
    Q_ASSERT(mDataModel.count() > 0);
    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    qreal min = INT_MAX;

    for (int i=0; i <mDataModel.count(); i++) {
        int itemCount = mDataModel.at(i)->countColumns();
        for (int j=0; j<itemCount; j++) {
            qreal temp = mDataModel.at(i)->valueAt(j);
            if (temp < min) {
                min = temp;
            }
        }
    }
    return min;
}

qreal BarChartModel::max()
{
//    qDebug() << "BarChartModel::max";
    Q_ASSERT(mDataModel.count() > 0);

    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    qreal max = INT_MIN;

    for (int i=0; i <mDataModel.count(); i++) {
        int itemCount = mDataModel.at(i)->countColumns();
        for (int j=0; j<itemCount; j++) {
            qreal temp = mDataModel.at(i)->valueAt(j);
            if (temp > max) {
                max = temp;
            }
        }
    }

    return max;
}

qreal BarChartModel::valueAt(int series, int item)
{
//    qDebug() << "BarChartModel::valueAt" << series << item;
    if ((series < 0) || (series >= mDataModel.count())) {
        // No series, no value.
        return 0;
    } else if ((item < 0) || (item >= mDataModel.at(series)->countColumns())) {
        // No item, no value.
        return 0;
    }

//    qDebug() << "ValueAt" << series << item << "=" << mDataModel.at(series)->valueAt(item);
    return mDataModel.at(series)->valueAt(item);
}

qreal BarChartModel::columnSum(int column)
{
//    qDebug() << "BarChartModel::columnSum";
    int sum(0);
    int count = mDataModel.count(); // Count rows

    for (int row = 0; row < count; row++) {
        if (column < mDataModel.at(row)->countColumns()) {
            sum += mDataModel.at(row)->valueAt(column);
        }
    }
    return sum;
}

qreal BarChartModel::maxColumnSum()
{
//    qDebug() << "BarChartModel::maxColumnSum";
    int max = INT_MIN;
    int count = countColumns();

    for (int col=0; col<count; col++) {
        int sum = columnSum(col);
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

#include "moc_barchartmodel_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
