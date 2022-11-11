// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/logxydomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCharts/QLogValueAxis>
#include <QtCore/QtMath>
#include <cmath>

QT_BEGIN_NAMESPACE

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

    adjustLogDomainRanges(minX, maxX);

    if (!qFuzzyCompare(m_minX, minX) || !qFuzzyCompare(m_maxX, maxX)) {
        m_minX = minX;
        m_maxX = maxX;
        axisXChanged = true;
        qreal logMinX = qLn(m_minX) / qLn(m_logBaseX);
        qreal logMaxX = qLn(m_maxX) / qLn(m_logBaseX);
        m_logLeftX = logMinX < logMaxX ? logMinX : logMaxX;
        m_logRightX = logMinX > logMaxX ? logMinX : logMaxX;
        if(!m_signalsBlocked)
            emit rangeHorizontalChanged(m_minX, m_maxX);
    }

    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
        m_minY = minY;
        m_maxY = maxY;
        axisYChanged = true;
        if (!m_signalsBlocked)
            emit rangeVerticalChanged(m_minY, m_maxY);
    }

    if (axisXChanged || axisYChanged)
        emit updated();
}

void LogXYDomain::zoomIn(const QRectF &rect)
{
    storeZoomReset();
    QRectF fixedRect = fixZoomRect(rect);
    qreal logLeftX = fixedRect.left() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal logRightX = fixedRect.right() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRightX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal dy = spanY() / m_size.height();
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    minY = maxY - dy * fixedRect.bottom();
    maxY = maxY - dy * fixedRect.top();

    setRange(minX, maxX, minY, maxY);
}

void LogXYDomain::zoomOut(const QRectF &rect)
{
    storeZoomReset();
    QRectF fixedRect = fixZoomRect(rect);
    const qreal factorX = m_size.width() / fixedRect.width();

    qreal logLeftX = m_logLeftX + (m_logRightX - m_logLeftX) / 2 * (1 - factorX);
    qreal logRightX = m_logLeftX + (m_logRightX - m_logLeftX) / 2 * (1 + factorX);
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRightX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal dy = spanY() / fixedRect.height();
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    maxY = minY + dy * fixedRect.bottom();
    minY = maxY - dy * m_size.height();

    if (logRightX > m_size.width())
        return;

    if (qIsInf(maxX))
        return;

    setRange(minX, maxX, minY, maxY);
}

void LogXYDomain::move(qreal dx, qreal dy)
{
    if (m_reverseX)
        dx = -dx;
    if (m_reverseY)
        dy = -dy;

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
    const qreal deltaX = m_size.width() / (m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / (m_maxY - m_minY);

    qreal x(0);
    qreal y = (point.y() - m_minY) * deltaY;
    if (!m_reverseY)
        y = m_size.height() - y;
    if (point.x() > 0) {
        x = ((qLn(point.x()) / qLn(m_logBaseX)) - m_logLeftX) * deltaX;
        if (m_reverseX)
            x = m_size.width() - x;
        ok = true;
    } else {
        x = 0;
        qWarning() << "Logarithms of zero and negative values are undefined.";
        ok = false;
    }
    return QPointF(x, y);
}

QList<QPointF> LogXYDomain::calculateGeometryPoints(const QList<QPointF> &list) const
{
    const qreal deltaX = m_size.width() / (m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / (m_maxY - m_minY);

    QList<QPointF> result;
    result.resize(list.size());

    for (int i = 0; i < list.size(); ++i) {
        if (list[i].x() > 0) {
            qreal x = ((qLn(list[i].x()) / qLn(m_logBaseX)) - m_logLeftX) * deltaX;
            if (m_reverseX)
                x = m_size.width() - x;
            qreal y = (list[i].y() - m_minY) * deltaY;
            if (!m_reverseY)
                y = m_size.height() - y;
            result[i].setX(x);
            result[i].setY(y);
        } else {
            qWarning() << "Logarithms of zero and negative values are undefined.";
            return QList<QPointF>();
        }
    }
    return result;
}

QPointF LogXYDomain::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width() / (m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / (m_maxY - m_minY);
    qreal x = m_reverseX ? (m_size.width() - point.x()) : point.x();
    x = qPow(m_logBaseX, m_logLeftX + x / deltaX);
    qreal y = m_reverseY ? point.y() : (m_size.height() - point.y());
    y /= deltaY;
    y += m_minY;
    return QPointF(x, y);
}

bool LogXYDomain::attachAxis(QAbstractAxis *axis)
{
    AbstractDomain::attachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Horizontal) {
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));
        handleHorizontalAxisBaseChanged(logAxis->base());
    }

    return true;
}

bool LogXYDomain::detachAxis(QAbstractAxis *axis)
{
    AbstractDomain::detachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Horizontal)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));

    return true;
}

void LogXYDomain::handleHorizontalAxisBaseChanged(qreal baseX)
{
    m_logBaseX = baseX;
    qreal logMinX = qLn(m_minX) / qLn(m_logBaseX);
    qreal logMaxX = qLn(m_maxX) / qLn(m_logBaseX);
    m_logLeftX = logMinX < logMaxX ? logMinX : logMaxX;
    m_logRightX = logMinX > logMaxX ? logMinX : logMaxX;
    emit updated();
}

// operators

bool Q_AUTOTEST_EXPORT operator== (const LogXYDomain &domain1, const LogXYDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX)
            && qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY)
            && qFuzzyIsNull(domain1.m_minX - domain2.m_minX)
            && qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool Q_AUTOTEST_EXPORT operator!= (const LogXYDomain &domain1, const LogXYDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug Q_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXYDomain &domain)
{
#ifdef QT_NO_TEXTSTREAM
    Q_UNUSED(domain);
#else
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
#endif
    return dbg.maybeSpace();
}

QT_END_NAMESPACE

#include "moc_logxydomain_p.cpp"
