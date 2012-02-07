#include "chartdataset_p.h"
#include "qxychartseries.h"

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

			QXYChartSeries* xyseries = static_cast<QXYChartSeries*>(series);

			for (int i = 0; i < xyseries->count(); i++)
			{
				qreal x = xyseries->x(i);
				qreal y = xyseries->y(i);
				domain.m_minX = qMin(domain.m_minX,x);
				domain.m_minY = qMin(domain.m_minY,y);
				domain.m_maxX = qMax(domain.m_maxX,x);
				domain.m_maxY = qMax(domain.m_maxY,y);
			}

			emit domainChanged();

			break;
		}
		default: {
			qDebug()<<__FUNCTION__<<"type" << series->type()<<"not supported";
			return;
			break;
		}

	}

	emit seriesAdded(series);
}

#include "moc_chartdataset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
