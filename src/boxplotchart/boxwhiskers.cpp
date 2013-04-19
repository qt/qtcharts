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

#include "boxwhiskers_p.h"
#include <QPainter>
#include <QDebug>
#include <QWidget>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BoxWhiskers::BoxWhiskers(AbstractDomain *domain, QGraphicsObject *parent) :
    QGraphicsObject(parent),
    m_domain(domain)
{
    //qDebug() << "BoxWhiskers::BoxWhiskers()";
}

BoxWhiskers::~BoxWhiskers()
{
    //qDebug() << "BoxWhiskers::~BoxWhiskers()";
}

void BoxWhiskers::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)

    qDebug() << "BoxWhiskers::mousePressEvent";
}

void BoxWhiskers::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)

    qDebug() << "BoxWhiskers::hoverEnterEvent";
}

void BoxWhiskers::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)

    qDebug() << "BoxWhiskers::hoverLeaveEvent";
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

    updateGeometry();
    update();
}


QSizeF BoxWhiskers::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    //Q_UNUSED(which)
    Q_UNUSED(constraint)

    qDebug() << "BoxWhiskers::sizeHint, which = " << which;

    return QSizeF();
}

void BoxWhiskers::setGeometry(const QRectF &rect) // TODO: Unused?
{
    Q_UNUSED(rect)

    qDebug() << "BoxWhiskers::setGeometry";
}

void BoxWhiskers::setDomainSize(const QSizeF &size)
{
    m_domainSize = size;

    updateBoundingRect();
}

QRectF BoxWhiskers::boundingRect() const
{
    return m_boundingRect;
}

void BoxWhiskers::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    //Q_UNUSED(painter)

    //painter->save();
    //painter->setClipRect(parentItem()->boundingRect());
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    qreal spanY = m_data.m_maxY - m_data.m_minY;
    //painter->setClipRect(parentItem()->boundingRect());
    painter->scale(m_domainSize.width() / m_data.m_boxItems, m_domainSize.height() / spanY);
    painter->drawPath(m_boxPath);
    //painter->restore();
}

void BoxWhiskers::updateGeometry()
{
    prepareGeometryChange();

    QPainterPath path;

    qreal columnWidth = 1.0 / m_data.m_seriesCount;
    qreal left = 0.25 * columnWidth + columnWidth * m_data.m_seriesIndex;
    qreal right = 0.75 * columnWidth + columnWidth * m_data.m_seriesIndex;
    qreal middle = 0.5 * columnWidth + columnWidth * m_data.m_seriesIndex;

    //whisker = 0.35 0.75

    // Upper whisker
    path.moveTo(left + m_data.m_index, m_data.m_maxY - m_data.m_upperExtreme);
    path.lineTo(right + m_data.m_index, m_data.m_maxY - m_data.m_upperExtreme);
    path.moveTo(middle + m_data.m_index, m_data.m_maxY - m_data.m_upperExtreme);
    path.lineTo(middle + m_data.m_index, m_data.m_maxY - m_data.m_upperQuartile);
    path.closeSubpath();

    // Middle Box
    path.addRect(left + m_data.m_index, m_data.m_maxY - m_data.m_upperQuartile,
                 0.5 * columnWidth, m_data.m_upperQuartile - m_data.m_lowerQuartile);

    // Median/mean line
    path.moveTo(left + m_data.m_index, m_data.m_maxY - m_data.m_median);
    path.lineTo(right + m_data.m_index, m_data.m_maxY - m_data.m_median);

    // Lower whisker
    path.moveTo(left + m_data.m_index, m_data.m_maxY - m_data.m_lowerExtreme);
    path.lineTo(right + m_data.m_index, m_data.m_maxY - m_data.m_lowerExtreme);
    path.moveTo(middle + m_data.m_index, m_data.m_maxY - m_data.m_lowerExtreme);
    path.lineTo(middle + m_data.m_index, m_data.m_maxY - m_data.m_lowerQuartile);
    path.closeSubpath();

    m_boxPath = path;

    updateBoundingRect();

//    qreal scaleY = m_domainSize.height() / (m_data.m_maxY - m_data.m_minY);
//    qreal scaleX = m_domainSize.width() / m_data.m_boxItems;
//    QRectF br = path.boundingRect();
//    m_boundingRect = QRectF( br.x() * scaleX, br.y() * scaleY, br.width() * scaleX, br.height() * scaleY);

    if (m_data.m_index == 5) {
        //qDebug() << "myValue = " << myValue;
        //qDebug() << "m_data.m_upperExtreme" << m_data.m_upperExtreme;
        //qDebug() << "m_boundingRect = " << m_boundingRect;
//        qDebug() << "x = " << m_boundingRect.x() << ", y = " << m_boundingRect.y() << ", width = "
//                 << m_boundingRect.width() << ", height = " << m_boundingRect.height();
    }
}

void BoxWhiskers::updateBoundingRect()
{
    qreal scaleY = m_domainSize.height() / (m_data.m_maxY - m_data.m_minY);
    qreal scaleX = m_domainSize.width() / m_data.m_boxItems;
    QRectF br = m_boxPath.boundingRect();
    m_boundingRect = QRectF( br.x() * scaleX, br.y() * scaleY, br.width() * scaleX, br.height() * scaleY);
}

#include "moc_boxwhiskers_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
