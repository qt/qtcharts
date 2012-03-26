#include "declarativescatterseries.h"
#include "declarativechart.h"
#include "declarativetablemodel.h"
#include "qchart.h"
#include "qscatterseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeScatterSeries::DeclarativeScatterSeries(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_chart(0),
    m_series(0),
    m_model(0),
    m_xColumn(0),
    m_yColumn(1)
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
//        if (!m_model)
//            m_model = new DeclarativeTableModel();
        if (m_model) {
            m_series->setModel(m_model);
            m_series->setModelMapping(m_xColumn, m_yColumn);
        }
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

DeclarativeTableModel *DeclarativeScatterSeries::model()
{
    if (m_series)
        return (DeclarativeTableModel *) m_series->model();
    else
        return m_model;
}

void DeclarativeScatterSeries::setModel(DeclarativeTableModel *model)
{
    m_model = model;
    if (m_chart && m_series) {
        // Hack: remove and add the series to force an update for the chart range
        m_chart->removeSeries(m_series);
        m_series = new QScatterSeries();
        m_series->setModel(m_model);
        m_series->setModelMapping(m_xColumn, m_yColumn);
        m_chart->addSeries(m_series);
    }
}

void DeclarativeScatterSeries::setXColumn(int xColumn)
{
    m_xColumn = xColumn;
    if (m_series && m_series->model())
        m_series->setModelMapping(m_xColumn, m_yColumn);
}

void DeclarativeScatterSeries::setYColumn(int yColumn)
{
    m_yColumn = yColumn;
    if (m_series && m_series->model())
        m_series->setModelMapping(m_xColumn, m_yColumn);
}

#include "moc_declarativescatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
