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

#include "boxwhiskers_p.h"
#include <QPainter>
#include <QWidget>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BoxWhiskers::BoxWhiskers(QBoxSet *set, AbstractDomain *domain, QGraphicsObject *parent) :
    QGraphicsObject(parent),
    m_boxSet(set),
    m_domain(domain)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButtonMask);
}

BoxWhiskers::~BoxWhiskers()
{
}

void BoxWhiskers::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    emit clicked(m_boxSet);
}

void BoxWhiskers::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    emit hovered(true, m_boxSet);
}

void BoxWhiskers::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    emit hovered(false, m_boxSet);
}

void BoxWhiskers::setBrush(const QBrush &brush)
{
    m_brush = brush;
    update();
}

void BoxWhiskers::setPen(const QPen &pen)
{
    m_pen = pen;
    update();
}

void BoxWhiskers::setLayout(const BoxWhiskersData &data)
{
    m_data = data;

    updateGeometry(m_domain);
    update();
}

QSizeF BoxWhiskers::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    return QSizeF();
}

void BoxWhiskers::setGeometry(const QRectF &rect)
{
    Q_UNUSED(rect)
}

QRectF BoxWhiskers::boundingRect() const
{
    return m_boundingRect;
}

void BoxWhiskers::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->setClipRect(parentItem()->boundingRect());
    painter->drawPath(m_boxPath);
}

void BoxWhiskers::updateGeometry(AbstractDomain *domain)
{
    m_domain = domain;

    prepareGeometryChange();

    QPainterPath path;
    m_boxPath = path;
    m_boundingRect = m_boxPath.boundingRect();

    qreal columnWidth = 1.0 / m_data.m_seriesCount;
    qreal left = 0.25 * columnWidth + columnWidth * m_data.m_seriesIndex + m_data.m_index - 0.5;
    qreal barWidth = columnWidth / 2.0;

    QPointF geometryPoint = m_domain->calculateGeometryPoint(QPointF(left, m_data.m_upperExtreme), m_validData);
    if (!m_validData)
        return;
    qreal geometryLeft = geometryPoint.x();
    qreal geometryUpperExtreme = geometryPoint.y();
    geometryPoint = m_domain->calculateGeometryPoint(QPointF(left + barWidth, m_data.m_upperQuartile), m_validData);
    if (!m_validData)
        return;
    qreal geometryRight = geometryPoint.x();
    qreal geometryUpperQuartile = geometryPoint.y();
    geometryPoint = m_domain->calculateGeometryPoint(QPointF(left, m_data.m_lowerQuartile), m_validData);
    if (!m_validData)
        return;
    qreal geometryLowerQuartile = geometryPoint.y();
    geometryPoint = m_domain->calculateGeometryPoint(QPointF(left, m_data.m_lowerExtreme), m_validData);
    if (!m_validData)
        return;
    qreal geometryLowerExtreme = geometryPoint.y();
    geometryPoint = m_domain->calculateGeometryPoint(QPointF(left, m_data.m_median), m_validData);
    if (!m_validData)
        return;
    qreal geometryMedian = geometryPoint.y();

    // Upper whisker
    path.moveTo(geometryLeft, geometryUpperExtreme);
    path.lineTo(geometryRight, geometryUpperExtreme);
    path.moveTo((geometryLeft + geometryRight) / 2.0, geometryUpperExtreme);
    path.lineTo((geometryLeft + geometryRight) / 2.0, geometryUpperQuartile);

    // Middle Box
    path.addRect(geometryLeft, geometryUpperQuartile, geometryRight - geometryLeft, geometryLowerQuartile - geometryUpperQuartile);

    // Median line
    path.moveTo(geometryLeft, geometryMedian);
    path.lineTo(geometryRight, geometryMedian);

    // Lower whisker
    path.moveTo(geometryLeft, geometryLowerExtreme);
    path.lineTo(geometryRight, geometryLowerExtreme);
    path.moveTo((geometryLeft + geometryRight) / 2.0, geometryLowerQuartile);
    path.lineTo((geometryLeft + geometryRight) / 2.0, geometryLowerExtreme);

    path.closeSubpath();

    m_boxPath = path;
    m_boundingRect = m_boxPath.boundingRect();

    qreal extra = (m_pen.width() / 2.0);
    m_boundingRect.adjust(-extra, -extra, extra, extra);
}

#include "moc_boxwhiskers_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
