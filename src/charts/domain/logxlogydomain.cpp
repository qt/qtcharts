// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/logxlogydomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCharts/QLogValueAxis>
#include <QtCore/QtMath>
#include <cmath>

QT_BEGIN_NAMESPACE

LogXLogYDomain::LogXLogYDomain(QObject *parent)
    : AbstractDomain(parent),
      m_logLeftX(0),
      m_logRightX(1),
      m_logBaseX(10),
      m_logLeftY(0),
      m_logRightY(1),
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

    adjustLogDomainRanges(minX, maxX);
    adjustLogDomainRanges(minY, maxY);

    if (!qFuzzyIsNull(m_minX - minX) || !qFuzzyIsNull(m_maxX - maxX)) {
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
        qreal logMinY = qLn(m_minY) / qLn(m_logBaseY);
        qreal logMaxY = qLn(m_maxY) / qLn(m_logBaseY);
        m_logLeftY = logMinY < logMaxY ? logMinY : logMaxY;
        m_logRightY = logMinY > logMaxY ? logMinY : logMaxY;
        if (!m_signalsBlocked)
            emit rangeVerticalChanged(m_minY, m_maxY);
    }

    if (axisXChanged || axisYChanged)
        emit updated();
}

void LogXLogYDomain::zoomIn(const QRectF &rect)
{
    storeZoomReset();
    QRectF fixedRect = fixZoomRect(rect);
    qreal logLeftX = fixedRect.left() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal logRightX = fixedRect.right() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRightX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal logLeftY = m_logRightY - fixedRect.bottom() * (m_logRightY - m_logLeftY) / m_size.height();
    qreal logRightY = m_logRightY - fixedRect.top() * (m_logRightY - m_logLeftY) / m_size.height();
    qreal leftY = qPow(m_logBaseY, logLeftY);
    qreal rightY = qPow(m_logBaseY, logRightY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

void LogXLogYDomain::zoomOut(const QRectF &rect)
{
    storeZoomReset();
    QRectF fixedRect = fixZoomRect(rect);
    const qreal factorX = m_size.width() / fixedRect.width();
    const qreal factorY = m_size.height() / fixedRect.height();

    qreal logLeftX = m_logLeftX + (m_logRightX - m_logLeftX) / 2 * (1 - factorX);
    qreal logRightX = m_logLeftX + (m_logRightX - m_logLeftX) / 2 * (1 + factorX);
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRightX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal newLogMinY = m_logLeftY + (m_logRightY - m_logLeftY) / 2 * (1 - factorY);
    qreal newLogMaxY = m_logLeftY + (m_logRightY - m_logLeftY) / 2 * (1 + factorY);
    qreal leftY = qPow(m_logBaseY, newLogMinY);
    qreal rightY = qPow(m_logBaseY, newLogMaxY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    if (logRightX > m_size.width() || newLogMaxY > m_size.height())
        return;

    if (qIsInf(maxX) || qIsInf(maxY))
        return;

    setRange(minX, maxX, minY, maxY);
}

void LogXLogYDomain::move(qreal dx, qreal dy)
{
    if (m_reverseX)
        dx = -dx;
    if (m_reverseY)
        dy = -dy;

    qreal stepX = dx * qAbs(m_logRightX - m_logLeftX) / m_size.width();
    qreal leftX = qPow(m_logBaseX, m_logLeftX + stepX);
    qreal rightX = qPow(m_logBaseX, m_logRightX + stepX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal stepY = dy * (m_logRightY - m_logLeftY) / m_size.height();
    qreal leftY = qPow(m_logBaseY, m_logLeftY + stepY);
    qreal rightY = qPow(m_logBaseY, m_logRightY + stepY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

QPointF LogXLogYDomain::calculateGeometryPoint(const QPointF &point, bool &ok) const
{
    const qreal deltaX = m_size.width() / qAbs(m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);
    qreal x(0);
    qreal y(0);
    if (point.x() > 0 && point.y() > 0) {
        x = ((qLn(point.x()) / qLn(m_logBaseX)) - m_logLeftX) * deltaX;
        y = ((qLn(point.y()) / qLn(m_logBaseY)) - m_logLeftY) * deltaY;
        ok = true;
    } else {
        qWarning() << "Logarithms of zero and negative values are undefined.";
        ok = false;
        if (point.x() > 0)
            x = ((qLn(point.x()) / qLn(m_logBaseX)) - m_logLeftX) * deltaX;
        else
            x = 0;
        if (point.y() > 0)
            y = ((qLn(point.y()) / qLn(m_logBaseY)) - m_logLeftY) * deltaY;
        else
            y = 0;
    }
    if (m_reverseX)
        x = m_size.width() - x;
    if (!m_reverseY)
        y = m_size.height() - y;
    return QPointF(x, y);
}

QList<QPointF> LogXLogYDomain::calculateGeometryPoints(const QList<QPointF> &list) const
{
    const qreal deltaX = m_size.width() / qAbs(m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);

    QList<QPointF> result;
    result.resize(list.size());

    for (int i = 0; i < list.size(); ++i) {
        if (list[i].x() > 0 && list[i].y() > 0) {
            qreal x = ((qLn(list[i].x()) / qLn(m_logBaseX)) - m_logLeftX) * deltaX;
            if (m_reverseX)
                x = m_size.width() - x;
            qreal y = ((qLn(list[i].y()) / qLn(m_logBaseY)) - m_logLeftY) * deltaY;
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

QPointF LogXLogYDomain::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width() / qAbs(m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);
    qreal x = m_reverseX ? (m_size.width() - point.x()) : point.x();
    x = qPow(m_logBaseX, m_logLeftX + x / deltaX);
    qreal y = m_reverseY ? point.y() : (m_size.height() - point.y());
    y = qPow(m_logBaseY, m_logLeftY + y / deltaY);
    return QPointF(x, y);
}

bool LogXLogYDomain::attachAxis(QAbstractAxis *axis)
{
    AbstractDomain::attachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Vertical) {
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));
        handleVerticalAxisBaseChanged(logAxis->base());
    }

    if (logAxis && logAxis->orientation() == Qt::Horizontal) {
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));
        handleHorizontalAxisBaseChanged(logAxis->base());
    }

    return true;
}

bool LogXLogYDomain::detachAxis(QAbstractAxis *axis)
{
    AbstractDomain::detachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Vertical)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));

    if (logAxis && logAxis->orientation() == Qt::Horizontal)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));

    return true;
}

void LogXLogYDomain::handleVerticalAxisBaseChanged(qreal baseY)
{
    m_logBaseY = baseY;
    qreal logMinY = qLn(m_minY) / qLn(m_logBaseY);
    qreal logMaxY = qLn(m_maxY) / qLn(m_logBaseY);
    m_logLeftY = logMinY < logMaxY ? logMinY : logMaxY;
    m_logRightY = logMinY > logMaxY ? logMinY : logMaxY;
    emit updated();
}

void LogXLogYDomain::handleHorizontalAxisBaseChanged(qreal baseX)
{
    m_logBaseX = baseX;
    qreal logMinX = qLn(m_minX) / qLn(m_logBaseX);
    qreal logMaxX = qLn(m_maxX) / qLn(m_logBaseX);
    m_logLeftX = logMinX < logMaxX ? logMinX : logMaxX;
    m_logRightX = logMinX > logMaxX ? logMinX : logMaxX;
    emit updated();
}

// operators

bool Q_AUTOTEST_EXPORT operator== (const LogXLogYDomain &domain1, const LogXLogYDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX)
            && qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY)
            && qFuzzyIsNull(domain1.m_minX - domain2.m_minX)
            && qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool Q_AUTOTEST_EXPORT operator!= (const LogXLogYDomain &domain1, const LogXLogYDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug Q_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXLogYDomain &domain)
{
#ifdef QT_NO_TEXTSTREAM
    Q_UNUSED(domain);
#else
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
#endif
    return dbg.maybeSpace();
}

QT_END_NAMESPACE

#include "moc_logxlogydomain_p.cpp"
