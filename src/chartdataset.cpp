#include "chartdataset_p.h"
#include "qchartaxis.h"
//series
#include "qlinechartseries.h"
#include "qbarchartseries.h"
#include "qstackedbarchartseries.h"
#include "qpercentbarchartseries.h"
#include "qpieseries.h"
#include "qscatterseries.h"

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
    // TODO Auto-generated destructor stub
}

const Domain ChartDataSet::domain(QChartAxis *axisY) const
{
	int i = m_domainMap.count(axisY);
	if(i == 0){
		return Domain();
	}
	i = i - m_domainIndex -1;
    return m_domainMap.values(axisY).at(i);
}

void ChartDataSet::addSeries(QChartSeries* series, QChartAxis *axisY)
{
    // TODO: we should check the series not already added
    series->setParent(this); // take ownership

    series->setParent(this); // take ownership
    clearDomains();

    if(axisY==0) axisY = m_axisY;

    QList<QChartSeries*>  seriesList = m_seriesMap.values(axisY);

    QList<Domain> domainList = m_domainMap.values(axisY);

    Q_ASSERT(domainList.size()<=1);

    Domain domain;

    if(domainList.size()>0) domain = domainList.at(0);

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
<<<<<<< HEAD
        qDebug() << "QChartSeries::SeriesTypeBar";
=======
>>>>>>> Common naming convention for barcharts
            QBarChartSeries* barSeries = static_cast<QBarChartSeries*>(series);
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

            QStackedBarChartSeries* stackedBarSeries = static_cast<QStackedBarChartSeries*>(series);
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

            QPercentBarChartSeries* percentBarSeries = static_cast<QPercentBarChartSeries*>(series);
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

    if(!m_domainMap.contains(axisY))
    {
        emit axisAdded(axisY);
        QObject::connect(axisY,SIGNAL(minChanged(qreal)),this,SLOT(handleMinChanged(qreal)));
        QObject::connect(axisY,SIGNAL(maxChanged(qreal)),this,SLOT(handleMaxChanged(qreal)));
        QObject::connect(axisY,SIGNAL(ticksChanged(QChartAxis*)),this,SLOT(handleTickChanged(QChartAxis*)));
    }
    m_domainMap.replace(axisY,domain);
    m_seriesMap.insert(axisY,series);

    if(!m_axisXInitialized)
    {
        emit axisAdded(axisX());
        QObject::connect(axisX(),SIGNAL(minChanged(qreal)),this,SLOT(handleMinChanged(qreal)));
        QObject::connect(axisX(),SIGNAL(maxChanged(qreal)),this,SLOT(handleMaxChanged(qreal)));
        QObject::connect(axisX(),SIGNAL(ticksChanged(QChartAxis*)),this,SLOT(handleTickChanged(QChartAxis*)));
        m_axisXInitialized=true;
    }


    emit seriesAdded(series);
    QStringList ylabels = createLabels(axisY,domain.m_minY,domain.m_maxY);
    QStringList xlabels = createLabels(axisX(),domain.m_minX,domain.m_maxX);
    emit axisLabelsChanged(axisY,ylabels);
    emit axisLabelsChanged(axisX(),xlabels);
    emit seriesDomainChanged(series,domain);

}

void ChartDataSet::removeSeries(QChartSeries* series)
{
    QList<QChartAxis*> keys = m_seriesMap.uniqueKeys();
    foreach(QChartAxis* axis , keys) {
        if(m_seriesMap.contains(axis,series)){
            emit seriesRemoved(series);
            m_seriesMap.remove(axis,series);
            //remove axis if no longer there
            if(!m_seriesMap.contains(axis) && axis != m_axisY){
                emit axisRemoved(axis);
                m_domainMap.remove(axis);
                delete axis;
            }
            break;
        }
    }
}

bool ChartDataSet::nextDomain()
{
    int limit = (m_domainMap.values().size()/m_domainMap.uniqueKeys().size())-1;

    if (m_domainIndex < limit) {
        m_domainIndex++;
        setDomain(m_domainIndex);
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
        setDomain(m_domainIndex);
        return true;
    }
    else {
        return false;
    }
}

void ChartDataSet::setDomain(int index)
{
    QList<QChartAxis*> domainList = m_domainMap.uniqueKeys();
    foreach (QChartAxis* axis , domainList) {
        int i = m_domainMap.count(axis) - index -1;
        Q_ASSERT(i>=0);
        Domain domain = m_domainMap.values(axis).at(i);
        QStringList labels = createLabels(axis,domain.m_minY,domain.m_maxY);
        QList<QChartSeries*> seriesList = m_seriesMap.values(axis);
        foreach(QChartSeries* series, seriesList) {
            emit seriesDomainChanged(series,domain);
        }
        emit axisLabelsChanged(axis,labels);
    }

    Domain domain = m_domainMap.value(axisY());
    QStringList labels = createLabels(axisX(),domain.m_minX,domain.m_maxX);
    emit axisLabelsChanged(axisX(),labels);
}

void ChartDataSet::clearDomains(int toIndex)
{
    Q_ASSERT(toIndex>=0);

    m_domainIndex = toIndex;

    QList<QChartAxis*> keys = m_domainMap.uniqueKeys();

    foreach (QChartAxis* key , keys)
    {
        QList<Domain> domains = m_domainMap.values(key);
        m_domainMap.remove(key);
        int i = domains.size() - toIndex - 1;
        while(i--){
            domains.removeFirst();
        }
        for(int j=domains.size()-1; j>=0 ;j--)
            m_domainMap.insert(key,domains.at(j));
    }
}

void ChartDataSet::addDomain(const QRectF& rect, const QRectF& viewport)
{
    Q_ASSERT(rect.isValid());
    Q_ASSERT(viewport.isValid());

    clearDomains(m_domainIndex);

    QList<QChartAxis*> domainList = m_domainMap.uniqueKeys();

    foreach (QChartAxis* axis , domainList){
        Domain domain(m_domainMap.value(axis).subDomain(rect,viewport.width(),viewport.height()));
        QStringList labels = createLabels(axis,domain.m_minY,domain.m_maxY);
        QList<QChartSeries*> seriesList = m_seriesMap.values(axis);
        foreach(QChartSeries* series, seriesList){
            emit seriesDomainChanged(series,domain);
        }
        emit axisLabelsChanged(axis,labels);
        m_domainMap.insert(axis,domain);
    }

    Domain domain = m_domainMap.value(axisY());
    QStringList labels = createLabels(axisX(),domain.m_minX,domain.m_maxX);
    emit axisLabelsChanged(axisX(),labels);

    m_domainIndex++;
}

QChartAxis* ChartDataSet::axisY(QChartSeries* series) const
{
    if(series == 0) return m_axisY;

    QList<QChartAxis*> keys = m_seriesMap.uniqueKeys();

    foreach(QChartAxis* axis , keys) {
        if(m_seriesMap.contains(axis,series)){
            return axis;
        }
    }
    return 0;
}

QStringList ChartDataSet::createLabels(QChartAxis* axis,qreal min, qreal max)
{
    Q_ASSERT(max>=min);

    QStringList labels;

    int ticks = axis->ticksCount();

    for(int i=0; i<= ticks; i++){
        qreal value = min + (i * (max - min)/ ticks);
        QString label = axis->axisTickLabel(value);
        if(label.isEmpty()){
            labels << QString::number(value);
        }else{
            labels << label;
        }
    }
    return labels;
}


void ChartDataSet::handleMinChanged(qreal min)
{

}

void ChartDataSet::handleMaxChanged(qreal max)
{

}

void ChartDataSet::handleTickChanged(QChartAxis* axis)
{
    Domain domain = m_domainMap.value(axisY());
    if(axis==axisX()){
        QStringList labels = createLabels(axis,domain.m_minX,domain.m_maxX);
        emit axisLabelsChanged(axis,labels);
    }else{
        QStringList labels = createLabels(axis,domain.m_minY,domain.m_maxY);
        emit axisLabelsChanged(axis,labels);
    }
}

#include "moc_chartdataset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
