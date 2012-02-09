#include <limits.h>
#include <QDebug>
#include "barchartseriesbase.h"
#include "bargroup.h"
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartSeriesBase::BarChartSeriesBase(QObject *parent)
    : QChartSeries(parent)
    ,mModel(*(new BarChartModel(this))) // TODO: is this ok?
{
}

int BarChartSeriesBase::addData(QList<qreal> data)
{
    return mModel.addData(data);
}

void BarChartSeriesBase::removeData(int id)
{
    mModel.removeData(id);
}

qreal BarChartSeriesBase::min()
{
    return mModel.min();
}

qreal BarChartSeriesBase::max()
{
    return mModel.max();
}

int BarChartSeriesBase::countColumns()
{
    return mModel.countColumns();
}

qreal BarChartSeriesBase::valueAt(int series, int item)
{
    return mModel.valueAt(series,item);
}

qreal BarChartSeriesBase::maxColumnSum()
{
    qDebug() << "BarChartSeriesBase::maxColumnSum" << mModel.maxColumnSum();
    return mModel.maxColumnSum();
}

BarChartModel& BarChartSeriesBase::model()
{
    return mModel;
}

#include "moc_barchartseriesbase.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
