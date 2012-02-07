#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "qxychartseries.h"
#include "xylinechartitem_p.h"
#include "linechartanimationitem_p.h"
#include "qchart.h"

#include <QAbstractAnimation>
#include <QPropertyAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart,ChartDataSet* dataset):QObject(chart),
m_chart(chart),
m_dataset(dataset),
m_rect(QRectF(QPoint(0,0),m_chart->size()))
{
	creteConnections();
}

ChartPresenter::~ChartPresenter()
{
}

void ChartPresenter::creteConnections()
{
    QObject::connect(m_chart,SIGNAL(geometryChanged()),this,SLOT(handleGeometryChanged()));
    QObject::connect(m_dataset,SIGNAL(seriesAdded(QChartSeries*)),this,SLOT(handleSeriesAdded(QChartSeries*)));
    QObject::connect(m_dataset,SIGNAL(domainChanged()),this,SLOT(handleDomainChanged()));
}

void ChartPresenter::handleGeometryChanged()
{
    m_rect = QRectF(QPoint(0,0),m_chart->size());

    int margin = m_chart->margin();
    m_rect.adjust(margin,margin, -margin, -margin);

    foreach (ChartItem *item, m_chartItems) {
        item->setPos(m_rect.topLeft());
        item->setSize(m_rect.size());
        item->updateItem();
    }
}

void ChartPresenter::handleSeriesAdded(QChartSeries* series)
{
    switch(series->type())
    {
        case QChartSeries::SeriesTypeLine: {

            QXYChartSeries* xyseries = static_cast<QXYChartSeries*>(series);
            //TODO: series->createViewItem();
            //XYLineChartItem* item = new XYLineChartItem(this,m_chart);
            XYLineChartItem* item = new LineChartAnimationItem(this,xyseries,m_chart);
            item->setDomain(m_dataset->domain());
            item->updateItem();
            m_chartItems.insert(series,item);
            break;
        }

        default: {
        	qDebug()<< "Series type" << series->type() << "not implemented.";
        	break;
        }
    }
}

void ChartPresenter::handleSeriesChanged(QChartSeries* series)
{
    switch(series->type())
    {
           case QChartSeries::SeriesTypeLine: {

               break;
           }

   }

   //m_chartItems.value(series)->updateItem();
}

#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
