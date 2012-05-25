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
#include "chartpresenter_p.h"
#include "qchart.h"
#include "qchart_p.h"
#include "qaxis.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"
#include "chartanimation_p.h"
#include "qabstractseries_p.h"
#include "qareaseries.h"
#include "chartaxis_p.h"
#include "chartaxisx_p.h"
#include "chartaxisy_p.h"
#include "areachartitem_p.h"
#include "chartbackground_p.h"
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart,ChartDataSet* dataset):QObject(chart),
m_chart(chart),
m_animator(0),
m_dataset(dataset),
m_chartTheme(0),
m_chartRect(QRectF(QPoint(0,0),m_chart->size())),
m_options(QChart::NoAnimation),
m_minLeftMargin(0),
m_minBottomMargin(0),
m_state(ShowState),
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

void ChartPresenter::setMinimumMarginWidth(ChartAxis* axis, qreal width)
{
    switch(axis->axisType()){
    case ChartAxis::X_AXIS:
    {
        if(width>m_chartRect.width()+ m_chartMargins.left()) {
            m_minLeftMargin= width - m_chartRect.width();
            updateLayout();
        }
        break;
    }
    case ChartAxis::Y_AXIS:
    {

        if(m_minLeftMargin!=width){
            m_minLeftMargin= width;
            updateLayout();
        }
        break;
    }

    }
}

void ChartPresenter::setMinimumMarginHeight(ChartAxis* axis, qreal height)
{
    switch(axis->axisType()){
    case ChartAxis::X_AXIS:
    {
        if(m_minBottomMargin!=height) {
            m_minBottomMargin= height;
            updateLayout();
        }
        break;
    }
    case ChartAxis::Y_AXIS:
    {

        if(height>m_chartMargins.bottom()+m_chartRect.height()){
            m_minBottomMargin= height - m_chartRect.height();
            updateLayout();
        }
        break;
    }

    }
}

void ChartPresenter::handleAxisAdded(QAxis* axis,Domain* domain)
{
    ChartAxis* item;

    if(axis == m_dataset->axisX()){
        item = new ChartAxisX(axis,this);
    }else{
        item = new ChartAxisY(axis,this);
    }

    if(m_options.testFlag(QChart::GridAxisAnimations)){
        item->setAnimator(m_animator);
        item->setAnimation(new AxisAnimation(item));
    }

    if(axis==m_dataset->axisX()){
        m_chartTheme->decorate(axis,true);
        QObject::connect(domain,SIGNAL(rangeXChanged(qreal,qreal,int)),item,SLOT(handleRangeChanged(qreal,qreal,int)));
        //initialize
        item->handleRangeChanged(domain->minX(),domain->maxX(),domain->tickXCount());

    }
    else{
        m_chartTheme->decorate(axis,false);
        QObject::connect(domain,SIGNAL(rangeYChanged(qreal,qreal,int)),item,SLOT(handleRangeChanged(qreal,qreal,int)));
        //initialize
        item->handleRangeChanged(domain->minY(),domain->maxY(),domain->tickYCount());
    }

    QObject::connect(this,SIGNAL(geometryChanged(QRectF)),item,SLOT(handleGeometryChanged(QRectF)));
    //initialize
    if(m_chartRect.isValid()) item->handleGeometryChanged(m_chartRect);
    m_axisItems.insert(axis, item);
}

void ChartPresenter::handleAxisRemoved(QAxis* axis)
{
    ChartAxis* item = m_axisItems.take(axis);
    Q_ASSERT(item);
    if(m_animator) m_animator->removeAnimation(item);
    delete item;
}


void ChartPresenter::handleSeriesAdded(QAbstractSeries* series,Domain* domain)
{
    Chart *item = series->d_ptr->createGraphics(this);
    Q_ASSERT(item);
    QObject::connect(this,SIGNAL(geometryChanged(QRectF)),item,SLOT(handleGeometryChanged(QRectF)));
    QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),item,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
    //initialize
    item->handleDomainChanged(domain->minX(),domain->maxX(),domain->minY(),domain->maxY());
    if(m_chartRect.isValid()) item->handleGeometryChanged(m_chartRect);
    m_chartItems.insert(series,item);
}

void ChartPresenter::handleSeriesRemoved(QAbstractSeries* series)
{
    Chart* item = m_chartItems.take(series);
    Q_ASSERT(item);
    if(m_animator) {
        //small hack to handle area animations
        if(series->type() == QAbstractSeries::SeriesTypeArea){
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
    m_chartTheme = ChartTheme::createTheme(theme);
    m_chartTheme->setForced(force);
    m_chartTheme->decorate(m_chart);
    m_chartTheme->decorate(m_chart->legend());
    resetAllElements();

    // We do not want "force" to stay on.
    // Bar/pie are calling decorate when adding/removing slices/bars which means
    // that to preserve users colors "force" must not be on.
    m_chartTheme->setForced(false);
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
    QList<QAxis *> axisList = m_axisItems.uniqueKeys();
    QList<QAbstractSeries *> seriesList = m_chartItems.uniqueKeys();

    foreach(QAxis *axis, axisList) {
        handleAxisRemoved(axis);
        handleAxisAdded(axis,m_dataset->domain(axis));
    }
    foreach(QAbstractSeries *series, seriesList) {
        handleSeriesRemoved(series);
        handleSeriesAdded(series,m_dataset->domain(series));
//        m_dataset->removeSeries(series);
//        m_dataset->addSeries(series);
    }
}

void ChartPresenter::zoomIn(qreal factor)
{
    QRectF rect = chartGeometry();
    rect.setWidth(rect.width()/factor);
    rect.setHeight(rect.height()/factor);
    rect.moveCenter(chartGeometry().center());
    zoomIn(rect);
}

void ChartPresenter::zoomIn(const QRectF& rect)
{
    QRectF r = rect.normalized();
    r.translate(-m_chartMargins.topLeft());
    if (!r.isValid())
        return;

    m_state = ZoomInState;
    m_statePoint = QPointF(r.center().x()/chartGeometry().width(),r.center().y()/chartGeometry().height());
    m_dataset->zoomInDomain(r,chartGeometry().size());
    m_state = ShowState;
}

void ChartPresenter::zoomOut(qreal factor)
{
    m_state = ZoomOutState;

    QRectF chartRect;
    chartRect.setSize(chartGeometry().size());

    QRectF rect;
    rect.setSize(chartRect.size()/factor);
    rect.moveCenter(chartRect.center());
    if (!rect.isValid())
        return;
    m_statePoint = QPointF(rect.center().x()/chartGeometry().width(),rect.center().y()/chartGeometry().height());
    m_dataset->zoomOutDomain(rect, chartRect.size());
    m_state = ShowState;
}

void ChartPresenter::scroll(int dx,int dy)
{

    if(dx<0) m_state=ScrollLeftState;
    if(dx>0) m_state=ScrollRightState;
    if(dy<0) m_state=ScrollUpState;
    if(dy>0) m_state=ScrollDownState;

    m_dataset->scrollDomain(dx,dy,chartGeometry().size());
    m_state = ShowState;
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

    if(m_chartRect!=chartRect && chartRect.isValid()){
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

void ChartPresenter::handleAnimationFinished()
{
   m_animations.removeAll(qobject_cast<ChartAnimation*>(sender()));
   if(m_animations.empty()) emit animationsFinished();
}

void ChartPresenter::startAnimation(ChartAnimation* animation)
{
    if (animation->state() != QAbstractAnimation::Stopped) animation->stop();
    QObject::connect(animation, SIGNAL(finished()),this,SLOT(handleAnimationFinished()),Qt::UniqueConnection);
    if(!m_animations.isEmpty()){
        m_animations.append(animation);
    }
    QTimer::singleShot(0, animation, SLOT(start()));
}

#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
