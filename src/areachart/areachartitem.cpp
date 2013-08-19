/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
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
#include "abstractdomain_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

AreaChartItem::AreaChartItem(QAreaSeries *areaSeries, QGraphicsItem* item)
    : ChartItem(areaSeries->d_func(),item),
      m_series(areaSeries),
      m_upper(0),
      m_lower(0),
      m_pointsVisible(false)
{
    setAcceptHoverEvents(true);
    setZValue(ChartPresenter::LineChartZValue);
    if (m_series->upperSeries())
        m_upper = new AreaBoundItem(this, m_series->upperSeries());
    if (m_series->lowerSeries())
        m_lower = new AreaBoundItem(this, m_series->lowerSeries());

    QObject::connect(m_series->d_func(), SIGNAL(updated()), this, SLOT(handleUpdated()));
    QObject::connect(m_series, SIGNAL(visibleChanged()), this, SLOT(handleUpdated()));
    QObject::connect(m_series, SIGNAL(opacityChanged()), this, SLOT(handleUpdated()));
    QObject::connect(this, SIGNAL(clicked(QPointF)), areaSeries, SIGNAL(clicked(QPointF)));
    QObject::connect(this, SIGNAL(hovered(QPointF,bool)), areaSeries, SIGNAL(hovered(QPointF,bool)));

    handleUpdated();
}

AreaChartItem::~AreaChartItem()
{
    delete m_upper;
    delete m_lower;
}

void AreaChartItem::setPresenter(ChartPresenter *presenter)
{
    if (m_upper)
        m_upper->setPresenter(presenter);
    if (m_lower) {
        m_lower->setPresenter(presenter);
    }
	ChartItem::setPresenter(presenter);
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
    QRectF rect(QPointF(0,0),domain()->size());

    path = m_upper->path();

    if (m_lower) {
        // Note: Polarcharts always draw area correctly only when both series have equal width or are
        // fully displayed. If one series is partally off-chart, the connecting line between
        // the series does not attach to the end of the partially hidden series but to the point
        // where it intersects the axis line. The problem is especially noticeable when one of the series
        // is entirely off-chart, in which case the connecting line connects two ends of the
        // visible series.
        // This happens because we get the paths from linechart, which omits off-chart segments.
        // To properly fix, linechart would need to provide true full path, in right, left, and the rest
        // portions to enable proper clipping. However, combining those to single visually unified area
        // would be a nightmare, since they would have to be painted separately.
        path.connectPath(m_lower->path().toReversed());
    } else {
        QPointF first = path.pointAtPercent(0);
        QPointF last =  path.pointAtPercent(1);
        if (presenter()->chartType() == QChart::ChartTypeCartesian) {
            path.lineTo(last.x(), rect.bottom());
            path.lineTo(first.x(), rect.bottom());
        } else { // polar
            path.lineTo(rect.center());
        }
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
    if (m_upper) {
        AbstractDomain* d = m_upper->domain();
        d->setSize(domain()->size());
        d->setRange(domain()->minX(),domain()->maxX(),domain()->minY(),domain()->maxY());
        m_upper->handleDomainUpdated();
    }

    if (m_lower) {
        AbstractDomain* d = m_lower->domain();
    	d->setSize(domain()->size());
    	d->setRange(domain()->minX(),domain()->maxX(),domain()->minY(),domain()->maxY());
    	m_lower->handleDomainUpdated();
    }
}

void AreaChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)
    painter->save();
    painter->setPen(m_linePen);
    painter->setBrush(m_brush);
    QRectF clipRect = QRectF(QPointF(0, 0), domain()->size());
    if (presenter()->chartType() == QChart::ChartTypePolar)
        painter->setClipRegion(QRegion(clipRect.toRect(), QRegion::Ellipse));
    else
        painter->setClipRect(clipRect);
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
    emit clicked(m_upper->domain()->calculateDomainPoint(event->pos()));
    ChartItem::mousePressEvent(event);
}

void AreaChartItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hovered(domain()->calculateDomainPoint(event->pos()), true);
    event->accept();
//    QGraphicsItem::hoverEnterEvent(event);
}

void AreaChartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hovered(domain()->calculateDomainPoint(event->pos()), false);
    event->accept();
//    QGraphicsItem::hoverEnterEvent(event);
}

#include "moc_areachartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
