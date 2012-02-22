#include <limits.h>
#include <QDebug>
#include "qstackedbarchartseries.h"
#include "qbarcategory.h"
#include "qbarset.h"
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QStackedBarChartSeries::QStackedBarChartSeries(QBarCategory *category, QObject *parent)
    : QChartSeries(parent)
    ,mModel(new BarChartModel(category, this))
{
}

void QStackedBarChartSeries::addBarSet(QBarSet *set)
{
    connect(this,SIGNAL(floatingValuesEnabled(bool)),set,SLOT(enableFloatingValues(bool)));
    connect(this,SIGNAL(hoverNamesEnabled(bool)),set,SLOT(enableHoverNames(bool)));
    mModel->addBarSet(set);
}

void QStackedBarChartSeries::removeBarSet(QBarSet *set)
{
    disconnect(set,SLOT(enableFloatingValues(bool)));
    disconnect(set,SLOT(enableHoverNames(bool)));
    mModel->removeBarSet(set);
}

int QStackedBarChartSeries::countSets()
{
    return mModel->countSets();
}

QBarSet* QStackedBarChartSeries::nextSet(bool getFirst)
{
    return mModel->nextSet(getFirst);
}

QList<QString> QStackedBarChartSeries::legend()
{
    return mModel->legend();
}

int QStackedBarChartSeries::countCategories()
{
    return mModel->countCategories();
}

qreal QStackedBarChartSeries::min()
{
    return mModel->min();
}

qreal QStackedBarChartSeries::max()
{
    return mModel->max();
}

qreal QStackedBarChartSeries::valueAt(int set, int category)
{
    return mModel->valueAt(set,category);
}

qreal QStackedBarChartSeries::maxCategorySum()
{
    return mModel->maxCategorySum();
}

BarChartModel& QStackedBarChartSeries::model()
{
    return *mModel;
}


#include "moc_qstackedbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

