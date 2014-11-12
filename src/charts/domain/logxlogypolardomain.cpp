/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/logxlogypolardomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCharts/QLogValueAxis>
#include <QtCore/QtMath>

QT_CHARTS_BEGIN_NAMESPACE

LogXLogYPolarDomain::LogXLogYPolarDomain(QObject *parent)
    : PolarDomain(parent),
      m_logLeftX(0),
      m_logRightX(1),
      m_logBaseX(10),
      m_logInnerY(0),
      m_logOuterY(1),
      m_logBaseY(10)
{
}

LogXLogYPolarDomain::~LogXLogYPolarDomain()
{
}

void LogXLogYPolarDomain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    bool axisXChanged = false;
    bool axisYChanged = false;

    adjustLogDomainRanges(minX, maxX);
    adjustLogDomainRanges(minY, maxY);

    if (!qFuzzyCompare(m_minX, minX) || !qFuzzyCompare(m_maxX, maxX)) {
        m_minX = minX;
        m_maxX = maxX;
        axisXChanged = true;
        qreal logMinX = log10(m_minX) / log10(m_logBaseX);
        qreal logMaxX = log10(m_maxX) / log10(m_logBaseX);
        m_logLeftX = logMinX < logMaxX ? logMinX : logMaxX;
        m_logRightX = logMinX > logMaxX ? logMinX : logMaxX;
        if (!m_signalsBlocked)
            emit rangeHorizontalChanged(m_minX, m_maxX);
    }

    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
        m_minY = minY;
        m_maxY = maxY;
        axisYChanged = true;
        qreal logMinY = log10(m_minY) / log10(m_logBaseY);
        qreal logMaxY = log10(m_maxY) / log10(m_logBaseY);
        m_logInnerY = logMinY < logMaxY ? logMinY : logMaxY;
        m_logOuterY = logMinY > logMaxY ? logMinY : logMaxY;
        if (!m_signalsBlocked)
            emit rangeVerticalChanged(m_minY, m_maxY);
    }

    if (axisXChanged || axisYChanged)
        emit updated();
}

void LogXLogYPolarDomain::zoomIn(const QRectF &rect)
{
    storeZoomReset();
    qreal logLeftX = rect.left() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal logRightX = rect.right() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRightX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal logLeftY = m_logOuterY - rect.bottom() * (m_logOuterY - m_logInnerY) / m_size.height();
    qreal logRightY = m_logOuterY - rect.top() * (m_logOuterY - m_logInnerY) / m_size.height();
    qreal leftY = qPow(m_logBaseY, logLeftY);
    qreal rightY = qPow(m_logBaseY, logRightY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

void LogXLogYPolarDomain::zoomOut(const QRectF &rect)
{
    storeZoomReset();
    const qreal factorX = m_size.width() / rect.width();

    qreal logLeftX = m_logLeftX + (m_logRightX - m_logLeftX) / 2.0 * (1.0 - factorX);
    qreal logRIghtX = m_logLeftX + (m_logRightX - m_logLeftX) / 2.0 * (1.0 + factorX);
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRIghtX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    const qreal factorY = m_size.height() / rect.height();
    qreal newLogMinY = m_logInnerY + (m_logOuterY - m_logInnerY) / 2.0 * (1.0 - factorY);
    qreal newLogMaxY = m_logInnerY + (m_logOuterY - m_logInnerY) / 2.0 * (1.0 + factorY);
    qreal leftY = qPow(m_logBaseY, newLogMinY);
    qreal rightY = qPow(m_logBaseY, newLogMaxY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

void LogXLogYPolarDomain::move(qreal dx, qreal dy)
{
    qreal stepX = dx * (m_logRightX - m_logLeftX) / m_size.width();
    qreal leftX = qPow(m_logBaseX, m_logLeftX + stepX);
    qreal rightX = qPow(m_logBaseX, m_logRightX + stepX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal stepY = dy * (m_logOuterY - m_logInnerY) / m_radius;
    qreal leftY = qPow(m_logBaseY, m_logInnerY + stepY);
    qreal rightY = qPow(m_logBaseY, m_logOuterY + stepY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

qreal LogXLogYPolarDomain::toAngularCoordinate(qreal value, bool &ok) const
{
    qreal retVal;
    if (value <= 0) {
        ok = false;
        retVal = 0.0;
    } else {
        ok =  true;
        const qreal tickSpan = 360.0 / qAbs(m_logRightX - m_logLeftX);
        const qreal logValue = log10(value) / log10(m_logBaseX);
        const qreal valueDelta = logValue - m_logLeftX;

        retVal = valueDelta * tickSpan;
    }
    return retVal;
}

qreal LogXLogYPolarDomain::toRadialCoordinate(qreal value, bool &ok) const
{
    qreal retVal;
    if (value <= 0) {
        ok = false;
        retVal = 0.0;
    } else {
        ok =  true;
        const qreal tickSpan = m_radius / qAbs(m_logOuterY - m_logInnerY);
        const qreal logValue = log10(value) / log10(m_logBaseY);
        const qreal valueDelta = logValue - m_logInnerY;

        retVal = valueDelta * tickSpan;

        if (retVal < 0.0)
            retVal = 0.0;
    }
    return retVal;
}

QPointF LogXLogYPolarDomain::calculateDomainPoint(const QPointF &point) const
{
    if (point == m_center)
        return QPointF(0.0, m_minY);

    QLineF line(m_center, point);
    qreal a = 90.0 - line.angle();
    if (a < 0.0)
        a += 360.0;

    const qreal deltaX = 360.0 / qAbs(m_logRightX - m_logLeftX);
    a = qPow(m_logBaseX, m_logLeftX + (a / deltaX));

    const qreal deltaY = m_radius / qAbs(m_logOuterY - m_logInnerY);
    qreal r = qPow(m_logBaseY, m_logInnerY + (line.length() / deltaY));

    return QPointF(a, r);
}

bool LogXLogYPolarDomain::attachAxis(QAbstractAxis *axis)
{
    AbstractDomain::attachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Horizontal) {
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));
        handleHorizontalAxisBaseChanged(logAxis->base());
    } else if (logAxis && logAxis->orientation() == Qt::Vertical){
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));
        handleVerticalAxisBaseChanged(logAxis->base());
    }

    return true;
}

bool LogXLogYPolarDomain::detachAxis(QAbstractAxis *axis)
{
    AbstractDomain::detachAxis(axis);
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Horizontal)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleHorizontalAxisBaseChanged(qreal)));
    else if (logAxis && logAxis->orientation() == Qt::Vertical)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));

    return true;
}

void LogXLogYPolarDomain::handleHorizontalAxisBaseChanged(qreal baseX)
{
    m_logBaseX = baseX;
    qreal logMinX = log10(m_minX) / log10(m_logBaseX);
    qreal logMaxX = log10(m_maxX) / log10(m_logBaseX);
    m_logLeftX = logMinX < logMaxX ? logMinX : logMaxX;
    m_logRightX = logMinX > logMaxX ? logMinX : logMaxX;
    emit updated();
}

void LogXLogYPolarDomain::handleVerticalAxisBaseChanged(qreal baseY)
{
    m_logBaseY = baseY;
    qreal logMinY = log10(m_minY) / log10(m_logBaseY);
    qreal logMaxY = log10(m_maxY) / log10(m_logBaseY);
    m_logInnerY = logMinY < logMaxY ? logMinY : logMaxY;
    m_logOuterY = logMinY > logMaxY ? logMinY : logMaxY;
    emit updated();
}

// operators

bool QT_CHARTS_AUTOTEST_EXPORT operator== (const LogXLogYPolarDomain &domain1, const LogXLogYPolarDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX)
            && qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY)
            && qFuzzyIsNull(domain1.m_minX - domain2.m_minX)
            && qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool QT_CHARTS_AUTOTEST_EXPORT operator!= (const LogXLogYPolarDomain &domain1, const LogXLogYPolarDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug QT_CHARTS_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXLogYPolarDomain &domain)
{
#ifdef QT_NO_TEXTSTREAM
    Q_UNUSED(domain)
#else
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
#endif
    return dbg.maybeSpace();
}

#include "moc_logxlogypolardomain_p.cpp"

QT_CHARTS_END_NAMESPACE
