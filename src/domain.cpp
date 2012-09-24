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

#include "domain_p.h"
#include "qabstractaxis_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Domain::Domain(QObject* parent)
    : QObject(parent),
      m_minX(0),
      m_maxX(0),
      m_minY(0),
      m_maxY(0)
{
}

Domain::~Domain()
{
}

void Domain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    bool axisXChanged = false;
    bool axisYChanged = false;

    if (!qFuzzyIsNull(m_minX - minX) || !qFuzzyIsNull(m_maxX - maxX)) {
        m_minX = minX;
        m_maxX = maxX;
        axisXChanged = true;
        emit rangeXChanged(m_minX, m_maxX);
    }

    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
        m_minY = minY;
        m_maxY = maxY;
        axisYChanged = true;
        emit rangeYChanged(m_minY, m_maxY);
    }

    if (axisXChanged || axisYChanged)
        emit updated();
}

void Domain::setRangeX(qreal min, qreal max)
{
    setRange(min, max, m_minY, m_maxY);
}

void Domain::setRangeY(qreal min, qreal max)
{
    setRange(m_minX, m_maxX, min, max);
}

void Domain::setMinX(qreal min)
{
    setRange(min, m_maxX, m_minY, m_maxY);
}

void Domain::setMaxX(qreal max)
{
    setRange(m_minX, max, m_minY, m_maxY);
}

void Domain::setMinY(qreal min)
{
    setRange(m_minX, m_maxX, min, m_maxY);
}

void Domain::setMaxY(qreal max)
{
    setRange(m_minX, m_maxX, m_minY, max);
}

qreal Domain::spanX() const
{
    Q_ASSERT(m_maxX >= m_minX);
    return m_maxX - m_minX;
}

qreal Domain::spanY() const
{
    Q_ASSERT(m_maxY >= m_minY);
    return m_maxY - m_minY;
}

bool Domain::isEmpty() const
{
    return qFuzzyIsNull(spanX()) || qFuzzyIsNull(spanY());
}

void Domain::zoomIn(const QRectF& rect, const QSizeF& size)
{
    qreal dx = spanX() / size.width();
    qreal dy = spanY() / size.height();

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

void Domain::zoomOut(const QRectF& rect, const QSizeF& size)
{
    qreal dx = spanX() / rect.width();
    qreal dy = spanY() / rect.height();

    qreal maxX = m_maxX;
    qreal minX = m_minX;
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    minX = maxX - dx * rect.right();
    maxX = minX + dx * size.width();
    maxY = minY + dy * rect.bottom();
    minY = maxY - dy * size.height();

    setRange(minX, maxX, minY, maxY);
}

void Domain::move(qreal dx, qreal dy, const QSizeF& size)
{
    qreal x = spanX() / size.width();
    qreal y = spanY() / size.height();

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

void Domain::emitUpdated()
{
    emit updated();
}

void Domain::handleAxisUpdated()
{
    QAbstractAxisPrivate* axis = qobject_cast<QAbstractAxisPrivate*>(sender());
    Q_ASSERT(axis);
    axis->setDirty(false);
    if (axis->orientation() == Qt::Horizontal)
        setRangeX(axis->min(), axis->max());
    else if (axis->orientation() == Qt::Vertical)
        setRangeY(axis->min(), axis->max());
}

bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator== (const Domain &domain1, const Domain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX) &&
            qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY) &&
            qFuzzyIsNull(domain1.m_minX - domain2.m_minX) &&
            qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}


bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator!= (const Domain &domain1, const Domain &domain2)
{
    return !(domain1 == domain2);
}


QDebug QTCOMMERCIALCHART_AUTOTEST_EXPORT operator<<(QDebug dbg, const Domain &domain)
{
    dbg.nospace() << "Domain(" << domain.m_minX << ',' << domain.m_maxX << ',' << domain.m_minY << ',' << domain.m_maxY << ')';
    return dbg.maybeSpace();
}

#include "moc_domain_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
