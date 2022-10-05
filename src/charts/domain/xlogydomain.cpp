// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/xlogydomain_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCharts/QLogValueAxis>
#include <QtCore/QtMath>
#include <cmath>

QT_BEGIN_NAMESPACE

XLogYDomain::XLogYDomain(QObject *parent)
    : AbstractDomain(parent),
      m_logLeftY(0),
      m_logRightY(1),
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

    adjustLogDomainRanges(minY, maxY);

    if (!qFuzzyIsNull(m_minX - minX) || !qFuzzyIsNull(m_maxX - maxX)) {
        m_minX = minX;
        m_maxX = maxX;
        axisXChanged = true;
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

void XLogYDomain::zoomIn(const QRectF &rect)
{
    storeZoomReset();
    QRectF fixedRect = fixZoomRect(rect);
    qreal dx = spanX() / m_size.width();
    qreal maxX = m_maxX;
    qreal minX = m_minX;

    maxX = minX + dx * fixedRect.right();
    minX = minX + dx * fixedRect.left();

    qreal logLeftY = m_logRightY - fixedRect.bottom() * (m_logRightY - m_logLeftY) / m_size.height();
    qreal logRightY = m_logRightY - fixedRect.top() * (m_logRightY - m_logLeftY) / m_size.height();
    qreal leftY = qPow(m_logBaseY, logLeftY);
    qreal rightY = qPow(m_logBaseY, logRightY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

void XLogYDomain::zoomOut(const QRectF &rect)
{
    storeZoomReset();
    QRectF fixedRect = fixZoomRect(rect);
    qreal dx = spanX() / fixedRect.width();
    qreal maxX = m_maxX;
    qreal minX = m_minX;

    minX = maxX - dx * fixedRect.right();
    maxX = minX + dx * m_size.width();

    const qreal factorY = m_size.height() / fixedRect.height();
    qreal newLogMinY = m_logLeftY + (m_logRightY - m_logLeftY) / 2 * (1 - factorY);
    qreal newLogMaxY = m_logLeftY + (m_logRightY - m_logLeftY) / 2 * (1 + factorY);
    qreal leftY = qPow(m_logBaseY, newLogMinY);
    qreal rightY = qPow(m_logBaseY, newLogMaxY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    if (newLogMaxY > m_size.height())
        return;

    if (qIsInf(maxY))
        return;

    setRange(minX, maxX, minY, maxY);
}

void XLogYDomain::move(qreal dx, qreal dy)
{
    if (m_reverseX)
        dx = -dx;
    if (m_reverseY)
        dy = -dy;

    qreal x = spanX() / m_size.width();
    qreal maxX = m_maxX;
    qreal minX = m_minX;

    if (dx != 0) {
        minX = minX + x * dx;
        maxX = maxX + x * dx;
    }

    qreal stepY = dy * (m_logRightY - m_logLeftY) / m_size.height();
    qreal leftY = qPow(m_logBaseY, m_logLeftY + stepY);
    qreal rightY = qPow(m_logBaseY, m_logRightY + stepY);
    qreal minY = leftY < rightY ? leftY : rightY;
    qreal maxY = leftY > rightY ? leftY : rightY;

    setRange(minX, maxX, minY, maxY);
}

QPointF XLogYDomain::calculateGeometryPoint(const QPointF &point, bool &ok) const
{
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);

    qreal x = (point.x() - m_minX) * deltaX;
    if (m_reverseX)
        x = m_size.width() - x;
    qreal y(0);
    if (point.y() > 0) {
        y = ((qLn(point.y()) / qLn(m_logBaseY)) - m_logLeftY) * deltaY;
        if (!m_reverseY)
            y = m_size.height() - y;
        ok = true;
    } else {
        y = m_size.height();
        qWarning() << "Logarithms of zero and negative values are undefined.";
        ok = false;
    }
    return QPointF(x, y);
}

QList<QPointF> XLogYDomain::calculateGeometryPoints(const QList<QPointF> &list) const
{
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);

    QList<QPointF> result;
    result.resize(list.size());

    for (int i = 0; i < list.size(); ++i) {
        if (list[i].y() > 0) {
            qreal x = (list[i].x() - m_minX) * deltaX;
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

QPointF XLogYDomain::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / qAbs(m_logRightY - m_logLeftY);
    qreal x = m_reverseX ? (m_size.width() - point.x()) : point.x();
    x /= deltaX;
    x += m_minX;
    qreal y = m_reverseY ? point.y() : (m_size.height() - point.y());
    y = qPow(m_logBaseY, m_logLeftY + y / deltaY);
    return QPointF(x, y);
}

bool XLogYDomain::attachAxis(QAbstractAxis *axis)
{
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Vertical) {
        QObject::connect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));
        handleVerticalAxisBaseChanged(logAxis->base());
    }
    return  AbstractDomain::attachAxis(axis);
}

bool XLogYDomain::detachAxis(QAbstractAxis *axis)
{
    QLogValueAxis *logAxis = qobject_cast<QLogValueAxis *>(axis);

    if (logAxis && logAxis->orientation() == Qt::Vertical)
        QObject::disconnect(logAxis, SIGNAL(baseChanged(qreal)), this, SLOT(handleVerticalAxisBaseChanged(qreal)));

    return AbstractDomain::detachAxis(axis);
}

void XLogYDomain::handleVerticalAxisBaseChanged(qreal baseY)
{
    m_logBaseY = baseY;
    qreal logMinY = qLn(m_minY) / qLn(m_logBaseY);
    qreal logMaxY = qLn(m_maxY) / qLn(m_logBaseY);
    m_logLeftY = logMinY < logMaxY ? logMinY : logMaxY;
    m_logRightY = logMinY > logMaxY ? logMinY : logMaxY;
    emit updated();
}

// operators

bool Q_AUTOTEST_EXPORT operator== (const XLogYDomain &domain1, const XLogYDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX)
            && qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY)
            && qFuzzyIsNull(domain1.m_minX - domain2.m_minX)
            && qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool Q_AUTOTEST_EXPORT operator!= (const XLogYDomain &domain1, const XLogYDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug Q_AUTOTEST_EXPORT operator<<(QDebug dbg, const XLogYDomain &domain)
{
#ifdef QT_NO_TEXTSTREAM
    Q_UNUSED(domain);
#else
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
#endif
    return dbg.maybeSpace();
}

QT_END_NAMESPACE

#include "moc_xlogydomain_p.cpp"
