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

#include "qvaluesaxis.h"
#include "qvaluesaxis_p.h"
#include "chartvaluesaxisx_p.h"
#include "chartvaluesaxisy_p.h"
#include "domain_p.h"
#include <cmath>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QValuesAxis
    \brief The QValuesAxis class is used for manipulating chart's axis.
    \mainclass

    ValuesAxis can be setup to show axis line with tick marks, grid lines and shades.
    Values of axis are drawn to position of ticks
*/

/*!
    \qmlclass ValuesAxis QValuesAxis
    \brief The ValuesAxis element is used for manipulating chart's axes

    ValueAxis can be setup to show axis line with tick marks, grid lines and shades.
    Values of axis are drawn to position of ticks

    To access Axes you can use ChartView API. For example:
    \code
        ChartView {
            ValuesAxis {
                id: xAxis
                min: 0
                max: 10
            }
        // Add a few series...
        }
    \endcode
*/

/*!
  \property QValuesAxis::min
  Defines the minimum value on the axis.
*/
/*!
  \qmlproperty real ValuesAxis::min
  Defines the minimum value on the axis.
*/

/*!
  \property QValuesAxis::max
  Defines the maximum value on the axis.
*/
/*!
  \qmlproperty real ValuesAxis::max
  Defines the maximum value on the axis.
*/

/*!
  \fn void QValuesAxis::minChanged(qreal min)
  Axis emits signal when \a min of axis has changed.
*/
/*!
  \qmlsignal ValuesAxis::onMinChanged(real min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QValuesAxis::maxChanged(qreal max)
  Axis emits signal when \a max of axis has changed.
*/
/*!
  \qmlsignal ValuesAxis::onMaxChanged(real max)
  Axis emits signal when \a max of axis has changed.
*/

/*!
  \fn void QValuesAxis::rangeChanged(qreal min, qreal max)
  Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
  \property QValuesAxis::ticksCount
  The number of tick marks for the axis.
*/

/*!
  \qmlproperty int ValuesAxis::ticksCount
  The number of tick marks for the axis.
*/

/*!
  \property QValuesAxis::niceNumbersEnabled
  Whether the nice numbers algorithm is enabled or not for the axis.
*/

/*!
  \qmlproperty bool ValuesAxis::niceNumbersEnabled
  Whether the nice numbers algorithm is enabled or not for the axis.
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QValuesAxis::QValuesAxis(QObject *parent) :
    QAbstractAxis(*new QValuesAxisPrivate(this),parent)
{

}

/*!
    \internal
*/
QValuesAxis::QValuesAxis(QValuesAxisPrivate &d,QObject *parent) : QAbstractAxis(d,parent)
{

}

/*!
    Destroys the object
*/
QValuesAxis::~QValuesAxis()
{

}

void QValuesAxis::setMin(qreal min)
{
    Q_D(QValuesAxis);
    setRange(min,d->m_max);
}

qreal QValuesAxis::min() const
{
    Q_D(const QValuesAxis);
    return d->m_min;
}

void QValuesAxis::setMax(qreal max)
{
    Q_D(QValuesAxis);
    setRange(d->m_min,max);
}

qreal QValuesAxis::max() const
{
    Q_D(const QValuesAxis);
    return d->m_max;
}

/*!
  Sets range from \a min to \a max on the axis.
*/
void QValuesAxis::setRange(qreal min, qreal max)
{
    Q_D(QValuesAxis);
    bool changed = false;

    if (!qFuzzyIsNull(d->m_min - min)) {
        d->m_min = min;
        changed = true;
        emit minChanged(min);
    }

    if (!qFuzzyIsNull(d->m_max - max)) {
        d->m_max = max;
        changed = true;
        emit maxChanged(max);
    }

    if(d->m_niceNumbers) d->looseNiceNumbers(d->m_min, d->m_max, d->m_tickCount);

    if (changed) {
        emit rangeChanged(d->m_min,d->m_max);
        d->emitUpdated();
    }
}

/*!
  Sets \a count for ticks on the axis.
*/
void QValuesAxis::setTicksCount(int count)
{
    Q_D(QValuesAxis);
    if (d->m_tickCount != count && count >=2) {
        d->m_tickCount = count;
        d->emitUpdated();
    }
}

/*!
  \fn int QValuesAxis::ticksCount() const
  Return number of ticks on the axis
*/
int QValuesAxis::ticksCount() const
{
    Q_D(const QValuesAxis);
    return d->m_tickCount;
}

void QValuesAxis::setNiceNumbersEnabled(bool enable)
{
    Q_D(QValuesAxis);
    if (d->m_niceNumbers != enable){
        d->m_niceNumbers = enable;
        if(enable && !qFuzzyIsNull(d->m_max - d->m_min)) setRange(d->min(),d->max());
    }
}

bool  QValuesAxis::niceNumbersEnabled() const
{
    Q_D(const QValuesAxis);
    return d->m_niceNumbers;
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QValuesAxis::type() const
{
    return AxisTypeValues;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QValuesAxisPrivate::QValuesAxisPrivate(QValuesAxis* q):
    QAbstractAxisPrivate(q),
    m_min(0),
    m_max(0),
    m_tickCount(5),
    m_niceNumbers(false)
{

}

QValuesAxisPrivate::~QValuesAxisPrivate()
{

}

void QValuesAxisPrivate::handleDomainUpdated()
{
   Q_Q(QValuesAxis);
   Domain* domain = qobject_cast<Domain*>(sender());
   Q_ASSERT(domain);

   if(orientation()==Qt::Horizontal){
       q->setRange(domain->minX(),domain->maxX());
   }else if(orientation()==Qt::Vertical){
       q->setRange(domain->minY(),domain->maxY());
   }
}


void QValuesAxisPrivate::setMin(const QVariant &min)
{
    Q_Q(QValuesAxis);
    bool ok;
    qreal value = min.toReal(&ok);
    if(ok) q->setMin(value);
}

void QValuesAxisPrivate::setMax(const QVariant &max)
{

    Q_Q(QValuesAxis);
    bool ok;
    qreal value = max.toReal(&ok);
    if(ok) q->setMax(value);
}

void QValuesAxisPrivate::setRange(const QVariant &min, const QVariant &max)
{
    Q_Q(QValuesAxis);
    bool ok1;
    bool ok2;
    qreal value1 = min.toReal(&ok1);
    qreal value2 = max.toReal(&ok2);
    if(ok1&&ok2) q->setRange(value1,value2);
}

ChartAxis* QValuesAxisPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QValuesAxis);
    if(m_orientation == Qt::Vertical){
        return new ChartValuesAxisY(q,presenter);
    }else{
        return new ChartValuesAxisX(q,presenter);
    }

}

void QValuesAxisPrivate::intializeDomain(Domain* domain)
{
    if(qFuzzyCompare(m_max,m_min)) {
        if(m_orientation==Qt::Vertical){
            m_min = domain->minY();
            m_max = domain->maxY();
        }else{
            m_min = domain->minX();
            m_max = domain->maxX();
        }
    } else {
        if(m_orientation==Qt::Vertical){
            domain->setRangeY(m_min, m_max);
        }else{
            domain->setRangeX(m_min, m_max);
        }
    }
}

//algorithm defined by Paul S.Heckbert GraphicalGems I

void QValuesAxisPrivate::looseNiceNumbers(qreal &min, qreal &max, int &ticksCount) const
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

qreal QValuesAxisPrivate::niceNumber(qreal x,bool ceiling) const
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

#include "moc_qvaluesaxis.cpp"
#include "moc_qvaluesaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
