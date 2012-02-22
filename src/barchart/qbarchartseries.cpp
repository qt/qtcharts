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
//    connect(this,SIGNAL(floatingValuesEnabled(bool)),set,SLOT(enableFloatingValues(bool)));
//    connect(this,SIGNAL(hoverNamesEnabled(bool)),set,SLOT(enableHoverNames(bool)));
    mModel->addBarSet(set);
}

void QBarChartSeries::removeBarSet(QBarSet *set)
{
//    disconnect(set,SLOT(enableFloatingValues(bool)));
//    disconnect(set,SLOT(enableHoverNames(bool)));
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

QList<QString> QBarChartSeries::legend()
{
    return mModel->legend();
}

void QBarChartSeries::enableFloatingValues(bool enabled)
{
    emit floatingValuesEnabled(enabled);
}

void QBarChartSeries::enableHoverNames(bool enabled)
{
    emit hoverNamesEnabled(enabled);
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
