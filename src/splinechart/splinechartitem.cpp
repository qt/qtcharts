/****************************************************************************
 **
 ** Copyright (C) 2013 Digia Plc
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
#include "abstractdomain_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

SplineChartItem::SplineChartItem(QSplineSeries *series, QGraphicsItem* item)
    : XYChart(series,item),
      m_series(series),
      m_pointsVisible(false),
      m_animation(0)
{
    setAcceptHoverEvents(true);
    setZValue(ChartPresenter::SplineChartZValue);
    QObject::connect(m_series->d_func(), SIGNAL(updated()), this, SLOT(handleUpdated()));
    QObject::connect(series, SIGNAL(visibleChanged()), this, SLOT(handleUpdated()));
    QObject::connect(series, SIGNAL(opacityChanged()), this, SLOT(handleUpdated()));
    handleUpdated();
}

QRectF SplineChartItem::boundingRect() const
{
    return m_rect;
}

QPainterPath SplineChartItem::shape() const
{
    QPainterPathStroker stroker;
    return stroker.createStroke(m_path);
}

void SplineChartItem::setAnimation(SplineAnimation *animation)
{
    m_animation = animation;
    XYChart::setAnimation(animation);
}

ChartAnimation *SplineChartItem::animation() const
{
    return m_animation;
}

void SplineChartItem::setControlGeometryPoints(QVector<QPointF>& points)
{
    m_controlPoints = points;
}

QVector<QPointF> SplineChartItem::controlGeometryPoints() const
{
    return m_controlPoints;
}

void SplineChartItem::updateChart(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, int index)
{
    QVector<QPointF> controlPoints;
    if (newPoints.count() >= 2)
        controlPoints = calculateControlPoints(newPoints);

    if (m_animation)
        m_animation->setup(oldPoints, newPoints, m_controlPoints, controlPoints, index);

    m_points = newPoints;
    m_controlPoints = controlPoints;
    setDirty(false);

    if (m_animation)
        presenter()->startAnimation(m_animation);
    else
        updateGeometry();
}

void SplineChartItem::updateGeometry()
{
    const QVector<QPointF> &points = m_points;
    const QVector<QPointF> &controlPoints = m_controlPoints;

    if ((points.size() < 2) || (controlPoints.size() < 2)) {
        prepareGeometryChange();
        m_path = QPainterPath();
        m_rect = QRect();
        return;
    }

    Q_ASSERT(points.count() * 2 - 2 == controlPoints.count());

    QPainterPath splinePath(points.at(0));

    for (int i = 0; i < points.size() - 1; i++) {
        const QPointF &point = points.at(i + 1);
        splinePath.cubicTo(controlPoints[2 * i], controlPoints[2 * i + 1], point);
    }

    prepareGeometryChange();
    //    QPainterPathStroker stroker;
    //    stroker.setWidth(m_linePen.width() / 2.0);
    //    m_path = stroker.createStroke(splinePath);
    m_path = splinePath;
    m_rect = splinePath.boundingRect();

}

/*!
  Calculates control points which are needed by QPainterPath.cubicTo function to draw the cubic Bezier cureve between two points.
  */
QVector<QPointF> SplineChartItem::calculateControlPoints(const QVector<QPointF> &points)
{
    QVector<QPointF> controlPoints;
    controlPoints.resize(points.count() * 2 - 2);

    int n = points.count() - 1;

    if (n == 1) {
        //for n==1
        controlPoints[0].setX((2 * points[0].x() + points[1].x()) / 3);
        controlPoints[0].setY((2 * points[0].y() + points[1].y()) / 3);
        controlPoints[1].setX(2 * controlPoints[0].x() - points[0].x());
        controlPoints[1].setY(2 * controlPoints[0].y() - points[0].y());
        return controlPoints;
    }

    // Calculate first Bezier control points
    // Set of equations for P0 to Pn points.
    //
    //  |   2   1   0   0   ... 0   0   0   ... 0   0   0   |   |   P1_1    |   |   P0 + 2 * P1             |
    //  |   1   4   1   0   ... 0   0   0   ... 0   0   0   |   |   P1_2    |   |   4 * P1 + 2 * P2         |
    //  |   0   1   4   1   ... 0   0   0   ... 0   0   0   |   |   P1_3    |   |   4 * P2 + 2 * P3         |
    //  |   .   .   .   .   .   .   .   .   .   .   .   .   |   |   ...     |   |   ...                     |
    //  |   0   0   0   0   ... 1   4   1   ... 0   0   0   | * |   P1_i    | = |   4 * P(i-1) + 2 * Pi     |
    //  |   .   .   .   .   .   .   .   .   .   .   .   .   |   |   ...     |   |   ...                     |
    //  |   0   0   0   0   0   0   0   0   ... 1   4   1   |   |   P1_(n-1)|   |   4 * P(n-2) + 2 * P(n-1) |
    //  |   0   0   0   0   0   0   0   0   ... 0   2   7   |   |   P1_n    |   |   8 * P(n-1) + Pn         |
    //
    QVector<qreal> vector;
    vector.resize(n);

    vector[0] = points[0].x() + 2 * points[1].x();


    for (int i = 1; i < n - 1; ++i)
        vector[i] = 4 * points[i].x() + 2 * points[i + 1].x();

    vector[n - 1] = (8 * points[n - 1].x() + points[n].x()) / 2.0;

    QVector<qreal> xControl = firstControlPoints(vector);

    vector[0] = points[0].y() + 2 * points[1].y();

    for (int i = 1; i < n - 1; ++i)
        vector[i] = 4 * points[i].y() + 2 * points[i + 1].y();

    vector[n - 1] = (8 * points[n - 1].y() + points[n].y()) / 2.0;

    QVector<qreal> yControl = firstControlPoints(vector);

    for (int i = 0, j = 0; i < n; ++i, ++j) {

        controlPoints[j].setX(xControl[i]);
        controlPoints[j].setY(yControl[i]);

        j++;

        if (i < n - 1) {
            controlPoints[j].setX(2 * points[i + 1].x() - xControl[i + 1]);
            controlPoints[j].setY(2 * points[i + 1].y() - yControl[i + 1]);
        } else {
            controlPoints[j].setX((points[n].x() + xControl[n - 1]) / 2);
            controlPoints[j].setY((points[n].y() + yControl[n - 1]) / 2);
        }
    }
    return controlPoints;
}

QVector<qreal> SplineChartItem::firstControlPoints(const QVector<qreal>& vector)
{
    QVector<qreal> result;

    int count = vector.count();
    result.resize(count);
    result[0] = vector[0] / 2.0;

    QVector<qreal> temp;
    temp.resize(count);
    temp[0] = 0;

    qreal b = 2.0;

    for (int i = 1; i < count; i++) {
        temp[i] = 1 / b;
        b = (i < count - 1 ? 4.0 : 3.5) - temp[i];
        result[i] = (vector[i] - result[i - 1]) / b;
    }

    for (int i = 1; i < count; i++)
        result[count - i - 1] -= temp[count - i] * result[count - i];

    return result;
}

//handlers

void SplineChartItem::handleUpdated()
{
    setVisible(m_series->isVisible());
    setOpacity(m_series->opacity());
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    m_pointPen = m_series->pen();
    m_pointPen.setWidthF(2 * m_pointPen.width());
    update();
}

//painter

void SplineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->save();
    painter->setClipRect(QRectF(QPointF(0,0),domain()->size()));
    painter->setPen(m_linePen);
    //    painter->setBrush(m_linePen.color());

    painter->drawPath(m_path);
    if (m_pointsVisible) {
        painter->setPen(m_pointPen);
        painter->drawPoints(geometryPoints());
    }
    painter->restore();
}

void SplineChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit XYChart::clicked(domain()->calculateDomainPoint(event->pos()));
    QGraphicsItem::mousePressEvent(event);
}

void SplineChartItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit XYChart::hovered(domain()->calculateDomainPoint(event->pos()), true);
    QGraphicsItem::hoverEnterEvent(event);
}

void SplineChartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit XYChart::hovered(domain()->calculateDomainPoint(event->pos()), false);
    QGraphicsItem::hoverLeaveEvent(event);
}

#include "moc_splinechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
