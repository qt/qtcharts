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

//TODO: optimize : remove points which are not visible

LineChartItem::LineChartItem(QLineSeries* series,ChartPresenter *presenter):XYChart(series,presenter),
QGraphicsItem(presenter ? presenter->rootItem() : 0),
m_series(series),
m_pointsVisible(false)
{
    setZValue(ChartPresenter::LineChartZValue);
    QObject::connect(series->d_func(),SIGNAL(updated()),this,SLOT(handleUpdated()));
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
    m_rect = linePath.boundingRect();
    setPos(origin());
}

void LineChartItem::handleUpdated()
{
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    m_pointPen = m_series->pen();
    m_pointPen.setWidthF(2*m_pointPen.width());
    update();
}

//painter

void LineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->save();
    painter->setPen(m_linePen);
    painter->setClipRect(clipRect());
    painter->drawPath(m_path);
    if(m_pointsVisible){
    	painter->setPen(m_pointPen);
    	painter->drawPoints(geometryPoints());
    }
    painter->restore();
}

void LineChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit XYChart::clicked(calculateDomainPoint(event->pos()));
}

#include "moc_linechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
