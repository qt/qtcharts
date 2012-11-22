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

#include "abstractdomain_p.h"
#include "qabstractaxis_p.h"
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

AbstractDomain::AbstractDomain(QObject *parent)
    : QObject(parent),
      m_minX(0),
      m_maxX(0),
      m_minY(0),
      m_maxY(0),
      m_axisSignalsBlocked(false)
{
}

AbstractDomain::~AbstractDomain()
{
}

void AbstractDomain::setSize(const QSizeF& size)
{
	if(m_size!=size)
	{
		m_size=size;
		emit updated();
	}
}

QSizeF AbstractDomain::size() const
{
	return m_size;
}

//void AbstractDomain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
//{
//    bool axisXChanged = false;
//    bool axisYChanged = false;

//    if (!qFuzzyIsNull(m_minX - minX) || !qFuzzyIsNull(m_maxX - maxX)) {
//        m_minX = minX;
//        m_maxX = maxX;
//        axisXChanged = true;
//        emit rangeHorizontalChanged(m_minX, m_maxX);
//    }

//    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
//        m_minY = minY;
//        m_maxY = maxY;
//        axisYChanged = true;
//        emit rangeVerticalChanged(m_minY, m_maxY);
//    }

//    if (axisXChanged || axisYChanged)
//        emit updated();
//}

void AbstractDomain::setRangeX(qreal min, qreal max)
{
    setRange(min, max, m_minY, m_maxY);
}

void AbstractDomain::setRangeY(qreal min, qreal max)
{
    setRange(m_minX, m_maxX, min, max);
}

void AbstractDomain::setMinX(qreal min)
{
    setRange(min, m_maxX, m_minY, m_maxY);
}

void AbstractDomain::setMaxX(qreal max)
{
    setRange(m_minX, max, m_minY, m_maxY);
}

void AbstractDomain::setMinY(qreal min)
{
    setRange(m_minX, m_maxX, min, m_maxY);
}

void AbstractDomain::setMaxY(qreal max)
{
    setRange(m_minX, m_maxX, m_minY, max);
}

qreal AbstractDomain::spanX() const
{
    Q_ASSERT(m_maxX >= m_minX);
    return m_maxX - m_minX;
}

qreal AbstractDomain::spanY() const
{
    Q_ASSERT(m_maxY >= m_minY);
    return m_maxY - m_minY;
}

bool AbstractDomain::isEmpty() const
{
    return qFuzzyIsNull(spanX()) || qFuzzyIsNull(spanY()) || m_size.isEmpty() ;
}

void AbstractDomain::zoomIn(const QRectF &rect)
{
    qreal dx = spanX() / m_size.width();
    qreal dy = spanY() / m_size.height();

    qreal maxX = m_maxX;
    qreal minX = m_minX;
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    maxX = minX + dx * rect.right();
    minX = minX + dx * rect.left();
    minY = maxY - dy * rect.bottom();
    maxY = maxY - dy * rect.top();

    setRange(minX, maxX, minY, maxY);
}

void AbstractDomain::zoomOut(const QRectF &rect)
{
    qreal dx = spanX() / rect.width();
    qreal dy = spanY() / rect.height();

    qreal maxX = m_maxX;
    qreal minX = m_minX;
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    minX = maxX - dx * rect.right();
    maxX = minX + dx * m_size.width();
    maxY = minY + dy * rect.bottom();
    minY = maxY - dy * m_size.height();

    setRange(minX, maxX, minY, maxY);
}

void AbstractDomain::move(qreal dx, qreal dy)
{
    qreal x = spanX() / m_size.width();
    qreal y = spanY() / m_size.height();

    qreal maxX = m_maxX;
    qreal minX = m_minX;
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    if (dx != 0) {
        minX = minX + x * dx;
        maxX = maxX + x * dx;
    }
    if (dy != 0) {
        minY = minY + y * dy;
        maxY = maxY + y * dy;
    }
    setRange(minX, maxX, minY, maxY);
}

//QPointF AbstractDomain::calculateGeometryPoint(const QPointF &point) const
//{
//    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
//    const qreal deltaY = m_size.height() / (m_maxY - m_minY);
//    qreal x = (point.x() - m_minX) * deltaX;
//    qreal y = (point.y() - m_minY) * -deltaY + m_size.height();
//    return QPointF(x, y);
//}

//QVector<QPointF> AbstractDomain::calculateGeometryPoints(const QList<QPointF>& vector) const
//{
//    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
//    const qreal deltaY = m_size.height() / (m_maxY - m_minY);

//    QVector<QPointF> result;
//    result.resize(vector.count());

//    for (int i = 0; i < vector.count(); ++i) {
//        qreal x = (vector[i].x() - m_minX) * deltaX;
//        qreal y = (vector[i].y() - m_minY) * -deltaY + m_size.height();
//        result[i].setX(x);
//        result[i].setY(y);
//    }
//    return result;
//}

QPointF AbstractDomain::calculateDomainPoint(const QPointF &point) const
{
    const qreal deltaX = m_size.width() / (m_maxX - m_minX);
    const qreal deltaY = m_size.height() / (m_maxY - m_minY);
    qreal x = point.x() / deltaX + m_minX;
    qreal y = (point.y() - m_size.height()) / (-deltaY) + m_minY;
    return QPointF(x, y);
}

// handlers

void AbstractDomain::handleVerticalAxisRangeChanged(qreal min, qreal max)
{
    if(!m_axisSignalsBlocked)
        setRangeY(min, max);
}

void AbstractDomain::handleHorizontalAxisRangeChanged(qreal min, qreal max)
{
    if(!m_axisSignalsBlocked)
        setRangeX(min, max);
}

void AbstractDomain::blockAxisSignals(bool block)
{
    m_axisSignalsBlocked=block;
}

//algorithm defined by Paul S.Heckbert GraphicalGems I

void AbstractDomain::looseNiceNumbers(qreal &min, qreal &max, int &ticksCount)
{
    qreal range = niceNumber(max - min, true); //range with ceiling
    qreal step = niceNumber(range / (ticksCount - 1), false);
    min = qFloor(min / step);
    max = qCeil(max / step);
    ticksCount = int(max - min) + 1;
    min *= step;
    max *= step;
}

//nice numbers can be expressed as form of 1*10^n, 2* 10^n or 5*10^n

qreal AbstractDomain::niceNumber(qreal x, bool ceiling)
{
    qreal z = qPow(10, qFloor(log10(x))); //find corresponding number of the form of 10^n than is smaller than x
    qreal q = x / z; //q<10 && q>=1;

    if (ceiling) {
        if (q <= 1.0) q = 1;
        else if (q <= 2.0) q = 2;
        else if (q <= 5.0) q = 5;
        else q = 10;
    } else {
        if (q < 1.5) q = 1;
        else if (q < 3.0) q = 2;
        else if (q < 7.0) q = 5;
        else q = 10;
    }
    return q * z;
}


// operators

bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator== (const AbstractDomain &domain1, const AbstractDomain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX) &&
            qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY) &&
            qFuzzyIsNull(domain1.m_minX - domain2.m_minX) &&
            qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator!= (const AbstractDomain &domain1, const AbstractDomain &domain2)
{
    return !(domain1 == domain2);
}


QDebug QTCOMMERCIALCHART_AUTOTEST_EXPORT operator<<(QDebug dbg, const AbstractDomain &domain)
{
    dbg.nospace() << "AbstractDomain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')' << domain.m_size;
    return dbg.maybeSpace();
}

#include "moc_abstractdomain_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
