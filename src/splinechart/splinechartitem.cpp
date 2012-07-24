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

#include "splinechartitem_p.h"
#include "qsplineseries_p.h"
#include "chartpresenter_p.h"
#include "splineanimation_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

SplineChartItem::SplineChartItem(QSplineSeries *series, ChartPresenter *presenter) :
    XYChart(series, presenter),
    QGraphicsItem(presenter ? presenter->rootItem() : 0),
    m_series(series),
    m_pointsVisible(false),
    m_animation(0)
{
    setZValue(ChartPresenter::LineChartZValue);
    QObject::connect(m_series->d_func(),SIGNAL(updated()),this,SLOT(handleUpdated()));
    QObject::connect(series, SIGNAL(visibleChanged()), this, SLOT(handleUpdated()));
    handleUpdated();
}

QRectF SplineChartItem::boundingRect() const
{
    return m_rect;
}

QPainterPath SplineChartItem::shape() const
{
    return m_path;
}

void SplineChartItem::setAnimation(SplineAnimation* animation)
{
    m_animation=animation;
    XYChart::setAnimation(animation);
}

ChartAnimation* SplineChartItem::animation() const
{
    return m_animation;
}

void SplineChartItem::setControlGeometryPoints(QVector<QPointF>& points)
{
    m_controlPoints=points;
}

QVector<QPointF> SplineChartItem::controlGeometryPoints() const
{
    return m_controlPoints;
}

void SplineChartItem::updateChart(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints,int index)
{
    QVector<QPointF> controlPoints;

    if(newPoints.count()>=2) {
        controlPoints.resize(newPoints.count()*2-2);
    }

    for (int i = 0; i < newPoints.size() - 1; i++) {
        controlPoints[2*i] = calculateGeometryControlPoint(2 * i);
        controlPoints[2 * i + 1] = calculateGeometryControlPoint(2 * i + 1);
    }

    if (controlPoints.count()<2) {
        setGeometryPoints(newPoints);
        setControlGeometryPoints(controlPoints);
        updateGeometry();
        return;
    }

    if (m_animation) {
        m_animation->setup(oldPoints,newPoints,m_controlPoints,controlPoints,index);
        setGeometryPoints(newPoints);
        setDirty(false);
        presenter()->startAnimation(m_animation);
    }
    else {
        setGeometryPoints(newPoints);
        setControlGeometryPoints(controlPoints);
        updateGeometry();
    }
}

QPointF SplineChartItem::calculateGeometryControlPoint(int index) const
{
    return XYChart::calculateGeometryPoint(m_series->d_func()->controlPoint(index));
}

void SplineChartItem::updateGeometry()
{
    const QVector<QPointF> &points = geometryPoints();
    const QVector<QPointF> &controlPoints = controlGeometryPoints();

    if ((points.size()<2) || (controlPoints.size()<2)) {
    	prepareGeometryChange();
        m_path = QPainterPath();
        m_rect = QRect();
        return;
    }

    Q_ASSERT(points.count()*2-2 == controlPoints.count());

    QPainterPath splinePath(points.at(0));

    for (int i = 0; i < points.size() - 1; i++) {
        const QPointF& point = points.at(i + 1);
        splinePath.cubicTo(controlPoints[2*i],controlPoints[2 * i + 1],point);
    }

    prepareGeometryChange();
    m_path = splinePath;
    m_rect = splinePath.boundingRect();
    setPos(origin());
}

//handlers

void SplineChartItem::handleUpdated()
{
    setVisible(m_series->isVisible());
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    m_pointPen = m_series->pen();
    m_pointPen.setWidthF(2*m_pointPen.width());
    update();
}

//painter

void SplineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->save();
    painter->setClipRect(clipRect());
    painter->setPen(m_linePen);
    painter->drawPath(m_path);
    if (m_pointsVisible) {
        painter->setPen(m_pointPen);
        painter->drawPoints(geometryPoints());
    }
    painter->restore();
}

void SplineChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit XYChart::clicked(calculateDomainPoint(event->pos()));
}

#include "moc_splinechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
