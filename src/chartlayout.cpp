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

#include "chartlayout_p.h"
#include "chartpresenter_p.h"
#include "qlegend_p.h"
#include "chartaxis_p.h"
#include "charttitle_p.h"
#include "chartbackground_p.h"
#include "legendmarker_p.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

static const qreal golden_ratio = 0.25;

ChartLayout::ChartLayout(ChartPresenter* presenter):
m_presenter(presenter),
m_margins(20,20,20,20),
m_minChartRect(0,0,200,200)
{

}

ChartLayout::~ChartLayout()
{

}

void ChartLayout::setGeometry(const QRectF& rect)
{
    Q_ASSERT(rect.isValid());

    QList<ChartAxis*> axes = m_presenter->axisItems();
    ChartTitle* title = m_presenter->titleElement();
    QLegend* legend = m_presenter->legend();
    ChartBackground* background = m_presenter->backgroundElement();

    QRectF contentGeometry = calculateBackgroundGeometry(rect,background);

    contentGeometry = calculateContentGeometry(contentGeometry);

    if (title && title->isVisible()) {
        contentGeometry = calculateTitleGeometry(contentGeometry,title);
    }

    if (legend->isAttachedToChart() && legend->isVisible()) {
        contentGeometry = calculateLegendGeometry(contentGeometry,legend);
    }

    calculateChartGeometry(contentGeometry,axes);

    //TODO remove me
#ifdef SHOW_LAYOUT
    LayoutDebuger* debuger = LayoutDebuger::instance();
    debuger->reset();
    debuger->setPen(QPen(Qt::red));
    debuger->add(backgroundGeometry,m_presenter->rootItem());
    debuger->add(titleGeometry,m_presenter->rootItem());
    debuger->add(legendGeometry ,m_presenter->rootItem());
    debuger->add(axisGeometry ,m_presenter->rootItem());
    debuger->add(geometry,m_presenter->rootItem());
    foreach(LegendMarker* marker,legend->d_ptr->markers()){
        debuger->add(marker->mapRectToScene(marker->boundingRect()),m_presenter->rootItem());
    }
#endif

    QGraphicsLayout::setGeometry(rect);
}

QRectF ChartLayout::calculateContentGeometry(const QRectF& geometry) const
{
	return geometry.adjusted(m_margins.left(),m_margins.top(),-m_margins.right(),-m_margins.bottom());
}

QRectF ChartLayout::calculateContentMinimum(const QRectF& minimum) const
{
    return  minimum.adjusted(0,0,m_margins.left()+m_margins.right(),m_margins.top() + m_margins.bottom());
}


QRectF ChartLayout::calculateBackgroundGeometry(const QRectF& geometry,ChartBackground* background) const
{
    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRectF backgroundGeometry = geometry.adjusted(left,top,-right,-bottom);
    if(background) background->setRect(backgroundGeometry);
    return backgroundGeometry;
}

QRectF ChartLayout::calculateBackgroundMinimum(const QRectF& minimum) const
{
    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    return minimum.adjusted(0,0,left + right,top+bottom);
}

QRectF ChartLayout::calculateChartGeometry(const QRectF& geometry, const QList<ChartAxis*>& axes) const
{

    QSizeF vertical(0,0);
    QSizeF horizontal(0,0);

    // check axis size
    foreach(ChartAxis* axis , axes) {
        if(axis->orientation()==Qt::Vertical && axis->isVisible()) {
            vertical = vertical.expandedTo(axis->effectiveSizeHint(Qt::MinimumSize));
        }
        else if(axis->orientation()==Qt::Horizontal && axis->isVisible()) {
            horizontal = horizontal.expandedTo(axis->effectiveSizeHint(Qt::MinimumSize));
        }

    }

    qreal width = qMin(vertical.width(),geometry.width() * golden_ratio);

    QRectF rect = geometry.adjusted(width,vertical.height()/2,-horizontal.width()/2,-horizontal.height());

    m_presenter->setChartsGeometry(rect);

    foreach(ChartAxis* axis , axes) {
        axis->setGeometry(geometry);
    }

    return rect;
}

QRectF ChartLayout::calculateAxisMinimum(const QRectF& minimum, const QList<ChartAxis*>& axes) const
{
    QSizeF vertical(0,0);
    QSizeF horizontal(0,0);

    // check axis size
    foreach(ChartAxis* axis , axes) {
        if(axis->orientation()==Qt::Vertical && axis->isVisible()){
            vertical = vertical.expandedTo(axis->effectiveSizeHint(Qt::MinimumSize));
        }else if(axis->orientation()==Qt::Horizontal && axis->isVisible()) {
            horizontal = horizontal.expandedTo(axis->effectiveSizeHint(Qt::MinimumSize));
        }
    }
    return  minimum.adjusted(0,0,horizontal.width()+vertical.width(),horizontal.height() + vertical.height());
}

QRectF ChartLayout::calculateLegendGeometry(const QRectF& geometry,QLegend* legend) const
{
    QSizeF size = legend->effectiveSizeHint(Qt::PreferredSize,QSizeF(-1,-1));
    QRectF legendRect;
    QRectF result;

    switch (legend->alignment()) {

        case Qt::AlignTop: {
            legendRect = QRectF(geometry.topLeft(),QSizeF(geometry.width(),size.height()));
            result = geometry.adjusted(0,legendRect.height(),0,0);
            break;
        }
        case Qt::AlignBottom: {
            legendRect = QRectF(QPointF(geometry.left(),geometry.bottom()-size.height()),QSizeF(geometry.width(),size.height()));
            result = geometry.adjusted(0,0,0,-legendRect.height());
            break;
        }
        case Qt::AlignLeft: {
            qreal width = qMin(size.width(),geometry.width()*golden_ratio);
            legendRect = QRectF(geometry.topLeft(),QSizeF(width,geometry.height()));
            result = geometry.adjusted(width,0,0,0);
            break;
        }
        case Qt::AlignRight: {
            qreal width = qMin(size.width(),geometry.width()*golden_ratio);
            legendRect = QRectF(QPointF(geometry.right()-width,geometry.top()),QSizeF(width,geometry.height()));
            result = geometry.adjusted(0,0,-width,0);
            break;
        }
        default: {
            break;
        }
    }

    legend->setGeometry(legendRect);

    return result;
}

QRectF ChartLayout::calculateLegendMinimum(const QRectF& geometry,QLegend* legend) const
{
        QSizeF minSize = legend->effectiveSizeHint(Qt::MinimumSize,QSizeF(-1,-1));
        return geometry.adjusted(0,0,minSize.width(),minSize.height());
}

QRectF ChartLayout::calculateTitleGeometry(const QRectF& geometry,ChartTitle* title) const
{
        title->setGeometry(geometry);
        QPointF center = geometry.center() - title->boundingRect().center();
        title->setPos(center.x(),title->pos().y());
        return geometry.adjusted(0,title->boundingRect().height(),0,0);
}

QRectF ChartLayout::calculateTitleMinimum(const QRectF& minimum,ChartTitle* title) const
{
        QSizeF min = title->sizeHint(Qt::MinimumSize);
        return  minimum.adjusted(0,0,min.width(),min.height());
}

QSizeF ChartLayout::sizeHint ( Qt::SizeHint which, const QSizeF & constraint) const
{
    Q_UNUSED(constraint);
    if(which == Qt::MinimumSize){
        QList<ChartAxis*> axes = m_presenter->axisItems();
        ChartTitle* title = m_presenter->titleElement();
        QLegend* legend = m_presenter->legend();
        QRectF minimumRect(0,0,0,0);
        minimumRect = calculateBackgroundMinimum(minimumRect);
        minimumRect = calculateContentMinimum(minimumRect);
        minimumRect = calculateTitleMinimum(minimumRect,title);
        minimumRect = calculateLegendMinimum(minimumRect,legend);
        minimumRect = calculateAxisMinimum(minimumRect,axes);
        return  minimumRect.united(m_minChartRect).size().toSize();
    }else
        return QSize(-1,-1);
}

void ChartLayout::setMargins(const QMargins& margins)
{

    if(m_margins != margins){
        m_margins = margins;
        updateGeometry();
    }
}

QMargins ChartLayout::margins() const
{
    return m_margins;
}

void ChartLayout::adjustChartGeometry()
{
    setGeometry(geometry());
}

QTCOMMERCIALCHART_END_NAMESPACE
