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

#include <private/logxlogydomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCharts/QLogValueAxis>
#include <QtCore/QtMath>

QT_CHARTS_BEGIN_NAMESPACE

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
        qreal logMinY = log10(m_minY) / log10(m_logBaseY);
        qreal logMaxY = log10(m_maxY) / log10(m_logBaseY);
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
    qreal logLeftX = rect.left() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal logRightX = rect.right() * (m_logRightX - m_logLeftX) / m_size.width() + m_logLeftX;
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRightX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal logLeftY = m_logRightY - rect.bottom() * (m_logRightY - m_logLeftY) / m_size.height();
    qreal logRightY = m_logRightY - rect.top() * (m_logRightY - m_logLeftY) / m_size.height();
    qreal leftY = qPow(m_logBaseY, logLeftY);
    qreal rightY = qPow(m_logBaseY, logRightY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

void LogXLogYDomain::zoomOut(const QRectF &rect)
{
    storeZoomReset();
    const qreal factorX = m_size.width() / rect.width();
    const qreal factorY = m_size.height() / rect.height();

    qreal logLeftX = m_logLeftX + (m_logRightX - m_logLeftX) / 2 * (1 - factorX);
    qreal logRIghtX = m_logLeftX + (m_logRightX - m_logLeftX) / 2 * (1 + factorX);
    qreal leftX = qPow(m_logBaseX, logLeftX);
    qreal rightX = qPow(m_logBaseX, logRIghtX);
    qreal minX = leftX < rightX ? leftX : rightX;
    qreal maxX = leftX > rightX ? leftX : rightX;

    qreal newLogMinY = m_logLeftY + (m_logRightY - m_logLeftY) / 2 * (1 - factorY);
    qreal newLogMaxY = m_logLeftY + (m_logRightY - m_logLeftY) / 2 * (1 + factorY);
    qreal leftY = qPow(m_logBaseY, newLogMinY);
    qreal rightY = qPow(m_logBaseY, newLogMaxY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

void LogXLogYDomain::move(qreal dx, qreal dy)
{
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
        x = (log10(point.x()) / log10(m_logBaseX)) * deltaX - m_logLeftX * deltaX;
        y = (log10(point.y()) / log10(m_logBaseY)) * -deltaY - m_logLeftY * -deltaY + m_size.height();
        ok = true;
    } else {
        qWarning() << "Logarithms of zero and negative values are undefined.";
        ok = false;
        if (point.x() > 0)
            x = (log10(point.x()) / log10(m_logBaseX)) * deltaX - m_logLeftX * deltaX;
        else
            x = 0;
        if (point.y() > 0) {
            y = (log10(point.y()) / log10(m_logBaseY)) * -deltaY - m_logLeftY * -deltaY
                    + m_size.height();
        } else {
            y = m_size.height();
        }
    }
    return QPointF(x, y);
}

QVector<QPointF> LogXLogYDomain::calculateGeometryPoints(const QList<QPointF> &vector) const
{
    const qreal deltaX = m_size.width() / qAbs(m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);

    QVector<QPointF> result;
    result.resize(vector.count());

    for (int i = 0; i < vector.count(); ++i) {
        if (vector[i].x() > 0 && vector[i].y() > 0) {
            qreal x = (log10(vector[i].x()) / log10(m_logBaseX)) * deltaX - m_logLeftX * deltaX;
            qreal y = (log10(vector[i].y()) / log10(m_logBaseY)) * -deltaY - m_logLeftY * -deltaY + m_size.height();
            result[i].setX(x);
            result[i].setY(y);
        } else {
            qWarning() << "Logarithms of zero and negative values are undefined.";
            return QVector<QPointF>();
        }
    }
    return result;
}

QPointF LogXLogYDomain::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width() / qAbs(m_logRightX - m_logLeftX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);
    qreal x = qPow(m_logBaseX, m_logLeftX + point.x() / deltaX);
    qreal y = qPow(m_logBaseY, m_logLeftY + (m_size.height() - point.y()) / deltaY);
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
    qreal logMinY = log10(m_minY) / log10(m_logBaseY);
    qreal logMaxY = log10(m_maxY) / log10(m_logBaseY);
    m_logLeftY = logMinY < logMaxY ? logMinY : logMaxY;
    m_logRightY = logMinY > logMaxY ? logMinY : logMaxY;
    emit updated();
}

void LogXLogYDomain::handleHorizontalAxisBaseChanged(qreal baseX)
{
    m_logBaseX = baseX;
    qreal logMinX = log10(m_minX) / log10(m_logBaseX);
    qreal logMaxX = log10(m_maxX) / log10(m_logBaseX);
    m_logLeftX = logMinX < logMaxX ? logMinX : logMaxX;
    m_logRightX = logMinX > logMaxX ? logMinX : logMaxX;
    emit updated();
}

// operators

bool QT_CHARTS_AUTOTEST_EXPORT operator== (const LogXLogYDomain &domain1, const LogXLogYDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX)
            && qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY)
            && qFuzzyIsNull(domain1.m_minX - domain2.m_minX)
            && qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool QT_CHARTS_AUTOTEST_EXPORT operator!= (const LogXLogYDomain &domain1, const LogXLogYDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug QT_CHARTS_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXLogYDomain &domain)
{
#ifdef QT_NO_TEXTSTREAM
    Q_UNUSED(domain)
#else
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
#endif
    return dbg.maybeSpace();
}

#include "moc_logxlogydomain_p.cpp"

QT_CHARTS_END_NAMESPACE
