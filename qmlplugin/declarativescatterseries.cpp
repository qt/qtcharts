#include "declarativescatterseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qscatterseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeScatterSeries::DeclarativeScatterSeries(QObject *parent) :
    QScatterSeries(parent)
{
}

void DeclarativeScatterSeries::seriesComplete()
{
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

    if (declarativeChart) {
        QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        Q_ASSERT(chart);
        qDebug() << "chart:" << chart;
        chart->addSeries(this);
    }
}

QObject *DeclarativeScatterSeries::seriesObject()
{
    return this;
}

QDeclarativeListProperty<DeclarativeXyPoint> DeclarativeScatterSeries::points()
{
    return DeclarativeXySeries::points();
}

void DeclarativeScatterSeries::appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                                            DeclarativeXyPoint *element)
{
    DeclarativeXySeries::appendPoints(list, element);
}

#include "moc_declarativescatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
