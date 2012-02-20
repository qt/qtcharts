#include <QDebug>
#include "qbarchartseries.h"
#include "qbarcategory.h"
#include "qbarset.h"
#include "barchartmodel_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

QBarChartSeries::QBarChartSeries(QBarCategory *category, QObject *parent)
    : QChartSeries(parent)
    ,mModel(new BarChartModel(category, this))
{
}

void QBarChartSeries::addBarSet(QBarSet *set)
{
    mModel->addBarSet(set);
}

void QBarChartSeries::removeBarSet(QBarSet *set)
{
    mModel->removeBarSet(set);
}

int QBarChartSeries::countSets()
{
    return mModel->countSets();
}

QBarSet* QBarChartSeries::nextSet(bool getFirst)
{
    return mModel->nextSet(getFirst);
}

int QBarChartSeries::countCategories()
{
    return mModel->countCategories();
}

qreal QBarChartSeries::min()
{
    return mModel->min();
}

qreal QBarChartSeries::max()
{
    return mModel->max();
}

qreal QBarChartSeries::valueAt(int set, int category)
{
    return mModel->valueAt(set,category);
}

qreal QBarChartSeries::maxCategorySum()
{
    return mModel->maxCategorySum();
}

BarChartModel& QBarChartSeries::model()
{
    return *mModel;
}


#include "moc_qbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
