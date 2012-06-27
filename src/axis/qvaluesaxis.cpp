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
#include "chartaxisx_p.h"
#include "chartaxisy_p.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QValuesAxis
    \brief The QValuesAxis class is used for manipulating chart's axis.
    \mainclass

    Axis can be setup to show axis line with tick marks, grid lines and shades.
*/

/*!
    \qmlclass Axis QValuesAxis
    \brief The Axis element is used for manipulating chart's axes

    Axis can be setup to show axis line with tick marks, grid lines and shades.

    To access Axes you can use ChartView API. For example:
    \code
        ChartView {
            axisX.min: 0
            axisX.max: 3
            axisX.ticksCount: 4
            axisY.min: 0
            axisY.max: 4
            // Add a few series...
        }
    \endcode
*/

/*!
  \property QValuesAxis::min
  Defines the minimum value on the axis.
*/
/*!
  \qmlproperty real Axis::min
  Defines the minimum value on the axis.
*/

/*!
  \property QValuesAxis::max
  Defines the maximum value on the axis.
*/
/*!
  \qmlproperty real Axis::max
  Defines the maximum value on the axis.
*/

/*!
  \fn void QValuesAxis::minChanged(qreal min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QValuesAxis::maxChanged(qreal max)
  Axis emits signal when \a max of axis has changed.
*/

/*!
  \fn void QValuesAxis::rangeChanged(qreal min, qreal max)
  Axis emits signal when \a min or \a max of axis has changed.
*/

QValuesAxis::QValuesAxis(QObject *parent) :
    QAbstractAxis(*new QValuesAxisPrivate(this),parent)
{

}

QValuesAxis::QValuesAxis(QValuesAxisPrivate &d,QObject *parent) : QAbstractAxis(d,parent)
{

}

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

    if (changed) {
       emit rangeChanged(d->m_min,d->m_max);
       emit d->changed(d->m_min, d->m_max, d->m_ticksCount, d->m_niceNumbers);
    }
}

/*!
  Sets \a count for ticks on the axis.
*/
void QValuesAxis::setTicksCount(int count)
{
    Q_D(QValuesAxis);
    if (d->m_ticksCount != count) {
        d->m_ticksCount = count;
        emit d->changed(d->m_min, d->m_max, d->m_ticksCount, d->m_niceNumbers);
    }
}

/*!
  \fn int QAbstractAxis::ticksCount() const
  Return number of ticks on the axis
*/
int QValuesAxis::ticksCount() const
{
    Q_D(const QValuesAxis);
    return d->m_ticksCount;
}

void QValuesAxis::setNiceNumbersEnabled(bool enable)
{
    Q_D(QValuesAxis);
    if (d->m_niceNumbers != enable){
        d->m_niceNumbers = enable;
        emit d->changed(d->m_min, d->m_max, d->m_ticksCount, d->m_niceNumbers);
    }
}

bool  QValuesAxis::niceNumbersEnabled() const
{
    Q_D(const QValuesAxis);
    return d->m_niceNumbers;
}

QAbstractAxis::AxisType QValuesAxis::type() const
{
    return AxisTypeValues;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QValuesAxisPrivate::QValuesAxisPrivate(QValuesAxis* q):
    QAbstractAxisPrivate(q),
    m_min(0),
    m_max(0),
    m_niceNumbers(false),
    m_ticksCount(5)
{

}

QValuesAxisPrivate::~QValuesAxisPrivate()
{

}

void QValuesAxisPrivate::handleAxisRangeChanged(qreal min, qreal max,int count)
{
   Q_Q(QValuesAxis);
   q->setRange(min,max);
   q->setTicksCount(count);
}


void QValuesAxisPrivate::setMin(const QVariant& min)
{
    Q_Q(QValuesAxis);
    bool ok;
    qreal value = min.toReal(&ok);
    if(ok) q->setMin(value);
}

void QValuesAxisPrivate::setMax(const QVariant& max)
{
    Q_Q(QValuesAxis);
    bool ok;
    qreal value = max.toReal(&ok);
    if(ok) q->setMax(value);
}

void QValuesAxisPrivate::setRange(const QVariant& min, const QVariant& max)
{
    Q_Q(QValuesAxis);
    bool ok1;
    bool ok2;
    qreal value1 = min.toReal(&ok1);
    qreal value2 = max.toReal(&ok2);
    if(ok1&&ok2) q->setRange(value1,value2);
}

int QValuesAxisPrivate::ticksCount() const
{
    return m_ticksCount;
}

ChartAxis* QValuesAxisPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QValuesAxis);
    if(m_orientation == Qt::Vertical){
        return new ChartAxisY(q,presenter);
    }else{
        return new ChartAxisX(q,presenter);
    }

}

#include "moc_qvaluesaxis.cpp"
#include "moc_qvaluesaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
