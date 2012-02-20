#include "declarativepieseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qpieseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativePieSeries::DeclarativePieSeries(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_chart(0),
    m_series(0)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    connect(this, SIGNAL(parentChanged()),
            this, SLOT(setParentForSeries()));
}

void DeclarativePieSeries::setParentForSeries()
{
    if (!m_series) {
        DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());
        if (declarativeChart) {
            QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
            qDebug() << "creating pie series for chart: " << chart;
            Q_ASSERT(chart);

            m_series = new QPieSeries();
            Q_ASSERT(m_series);
            foreach (QPieSlice* slice, m_data) {
                // Have to duplicate the data
                m_series->add(slice->value(), slice->label());
            }
            chart->addSeries(m_series);
            //chart->axisY();
        }
    }
}

QDeclarativeListProperty<QPieSlice> DeclarativePieSeries::data()
{
    return QDeclarativeListProperty<QPieSlice>(this, 0, &DeclarativePieSeries::appendData);
}

void DeclarativePieSeries::appendData(QDeclarativeListProperty<QPieSlice> *list,
                                      QPieSlice *slice)
{
    DeclarativePieSeries *series = qobject_cast<DeclarativePieSeries *>(list->object);
    if (series) {
        series->m_data.append(slice);
        // Have to duplicate the data
        if (series->m_series)
            series->m_series->add(slice->value(), slice->label());
    }
}

#include "moc_declarativepieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
