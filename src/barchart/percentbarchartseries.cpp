#include "percentbarchartseries.h"

#include <limits.h>
#include <QDebug>
#include "percentbarchartseries.h"
#include "qbarset.h"
#include "qbarcategory.h"
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PercentBarChartSeries::PercentBarChartSeries(QBarCategory &category, QObject *parent)
    : QChartSeries(parent)
    ,mModel(new BarChartModel(category, this))
{
}

void PercentBarChartSeries::addBarSet(QBarSet &set)
{
    mModel->addBarSet(set);
}

void PercentBarChartSeries::removeBarSet(QBarSet &set)
{
    mModel->removeBarSet(set);
}

int PercentBarChartSeries::countCategories()
{
    return mModel->countCategories();
}

qreal PercentBarChartSeries::min()
{
    return mModel->min();
}

qreal PercentBarChartSeries::max()
{
    return mModel->max();
}

qreal PercentBarChartSeries::valueAt(int set, int category)
{
    return mModel->valueAt(set,category);
}

qreal PercentBarChartSeries::maxCategorySum()
{
    return mModel->maxCategorySum();
}

BarChartModel& PercentBarChartSeries::model()
{
    return *mModel;
}


#include "moc_percentbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

