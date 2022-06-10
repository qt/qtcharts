// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/logxypolardomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCharts/QLogValueAxis>
#include <QtCore/QtMath>
#include <cmath>

QT_BEGIN_NAMESPACE

LogXYPolarDomain::LogXYPolarDomain(QObject *parent)
    : PolarDomain(parent),
      m_logLeftX(0),
      m_logRightX(1),
      m_logBaseX(10)
{
}

LogXYPolarDomain::~LogXYPolarDomain()
{
}

void LogXYPolarDomain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
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
        if (!m_signalsBlocked)
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

void LogXYPolarDomain::zoomIn(const QRectF &rect)
{
    storeZoomReset();
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

void LogXYPolarDomain::zoomOut(const QRectF &rect)
{
    storeZoomReset();
    const qreal factorX = m_size.width() / rect.width();

    qreal logLeftX = m_logLeftX + (m_logRightX - m_logLeftX) / 2.0 * (1.0 - factorX);
    qreal logRIghtX = m_logLeftX + (m_logRightX - m_logLeftX) / 2.0 * (1.0 + factorX);
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

void LogXYPolarDomain::move(qreal dx, qreal dy)
{
    qreal stepX = dx * (m_logRightX - m_logLeftX) / m_size.width();
    qreal leftX = qPow(m_logBaseX, m_logLeftX + stepX);
    qreal rightX = qPow(m_logBaseX, m_logRightX + stepX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal y = spanY() / m_radius;
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    if (dy != 0) {
        minY = minY + y * dy;
        maxY = maxY + y * dy;
    }
    setRange(minX, maxX, minY, maxY);
}

qreal LogXYPolarDomain::toAngularCoordinate(qreal value, bool &ok) const
{
    qreal retVal;
    if (value <= 0) {
        ok = false;
        retVal = 0.0;
    } else {
        ok =  true;
        const qreal tickSpan = 360.0 / qAbs(m_logRightX - m_logLeftX);
        const qreal logValue = qLn(value) / qLn(m_logBaseX);
        const qreal valueDelta = logValue - m_logLeftX;

        retVal = valueDelta * tickSpan;
    }
    return retVal;
}

qreal LogXYPolarDomain::toRadialCoordinate(qreal value, bool &ok) const
{
    ok = true;
    if (value < m_minY)
        value = m_minY;

    // Dont limit the max. The drawing should clip the stuff that goes out of the grid
    qreal f = (value - m_minY) / (m_maxY - m_minY);

    return f * m_radius;
}

QPointF LogXYPolarDomain::calculateDomainPoint(const QPointF &point) const
{
    if (point == m_center)
        return QPointF(0.0, m_minY);

    QLineF line(m_center, point);
    qreal a = 90.0 - line.angle();
    if (a < 0.0)
        a += 360.0;

    const qreal deltaX = 360.0 / qAbs(m_logRightX - m_logLeftX);
    a = qPow(m_logBaseX, m_logLeftX + (a / deltaX));

    qreal r = m_minY + ((m_maxY - m_minY) * (line.length() / m_radius));

    return QPointF(a, r);
}

bool LogXYPolarDomain::attachAxis(QAbstractAxis *axis)
{
    AbstractDomain::attachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Horizontal) {
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));
        handleHorizontalAxisBaseChanged(logAxis->base());
    }

    return true;
}

bool LogXYPolarDomain::detachAxis(QAbstractAxis *axis)
{
    AbstractDomain::detachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Horizontal)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));

    return true;
}

void LogXYPolarDomain::handleHorizontalAxisBaseChanged(qreal baseX)
{
    m_logBaseX = baseX;
    qreal logMinX = qLn(m_minX) / qLn(m_logBaseX);
    qreal logMaxX = qLn(m_maxX) / qLn(m_logBaseX);
    m_logLeftX = logMinX < logMaxX ? logMinX : logMaxX;
    m_logRightX = logMinX > logMaxX ? logMinX : logMaxX;
    emit updated();
}

// operators

bool Q_AUTOTEST_EXPORT operator== (const LogXYPolarDomain &domain1, const LogXYPolarDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX)
            && qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY)
            && qFuzzyIsNull(domain1.m_minX - domain2.m_minX)
            && qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool Q_AUTOTEST_EXPORT operator!= (const LogXYPolarDomain &domain1, const LogXYPolarDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug Q_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXYPolarDomain &domain)
{
#ifdef QT_NO_TEXTSTREAM
    Q_UNUSED(domain);
#else
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
#endif
    return dbg.maybeSpace();
}

QT_END_NAMESPACE

#include "moc_logxypolardomain_p.cpp"
