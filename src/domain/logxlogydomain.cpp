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

#include "logxlogydomain_p.h"
#include "qabstractaxis_p.h"
#include "qlogvalueaxis.h"
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LogXLogYDomain::LogXLogYDomain(QObject *parent)
    : AbstractDomain(parent),
      m_logMinX(0),
      m_logMaxX(1),
      m_logBaseX(10),
      m_logMinY(0),
      m_logMaxY(1),
      m_logBaseY(10)
{
}

LogXLogYDomain::~LogXLogYDomain()
{
}

void LogXLogYDomain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    bool axisXChanged = false;
    bool axisYChanged = false;

    if (!qFuzzyIsNull(m_minX - minX) || !qFuzzyIsNull(m_maxX - maxX)) {
        m_minX = minX;
        m_maxX = maxX;
        axisXChanged = true;
        m_logMinX = log10(m_minX) / log10(m_logBaseX);
        m_logMaxX = log10(m_maxX) / log10(m_logBaseX);
        if(!m_signalsBlocked)
        emit rangeHorizontalChanged(m_minX, m_maxX);
    }

    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
        m_minY = minY;
        m_maxY = maxY;
        axisYChanged = true;
        m_logMinY = log10(m_minY) / log10(m_logBaseY);
        m_logMaxY = log10(m_maxY) / log10(m_logBaseY);
        if(!m_signalsBlocked)
        emit rangeVerticalChanged(m_minY, m_maxY);
    }

    if (axisXChanged || axisYChanged)
        emit updated();
}

void LogXLogYDomain::zoomIn(const QRectF &rect)
{
    qreal newLogMinX = rect.left() * (m_logMaxX - m_logMinX) / m_size.width() + m_logMinX;
    qreal newLogMaxX = rect.right() * (m_logMaxX - m_logMinX) / m_size.width() + m_logMinX;
    qreal minX = qPow(m_logBaseX, newLogMinX);
    qreal maxX = qPow(m_logBaseX, newLogMaxX);

    qreal newLogMinY = m_logMaxY - rect.bottom() * (m_logMaxY - m_logMinY) / m_size.height();
    qreal newLogMaxY = m_logMaxY - rect.top() * (m_logMaxY - m_logMinY) / m_size.height();
    qreal minY = qPow(m_logBaseY, newLogMinY);
    qreal maxY = qPow(m_logBaseY, newLogMaxY);

    setRange(minX, maxX, minY, maxY);
}

void LogXLogYDomain::zoomOut(const QRectF &rect)
{
    qreal ratioX = m_size.width()/rect.width();
    qreal newLogMinX = m_logMinX - (m_logMaxX - m_logMinX) / ratioX;
    qreal newLogMaxX = m_logMaxX + (m_logMaxX - m_logMinX) / ratioX;
    qreal minX = qPow(m_logBaseX, newLogMinX);
    qreal maxX = qPow(m_logBaseX, newLogMaxX);

    qreal ratioY = m_size.height()/rect.height();
    qreal newLogMinY = m_logMaxY - (m_logMaxY - m_logMinY) / ratioY;
    qreal newLogMaxY = m_logMaxY + (m_logMaxY - m_logMinY) / ratioY;
    qreal minY = qPow(m_logBaseY, newLogMinY);
    qreal maxY = qPow(m_logBaseY, newLogMaxY);

    setRange(minX, maxX, minY, maxY);
}

void LogXLogYDomain::move(qreal dx, qreal dy)
{
    qreal stepX = dx * qAbs(m_logMaxX - m_logMinX) / m_size.width();
    qreal minX = qPow(m_logBaseX, m_logMinX + stepX);
    qreal maxX = qPow(m_logBaseX, m_logMaxX + stepX);

    qreal stepY = dy * qAbs(m_logMaxY - m_logMinY) / m_size.height();
    qreal minY = qPow(m_logBaseY, m_logMinY + stepY);
    qreal maxY = qPow(m_logBaseY, m_logMaxY + stepY);

    setRange(minX, maxX, minY, maxY);
}

QPointF LogXLogYDomain::calculateGeometryPoint(const QPointF &point) const
{
    const qreal leftEdgeX= m_logMinX < m_logMaxX ? m_logMinX : m_logMaxX;
    const qreal leftEdgeY = m_logMinY < m_logMaxY ? m_logMinY : m_logMaxY;
    const qreal deltaX = m_size.width() / qAbs(m_logMaxX - m_logMinX);
    const qreal deltaY = m_size.height() / qAbs(m_logMaxY - m_logMinY);
    qreal x = (log10(point.x()) / log10(m_logBaseX)) * deltaX - leftEdgeX * deltaX;
    qreal y = (log10(point.y()) / log10(m_logBaseY)) * -deltaY - leftEdgeY * -deltaY + m_size.height();
    return QPointF(x, y);
}

QVector<QPointF> LogXLogYDomain::calculateGeometryPoints(const QList<QPointF>& vector) const
{
    const qreal leftEdgeX= m_logMinX < m_logMaxX ? m_logMinX : m_logMaxX;
    const qreal leftEdgeY = m_logMinY < m_logMaxY ? m_logMinY : m_logMaxY;
    const qreal deltaX = m_size.width() / qAbs(m_logMaxX - m_logMinX);
    const qreal deltaY = m_size.height() / qAbs(m_logMaxY - m_logMinY);

    QVector<QPointF> result;
    result.resize(vector.count());

    for (int i = 0; i < vector.count(); ++i) {
        qreal x = (log10(vector[i].x()) / log10(m_logBaseX)) * deltaX - leftEdgeX * deltaX;
        qreal y = (log10(vector[i].y()) / log10(m_logBaseY)) * -deltaY - leftEdgeY * -deltaY + m_size.height();
        result[i].setX(x);
        result[i].setY(y);
    }
    return result;
}

QPointF LogXLogYDomain::calculateDomainPoint(const QPointF &point) const
{
    const qreal leftEdgeX= m_logMinX < m_logMaxX ? m_logMinX : m_logMaxX;
    const qreal leftEdgeY = m_logMinY < m_logMaxY ? m_logMinY : m_logMaxY;
    const qreal deltaX = m_size.width() / qAbs(m_logMaxX - m_logMinX);
    const qreal deltaY = m_size.height() / qAbs(m_logMaxY - m_logMinY);
    qreal x = qPow(m_logBaseX, leftEdgeX + point.x() / deltaX);
    qreal y = qPow(m_logBaseY, leftEdgeY + (m_size.height() - point.y()) / deltaY);
    return QPointF(x, y);
}

bool LogXLogYDomain::attachAxis(QAbstractAxis* axis)
{
    AbstractDomain::attachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if(logAxis && logAxis->orientation()==Qt::Vertical)
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));

    if(logAxis && logAxis->orientation()==Qt::Horizontal)
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));

    return true;
}

bool LogXLogYDomain::detachAxis(QAbstractAxis* axis)
{
    AbstractDomain::detachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if(logAxis && logAxis->orientation()==Qt::Vertical)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));

    if(logAxis && logAxis->orientation()==Qt::Horizontal)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));

    return true;
}

void LogXLogYDomain::handleVerticalAxisBaseChanged(qreal baseY)
{
    m_logBaseY = baseY;
    m_logMinY = log10(m_minY) / log10(m_logBaseY);
    m_logMaxY = log10(m_maxY) / log10(m_logBaseY);
}

void LogXLogYDomain::handleHorizontalAxisBaseChanged(qreal baseX)
{
    m_logBaseX = baseX;
    m_logMinX = log10(m_minX) / log10(m_logBaseX);
    m_logMaxX = log10(m_maxX) / log10(m_logBaseX);
}

// operators

bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator== (const LogXLogYDomain &domain1, const LogXLogYDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX) &&
            qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY) &&
            qFuzzyIsNull(domain1.m_minX - domain2.m_minX) &&
            qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator!= (const LogXLogYDomain &domain1, const LogXLogYDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug QTCOMMERCIALCHART_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXLogYDomain &domain)
{
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
    return dbg.maybeSpace();
}

#include "moc_logxlogydomain_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
