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

#include "areachartitem_p.h"
#include "qareaseries.h"
#include "qareaseries_p.h"
#include "qlineseries.h"
#include "chartpresenter_p.h"
#include "domain_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

AreaChartItem::AreaChartItem(QAreaSeries *areaSeries, ChartPresenter *presenter)
    : ChartItem(presenter),
    m_series(areaSeries),
    m_upper(0),
    m_lower(0),
    m_pointsVisible(false)
{
    setZValue(ChartPresenter::LineChartZValue);
    m_upper = new AreaBoundItem(this,m_series->upperSeries(),presenter);
    if (m_series->lowerSeries()){
        m_lower = new AreaBoundItem(this,m_series->lowerSeries(),presenter);
    }

    QObject::connect(m_series->d_func(),SIGNAL(updated()),this,SLOT(handleUpdated()));
    QObject::connect(m_series, SIGNAL(visibleChanged()), this, SLOT(handleUpdated()));
    QObject::connect(m_series, SIGNAL(opacityChanged()), this, SLOT(handleUpdated()));
    QObject::connect(this,SIGNAL(clicked(QPointF)),areaSeries,SIGNAL(clicked(QPointF)));

    handleUpdated();
}

AreaChartItem::~AreaChartItem()
{
    delete m_upper;
    delete m_lower;
}

QRectF AreaChartItem::boundingRect() const
{
    return m_rect;
}

QPainterPath AreaChartItem::shape() const
{
    return m_path;
}

void AreaChartItem::updatePath()
{
    QPainterPath path;

    path = m_upper->path();

    if (m_lower) {
        path.connectPath(m_lower->path().toReversed());
    } else {
        QPointF first = path.pointAtPercent(0);
        QPointF last =  path.pointAtPercent(1);
        path.lineTo(last.x(),m_clipRect.bottom());
        path.lineTo(first.x(),m_clipRect.bottom());
    }
    path.closeSubpath();
    prepareGeometryChange();
    m_path = path;
    m_rect = path.boundingRect();
    update();
}

void AreaChartItem::handleUpdated()
{
    setVisible(m_series->isVisible());
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    m_brush = m_series->brush();
    m_pointPen = m_series->pen();
    m_pointPen.setWidthF(2 * m_pointPen.width());
    setOpacity(m_series->opacity());

    update();
}

void AreaChartItem::handleDomainUpdated()
{
    m_upper->setDomain(domain());
    m_upper->handleDomainUpdated();
    if (m_lower){
        m_lower->setDomain(domain());
        m_lower->handleDomainUpdated();
    }
}

void AreaChartItem::handleGeometryChanged(const QRectF &rect)
{
    m_clipRect=rect.translated(-rect.topLeft());
    setPos(rect.topLeft());
    m_upper->handleGeometryChanged(rect);
    if (m_lower)
        m_lower->handleGeometryChanged(rect);
}

void AreaChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->save();
    painter->setPen(m_linePen);
    painter->setBrush(m_brush);
    painter->setClipRect(m_clipRect);
    painter->drawPath(m_path);
    if (m_pointsVisible) {
           painter->setPen(m_pointPen);
           painter->drawPoints(m_upper->geometryPoints());
           if (m_lower)
               painter->drawPoints(m_lower->geometryPoints());
    }
    painter->restore();
}

void AreaChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(m_upper->calculateDomainPoint(event->pos()));
    ChartItem::mousePressEvent(event);
}

#include "moc_areachartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
