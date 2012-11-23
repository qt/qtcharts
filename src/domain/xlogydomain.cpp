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

#include "xlogydomain_p.h"
#include "qabstractaxis_p.h"
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

XLogYDomain::XLogYDomain(QObject *parent)
    : AbstractDomain(parent),
      m_logMinY(0),
      m_logMaxY(1),
      m_logBaseY(10)
{
}

XLogYDomain::~XLogYDomain()
{
}

void XLogYDomain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    bool axisXChanged = false;
    bool axisYChanged = false;

    if (!qFuzzyIsNull(m_minX - minX) || !qFuzzyIsNull(m_maxX - maxX)) {
        m_minX = minX;
        m_maxX = maxX;
        axisXChanged = true;
        emit rangeHorizontalChanged(m_minX, m_maxX);
    }

    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
        m_minY = minY;
        m_maxY = maxY;
        axisYChanged = true;
        m_logMinY = log10(m_minY) / log10(m_logBaseY);
        m_logMaxY = log10(m_maxY) / log10(m_logBaseY);
        emit rangeVerticalChanged(m_minY, m_maxY);
    }

    if (axisXChanged || axisYChanged)
        emit updated();
}

void XLogYDomain::zoomIn(const QRectF &rect)
{
    qreal dx = spanX() / m_size.width();
    qreal maxX = m_maxX;
    qreal minX = m_minX;

    maxX = minX + dx * rect.right();
    minX = minX + dx * rect.left();

    qreal newLogMinY = m_logMaxY - rect.bottom() * (m_logMaxY - m_logMinY) / m_size.height();
    qreal newLogMaxY = m_logMaxY - rect.top() * (m_logMaxY - m_logMinY) / m_size.height();
    qreal minY = qPow(m_logBaseY, newLogMinY);
    qreal maxY = qPow(m_logBaseY, newLogMaxY);

    setRange(minX, maxX, minY, maxY);
}

void XLogYDomain::zoomOut(const QRectF &rect)
{
    qreal dx = spanX() / rect.width();
    qreal maxX = m_maxX;
    qreal minX = m_minX;

    minX = maxX - dx * rect.right();
    maxX = minX + dx * m_size.width();

    qreal ratioY = m_size.height()/rect.height();
    qreal newLogMinY = m_logMaxY - (m_logMaxY - m_logMinY) / ratioY;
    qreal newLogMaxY = m_logMaxY + (m_logMaxY - m_logMinY) / ratioY;
    qreal minY = qPow(m_logBaseY, newLogMinY);
    qreal maxY = qPow(m_logBaseY, newLogMaxY);

    setRange(minX, maxX, minY, maxY);
}

void XLogYDomain::move(qreal dx, qreal dy)
{
    qreal x = spanX() / m_size.width();
    qreal maxX = m_maxX;
    qreal minX = m_minX;

    if (dx != 0) {
        minX = minX + x * dx;
        maxX = maxX + x * dx;
    }

    qreal stepY = dy * qAbs(m_logMaxY - m_logMinY) / m_size.height();
    qreal minY = qPow(m_logBaseY, m_logMinY + stepY);
    qreal maxY = qPow(m_logBaseY, m_logMaxY + stepY);

    setRange(minX, maxX, minY, maxY);
}

QPointF XLogYDomain::calculateGeometryPoint(const QPointF &point) const
{
    const qreal leftEdge = m_logMinY < m_logMaxY ? m_logMinY : m_logMaxY;
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / qAbs(m_logMaxY - m_logMinY);

    qreal x = (point.x() - m_minX) * deltaX;
    qreal y = (log10(point.y()) / log10(m_logBaseY)) * -deltaY - leftEdge * -deltaY + m_size.height();
    return QPointF(x, y);
}

QVector<QPointF> XLogYDomain::calculateGeometryPoints(const QList<QPointF>& vector) const
{
    const qreal leftEdge = m_logMinY < m_logMaxY ? m_logMinY : m_logMaxY;
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / qAbs(m_logMaxY - m_logMinY);

    QVector<QPointF> result;
    result.resize(vector.count());

    for (int i = 0; i < vector.count(); ++i) {
        qreal x = (vector[i].x() - m_minX) * deltaX;
        qreal y = (log10(vector[i].y()) / log10(m_logBaseY)) * -deltaY - leftEdge * -deltaY + m_size.height();
        result[i].setX(x);
        result[i].setY(y);
    }
    return result;
}

QPointF XLogYDomain::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / (m_maxY - m_minY);
    qreal x = point.x() / deltaX + m_minX;
    qreal y = (point.y() - m_size.height()) / (-deltaY) + m_minY;
    return QPointF(x, y);
}

// operators

bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator== (const XLogYDomain &domain1, const XLogYDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX) &&
            qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY) &&
            qFuzzyIsNull(domain1.m_minX - domain2.m_minX) &&
            qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator!= (const XLogYDomain &domain1, const XLogYDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug QTCOMMERCIALCHART_AUTOTEST_EXPORT operator<<(QDebug dbg, const XLogYDomain &domain)
{
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
    return dbg.maybeSpace();
}

#include "moc_xlogydomain_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
