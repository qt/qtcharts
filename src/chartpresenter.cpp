#include "qchart.h"
#include "qchartaxis.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
//series
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qlineseries.h"
#include "qareaseries.h"
#include "qpieseries.h"
#include "qscatterseries.h"
#include "qsplineseries.h"
//items
#include "axisitem_p.h"
#include "axisanimationitem_p.h"
#include "areachartitem_p.h"
#include "barpresenter_p.h"
#include "stackedbarpresenter_p.h"
#include "percentbarpresenter_p.h"
#include "linechartitem_p.h"
#include "linechartanimationitem_p.h"
#include "piepresenter_p.h"
#include "scatterpresenter_p.h"
#include "splinepresenter_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart,ChartDataSet* dataset):QObject(chart),
    m_chart(chart),
    m_dataset(dataset),
    m_chartTheme(0),
    m_zoomIndex(0),
    m_marginSize(0),
    m_rect(QRectF(QPoint(0,0),m_chart->size())),
    m_options(QChart::NoAnimation)
{
    createConnections();
    setChartTheme(QChart::ChartThemeDefault);
}

ChartPresenter::~ChartPresenter()
{
}

void ChartPresenter::createConnections()
{
    QObject::connect(m_chart,SIGNAL(geometryChanged()),this,SLOT(handleGeometryChanged()));
    QObject::connect(m_dataset,SIGNAL(seriesAdded(QSeries*,Domain*)),this,SLOT(handleSeriesAdded(QSeries*,Domain*)));
    QObject::connect(m_dataset,SIGNAL(seriesRemoved(QSeries*)),this,SLOT(handleSeriesRemoved(QSeries*)));
    QObject::connect(m_dataset,SIGNAL(axisAdded(QChartAxis*,Domain*)),this,SLOT(handleAxisAdded(QChartAxis*,Domain*)));
    QObject::connect(m_dataset,SIGNAL(axisRemoved(QChartAxis*)),this,SLOT(handleAxisRemoved(QChartAxis*)));
}


QRectF ChartPresenter::geometry() const
{
    return m_rect;
}

void ChartPresenter::handleGeometryChanged()
{
    QRectF rect(QPoint(0,0),m_chart->size());
    rect.adjust(m_marginSize,m_marginSize, -m_marginSize, -m_marginSize);

    //rewrite zoom stack
    for(int i=0;i<m_zoomStack.count();i++){
        QRectF r = m_zoomStack[i];
        qreal w = rect.width()/m_rect.width();
        qreal h = rect.height()/m_rect.height();
        QPointF tl = r.topLeft();
        tl.setX(tl.x()*w);
        tl.setY(tl.y()*h);
        QPointF br = r.bottomRight();
        br.setX(br.x()*w);
        br.setY(br.y()*h);
        r.setTopLeft(tl);
        r.setBottomRight(br);
        m_zoomStack[i]=r;
    }

    m_rect = rect;
    Q_ASSERT(m_rect.isValid());
    emit geometryChanged(m_rect);
}

int ChartPresenter::margin() const
{
    return m_marginSize;
}

void ChartPresenter::setMargin(int margin)
{
    m_marginSize = margin;
}

void ChartPresenter::handleAxisAdded(QChartAxis* axis,Domain* domain)
{

    AxisItem* item ;

    if(!m_options.testFlag(QChart::GridAxisAnimations))
    {
        item = new AxisItem(axis,axis==m_dataset->axisX()?AxisItem::X_AXIS : AxisItem::Y_AXIS,m_chart);
    }else{
        item = new AxisAnimationItem(axis,axis==m_dataset->axisX()?AxisItem::X_AXIS : AxisItem::Y_AXIS,m_chart);
    }
    if(axis==m_dataset->axisX()){
        QObject::connect(domain,SIGNAL(rangeXChanged(qreal,qreal)),item,SLOT(handleRangeChanged(qreal,qreal)));
        //initialize
        item->handleRangeChanged(domain->minX(),domain->maxX());
        item->handleTicksCountChanged(4);
    }
    else{
        QObject::connect(domain,SIGNAL(rangeYChanged(qreal,qreal)),item,SLOT(handleRangeChanged(qreal,qreal)));
        //initialize
        item->handleRangeChanged(domain->minY(),domain->maxY());
        item->handleTicksCountChanged(4);
    }

    QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
    //initialize
    item->handleGeometryChanged(m_rect);
    m_chartTheme->decorate(axis,item);
    m_axisItems.insert(axis,item);
}

void ChartPresenter::handleAxisRemoved(QChartAxis* axis)
{
    AxisItem* item = m_axisItems.take(axis);
    Q_ASSERT(item);
    delete item;
}


void ChartPresenter::handleSeriesAdded(QSeries* series,Domain* domain)
{
    switch(series->type())
    {
    case QSeries::SeriesTypeLine: {

        QLineSeries* lineSeries = static_cast<QLineSeries*>(series);
        LineChartItem* item;
        if(m_options.testFlag(QChart::SeriesAnimations)){
            item = new LineChartAnimationItem(lineSeries,m_chart);
        }else{
            item = new LineChartItem(lineSeries,m_chart);
        }
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),item,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        //initialize
        item->handleDomainChanged(domain->minX(),domain->maxX(),domain->minY(),domain->maxY());
        if(m_rect.isValid()) item->handleGeometryChanged(m_rect);
        //decorate
        m_chartTheme->decorate(item,lineSeries,m_chartItems.count());
        m_chartItems.insert(series,item);
        break;
    }

    case QSeries::SeriesTypeArea: {

        QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
        AreaChartItem* item;
        if(m_options.testFlag(QChart::SeriesAnimations)) {
            item = new AreaChartItem(areaSeries,m_chart);
        }
        else {
            item = new AreaChartItem(areaSeries,m_chart);
        }
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),item,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        //initialize
         item->handleDomainChanged(domain->minX(),domain->maxX(),domain->minY(),domain->maxY());
         if(m_rect.isValid()) item->handleGeometryChanged(m_rect);
         //decorate
        m_chartTheme->decorate(item,areaSeries,m_chartItems.count());
        m_chartItems.insert(series,item);
        break;
    }

    case QSeries::SeriesTypeBar: {
        QBarSeries* barSeries = static_cast<QBarSeries*>(series);
        BarPresenter* item = new BarPresenter(barSeries,m_chart);
        m_chartTheme->decorate(item,barSeries,m_chartItems.count());
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
        //            QObject::connect(barSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
        m_chartItems.insert(series,item);
        // m_axisXItem->setVisible(false);
        if(m_rect.isValid()) item->handleGeometryChanged(m_rect);
        break;
    }

    case QSeries::SeriesTypeStackedBar: {

        QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
        StackedBarPresenter* item = new StackedBarPresenter(stackedBarSeries,m_chart);
        m_chartTheme->decorate(item,stackedBarSeries,m_chartItems.count());
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
        //            QObject::connect(stackedBarSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
        m_chartItems.insert(series,item);
        if(m_rect.isValid()) item->handleGeometryChanged(m_rect);
        break;
    }

    case QSeries::SeriesTypePercentBar: {

        QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
        PercentBarPresenter* item = new PercentBarPresenter(percentBarSeries,m_chart);
        m_chartTheme->decorate(item,percentBarSeries ,m_chartItems.count());
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
        //            QObject::connect(percentBarSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
        m_chartItems.insert(series,item);
        if(m_rect.isValid()) item->handleGeometryChanged(m_rect);
        break;
    }
    case QSeries::SeriesTypeScatter: {
        QScatterSeries *scatterSeries = qobject_cast<QScatterSeries *>(series);
        ScatterPresenter *scatterPresenter = new ScatterPresenter(scatterSeries, m_chart);
        QObject::connect(scatterPresenter, SIGNAL(clicked(QPointF)),
                         scatterSeries, SIGNAL(clicked(QPointF)));
        QObject::connect(this, SIGNAL(geometryChanged(const QRectF&)),
                         scatterPresenter, SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain, SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),
                         scatterPresenter, SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        m_chartTheme->decorate(scatterPresenter, scatterSeries, m_chartItems.count());
        m_chartItems.insert(scatterSeries, scatterPresenter);
        if (m_rect.isValid())
            scatterPresenter->handleGeometryChanged(m_rect);
        scatterPresenter->handleDomainChanged(domain->minX(), domain->maxX(), domain->minY(), domain->maxY());
        break;
    }
    case QSeries::SeriesTypePie: {
        QPieSeries *s = qobject_cast<QPieSeries *>(series);
        PiePresenter* pie = new PiePresenter(m_chart, s);
        m_chartTheme->decorate(pie, s, m_chartItems.count());
        QObject::connect(this, SIGNAL(geometryChanged(const QRectF&)), pie, SLOT(handleGeometryChanged(const QRectF&)));

        // Hide all from background when there is only piechart
        // TODO: refactor this ugly code... should be one setting for this
        if (m_chartItems.count() == 0) {
            m_chart->axisX()->setAxisVisible(false);
            m_chart->axisY()->setAxisVisible(false);
            m_chart->axisX()->setGridVisible(false);
            m_chart->axisY()->setGridVisible(false);
            m_chart->axisX()->setLabelsVisible(false);
            m_chart->axisY()->setLabelsVisible(false);
            m_chart->axisX()->setShadesVisible(false);
            m_chart->axisY()->setShadesVisible(false);
            m_chart->setChartBackgroundBrush(Qt::transparent);
        }

        m_chartItems.insert(series, pie);
        pie->handleGeometryChanged(m_rect);
        break;
    }

    case QSeries::SeriesTypeSpline: {
        QSplineSeries* splineSeries = qobject_cast<QSplineSeries*>(series);
        SplinePresenter* splinePresenter = new SplinePresenter(splineSeries, m_chart);
        QObject::connect(this, SIGNAL(geometryChanged(const QRectF&)), splinePresenter, SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),splinePresenter,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        //initialize
        splinePresenter->handleDomainChanged(domain->minX(),domain->maxX(),domain->minY(),domain->maxY());
        m_chartTheme->decorate(splinePresenter, splineSeries, m_chartItems.count());
        m_chartItems.insert(splineSeries, splinePresenter);
        break;
    }
    default: {
        qDebug()<< "Series type" << series->type() << "not implemented.";
        break;
    }
    }

    zoomReset();
}

void ChartPresenter::handleSeriesRemoved(QSeries* series)
{
    ChartItem* item = m_chartItems.take(series);
    delete item;
}

void ChartPresenter::setChartTheme(QChart::ChartTheme theme)
{
    delete m_chartTheme;

    m_chartTheme = ChartTheme::createTheme(theme);

    m_chartTheme->decorate(m_chart);
    QMapIterator<QSeries*,ChartItem*> i(m_chartItems);

    int index=0;
    while (i.hasNext()) {
        i.next();
        m_chartTheme->decorate(i.value(),i.key(),index);
        index++;
    }

    QMapIterator<QChartAxis*,AxisItem*> j(m_axisItems);
    while (j.hasNext()) {
        j.next();
        m_chartTheme->decorate(j.key(),j.value());
    }
}

QChart::ChartTheme ChartPresenter::chartTheme()
{
    return m_chartTheme->id();
}

void ChartPresenter::setAnimationOptions(QChart::AnimationOptions options)
{
    if(m_options!=options) {

        m_options=options;

        //recreate elements
        QList<QChartAxis*> axisList = m_axisItems.uniqueKeys();
        QList<QSeries*> seriesList = m_chartItems.uniqueKeys();

        foreach(QChartAxis* axis, axisList) {
            handleAxisRemoved(axis);
            handleAxisAdded(axis,m_dataset->domain(axis));
        }
        foreach(QSeries* series, seriesList) {
            handleSeriesRemoved(series);
            handleSeriesAdded(series,m_dataset->domain(series));
        }
    }
}

void ChartPresenter::zoomIn()
{
	QRectF rect = geometry();
	rect.setWidth(rect.width()/2);
	rect.setHeight(rect.height()/2);
	rect.moveCenter(geometry().center());
	zoomIn(rect);
}

void ChartPresenter::zoomIn(const QRectF& rect)
{
	QRectF r = rect.normalized();
	r.translate(-m_marginSize, -m_marginSize);
	m_dataset->zoomInDomain(r,geometry().size());
	m_zoomStack<<r;
	m_zoomIndex++;
}

void ChartPresenter::zoomOut()
{
	if(m_zoomIndex==0) return;
	m_dataset->zoomOutDomain(m_zoomStack[m_zoomIndex-1],geometry().size());
	m_zoomIndex--;
	m_zoomStack.resize(m_zoomIndex);
}

void ChartPresenter::zoomReset()
{
    m_zoomIndex=0;
    m_zoomStack.resize(m_zoomIndex);
}

QChart::AnimationOptions ChartPresenter::animationOptions() const
{
    return m_options;
}


#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
