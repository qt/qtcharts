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
#include <cmath>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Domain::Domain(QObject* parent):QObject(parent),
m_minX(0),
m_maxX(0),
m_minY(0),
m_maxY(0),
m_tickXCount(5),
m_tickYCount(5),
m_niceNumbers(false)
{
}

Domain::~Domain()
{
}

void Domain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    setRange(minX, maxX, minY, maxY,m_tickXCount,m_tickYCount);
}

void Domain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY,int tickXCount,int tickYCount)
{
    bool domainChanged = false;
    bool tickXChanged = false;
    bool tickYChanged = false;

    if(m_tickXCount!=tickXCount) {
        m_tickXCount=tickXCount;
        tickXChanged=true;
    }

    if(m_tickYCount!=tickYCount) {
        m_tickYCount=tickYCount;
        tickYChanged=true;
    }

    if (!qFuzzyIsNull(m_minX - minX) || !qFuzzyIsNull(m_maxX - maxX)) {
        if(m_niceNumbers) looseNiceNumbers(minX, maxX, m_tickXCount);
        m_minX=minX;
        m_maxX=maxX;
        domainChanged=true;
        tickXChanged=false;
        emit rangeXChanged(minX,maxX, m_tickXCount);
    }

    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
        if(m_niceNumbers) looseNiceNumbers(minY, maxY, m_tickYCount);
        m_minY=minY;
        m_maxY=maxY;
        domainChanged=true;
        tickYChanged=false;
        emit rangeYChanged(minY,maxY, m_tickYCount);
    }

    if(domainChanged) {
        emit this->domainChanged(m_minX, m_maxX, m_minY, m_maxY);
    }

    if(tickXChanged) {
        emit rangeXChanged(minX,maxX, m_tickXCount);
    }

    if(tickYChanged) {
        emit rangeYChanged(minY,maxY, m_tickYCount);
    }
}

void Domain::setRangeX(qreal min, qreal max)
{
    setRange(min,max,m_minY, m_maxY);
}

void Domain::setRangeX(qreal min, qreal max, int tickCount)
{
    setRange(min,max,m_minY, m_maxY,tickCount,m_tickYCount);
}

void Domain::setRangeY(qreal min, qreal max)
{
    setRange(m_minX, m_maxX, min, max);
}

void Domain::setRangeY(qreal min, qreal max,int tickCount)
{
    setRange(m_minX, m_maxX, min, max,m_tickXCount,tickCount);
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

    m_maxX = m_minX + dx * rect.right();
    m_minX = m_minX + dx * rect.left();
    m_minY = m_maxY - dy * rect.bottom();
    m_maxY = m_maxY - dy * rect.top();

    if(m_niceNumbers) {
        looseNiceNumbers(m_minX, m_maxX, m_tickXCount);
        looseNiceNumbers(m_minY, m_maxY, m_tickYCount);
    }

    emit domainChanged(m_minX, m_maxX, m_minY, m_maxY);
    emit rangeXChanged(m_minX, m_maxX, m_tickXCount);
    emit rangeYChanged(m_minY, m_maxY, m_tickYCount);
}

void Domain::zoomOut(const QRectF& rect, const QSizeF& size)
{
    qreal dx = spanX() / rect.width();
    qreal dy = spanY() / rect.height();

    m_minX = m_maxX - dx * rect.right();
    m_maxX = m_minX + dx * size.width();
    m_maxY = m_minY + dy * rect.bottom();
    m_minY = m_maxY - dy * size.height();

    if(m_niceNumbers) {
        looseNiceNumbers(m_minX, m_maxX, m_tickXCount);
        looseNiceNumbers(m_minY, m_maxY, m_tickYCount);
    }

    emit domainChanged(m_minX, m_maxX, m_minY, m_maxY);
    emit rangeXChanged(m_minX, m_maxX, m_tickXCount);
    emit rangeYChanged(m_minY, m_maxY, m_tickYCount);
}

void Domain::move(int dx,int dy,const QSizeF& size)
{
    qreal x = spanX() / size.width();
    qreal y = spanY() / size.height();

    if(dx!=0) {
        m_minX = m_minX + x * dx;
        m_maxX = m_maxX + x * dx;
        emit rangeXChanged(m_minX, m_maxX, m_tickXCount);
    }
    if(dy!=0) {
        m_minY = m_minY + y * dy;
        m_maxY = m_maxY + y * dy;
        emit rangeYChanged(m_minY, m_maxY, m_tickYCount);
    }

    emit domainChanged(m_minX, m_maxX, m_minY, m_maxY);
}

void Domain::handleAxisXChanged(qreal min,qreal max,int tickXCount,bool niceNumbers)
{
    if (niceNumbers && m_niceNumbers != niceNumbers) {
        m_niceNumbers = niceNumbers;
        //force recalculation
        m_minX = 0;
        m_maxX = 0;
    }
    setRange(min,max,m_minY, m_maxY,tickXCount,m_tickYCount);
}

void Domain::handleAxisYChanged(qreal min,qreal max,int tickYCount,bool niceNumbers)
{
    if (niceNumbers && m_niceNumbers != niceNumbers) {
        m_niceNumbers = niceNumbers;
        //force recalculation
        m_minY = 0;
        m_maxY = 0;
    }
    setRange(m_minX, m_maxX, min, max,m_tickXCount,tickYCount);
}

//algorithm defined by Paul S.Heckbert GraphicalGems I

void Domain::looseNiceNumbers(qreal &min, qreal &max, int &ticksCount)
{
    qreal range = niceNumber(max-min,true); //range with ceiling
    qreal step = niceNumber(range/(ticksCount-1),false);
    min = floor(min/step);
    max = ceil(max/step);
    ticksCount = int(max-min) +1;
    min*=step;
    max*=step;
}

//nice numbers can be expressed as form of 1*10^n, 2* 10^n or 5*10^n

qreal Domain::niceNumber(qreal x,bool ceiling)
{
    qreal z = pow(10,floor(log10(x))); //find corresponding number of the form of 10^n than is smaller than x
    qreal q = x/z;//q<10 && q>=1;

    if(ceiling) {
        if(q <= 1.0) q=1;
        else if(q <= 2.0) q=2;
        else if(q <= 5.0) q=5;
        else q=10;
    }
    else {
        if(q < 1.5) q=1;
        else if(q < 3.0) q=2;
        else if(q < 7.0) q=5;
        else q=10;
    }
    return q*z;
}

bool operator== (const Domain &domain1, const Domain &domain2)
{
    return (qFuzzyIsNull(domain1.m_maxX - domain2.m_maxX) &&
        qFuzzyIsNull(domain1.m_maxY - domain2.m_maxY) &&
        qFuzzyIsNull(domain1.m_minX - domain2.m_minX) &&
        qFuzzyIsNull(domain1.m_minY - domain2.m_minY));
}

bool operator!= (const Domain &domain1, const Domain &domain2)
{
    return !(domain1 == domain2);
}

QDebug operator<<(QDebug dbg, const Domain &domain)
{
    dbg.nospace() << "Domain("<<domain.m_minX<<','<<domain.m_maxX<<','<<domain.m_minY<<','<<domain.m_maxY<<')' << domain.m_tickXCount << "," << domain.m_tickYCount ;
    return dbg.maybeSpace();
}

#include "moc_domain_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
