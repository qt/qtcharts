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

LineChartItem::LineChartItem(QLineSeries* series,ChartPresenter *presenter):
    XYChart(series, presenter),
    QGraphicsItem(presenter ? presenter->rootItem() : 0),
    m_series(series),
    m_pointsVisible(false)
{
    setZValue(ChartPresenter::LineChartZValue);
    QObject::connect(series->d_func(),SIGNAL(updated()),this,SLOT(handleUpdated()));
    QObject::connect(series, SIGNAL(visibleChanged()), this, SLOT(handleUpdated()));
    handleUpdated();
}

QRectF LineChartItem::boundingRect() const
{
	return m_rect;
}

QPainterPath LineChartItem::shape() const
{
    // Increase the size of the path slightly to make mouse interactions more natural
    QPainterPathStroker s;
    s.setCapStyle(Qt::RoundCap);
    s.setJoinStyle(Qt::RoundJoin);
    qreal spacing = qMax(mouseEventMinWidth, (qreal) m_linePen.width());
    s.setWidth(spacing);
    return s.createStroke(m_path);
}

void LineChartItem::updateGeometry()
{
    const QVector<QPointF>& points = geometryPoints();

    if(points.size()==0)
    {
        prepareGeometryChange();
        m_path = QPainterPath();
        m_rect = QRect();
        return;
    }

    QPainterPath linePath(points.at(0));

    for(int i=1; i< points.size();i++) {
        linePath.lineTo(points.at(i));
    }

    prepareGeometryChange();

    m_path = linePath;

    // When defining bounding rectangle,
    // 1. take the line width into account (otherwise you will get drawing artifacts) and
    // 2. take the shape into account (otherwise you will not get mouse events through on border
    // areas).
    const qreal sqrtOf2 = 1.414214;
    const qreal spacing = qMax(mouseEventMinWidth / 2.0,
                               sqrtOf2 * (qreal) m_linePen.width() / 2.0);
    m_rect = m_path.boundingRect().adjusted(-spacing, -spacing, spacing, spacing);

    setPos(origin());
}

void LineChartItem::handleUpdated()
{
    setVisible(m_series->isVisible());
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    m_pointPen = m_series->pen();
    m_pointPen.setWidthF(2*m_pointPen.width());
    update();
}

void LineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->save();
    painter->setPen(m_linePen);
    painter->setClipRect(clipRect());
    // Draw lines
    const QVector<QPointF> &points = geometryPoints();
    for (int i(1); i < points.size();i++)
        painter->drawLine(points.at(i-1), points.at(i));
    // Draw points
    if (m_pointsVisible){
        painter->setPen(m_pointPen);
        painter->drawPoints(geometryPoints());
    }
    painter->restore();
}

void LineChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit XYChart::clicked(calculateDomainPoint(event->pos()));
    QGraphicsItem::mousePressEvent(event);
}

#include "moc_linechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
