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

QBarSet* QBarChartSeries::setAt(int index)
{
    return mModel->setAt(index);
}

QList<QString> QBarChartSeries::legend()
{
    return mModel->legend();
}

QString QBarChartSeries::label(int category)
{
    return mModel->label(category);
}

void QBarChartSeries::enableFloatingValues(bool enabled)
{
    if (enabled) {
        for (int i=0; i<mModel->countSets(); i++) {
            QBarSet *set = mModel->setAt(i);
            connect(set,SIGNAL(clicked()),set,SIGNAL(toggleFloatingValues()));
        }
    } else {
        for (int i=0; i<mModel->countSets(); i++) {
            QBarSet *set = mModel->setAt(i);
            disconnect(set,SIGNAL(clicked()),set,SIGNAL(toggleFloatingValues()));
        }
    }
}

void QBarChartSeries::enableToolTip(bool enabled)
{
    if (enabled) {
        for (int i=0; i<mModel->countSets(); i++) {
            QBarSet *set = mModel->setAt(i);
            connect(set,SIGNAL(showToolTip(QPoint,QString)),this,SIGNAL(showToolTip(QPoint,QString)));
        }
    } else {
        for (int i=0; i<mModel->countSets(); i++) {
            QBarSet *set = mModel->setAt(i);
            disconnect(set,SIGNAL(showToolTip(QPoint,QString)),this,SIGNAL(showToolTip(QPoint,QString)));
        }
    }
}

void QBarChartSeries::enableSeparators(bool enabled)
{
    emit separatorsEnabled(enabled);
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

qreal QBarChartSeries::percentageAt(int set, int category)
{
    return mModel->percentageAt(set,category);
}

qreal QBarChartSeries::categorySum(int category)
{
    return mModel->categorySum(category);
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
