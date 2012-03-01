#include "chartdataset_p.h"
#include "qchartaxis.h"
//series
#include "qlineseries.h"
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
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

void ChartDataSet::addSeries(QSeries* series, QChartAxis *axisY)
{
    // TODO: we should check the series not already added

    series->setParent(this); // take ownership
    clearDomains();

    if(axisY==0) axisY = m_axisY;
    axisY->setParent(this); // take ownership

    QList<QSeries*>  seriesList = m_seriesMap.values(axisY);

    QList<Domain> domainList = m_domainMap.values(axisY);

    Q_ASSERT(domainList.size()<=1);

    Domain domain;

    if(domainList.size()>0) domain = domainList.at(0);

    switch(series->type())
    {
        case QSeries::SeriesTypeLine: {

            QLineSeries* xyseries = static_cast<QLineSeries*>(series);

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
        case QSeries::SeriesTypeBar: {
        qDebug() << "QChartSeries::SeriesTypeBar";
            QBarSeries* barSeries = static_cast<QBarSeries*>(series);
            qreal x = barSeries->categoryCount();
            qreal y = barSeries->max();
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = qMin(domain.m_minY,y);
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = qMax(domain.m_maxY,y);
            break;
        }
        case QSeries::SeriesTypeStackedBar: {
        qDebug() << "QChartSeries::SeriesTypeStackedBar";

            QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
            qreal x = stackedBarSeries->categoryCount();
            qreal y = stackedBarSeries->maxCategorySum();
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = qMin(domain.m_minY,y);
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = qMax(domain.m_maxY,y);
            break;
        }
        case QSeries::SeriesTypePercentBar: {
        qDebug() << "QChartSeries::SeriesTypePercentBar";

            QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
            qreal x = percentBarSeries->categoryCount();
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = 0;
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = 100;
            break;
        }

        case QSeries::SeriesTypePie: {
            QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
            // TODO: domain stuff
            break;
        }

        case QSeries::SeriesTypeScatter: {
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
        QObject::connect(axisY,SIGNAL(rangeChanged(QChartAxis*)),this,SLOT(handleRangeChanged(QChartAxis*)));
        QObject::connect(axisY,SIGNAL(ticksChanged(QChartAxis*)),this,SLOT(handleTickChanged(QChartAxis*)));
    }

    if(!m_axisXInitialized)
    {
        emit axisAdded(axisX());
        QObject::connect(axisX(),SIGNAL(rangeChanged(QChartAxis*)),this,SLOT(handleRangeChanged(QChartAxis*)));
        QObject::connect(axisX(),SIGNAL(ticksChanged(QChartAxis*)),this,SLOT(handleTickChanged(QChartAxis*)));
        m_axisXInitialized=true;
    }

    m_domainMap.replace(axisY,domain);
    m_seriesMap.insert(axisY,series);
    emit seriesAdded(series);
    setDomain(m_domainIndex,axisY);

}

void ChartDataSet::removeSeries(QSeries* series)
{
    QList<QChartAxis*> keys = m_seriesMap.uniqueKeys();
    foreach(QChartAxis* axis , keys) {
        if(m_seriesMap.contains(axis,series)){
            emit seriesRemoved(series);
            m_seriesMap.remove(axis,series);
            //remove axis if no longer there
            if(!m_seriesMap.contains(axis)){
                emit axisRemoved(axis);
                m_domainMap.remove(axis);
                if(axis != m_axisY)
                delete axis;
            }
            series->setParent(0);
            break;
        }
    }
}

void ChartDataSet::removeAllSeries()
{
    QList<QChartAxis*> keys = m_seriesMap.uniqueKeys();
    foreach(QChartAxis* axis , keys) {
        QList<QSeries*> seriesList = m_seriesMap.values(axis);
        for(int i =0 ; i < seriesList.size();i++ )
        {
            emit seriesRemoved(seriesList.at(i));
            delete(seriesList.at(i));
        }
        m_seriesMap.remove(axis);
        m_domainMap.remove(axis);
        emit axisRemoved(axis);
        if(axis != m_axisY) delete axis;
        }
    m_domainIndex=0;
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

    if(domainList.count()==0) return;

    Domain domain;

    foreach (QChartAxis* axis , domainList) {
        int i = m_domainMap.count(axis) - index -1;
        Q_ASSERT(i>=0);
        domain = m_domainMap.values(axis).at(i);
        QStringList labels = createLabels(axis,domain.m_minY,domain.m_maxY);
        QList<QSeries*> seriesList = m_seriesMap.values(axis);
        foreach(QSeries* series, seriesList) {
            emit seriesDomainChanged(series,domain);
        }
        axis->updateRange(domain.m_minY,domain.m_maxY);
        emit axisRangeChanged(axis,labels);

    }

    QStringList labels = createLabels(axisX(),domain.m_minX,domain.m_maxX);
    axisX()->updateRange(domain.m_minX,domain.m_maxY);
    emit axisRangeChanged(axisX(),labels);
}

void ChartDataSet::setDomain(int index,QChartAxis* axis)
{
    int i = m_domainMap.count(axis) - index -1;
    Q_ASSERT(i>=0);
    Domain domain = m_domainMap.values(axis).at(i);
    {
    QStringList labels = createLabels(axis,domain.m_minY,domain.m_maxY);
    QList<QSeries*> seriesList = m_seriesMap.values(axis);
    foreach(QSeries* series, seriesList) {
        emit seriesDomainChanged(series,domain);
    }
    axis->updateRange(domain.m_minY,domain.m_maxY);
    emit axisRangeChanged(axis,labels);
    }

    QStringList labels = createLabels(axisX(),domain.m_minX,domain.m_maxX);
    axisX()->updateRange(domain.m_minX,domain.m_maxY);
    emit axisRangeChanged(axisX(),labels);
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

    Domain domain;

    foreach (QChartAxis* axis , domainList){
        domain = m_domainMap.value(axis).subDomain(rect,viewport.width(),viewport.height());
        m_domainMap.insert(axis,domain);
    }

    setDomain(++m_domainIndex);
}

QChartAxis* ChartDataSet::axisY(QSeries* series) const
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

    int ticks = axis->ticksCount()-1;

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


void ChartDataSet::handleRangeChanged(QChartAxis* axis)
{
    qreal min = axis->min();
    qreal max = axis->max();

    if(axis==axisX()) {

        m_domainIndex=0;

        clearDomains(m_domainIndex);

        QList<QChartAxis*> domainList = m_domainMap.uniqueKeys();

        foreach (QChartAxis* axis , domainList) {

            Q_ASSERT(m_domainMap.values(axis).size()==1);

            Domain domain = m_domainMap.value(axis);
            domain.m_minX=min;
            domain.m_maxX=max;
            m_domainMap.replace(axis,domain);
        }

        setDomain(m_domainIndex);

    }
    else {

        QList<Domain> domains = m_domainMap.values(axis);
        m_domainMap.remove(axis);

        for(int i=0;i<domains.size();i++)
        {
            domains[i].m_minY=min;
            domains[i].m_maxY=max;
        }

        for(int j=domains.size()-1; j>=0;j--)
        m_domainMap.insert(axis,domains.at(j));

        setDomain(m_domainIndex,axis);
    }


}

void ChartDataSet::handleTickChanged(QChartAxis* axis)
{
    if(axis==axisX()){
        Domain domain = m_domainMap.value(axisY());
        QStringList labels = createLabels(axis,domain.m_minX,domain.m_maxX);
        emit axisRangeChanged(axis,labels);
    }else{
        Domain domain = m_domainMap.value(axis);
        QStringList labels = createLabels(axis,domain.m_minY,domain.m_maxY);
        emit axisRangeChanged(axis,labels);
    }
}

#include "moc_chartdataset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
