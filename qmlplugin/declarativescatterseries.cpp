#include "declarativescatterseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qscatterseries.h"
#include <cmath>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeScatterSeries::DeclarativeScatterSeries(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_chart(0),
    m_series(0)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    connect(this, SIGNAL(parentChanged()),
            this, SLOT(setParentForSeries()));
}

void DeclarativeScatterSeries::setParentForSeries()
{
    if (!m_series)
        initSeries();
}

void DeclarativeScatterSeries::initSeries()
{
    Q_ASSERT(!m_series);
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

    if (declarativeChart) {
        QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        qDebug() << "creating scatter series for chart: " << chart;
        Q_ASSERT(chart);

        m_series = new QScatterSeries();
        Q_ASSERT(m_series);
        for (int i(0); i < m_data.count(); i++) {
            ScatterElement *element = m_data.at(i);
            *m_series << QPointF(element->x(), element->y());
        }
        chart->addSeries(m_series);
    }
}

QDeclarativeListProperty<ScatterElement> DeclarativeScatterSeries::data()
{
    return QDeclarativeListProperty<ScatterElement>(this, 0,
                                                    &DeclarativeScatterSeries::appendData);
}

void DeclarativeScatterSeries::appendData(QDeclarativeListProperty<ScatterElement> *list,
                                          ScatterElement *element)
{
    DeclarativeScatterSeries *series = qobject_cast<DeclarativeScatterSeries *>(list->object);
    qDebug() << "appendData: " << series;
    qDebug() << "appendData: " << element;
    qDebug() << "appendData: " << element->x();
    qDebug() << "appendData: " << element->y();
    qDebug() << "appendData: " << series->m_series;
    if (series) {
        series->m_data.append(element);
        if (series->m_series)
            series->m_series->addData(QPointF(element->x(), element->y()));
    }
}

#include "moc_declarativescatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
