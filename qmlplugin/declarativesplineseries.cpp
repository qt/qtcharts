#include "declarativesplineseries.h"
#include "declarativechart.h"
#include "qchart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeSplineSeries::DeclarativeSplineSeries(QObject *parent) :
    QSplineSeries(parent)
{
}

void DeclarativeSplineSeries::seriesComplete()
{
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

    if (declarativeChart) {
        QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        Q_ASSERT(chart);
        chart->addSeries(this);
    }
}

QObject *DeclarativeSplineSeries::seriesObject()
{
    return this;
}

QDeclarativeListProperty<DeclarativeXyPoint> DeclarativeSplineSeries::points()
{
    return DeclarativeXySeries::points();
}

void DeclarativeSplineSeries::appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                       DeclarativeXyPoint *element)
{
    DeclarativeXySeries::appendPoints(list, element);
}

#include "moc_declarativesplineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
