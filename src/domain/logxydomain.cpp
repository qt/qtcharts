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

#include "logxydomain_p.h"
#include "qabstractaxis_p.h"
#include "qlogvalueaxis.h"
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

LogXYDomain::LogXYDomain(QObject *parent)
    : AbstractDomain(parent),
      m_logLeftX(0),
      m_logRightX(1),
      m_logBaseX(10)
{
}

LogXYDomain::~LogXYDomain()
{
}

void LogXYDomain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    bool axisXChanged = false;
    bool axisYChanged = false;

    if (!qFuzzyCompare(m_minX, minX) || !qFuzzyCompare(m_maxX, maxX)) {
        m_minX = minX;
        m_maxX = maxX;
        axisXChanged = true;
        qreal logMinX = log10(m_minX) / log10(m_logBaseX);
        qreal logMaxX = log10(m_maxX) / log10(m_logBaseX);
        m_logLeftX = logMinX < logMaxX ? logMinX : logMaxX;
        m_logRightX = logMinX > logMaxX ? logMinX : logMaxX;
        if(!m_signalsBlocked)
            emit rangeHorizontalChanged(m_minX, m_maxX);
    }

    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
        m_minY = minY;
        m_maxY = maxY;
        axisYChanged = true;
        if(!m_signalsBlocked)
            emit rangeVerticalChanged(m_minY, m_maxY);
    }

    if (axisXChanged || axisYChanged)
        emit updated();
}

void LogXYDomain::zoomIn(const QRectF &rect)
{
    qreal logLeftX = rect.left() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal logRightX = rect.right() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRightX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal dy = spanY() / m_size.height();
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    minY = maxY - dy * rect.bottom();
    maxY = maxY - dy * rect.top();

    setRange(minX, maxX, minY, maxY);
}

void LogXYDomain::zoomOut(const QRectF &rect)
{
    const qreal factorX = m_size.width() / rect.width();

    qreal logLeftX = m_logLeftX + (m_logRightX - m_logLeftX) / 2 * (1 - factorX);
    qreal logRIghtX = m_logLeftX + (m_logRightX - m_logLeftX) / 2 * (1 + factorX);
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRIghtX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal dy = spanY() / rect.height();
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    maxY = minY + dy * rect.bottom();
    minY = maxY - dy * m_size.height();

    setRange(minX, maxX, minY, maxY);
}

void LogXYDomain::move(qreal dx, qreal dy)
{
    qreal stepX = dx * (m_logRightX - m_logLeftX) / m_size.width();
    qreal leftX = qPow(m_logBaseX, m_logLeftX + stepX);
    qreal rightX = qPow(m_logBaseX, m_logRightX + stepX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal y = spanY() / m_size.height();
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    if (dy != 0) {
        minY = minY + y * dy;
        maxY = maxY + y * dy;
    }
    setRange(minX, maxX, minY, maxY);
}

QPointF LogXYDomain::calculateGeometryPoint(const QPointF &point, bool &ok) const
{

    if (point.x() > 0) {
        const qreal deltaX = m_size.width() / (m_logRightX - m_logLeftX);
        const qreal deltaY = m_size.height() / (m_maxY - m_minY);

        qreal x = (log10(point.x()) / log10(m_logBaseX)) * deltaX - m_logLeftX * deltaX;
        qreal y = (point.y() - m_minY) * -deltaY + m_size.height();
        ok = true;
        return QPointF(x, y);
    } else {
        qWarning() << "Logarithm of negative value is undefined. Empty layout returned";
        ok = false;
        return QPointF();
    }
}

QVector<QPointF> LogXYDomain::calculateGeometryPoints(const QList<QPointF>& vector) const
{
    const qreal deltaX = m_size.width() / (m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / (m_maxY - m_minY);

    QVector<QPointF> result;
    result.resize(vector.count());

    for (int i = 0; i < vector.count(); ++i) {
        if (vector[i].x() > 0) {
            qreal x = (log10(vector[i].x()) / log10(m_logBaseX)) * deltaX - m_logLeftX * deltaX;
            qreal y = (vector[i].y() - m_minY) * -deltaY + m_size.height();
            result[i].setX(x);
            result[i].setY(y);
        } else {
            qWarning() << "Logarithm of negative value is undefined. Empty layout returned";
            return QVector<QPointF>();
        }
    }
    return result;
}

QPointF LogXYDomain::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width() / (m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / (m_maxY - m_minY);
    qreal x = qPow(m_logBaseX, m_logLeftX + point.x() / deltaX);
    qreal y = (point.y() - m_size.height()) / (-deltaY) + m_minY;
    return QPointF(x, y);
}

bool LogXYDomain::attachAxis(QAbstractAxis* axis)
{
    AbstractDomain::attachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if(logAxis && logAxis->orientation()==Qt::Horizontal) {
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));
        handleHorizontalAxisBaseChanged(logAxis->base());
    }

    return true;
}

bool LogXYDomain::detachAxis(QAbstractAxis* axis)
{
    AbstractDomain::detachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if(logAxis && logAxis->orientation()==Qt::Horizontal)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));

    return true;
}

void LogXYDomain::handleHorizontalAxisBaseChanged(qreal baseX)
{
    m_logBaseX = baseX;
    qreal logMinX = log10(m_minX) / log10(m_logBaseX);
    qreal logMaxX = log10(m_maxX) / log10(m_logBaseX);
    m_logLeftX = logMinX < logMaxX ? logMinX : logMaxX;
    m_logRightX = logMinX > logMaxX ? logMinX : logMaxX;
    emit updated();
}

// operators

bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator== (const LogXYDomain &domain1, const LogXYDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX) &&
            qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY) &&
            qFuzzyIsNull(domain1.m_minX - domain2.m_minX) &&
            qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator!= (const LogXYDomain &domain1, const LogXYDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug QTCOMMERCIALCHART_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXYDomain &domain)
{
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
    return dbg.maybeSpace();
}

#include "moc_logxydomain_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
