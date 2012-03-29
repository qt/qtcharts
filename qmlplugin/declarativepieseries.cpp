#include "declarativepieseries.h"
#include "declarativechart.h"
#include "qchart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativePieSeries::DeclarativePieSeries(QObject *parent) :
    QPieSeries(parent),
    m_chart(0)
{
}

void DeclarativePieSeries::classBegin()
{
}

void DeclarativePieSeries::componentComplete()
{
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());
    if (declarativeChart) {
        QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        Q_ASSERT(chart);
        qDebug() << "parent for pie:" << chart;
        chart->addSeries(this);
    }
}

QDeclarativeListProperty<QPieSlice> DeclarativePieSeries::slices()
{
    return QDeclarativeListProperty<QPieSlice>(this, 0, &DeclarativePieSeries::appendSlice);
}

void DeclarativePieSeries::appendSlice(QDeclarativeListProperty<QPieSlice> *list,
                                      QPieSlice *slice)
{
    DeclarativePieSeries *series = qobject_cast<DeclarativePieSeries *>(list->object);
    if (series)
        series->append(slice->value(), slice->label());
}

#include "moc_declarativepieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
