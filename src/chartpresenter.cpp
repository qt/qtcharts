/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qchart.h"
#include "qchart_p.h"
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
#include "barchartitem_p.h"
#include "stackedbarchartitem_p.h"
#include "percentbarchartitem_p.h"
#include "linechartitem_p.h"
#include "piechartitem_p.h"
#include "scatterchartitem_p.h"
#include "splinechartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart,ChartDataSet* dataset):QObject(chart),
    m_chart(chart),
    m_animator(0),
    m_dataset(dataset),
    m_chartTheme(0),
    m_chartRect(QRectF(QPoint(0,0),m_chart->size())),
    m_options(QChart::NoAnimation),
    m_themeForce(false),
    m_minLeftMargin(0),
    m_minBottomMargin(0),
    m_backgroundItem(0),
    m_titleItem(0),
    m_marginBig(60),
    m_marginSmall(20),
    m_marginTiny(10),
    m_chartMargins(QRect(m_marginBig,m_marginBig,0,0))
{
}

ChartPresenter::~ChartPresenter()
{
	delete m_chartTheme;
}

void ChartPresenter::setGeometry(const QRectF& rect)
{
    m_rect = rect;
    Q_ASSERT(m_rect.isValid());
    updateLayout();
}

void ChartPresenter::setMinimumMarginWidth(Axis* axis, qreal width)
{
    switch(axis->axisType()){
        case Axis::X_AXIS:
        {
            if(width>m_chartRect.width()+ m_chartMargins.left()) {
                m_minLeftMargin= width - m_chartRect.width();
                updateLayout();
            }
            break;
        }
        case Axis::Y_AXIS:
        {

            if(m_minLeftMargin!=width){
                m_minLeftMargin= width;
                updateLayout();
            }
            break;
        }

    }
}

void ChartPresenter::setMinimumMarginHeight(Axis* axis, qreal height)
{
    switch(axis->axisType()){
        case Axis::X_AXIS:
        {
            if(m_minBottomMargin!=height) {
                m_minBottomMargin= height;
                updateLayout();
            }
            break;
        }
        case Axis::Y_AXIS:
        {

            if(height>m_chartMargins.bottom()+m_chartRect.height()){
                m_minBottomMargin= height - m_chartRect.height();
               updateLayout();
            }
            break;
        }

    }
}

void ChartPresenter::handleAxisAdded(QChartAxis* axis,Domain* domain)
{
    Axis* item = new Axis(axis,this,axis==m_dataset->axisX()?Axis::X_AXIS : Axis::Y_AXIS);

    if(m_options.testFlag(QChart::GridAxisAnimations)){
        m_animator->addAnimation(item);
    }

    if(axis==m_dataset->axisX()){
        m_chartTheme->decorate(axis,true,m_themeForce);
        QObject::connect(domain,SIGNAL(rangeXChanged(qreal,qreal,int)),item,SLOT(handleRangeChanged(qreal,qreal,int)));
        //initialize
        item->handleRangeChanged(domain->minX(),domain->maxX(),domain->tickXCount());

    }
    else{
        m_chartTheme->decorate(axis,false,m_themeForce);
        QObject::connect(domain,SIGNAL(rangeYChanged(qreal,qreal,int)),item,SLOT(handleRangeChanged(qreal,qreal,int)));
        //initialize
        item->handleRangeChanged(domain->minY(),domain->maxY(),domain->tickYCount());
    }

    QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
    //initialize
    item->handleGeometryChanged(m_chartRect);
    m_axisItems.insert(axis, item);
}

void ChartPresenter::handleAxisRemoved(QChartAxis* axis)
{
    Axis* item = m_axisItems.take(axis);
    Q_ASSERT(item);
    if(m_animator) m_animator->removeAnimation(item);
    delete item;
}


void ChartPresenter::handleSeriesAdded(QSeries* series,Domain* domain)
{
	Chart *item = 0 ;

    switch(series->type())
    {
    case QSeries::SeriesTypeLine: {

        QLineSeries* lineSeries = static_cast<QLineSeries*>(series);
        LineChartItem* line = new LineChartItem(lineSeries,this);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
        	m_animator->addAnimation(line);
        }
        m_chartTheme->decorate(lineSeries, m_dataset->seriesIndex(series),m_themeForce);
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),line,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),line,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item = line;
        break;
    }

    case QSeries::SeriesTypeArea: {

        QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
        AreaChartItem* area = new AreaChartItem(areaSeries,this);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
            m_animator->addAnimation(area->upperLineItem());
            if(areaSeries->lowerSeries())  m_animator->addAnimation(area->lowerLineItem());
        }
        m_chartTheme->decorate(areaSeries, m_dataset->seriesIndex(series),m_themeForce);
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),area,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),area,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item=area;
        break;
    }

    case QSeries::SeriesTypeBar: {
        QBarSeries* barSeries = static_cast<QBarSeries*>(series);
        BarChartItem* bar = new BarChartItem(barSeries,this);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
            m_animator->addAnimation(bar);
        }
        m_chartTheme->decorate(barSeries, m_dataset->seriesIndex(barSeries),m_themeForce);
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),bar,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),bar,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item=bar;
        break;
    }

    case QSeries::SeriesTypeStackedBar: {
        QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
        StackedBarChartItem* bar = new StackedBarChartItem(stackedBarSeries,this);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
            m_animator->addAnimation(bar);
        }
        m_chartTheme->decorate(stackedBarSeries, m_dataset->seriesIndex(stackedBarSeries),m_themeForce);
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),bar,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),bar,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item=bar;
        break;
    }

    case QSeries::SeriesTypePercentBar: {
        QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
        PercentBarChartItem* bar = new PercentBarChartItem(percentBarSeries,this);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
            m_animator->addAnimation(bar);
        }
        m_chartTheme->decorate(percentBarSeries, m_dataset->seriesIndex(percentBarSeries),m_themeForce);
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),bar,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),bar,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        item=bar;
        break;
    }

    case QSeries::SeriesTypeScatter: {

    	QScatterSeries *scatterSeries = static_cast<QScatterSeries *>(series);
            ScatterChartItem *scatter = new ScatterChartItem(scatterSeries,this);
            if(m_options.testFlag(QChart::SeriesAnimations)) {
                m_animator->addAnimation(scatter);
            }
            m_chartTheme->decorate(scatterSeries, m_dataset->seriesIndex(series),m_themeForce);
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),scatter,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),scatter,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
            item = scatter;
            break;
	}

    case QSeries::SeriesTypePie: {
        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        PieChartItem* pie = new PieChartItem(pieSeries, this);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
            m_animator->addAnimation(pie);
        }
        m_chartTheme->decorate(pieSeries, m_dataset->seriesIndex(series),m_themeForce);
        QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),pie,SLOT(handleGeometryChanged(const QRectF&)));
        QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),pie,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
        // Hide all from background when there is only piechart
        // TODO: refactor this ugly code... should be one setting for this
        if (m_chartItems.count() == 0) {
            m_chart->axisX()->hide();
            m_chart->axisY()->hide();
        }
        item=pie;
        break;
    }

    case QSeries::SeriesTypeSpline: {
        QSplineSeries* splineSeries = static_cast<QSplineSeries*>(series);
        SplineChartItem* spline  = new SplineChartItem(splineSeries, this);
        if(m_options.testFlag(QChart::SeriesAnimations)) {
            m_animator->addAnimation(spline);
        }
        m_chartTheme->decorate(splineSeries, m_dataset->seriesIndex(series),m_themeForce);
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
    if(m_chartRect.isValid()) item->handleGeometryChanged(m_chartRect);
    m_chartItems.insert(series,item);
}

void ChartPresenter::handleSeriesRemoved(QSeries* series)
{
    Chart* item = m_chartItems.take(series);
    Q_ASSERT(item);
    if(m_animator) {
        //small hack to handle area animations
        if(series->type()==QSeries::SeriesTypeArea){
             QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
             AreaChartItem* area = static_cast<AreaChartItem*>(item);
             m_animator->removeAnimation(area->upperLineItem());
             if(areaSeries->lowerSeries())  m_animator->removeAnimation(area->lowerLineItem());
        }else
        m_animator->removeAnimation(item);
    }
    delete item;
}

void ChartPresenter::setTheme(QChart::ChartTheme theme,bool force)
{
	if(m_chartTheme && m_chartTheme->id() == theme) return;
    delete m_chartTheme;
    m_themeForce = force;
    m_chartTheme = ChartTheme::createTheme(theme);
    m_chartTheme->decorate(m_chart,m_themeForce);
    m_chartTheme->decorate(m_chart->legend(),m_themeForce);
    resetAllElements();
}

QChart::ChartTheme ChartPresenter::theme()
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
	QRectF rect = chartGeometry();
	rect.setWidth(rect.width()/2);
	rect.setHeight(rect.height()/2);
	rect.moveCenter(chartGeometry().center());
	zoomIn(rect);
}

void ChartPresenter::zoomIn(const QRectF& rect)
{
	QRectF r = rect.normalized();
    r.translate(-m_chartMargins.topLeft());
	if(m_animator) {

		QPointF point(r.center().x()/chartGeometry().width(),r.center().y()/chartGeometry().height());
		m_animator->setState(ChartAnimator::ZoomInState,point);
	}
	m_dataset->zoomInDomain(r,chartGeometry().size());
	if(m_animator) {
		m_animator->setState(ChartAnimator::ShowState);
	}
}

void ChartPresenter::zoomOut()
{
	if(m_animator)
	{
		m_animator->setState(ChartAnimator::ZoomOutState);
	}

	QSizeF size = chartGeometry().size();
	QRectF rect = chartGeometry();
    rect.translate(-m_chartMargins.topLeft());
    m_dataset->zoomOutDomain(rect.adjusted(size.width()/4,size.height()/4,-size.width()/4,-size.height()/4),size);
    //m_dataset->zoomOutDomain(m_zoomStack[m_zoomIndex-1],geometry().size());

	if(m_animator){
			m_animator->setState(ChartAnimator::ShowState);
	}
}

void ChartPresenter::scroll(int dx,int dy)
{
	if(m_animator){
		if(dx<0) m_animator->setState(ChartAnimator::ScrollLeftState,QPointF());
		if(dx>0) m_animator->setState(ChartAnimator::ScrollRightState,QPointF());
		if(dy<0) m_animator->setState(ChartAnimator::ScrollUpState,QPointF());
		if(dy>0) m_animator->setState(ChartAnimator::ScrollDownState,QPointF());
	}

	m_dataset->scrollDomain(dx,dy,chartGeometry().size());

    if(m_animator){
		m_animator->setState(ChartAnimator::ShowState);
	}
}

QChart::AnimationOptions ChartPresenter::animationOptions() const
{
    return m_options;
}

void ChartPresenter::updateLayout()
{
    if (!m_rect.isValid()) return;

    // recalculate title size

    QSize titleSize;
    int titlePadding=0;

    if (m_titleItem) {
        titleSize= m_titleItem->boundingRect().size().toSize();
    }

    //defaults
    m_chartMargins = QRect(QPoint(m_minLeftMargin>m_marginBig?m_minLeftMargin:m_marginBig,m_marginBig),QPoint(m_marginBig,m_minBottomMargin>m_marginBig?m_minBottomMargin:m_marginBig));
    titlePadding = m_chartMargins.top()/2;

    QLegend* legend = m_chart->d_ptr->m_legend;

    // recalculate legend position
    if (legend->isAttachedToChart() && legend->isEnabled()) {

        QRect legendRect;

        // Reserve some space for legend
        switch (legend->alignment()) {

            case QLegend::AlignmentTop: {
                int ledgendSize = legend->minHeight();
                int topPadding = 2*m_marginTiny + titleSize.height() + ledgendSize + m_marginTiny;
                m_chartMargins = QRect(QPoint(m_chartMargins.left(),topPadding),QPoint(m_chartMargins.right(),m_chartMargins.bottom()));
                m_legendMargins = QRect(QPoint(m_chartMargins.left(),topPadding - (ledgendSize + m_marginTiny)),QPoint(m_chartMargins.right(),m_rect.height()-topPadding + m_marginTiny));
                titlePadding = m_marginTiny + m_marginTiny;
                break;
            }
            case QLegend::AlignmentBottom: {
                int ledgendSize = legend->minHeight();
                int bottomPadding = m_marginTiny + m_marginSmall + ledgendSize + m_marginTiny + m_minBottomMargin;
                m_chartMargins = QRect(QPoint(m_chartMargins.left(),m_chartMargins.top()),QPoint(m_chartMargins.right(),bottomPadding));
                m_legendMargins = QRect(QPoint(m_chartMargins.left(),m_rect.height()-bottomPadding + m_marginTiny + m_minBottomMargin),QPoint(m_chartMargins.right(),m_marginTiny + m_marginSmall));
                titlePadding = m_chartMargins.top()/2;
                break;
            }
            case QLegend::AlignmentLeft: {
                int ledgendSize = legend->minWidth();
                int leftPadding = m_marginTiny + m_marginSmall + ledgendSize + m_marginTiny + m_minLeftMargin;
                m_chartMargins = QRect(QPoint(leftPadding,m_chartMargins.top()),QPoint(m_chartMargins.right(),m_chartMargins.bottom()));
                m_legendMargins = QRect(QPoint(m_marginTiny + m_marginSmall,m_chartMargins.top()),QPoint(m_rect.width()-leftPadding + m_marginTiny + m_minLeftMargin,m_chartMargins.bottom()));
                titlePadding = m_chartMargins.top()/2;
                break;
            }
            case QLegend::AlignmentRight: {
                int ledgendSize = legend->minWidth();
                int rightPadding = m_marginTiny + m_marginSmall + ledgendSize + m_marginTiny;
                m_chartMargins = QRect(QPoint(m_chartMargins.left(),m_chartMargins.top()),QPoint(rightPadding,m_chartMargins.bottom()));
                m_legendMargins = QRect(QPoint(m_rect.width()- rightPadding+ m_marginTiny ,m_chartMargins.top()),QPoint(m_marginTiny + m_marginSmall,m_chartMargins.bottom()));
                titlePadding = m_chartMargins.top()/2;
                break;
            }
            default: {
                break;
            }
        }
    }

    if(m_rect.width()<2*(m_chartMargins.top()+m_chartMargins.bottom()) || m_rect.height()< 2*(m_chartMargins.top() + m_chartMargins.bottom()))
    {
        m_chart->setMinimumSize(2*(m_chartMargins.top()+m_chartMargins.bottom()),2*(m_chartMargins.top() + m_chartMargins.bottom()));
        return;
    }


    // recalculate title position
    if (m_titleItem) {
        QPointF center = m_rect.center() -m_titleItem->boundingRect().center();
        m_titleItem->setPos(center.x(),titlePadding);
    }

    //recalculate background gradient
    if (m_backgroundItem) {
        m_backgroundItem->setRect(m_rect.adjusted(m_marginTiny,m_marginTiny, -m_marginTiny, -m_marginTiny));
    }


    QRectF chartRect = m_rect.adjusted(m_chartMargins.left(),m_chartMargins.top(),-m_chartMargins.right(),-m_chartMargins.bottom());

    legend->setGeometry(m_rect.adjusted(m_legendMargins.left(),m_legendMargins.top(),-m_legendMargins.right(),-m_legendMargins.bottom()));

   if(m_chartRect!=chartRect){
       m_chartRect=chartRect;
       emit geometryChanged(m_chartRect);
   }


}

void ChartPresenter::createChartBackgroundItem()
{
    if (!m_backgroundItem) {
        m_backgroundItem = new ChartBackground(rootItem());
        m_backgroundItem->setPen(Qt::NoPen);
        m_backgroundItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

void ChartPresenter::createChartTitleItem()
{
    if (!m_titleItem) {
        m_titleItem = new QGraphicsSimpleTextItem(rootItem());
        m_titleItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
