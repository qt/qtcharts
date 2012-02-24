#include "declarativeseries.h"
#include "declarativechart.h"
#include <qscatterseries.h>
#include <qlinechartseries.h>
#include <qpieseries.h>
#include <cmath>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeSeries::DeclarativeSeries(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_seriesType(SeriesTypeInvalid), // TODO: default type?
    m_chart(0),
    m_series(0)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    connect(this, SIGNAL(parentChanged()),
            this, SLOT(setParentForSeries()));
}

void DeclarativeSeries::setSeriesType(SeriesType type)
{
    if (!m_series || type != m_seriesType) {
        m_seriesType = type;
        initSeries();
    } else {
        m_seriesType = type;
    }
}

void DeclarativeSeries::setParentForSeries()
{
    if (!m_series)
        initSeries();
    else if (m_series->type() != m_seriesType)
        initSeries();
}

void DeclarativeSeries::initSeries()
{
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

    if (declarativeChart && m_seriesType != SeriesTypeInvalid) {
        delete m_series;
        m_series = 0;

        QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        qDebug() << "creating series for chart: " << chart;
        Q_ASSERT(chart);

        switch (m_seriesType) {
        case SeriesTypePie: {
            QPieSeries *pieSeries = new QPieSeries();
            chart->addSeries(pieSeries);
            QList<qreal> data;
            data << 1.0;
            data << 12.0;
            data << 4.0;
            Q_ASSERT(pieSeries->setData(data));
            m_series = pieSeries;
            break;
        }
        default:
            Q_ASSERT(false);
            break;
        }
    }
}

#include "moc_declarativeseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
