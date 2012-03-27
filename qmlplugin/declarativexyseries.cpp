//#include "DeclarativeXySeries.h"
#include "declarativexyseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qxyseries.h"
#include "qareaseries.h"
#include "qsplineseries.h"
#include "qscatterseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeXySeries::DeclarativeXySeries(QSeries::QSeriesType type, QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    m_seriesType(type),
    m_chart(0),
    m_series(0)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

DeclarativeXySeries::~DeclarativeXySeries()
{
}

void DeclarativeXySeries::componentComplete()
{
    Q_ASSERT(!m_series);
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());

    if (declarativeChart) {
        m_chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        Q_ASSERT(m_chart);

        switch (m_seriesType) {
        case QSeries::SeriesTypeLine:
            qDebug() << "creating line series for chart: " << m_chart;
            m_series = new QLineSeries();
            break;
        case QSeries::SeriesTypeArea:
            qDebug() << "TODO: creating area series for chart: " << m_chart;
//            m_series = new QAreaSeries();
            break;
        case QSeries::SeriesTypeSpline:
            qDebug() << "creating spline series for chart: " << m_chart;
            m_series = new QSplineSeries();
            break;
        case QSeries::SeriesTypeScatter:
            qDebug() << "creating scatter series for chart: " << m_chart;
            m_series = new QScatterSeries();
            break;
        default:
            Q_ASSERT(false);
        }

        for (int i(0); i < m_points.count(); i++) {
            DeclarativeXyPoint *element = m_points.at(i);
            m_series->add(element->x(), element->y());
        }
        m_chart->addSeries(m_series);
    }
}

QDeclarativeListProperty<DeclarativeXyPoint> DeclarativeXySeries::points()
{
    return QDeclarativeListProperty<DeclarativeXyPoint>(this, 0, &DeclarativeXySeries::appendPoints);
}

void DeclarativeXySeries::appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                                          DeclarativeXyPoint *element)
{
    DeclarativeXySeries *series = qobject_cast<DeclarativeXySeries *>(list->object);
    qDebug() << "appendPoints: " << series;
    qDebug() << "appendPoints: " << element;
    qDebug() << "appendPoints: " << element->x();
    qDebug() << "appendPoints: " << element->y();
    qDebug() << "appendPoints: " << series->m_series;
    if (series) {
        series->m_points.append(element);
        if (series->m_series)
            series->m_series->add(element->x(), element->y());
    }
}

#include "moc_declarativexyseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
