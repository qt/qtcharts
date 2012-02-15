#include "declarativeseries.h"
#include "declarativechart.h"
#include <qscatterseries.h>
#include <qlinechartseries.h>
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
        case SeriesTypeLine: {
            m_series = new QLineChartSeries(this);
            for (qreal i(0.0); i < 100.0; i += 1.0)
                ((QLineChartSeries *)m_series)->add(i, i);
            chart->addSeries(m_series);
            break;
        }
        case SeriesTypeBar:
            // fallthrough; bar and scatter use the same test data
        case SeriesTypeScatter: {
            m_series = chart->createSeries((QChartSeries::QChartSeriesType) m_seriesType);
            QScatterSeries *scatter = qobject_cast<QScatterSeries *>(m_series);
            Q_ASSERT(scatter);
            for (qreal i = 0; i < 100; i += 0.1)
                scatter->addData(QPointF(i + (rand() % 5),
                                         abs(sin(3.14159265358979 / 50 * i) * 100) + (rand() % 5)));
            break;
        }
        case SeriesTypeStackedBar:
            break;
        case SeriesTypePercentBar:
            break;
        case SeriesTypePie: {
            m_series = chart->createSeries((QChartSeries::QChartSeriesType) m_seriesType);
            QList<qreal> data;
            data << 1.0;
            data << 12.0;
            data << 4.0;
            Q_ASSERT(m_series->setData(data));
            break;
        }
        default:
            break;
        }
    }
}

QVariant DeclarativeSeries::itemChange(GraphicsItemChange change,
                                       const QVariant &value)
{
    // For debugging purposes only:
//    qDebug() << QString::number(change) << " : " << value.toString();
    return QGraphicsItem::itemChange(change, value);
}


#include "moc_declarativeseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
