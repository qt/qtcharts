#include "declarativescatterseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qscatterseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeScatterSeries::DeclarativeScatterSeries(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_chart(0),
    m_series(0)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

DeclarativeScatterSeries::~DeclarativeScatterSeries()
{
}

void DeclarativeScatterSeries::componentComplete()
{
    Q_ASSERT(!m_series);
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

    if (declarativeChart) {
        m_chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        qDebug() << "creating scatter series for chart: " << m_chart;
        Q_ASSERT(m_chart);

        m_series = new QScatterSeries();
        for (int i(0); i < m_data.count(); i++) {
            DeclarativeXyPoint *element = m_data.at(i);
            *m_series << QPointF(element->x(), element->y());
        }
        m_chart->addSeries(m_series);
    }
}

QDeclarativeListProperty<DeclarativeXyPoint> DeclarativeScatterSeries::data()
{
    return QDeclarativeListProperty<DeclarativeXyPoint>(this, 0,
                                                    &DeclarativeScatterSeries::appendData);
}

void DeclarativeScatterSeries::appendData(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                                          DeclarativeXyPoint *element)
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
            series->m_series->add(element->x(), element->y());
    }
}

#include "moc_declarativescatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
