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

Domain::Domain(QObject* parent) : QObject(parent),
    m_minX(0),
    m_maxX(0),
    m_minY(0),
    m_maxY(0),
    m_tickXCount(5),
    m_tickYCount(5),
    m_niceXNumbers(false),
    m_niceYNumbers(false)
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
    bool axisXChanged = false;
    bool axisYChanged = false;

    if(m_tickXCount!=tickXCount) {
        m_tickXCount=tickXCount;
        axisXChanged=true;
    }

    if(m_tickYCount!=tickYCount) {
        m_tickYCount=tickYCount;
        axisYChanged=true;
    }

    if (!qFuzzyIsNull(m_minX - minX) || !qFuzzyIsNull(m_maxX - maxX)) {
        if(m_niceXNumbers) looseNiceNumbers(minX, maxX, m_tickXCount);
        m_minX=minX;
        m_maxX=maxX;
        axisXChanged=true;
    }

    if (!qFuzzyIsNull(m_minY - minY) || !qFuzzyIsNull(m_maxY - maxY)) {
        if(m_niceYNumbers) looseNiceNumbers(minY, maxY, m_tickYCount);
        m_minY=minY;
        m_maxY=maxY;
        axisYChanged=true;
    }

    if(axisXChanged || axisYChanged) {
        emit this->domainChanged(m_minX, m_maxX, m_minY, m_maxY);
    }

    if(axisXChanged) {
        emit rangeXChanged(minX,maxX, m_tickXCount);
    }

    if(axisYChanged) {
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

    qreal maxX = m_maxX;
    qreal minX = m_minX;
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    maxX = minX + dx * rect.right();
    minX = minX + dx * rect.left();
    minY = maxY - dy * rect.bottom();
    maxY = maxY - dy * rect.top();

    int tickXCount = m_tickXCount;
    int tickYCount = m_tickYCount;

    if(m_niceXNumbers) {
        looseNiceNumbers(minX, maxX, tickXCount);
    }
    if(m_niceYNumbers) {
        looseNiceNumbers(minY, maxY, tickYCount);
    }
    setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
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

    int tickXCount = m_tickXCount;
    int tickYCount = m_tickYCount;

    if(m_niceXNumbers) {
        looseNiceNumbers(minX, maxX, tickXCount);
    }
    if(m_niceYNumbers) {
        looseNiceNumbers(minY, maxY, tickYCount);
    }
    setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
}

void Domain::move(qreal dx,qreal dy,const QSizeF& size)
{
    qreal x = spanX() / size.width();
    qreal y = spanY() / size.height();

    qreal maxX = m_maxX;
    qreal minX = m_minX;
    qreal minY = m_minY;
    qreal maxY = m_maxY;

    if(dx!=0) {
        minX = minX + x * dx;
        maxX = maxX + x * dx;
    }
    if(dy!=0) {
        minY = minY + y * dy;
        maxY = maxY + y * dy;
    }
    setRange(minX,maxX,minY,maxY);
}

void Domain::handleAxisXChanged(qreal min,qreal max,int tickXCount,bool niceNumbers)
{
    if (m_niceXNumbers != niceNumbers) {
        m_niceXNumbers = niceNumbers;
        //force recalculation
        m_minX = 0;
        m_maxX = 0;
    }
    setRange(min,max,m_minY, m_maxY,tickXCount,m_tickYCount);
}

void Domain::handleAxisYChanged(qreal min,qreal max,int tickYCount,bool niceNumbers)
{
    if (m_niceYNumbers != niceNumbers) {
        m_niceYNumbers = niceNumbers;
        //force recalculation
        m_minY = 0;
        m_maxY = 0;
    }
    setRange(m_minX, m_maxX, min, max,m_tickXCount,tickYCount);
}

//algorithm defined by Paul S.Heckbert GraphicalGems I

void Domain::looseNiceNumbers(qreal &min, qreal &max, int &ticksCount) const
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

qreal Domain::niceNumber(qreal x,bool ceiling) const
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
    dbg.nospace() << "Domain("<<domain.m_minX<<','<<domain.m_maxX<<','<<domain.m_minY<<','<<domain.m_maxY<<')' << domain.m_tickXCount << "," << domain.m_tickYCount ;
    return dbg.maybeSpace();
}

#include "moc_domain_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
