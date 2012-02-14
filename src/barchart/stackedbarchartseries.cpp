#include <limits.h>
#include <QDebug>
#include "stackedbarchartseries.h"
#include "qbarcategory.h"
#include "qbarset.h"
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

StackedBarChartSeries::StackedBarChartSeries(QBarCategory &category, QObject *parent)
    : QChartSeries(parent)
    ,mModel(new BarChartModel(category, this))
{
}

void StackedBarChartSeries::addBarSet(QBarSet &set)
{
    mModel->addBarSet(set);
}

void StackedBarChartSeries::removeBarSet(QBarSet &set)
{
    mModel->removeBarSet(set);
}

int StackedBarChartSeries::countCategories()
{
    return mModel->countCategories();
}

qreal StackedBarChartSeries::min()
{
    return mModel->min();
}

qreal StackedBarChartSeries::max()
{
    return mModel->max();
}

qreal StackedBarChartSeries::valueAt(int set, int category)
{
    return mModel->valueAt(set,category);
}

qreal StackedBarChartSeries::maxCategorySum()
{
    return mModel->maxCategorySum();
}

BarChartModel& StackedBarChartSeries::model()
{
    return *mModel;
}


#include "moc_stackedbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

