#include "chartdataset_p.h"
//series
#include "qlinechartseries.h"
#include "barchartseries.h"
#include "stackedbarchartseries.h"
#include "percentbarchartseries.h"
#include "qpieseries.h"
#include "qscatterseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDataSet::ChartDataSet(QObject *parent):QObject(parent)
{
    Domain domain;
    m_domains<<domain;
}

ChartDataSet::~ChartDataSet()
{
    // TODO Auto-generated destructor stub
}

const Domain& ChartDataSet::domain() const
{
    return m_domains[m_domainIndex];
}

void ChartDataSet::addSeries(QChartSeries* series)
{
    // TODO: we should check the series not already added
    m_chartSeries << series;
    m_domainIndex = 0;
    m_domains.resize(1);

    Domain& domain = m_domains[m_domainIndex];

    switch(series->type())
    {
        case QChartSeries::SeriesTypeLine: {

            QLineChartSeries* xyseries = static_cast<QLineChartSeries*>(series);

            for (int i = 0; i < xyseries->count(); i++)
            {
                qreal x = xyseries->x(i);
                qreal y = xyseries->y(i);
                domain.m_minX = qMin(domain.m_minX,x);
                domain.m_minY = qMin(domain.m_minY,y);
                domain.m_maxX = qMax(domain.m_maxX,x);
                domain.m_maxY = qMax(domain.m_maxY,y);
            }
            break;
        }
        case QChartSeries::SeriesTypeBar: {
        qDebug() << "QChartSeries::SeriesTypeBar";
            BarChartSeries* barSeries = static_cast<BarChartSeries*>(series);
            qreal x = barSeries->countCategories();
            qreal y = barSeries->max();
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = qMin(domain.m_minY,y);
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = qMax(domain.m_maxY,y);
            break;
        }
        case QChartSeries::SeriesTypeStackedBar: {
        qDebug() << "QChartSeries::SeriesTypeStackedBar";

            StackedBarChartSeries* stackedBarSeries = static_cast<StackedBarChartSeries*>(series);
            qreal x = stackedBarSeries->countCategories();
            qreal y = stackedBarSeries->maxCategorySum();
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = qMin(domain.m_minY,y);
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = qMax(domain.m_maxY,y);
            break;
        }
        case QChartSeries::SeriesTypePercentBar: {
        qDebug() << "QChartSeries::SeriesTypePercentBar";

            PercentBarChartSeries* percentBarSeries = static_cast<PercentBarChartSeries*>(series);
            qreal x = percentBarSeries->countCategories();
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = 0;
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = 100;
            break;
        }

        case QChartSeries::SeriesTypePie: {
            QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
            // TODO: domain stuff
            break;
        }

        case QChartSeries::SeriesTypeScatter: {
            QScatterSeries *scatterSeries = qobject_cast<QScatterSeries *>(series);
            Q_ASSERT(scatterSeries);
            foreach (QPointF point, scatterSeries->data()) {
                domain.m_minX = qMin(domain.m_minX, point.x());
                domain.m_maxX = qMax(domain.m_maxX, point.x());
                domain.m_minY = qMin(domain.m_minY, point.y());
                domain.m_maxY = qMax(domain.m_maxY, point.y());
            }
            break;
        }

        default: {
            qDebug()<<__FUNCTION__<<"type" << series->type()<<"not supported";
            return;
            break;
        }

    }

    emit seriesAdded(series);
    emit domainChanged(domain);
}

bool ChartDataSet::nextDomain()
{
    if (m_domainIndex < m_domains.count() - 1) {
        m_domainIndex++;
        emit domainChanged(m_domains[m_domainIndex]);
        return true;
    }
    else {
        return false;
    }
}

bool ChartDataSet::previousDomain()
{
    if (m_domainIndex > 0) {
        m_domainIndex--;
        emit domainChanged(m_domains[m_domainIndex]);
        return true;
    }
    else {
        return false;
    }
}

void ChartDataSet::clearDomains()
{
    if (m_domainIndex > 0) {
        m_domainIndex = 0;
        emit domainChanged(m_domains[m_domainIndex]);
    }
}

void ChartDataSet::addDomain(const Domain& domain)
{
    m_domains.resize(m_domainIndex + 1);
    m_domains << domain;
    m_domainIndex++;

    emit domainChanged(domain);
}

#include "moc_chartdataset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
