#include "qchart.h"
#include "qchartaxis.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"
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
#include "areachartitem_p.h"
#include "barpresenter_p.h"
#include "stackedbarpresenter_p.h"
#include "percentbarpresenter_p.h"
#include "linechartitem_p.h"
#include "piepresenter_p.h"
#include "scatterchartitem_p.h"
#include "splinechartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart,ChartDataSet* dataset):QObject(chart),
    m_chart(chart),
    m_animator(0),
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
	delete m_chartTheme;
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
    AxisItem* item = new AxisItem(axis,this,axis==m_dataset->axisX()?AxisItem::X_AXIS : AxisItem::Y_AXIS,m_chart);

    if(m_options.testFlag(QChart::GridAxisAnimations)){
        m_animator->addAnimation(item);
    }

    if(axis==m_dataset->axisX()){
        QObject::connect(domain,SIGNAL(rangeXChanged(qreal,qreal,int)),item,SLOT(handleRangeChanged(qreal,qreal,int)));
        //initialize
        item->handleRangeChanged(domain->minX(),domain->maxX(),domain->tickXCount());
    }
    else{
        QObject::connect(domain,SIGNAL(rangeYChanged(qreal,qreal,int)),item,SLOT(handleRangeChanged(qreal,qreal,int)));
        //initialize
        item->handleRangeChanged(domain->minY(),domain->maxY(),domain->tickYCount());
    }

    QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
    //initialize
    item->handleGeometryChanged(m_rect);
    m_chartTheme->decorate(axis, m_chart);
    m_axisItems.insert(axis, item);
}

void ChartPresenter::handleAxisRemoved(QChartAxis* axis)
{
    AxisItem* item = m_axisItems.take(axis);
    Q_ASSERT(item);
    if(m_animator) m_animator->removeAnimation(item);
    delete item;
}


void ChartPresenter::handleSeriesAdded(QSeries* series,Domain* domain)
{
	ChartItem *item = 0 ;

    switch(series->type())
    {
    case QSeries::SeriesTypeLine: {

        QLineSeries* lineSeries = static_cast<QLineSeries*>(series);
        LineChartItem* line = new LineChartItem(lineSeries,m_chart);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
        	m_animator->addAnimation(line);
        }
        m_chartTheme->decorate(line, lineSeries, m_dataset->seriesIndex(series));
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),line,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),line,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item = line;
        break;
    }

    case QSeries::SeriesTypeArea: {

        QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
        AreaChartItem* area = new AreaChartItem(areaSeries,m_chart);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
           m_animator->addAnimation(area->upperLineItem());
           if(areaSeries->lowerSeries())  m_animator->addAnimation(area->lowerLineItem());
        }
        m_chartTheme->decorate(area, areaSeries, m_dataset->seriesIndex(series));
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),area,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),area,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item=area;
        break;
    }

    case QSeries::SeriesTypeBar: {
        QBarSeries* barSeries = static_cast<QBarSeries*>(series);
        BarPresenter* bar = new BarPresenter(barSeries,m_chart);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
         //  m_animator->addAnimation(bar);
        }
        m_chartTheme->decorate(bar, barSeries, m_dataset->seriesIndex(barSeries));
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),bar,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),bar,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item=bar;
        break;
    }

    case QSeries::SeriesTypeStackedBar: {
        QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
        StackedBarPresenter* bar = new StackedBarPresenter(stackedBarSeries,m_chart);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
         //  m_animator->addAnimation(bar);
        }
        m_chartTheme->decorate(bar, stackedBarSeries, m_dataset->seriesIndex(stackedBarSeries));
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),bar,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),bar,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item=bar;
        break;
    }

    case QSeries::SeriesTypePercentBar: {
        QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
        PercentBarPresenter* bar = new PercentBarPresenter(percentBarSeries,m_chart);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
         //  m_animator->addAnimation(bar);
        }
        m_chartTheme->decorate(bar, percentBarSeries, m_dataset->seriesIndex(percentBarSeries));
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),bar,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),bar,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item=bar;
        break;
    }

    case QSeries::SeriesTypeScatter: {
    	QScatterSeries *scatterSeries = static_cast<QScatterSeries *>(series);
            ScatterChartItem *scatter = new ScatterChartItem(scatterSeries, m_chart);
            if(m_options.testFlag(QChart::SeriesAnimations)) {
                m_animator->addAnimation(scatter);
            }
            m_chartTheme->decorate(scatter, scatterSeries, m_dataset->seriesIndex(series));
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),scatter,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),scatter,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
            item = scatter;
            break;
	}

    case QSeries::SeriesTypePie: {
        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        PiePresenter* pie = new PiePresenter(m_chart, pieSeries);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
           // m_animator->addAnimation(pie);
        }
        m_chartTheme->decorate(pie, pieSeries, m_dataset->seriesIndex(series));
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),pie,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),pie,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        // Hide all from background when there is only piechart
        // TODO: refactor this ugly code... should be one setting for this
        if (m_chartItems.count() == 0) {
            m_chart->axisX()->hide();
            m_chart->axisY()->hide();
            m_chart->setChartBackgroundBrush(Qt::transparent);
        }
        item=pie;
        break;
    }

    case QSeries::SeriesTypeSpline: {
        QSplineSeries* splineSeries = static_cast<QSplineSeries*>(series);
        SplineChartItem* spline  = new SplineChartItem(splineSeries, m_chart);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
            m_animator->addAnimation(spline);
        }
        m_chartTheme->decorate(spline, splineSeries, m_dataset->seriesIndex(series));
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),spline,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),spline,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item=spline;
        break;
    }
    default: {
        qDebug()<< "Series type" << series->type() << "not implemented.";
        break;
    }
    }

    //initialize
    item->handleDomainChanged(domain->minX(),domain->maxX(),domain->minY(),domain->maxY());
    if(m_rect.isValid()) item->handleGeometryChanged(m_rect);
    m_chartItems.insert(series,item);
    zoomReset();
}

void ChartPresenter::handleSeriesRemoved(QSeries* series)
{
    ChartItem* item = m_chartItems.take(series);
    Q_ASSERT(item);
    if(m_animator) {
        //small hack to handle area animations
        if(series->type()==QSeries::SeriesTypeArea){
             QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
             AreaChartItem* area = static_cast<AreaChartItem*>(item);
             m_animator->removeAnimation(area->upperLineItem());
             if(areaSeries->lowerSeries())  m_animator->addAnimation(area->lowerLineItem());
        }else
        m_animator->removeAnimation(item);
    }
    delete item;
}

void ChartPresenter::setChartTheme(QChart::ChartTheme theme)
{
	if(m_chartTheme && m_chartTheme->id() == theme) return;
    delete m_chartTheme;
    m_chartTheme = ChartTheme::createTheme(theme);
    m_chartTheme->decorate(m_chart);
    m_chartTheme->decorate(m_chart->legend());
    resetAllElements();
}

QChart::ChartTheme ChartPresenter::chartTheme()
{
    return m_chartTheme->id();
}

void ChartPresenter::setAnimationOptions(QChart::AnimationOptions options)
{
    if(m_options!=options) {

        m_options=options;

        if(m_options!=QChart::NoAnimation && !m_animator) {
            m_animator= new ChartAnimator(this);

        }
        resetAllElements();
    }

}

void ChartPresenter::resetAllElements()
{
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
	if(m_animator) {

		QPointF point(r.center().x()/geometry().width(),r.center().y()/geometry().height());
		m_animator->setState(ChartAnimator::ZoomInState,point);
	}
	m_dataset->zoomInDomain(r,geometry().size());
	m_zoomStack<<r;
	m_zoomIndex++;
	if(m_animator) {
		m_animator->setState(ChartAnimator::ShowState);
	}
}

void ChartPresenter::zoomOut()
{
	if(m_zoomIndex==0) return;
	if(m_animator)
	{
		m_animator->setState(ChartAnimator::ZoomOutState);
	}
	m_dataset->zoomOutDomain(m_zoomStack[m_zoomIndex-1],geometry().size());
	m_zoomIndex--;
	m_zoomStack.resize(m_zoomIndex);
	if(m_animator){
			m_animator->setState(ChartAnimator::ShowState);
	}
}

void ChartPresenter::zoomReset()
{
    m_zoomIndex=0;
    m_zoomStack.resize(m_zoomIndex);
}

void ChartPresenter::scroll(int dx,int dy)
{
	if(m_animator){
		if(dx<0) m_animator->setState(ChartAnimator::ScrollLeftState,QPointF());
		if(dx>0) m_animator->setState(ChartAnimator::ScrollRightState,QPointF());
		if(dy<0) m_animator->setState(ChartAnimator::ScrollUpState,QPointF());
		if(dy>0) m_animator->setState(ChartAnimator::ScrollDownState,QPointF());
	}

	m_dataset->scrollDomain(dx,dy,geometry().size());

    if(m_animator){
		m_animator->setState(ChartAnimator::ShowState);
	}
}

QChart::AnimationOptions ChartPresenter::animationOptions() const
{
    return m_options;
}


#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
