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
    QModelIndex modelIndex = mModel->index(0,0);
    int min = mModel->data(modelIndex).toInt();

    for (int i=0; i <mModel->rowCount(); i++) {
        for(int j=0; j<mModel->columnCount(); j++) {
            modelIndex = mModel->index(i,j);
            int temp = mModel->data(modelIndex).toInt();
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
    QModelIndex modelIndex = mModel->index(0,0);
    int max = mModel->data(modelIndex).toInt();

    for (int i=0; i <mModel->rowCount(); i++) {
        for(int j=0; j<mModel->columnCount(); j++) {
            modelIndex = mModel->index(i,j);
            int temp = mModel->data(modelIndex).toInt();
            if (temp > max) {
                max = temp;
            }
        }
    }
    return max;
}


int BarChartSeries::countSeries()
{
    return mModel->rowCount();
}

int BarChartSeries::countItemsInSeries()
{
    return mModel->columnCount();
}

int BarChartSeries::countTotalItems()
{
    return mModel->rowCount() * mModel->columnCount();
}

int BarChartSeries::valueAt(int series, int item)
{
    QModelIndex index = mModel->index(series,item);
    return mModel->data(index).toInt();
}

/*
void BarChartSeries::chartSizeChanged(QRectF rect)
{
    qDebug() << "barchart size changed:" << rect;
//    mBarGroup->resize(rect.toRect().width(), rect.toRect().height());
}
*/
#include "moc_barchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
