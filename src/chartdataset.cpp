#include "chartdataset_p.h"
#include "qchartaxis.h"
//series
#include "qlineseries.h"
#include "qareaseries.h"
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qpieseries.h"
#include "qscatterseries.h"
#include "qsplineseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDataSet::ChartDataSet(QObject *parent):QObject(parent),
    m_axisX(new QChartAxis(this)),
    m_axisY(new QChartAxis(this)),
    m_domainIndex(0),
    m_axisXInitialized(false)
{
}

ChartDataSet::~ChartDataSet()
{
}

void ChartDataSet::addSeries(QSeries* series, QChartAxis *axisY)
{
    if(axisY==0) axisY = m_axisY;

    QChartAxis* axis = m_seriesAxisMap.value(series);

    if(axis) {
        qWarning() << "Can not add series. Series already on the chart";
        return;
    }

    if(!series->parent()){
       series->setParent(this); // take ownership
    };

    if(!axisY->parent()){
       axisY->setParent(this); // take ownership
    }

    Domain* domain = m_axisDomainMap.value(axisY);

    if(!domain) {
        domain = new Domain();

        QObject::connect(axisY,SIGNAL(rangeChanged(qreal,qreal)),domain,SLOT(handleAxisRangeYChanged(qreal,qreal)));
        QObject::connect(axisX(),SIGNAL(rangeChanged(qreal,qreal)),domain,SLOT(handleAxisRangeXChanged(qreal,qreal)));
        //initialize
        m_axisDomainMap.insert(axisY,domain);
        emit axisAdded(axisY,domain);
    }

    if(!m_axisXInitialized){
       emit axisAdded(axisX(),domain);
       m_axisXInitialized=true;
    }

    calculateDomain(series,domain);

    m_seriesAxisMap.insert(series,axisY);
    emit seriesAdded(series,domain);

}

void ChartDataSet::removeSeries(QSeries* series)
{

    QChartAxis* axis = m_seriesAxisMap.value(series);

    if(!axis){
        qWarning()<<"Can not remove series. Series not found on the chart.";
        return;
    }
    emit seriesRemoved(series);
    m_seriesAxisMap.remove(series);

    if(series->parent()==this){
        delete series;
        series=0;
    }

    QList<QChartAxis*> axes =  m_seriesAxisMap.values();

    int i = axes.indexOf(axis);

    if(i==-1){
        Domain* domain = m_axisDomainMap.take(axis);
        emit axisRemoved(axis);
        if(axis!=axisY()){
            if(axis->parent()==this){
                delete axis;
                axis=0;
            }
        }
        delete domain;
    }

    if(m_seriesAxisMap.values().size()==0)
    {
        m_axisXInitialized=false;
        emit axisRemoved(axisX());
    }
}

void ChartDataSet::removeAllSeries()
{

    QList<QSeries*> series =  m_seriesAxisMap.keys();

    foreach(QSeries* s , series) {
        removeSeries(s);
    }

    Q_ASSERT(m_seriesAxisMap.count()==0);
    Q_ASSERT(m_axisDomainMap.count()==0);

}

//to be removed with PIMPL
void ChartDataSet::calculateDomain(QSeries* series,Domain* domain) const
{
    switch(series->type())
    {
        case QSeries::SeriesTypeLine:
        case QSeries::SeriesTypeSpline:
        case QSeries::SeriesTypeScatter:
        {

            QXYSeries* xySeries = static_cast<QXYSeries*>(series);

            qreal minX(domain->minX());
            qreal minY(domain->minY());
            qreal maxX(domain->maxX());
            qreal maxY(domain->maxY());

            for (int i = 0; i < xySeries->count(); i++)
            {
                qreal x = xySeries->x(i);
                qreal y = xySeries->y(i);
                minX = qMin(minX, x);
                minY = qMin(minY, y);
                maxX = qMax(maxX, x);
                maxY = qMax(maxY, y);
                domain->setMinX(qMin(domain->minX(),x));
                domain->setMinY(qMin(domain->minY(),y));
                domain->setMaxX(qMax(domain->maxX(),x));
                domain->setMaxY(qMax(domain->maxY(),y));
            }
            break;
        }
        case QSeries::SeriesTypeArea: {

            QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);

            QLineSeries* upperSeries = areaSeries->upperSeries();
            QLineSeries* lowerSeries = areaSeries->lowerSeries();

            for (int i = 0; i < upperSeries->count(); i++)
            {
                qreal x = upperSeries->x(i);
                qreal y = upperSeries->y(i);
                domain->setMinX(qMin(domain->minX(),x));
                domain->setMinY(qMin(domain->minY(),y));
                domain->setMaxX(qMax(domain->maxX(),x));
                domain->setMaxY(qMax(domain->maxY(),y));
            }
            if(lowerSeries) {
                for (int i = 0; i < lowerSeries->count(); i++)
                {
                    qreal x = lowerSeries->x(i);
                    qreal y = lowerSeries->y(i);
                    domain->setMinX(qMin(domain->minX(),x));
                    domain->setMinY(qMin(domain->minY(),y));
                    domain->setMaxX(qMax(domain->maxX(),x));
                    domain->setMaxY(qMax(domain->maxY(),y));
                }}
            break;
        }
        case QSeries::SeriesTypeBar: {
            qDebug() << "QChartSeries::SeriesTypeBar";
            QBarSeries* barSeries = static_cast<QBarSeries*>(series);
            qreal x = barSeries->categoryCount();
            qreal y = barSeries->max();
            domain->setMinX(qMin(domain->minX(),x));
            domain->setMinY(qMin(domain->minY(),y));
            domain->setMaxX(qMax(domain->maxX(),x));
            domain->setMaxY(qMax(domain->maxY(),y));
            break;
        }
        case QSeries::SeriesTypeStackedBar: {
            qDebug() << "QChartSeries::SeriesTypeStackedBar";

            QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
            qreal x = stackedBarSeries->categoryCount();
            qreal y = stackedBarSeries->maxCategorySum();
            domain->setMinX(qMin(domain->minX(),x));
            domain->setMinY(qMin(domain->minY(),y));
            domain->setMaxX(qMax(domain->maxX(),x));
            domain->setMaxY(qMax(domain->maxY(),y));
            break;
        }
        case QSeries::SeriesTypePercentBar: {
            qDebug() << "QChartSeries::SeriesTypePercentBar";

            QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
            qreal x = percentBarSeries->categoryCount();
            domain->setMinX(qMin(domain->minX(),x));
            domain->setMinY(0);
            domain->setMaxX(qMax(domain->maxX(),x));
            domain->setMaxY(100);
            break;
        }

        case QSeries::SeriesTypePie: {
            QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
            // TODO: domain stuff
            break;
        }


        default: {
            qDebug()<<__FUNCTION__<<"type" << series->type()<<"not supported";
            return;
            break;
        }

    }
}

void ChartDataSet::zoomInDomain(const QRectF& rect, const QSizeF& size)
{
    QMapIterator<QChartAxis*, Domain*> i( m_axisDomainMap);
    while (i.hasNext()) {
        i.next();
        i.value()->zoomIn(rect,size);
    }
}

void ChartDataSet::zoomOutDomain(const QRectF& rect, const QSizeF& size)
{
    QMapIterator<QChartAxis*, Domain*> i( m_axisDomainMap);
    while (i.hasNext()) {
        i.next();
        i.value()->zoomOut(rect,size);
    }
}

QChartAxis* ChartDataSet::axisY(QSeries* series) const
{
    if(series == 0) return m_axisY;
    return m_seriesAxisMap.value(series);
}

Domain* ChartDataSet::domain(QSeries* series) const
{
	QChartAxis* axis = m_seriesAxisMap.value(series);
	if(axis){
		return m_axisDomainMap.value(axis);
	}else
		return 0;
}

Domain* ChartDataSet::domain(QChartAxis* axis) const
{
    if(axis==axisX()) {
        return  m_axisDomainMap.value(axisY());
    }
    else {
        return m_axisDomainMap.value(axis);
    }
}

QChartAxis* ChartDataSet::axis(QSeries* series) const
{
	return m_seriesAxisMap.value(series);
}

#include "moc_chartdataset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
