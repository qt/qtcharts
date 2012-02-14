#include <QDebug>
#include "barchartseries.h"
#include "qbarcategory.h"
#include "qbarset.h"
#include "barchartmodel_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartSeries::BarChartSeries(QBarCategory &category, QObject *parent)
    : QChartSeries(parent)
    ,mModel(new BarChartModel(category, this))
{
}

void BarChartSeries::addBarSet(QBarSet &set)
{
    mModel->addBarSet(set);
}

void BarChartSeries::removeBarSet(QBarSet &set)
{
    mModel->removeBarSet(set);
}

int BarChartSeries::countCategories()
{
    return mModel->countCategories();
}

qreal BarChartSeries::min()
{
    return mModel->min();
}

qreal BarChartSeries::max()
{
    return mModel->max();
}

qreal BarChartSeries::valueAt(int set, int category)
{
    return mModel->valueAt(set,category);
}

qreal BarChartSeries::maxCategorySum()
{
    return mModel->maxCategorySum();
}

BarChartModel& BarChartSeries::model()
{
    return *mModel;
}


#include "moc_barchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
