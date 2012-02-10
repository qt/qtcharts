#include <limits.h>
#include <QDebug>
#include "barchartseriesbase.h"
#include "bargroup.h"
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartSeriesBase::BarChartSeriesBase(QObject *parent)
    : QChartSeries(parent)
    ,mModel(new BarChartModel(this))
{
}

int BarChartSeriesBase::addData(QList<qreal> data)
{
    return mModel->addData(data);
}

void BarChartSeriesBase::removeData(int id)
{
    mModel->removeData(id);
}

void BarChartSeriesBase::setLabels(QList<QString> labels)
{
    mLabels = labels;
}

qreal BarChartSeriesBase::min()
{
    return mModel->min();
}

qreal BarChartSeriesBase::max()
{
    return mModel->max();
}

int BarChartSeriesBase::countColumns()
{
    return mModel->countColumns();
}

qreal BarChartSeriesBase::valueAt(int series, int item)
{
//    qDebug() << "BarChartSeriesBase::valueAt" << series << item;
    return mModel->valueAt(series,item);
}

qreal BarChartSeriesBase::maxColumnSum()
{
//    qDebug() << "BarChartSeriesBase::maxColumnSum" << mModel->maxColumnSum();
    return mModel->maxColumnSum();
}

BarChartModel& BarChartSeriesBase::model()
{
    return *mModel;
}

QString BarChartSeriesBase::label(int item)
{
    if ((item>=0) && (item < mLabels.count()))  {
        return mLabels.at(item);
    }

    return QString("");
}

#include "moc_barchartseriesbase.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
