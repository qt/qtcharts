#include "declarativelineseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qlineseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeLineSeries::DeclarativeLineSeries(QObject *parent) :
    QLineSeries(parent)
{
}

void DeclarativeLineSeries::componentComplete()
{
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

    if (declarativeChart) {
        QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        Q_ASSERT(chart);
        chart->addSeries(this);
    }
}

QDeclarativeListProperty<DeclarativeXyPoint> DeclarativeLineSeries::points()
{
    return QDeclarativeListProperty<DeclarativeXyPoint>(this, 0, &DeclarativeXySeries::appendPoints);
}

void DeclarativeLineSeries::appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                       DeclarativeXyPoint *element)
{
    DeclarativeXySeries::appendPoints(list, element);
}

#include "moc_declarativelineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
