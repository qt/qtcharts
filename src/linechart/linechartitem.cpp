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

#include "linechartitem_p.h"
#include "qlineseries.h"
#include "qlineseries_p.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

const qreal mouseEventMinWidth(12);

LineChartItem::LineChartItem(QLineSeries *series, ChartPresenter *presenter)
    : XYChart(series, presenter),
      QGraphicsItem(presenter ? presenter->rootItem() : 0),
      m_series(series),
      m_pointsVisible(false)
{
    setAcceptHoverEvents(true);
    setZValue(ChartPresenter::LineChartZValue);
    QObject::connect(series->d_func(), SIGNAL(updated()), this, SLOT(handleUpdated()));
    QObject::connect(series, SIGNAL(visibleChanged()), this, SLOT(handleUpdated()));
    QObject::connect(series, SIGNAL(opacityChanged()), this, SLOT(handleUpdated()));
    handleUpdated();
}

QRectF LineChartItem::boundingRect() const
{
    return m_rect;
}

QPainterPath LineChartItem::shape() const
{
    return m_path;
}

void LineChartItem::updateGeometry()
{
    m_points = geometryPoints();

    if (m_points.size() == 0) {
        prepareGeometryChange();
        m_path = QPainterPath();
        m_rect = QRect();
        return;
    }

    QPainterPath linePath(m_points.at(0));

    if (m_pointsVisible) {

        int size = m_linePen.width();
        linePath.addEllipse(m_points.at(0), size, size);
        for (int i = 1; i < m_points.size(); i++) {
            linePath.lineTo(m_points.at(i));
            linePath.addEllipse(m_points.at(i), size, size);
            linePath.moveTo(m_points.at(i));
        }

    } else {
        for (int i = 1; i < m_points.size(); i++)
            linePath.lineTo(m_points.at(i));
    }

    m_linePath = linePath;

    QPainterPathStroker stroker;
    // QPainter::drawLine does not respect join styles, for example BevelJoin becomes MiterJoin.
    // This is why we are prepared for the "worst case" scenario, i.e. use always MiterJoin and
    // multiply line width with square root of two when defining shape and bounding rectangle.
    stroker.setWidth(m_linePen.width() * 1.42);
    stroker.setJoinStyle(Qt::MiterJoin);
    stroker.setCapStyle(Qt::SquareCap);
    stroker.setMiterLimit(m_linePen.miterLimit());

    prepareGeometryChange();

    m_path = stroker.createStroke(linePath);
    m_rect = m_path.boundingRect();

    setPos(origin());
}

void LineChartItem::handleUpdated()
{
    setVisible(m_series->isVisible());
    setOpacity(m_series->opacity());
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    update();
}

void LineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->save();
    painter->setPen(m_linePen);
    painter->setBrush(m_linePen.color());
    painter->setClipRect(clipRect());

    if (m_pointsVisible) {
        painter->drawPath(m_linePath);
    } else {
        for (int i(1); i < m_points.size(); i++)
            painter->drawLine(m_points.at(i - 1), m_points.at(i));
    }
    painter->restore();
}

void LineChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit XYChart::clicked(calculateDomainPoint(event->pos()));
    QGraphicsItem::mousePressEvent(event);
}

void LineChartItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit XYChart::hovered(calculateDomainPoint(event->pos()), true);
    event->accept();
//    QGraphicsItem::hoverEnterEvent(event);
}

void LineChartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit XYChart::hovered(calculateDomainPoint(event->pos()), false);
    event->accept();
//    QGraphicsItem::hoverEnterEvent(event);
}

#include "moc_linechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
