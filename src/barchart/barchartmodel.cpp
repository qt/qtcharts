#include <limits.h>
#include <QVector>
#include <QDebug>
#include "barchartmodel_p.h"
#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartModel::BarChartModel(QStringList categories, QObject *parent) :
    QObject(parent)
    ,mCategory(categories)
{
}

QStringList BarChartModel::category()
{
    return mCategory;
}

void BarChartModel::addBarSet(QBarSet *set)
{
    mDataModel.append(set);
}

void BarChartModel::removeBarSet(QBarSet *set)
{
    if (mDataModel.contains(set)) {
        mDataModel.removeOne(set);
    }
}

QBarSet* BarChartModel::setAt(int index)
{
    return mDataModel.at(index);
}

QList<QBarSet*> BarChartModel::barSets()
{
    return mDataModel;
}

QList<QSeries::Legend> BarChartModel::legend()
{
    QList<QSeries::Legend> legend;

    for (int i=0; i<mDataModel.count(); i++) {
        QSeries::Legend l;
        l.mName = mDataModel.at(i)->name();
        l.mPen = mDataModel.at(i)->pen();
        legend.append(l);
    }
    return legend;
}

int BarChartModel::barsetCount()
{
    return mDataModel.count();
}

int BarChartModel::categoryCount()
{
    return mCategory.count();
}

qreal BarChartModel::min()
{
    Q_ASSERT(mDataModel.count() > 0);
    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    qreal min = INT_MAX;

    for (int i=0; i <mDataModel.count(); i++) {
        int itemCount = mDataModel.at(i)->count();
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
    Q_ASSERT(mDataModel.count() > 0);

    // TODO: make min and max members and update them when data changes.
    // This is slower since they are checked every time, even if data is same since previous call.
    qreal max = INT_MIN;

    for (int i=0; i <mDataModel.count(); i++) {
        int itemCount = mDataModel.at(i)->count();
        for (int j=0; j<itemCount; j++) {
            qreal temp = mDataModel.at(i)->valueAt(j);
            if (temp > max) {
                max = temp;
            }
        }
    }

    return max;
}

qreal BarChartModel::valueAt(int set, int category)
{
    if ((set < 0) || (set >= mDataModel.count())) {
        // No set, no value.
        return 0;
    } else if ((category < 0) || (category >= mDataModel.at(set)->count())) {
        // No category, no value.
        return 0;
    }

    return mDataModel.at(set)->valueAt(category);
}

qreal BarChartModel::percentageAt(int set, int category)
{
    if ((set < 0) || (set >= mDataModel.count())) {
        // No set, no value.
        return 0;
    } else if ((category < 0) || (category >= mDataModel.at(set)->count())) {
        // No category, no value.
        return 0;
    }

    qreal value = mDataModel.at(set)->valueAt(category);
    qreal total = categorySum(category);
    if (0 == total) {
        return 100.0;
    }

    return value / total;
}


qreal BarChartModel::categorySum(int category)
{
    qreal sum(0);
    int count = mDataModel.count(); // Count sets

    for (int set = 0; set < count; set++) {
        if (category < mDataModel.at(set)->count()) {
            sum += mDataModel.at(set)->valueAt(category);
        }
    }
    return sum;
}

qreal BarChartModel::maxCategorySum()
{
    qreal max = INT_MIN;
    int count = categoryCount();

    for (int col=0; col<count; col++) {
        qreal sum = categorySum(col);
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

QString BarChartModel::label(int category)
{
    return mCategory.at(category);
}

#include "moc_barchartmodel_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
