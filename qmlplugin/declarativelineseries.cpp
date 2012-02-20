#include "declarativelineseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qlinechartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeLineSeries::DeclarativeLineSeries(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    connect(this, SIGNAL(parentChanged()),
            this, SLOT(setParentForSeries()));
}

void DeclarativeLineSeries::setParentForSeries()
{
    if (!m_series) {
        DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

        if (declarativeChart) {
            QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
            qDebug() << "creating line series for chart: " << chart;
            Q_ASSERT(chart);

            m_series = new QLineChartSeries();
            Q_ASSERT(m_series);
            for (int i(0); i < m_data.count(); i++) {
                ScatterElement *element = m_data.at(i);
                m_series->add(element->x(), element->y());
            }
            chart->addSeries(m_series);
        }
    }
}

QDeclarativeListProperty<ScatterElement> DeclarativeLineSeries::data()
{
    return QDeclarativeListProperty<ScatterElement>(this, 0, &DeclarativeLineSeries::appendData);
}

void DeclarativeLineSeries::appendData(QDeclarativeListProperty<ScatterElement> *list,
                                       ScatterElement *element)
{
    DeclarativeLineSeries *series = qobject_cast<DeclarativeLineSeries *>(list->object);
    if (series) {
        series->m_data.append(element);
        if (series->m_series)
            series->m_series->add(element->x(), element->y());
    }
}

#include "moc_declarativelineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
