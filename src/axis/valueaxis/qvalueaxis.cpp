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

#include "qvalueaxis.h"
#include "qvalueaxis_p.h"
#include "chartvalueaxisx_p.h"
#include "chartvalueaxisy_p.h"
#include "domain_p.h"
#include "chartdataset_p.h"
#include <qmath.h>


QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QValueAxis
    \brief The QValueAxis class is used for manipulating chart's axis.
    \mainclass

    ValueAxis can be setup to show axis line with tick marks, grid lines and shades.
    Values of axis are drawn to position of ticks.

    Example code on how to use QValueAxis.
    \code
    QChartView *chartView = new QChartView;
    QLineSeries *series = new QLineSeries;
    // ...
    chartView->chart()->addSeries(series);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(10, 20.5);
    axisX->setTickCount(10);
    axisX->setLabelFormat("%.2f");
    chartView->chart()->setAxisX(axisX, series);
    \endcode
*/

/*!
    \qmlclass ValueAxis QValueAxis
    \inherits AbstractAxis
    \brief The ValueAxis element is used for manipulating chart's axes

    ValueAxis can be setup to show axis line with tick marks, grid lines and shades.
    Values of axis are drawn to position of ticks

    To access Axes you can use ChartView API. For example:
    \code
        ChartView {
            ValueAxis {
                id: xAxis
                min: 0
                max: 10
            }
        // Add a few series...
        }
    \endcode
*/

/*!
  \property QValueAxis::min
  Defines the minimum value on the axis.
  When setting this property the max is adjusted if necessary, to ensure that the range remains valid.
*/
/*!
  \qmlproperty real ValueAxis::min
  Defines the minimum value on the axis.
  When setting this property the max is adjusted if necessary, to ensure that the range remains valid.
*/

/*!
  \property QValueAxis::max
  Defines the maximum value on the axis.
  When setting this property the min is adjusted if necessary, to ensure that the range remains valid.
*/
/*!
  \qmlproperty real ValueAxis::max
  Defines the maximum value on the axis.
  When setting this property the min is adjusted if necessary, to ensure that the range remains valid.
*/

/*!
  \property QValueAxis::labelFormat
  Defines the label format for the axis.
  See QString::sprintf() for the details.
*/
/*!
  \qmlproperty real ValueAxis::labelFormat
  Defines the label format for the axis.
  See QString::sprintf() for the details.
*/

/*!
  \fn void QValueAxis::minChanged(qreal min)
  Axis emits signal when \a min of axis has changed.
*/
/*!
  \qmlsignal ValueAxis::onMinChanged(real min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QValueAxis::maxChanged(qreal max)
  Axis emits signal when \a max of axis has changed.
*/
/*!
  \qmlsignal ValueAxis::onMaxChanged(real max)
  Axis emits signal when \a max of axis has changed.
*/

/*!
  \fn void QValueAxis::rangeChanged(qreal min, qreal max)
  Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
  \property QValueAxis::tickCount
  The number of tick marks for the axis.
*/

/*!
  \qmlproperty int ValueAxis::tickCount
  The number of tick marks for the axis.
*/

/*!
  \property QValueAxis::niceNumbersEnabled
  Whether the nice numbers algorithm is enabled or not for the axis.
*/

/*!
  \qmlproperty bool ValueAxis::niceNumbersEnabled
  Whether the nice numbers algorithm is enabled or not for the axis.
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QValueAxis::QValueAxis(QObject *parent) :
    QAbstractAxis(*new QValueAxisPrivate(this), parent)
{

}

/*!
    \internal
*/
QValueAxis::QValueAxis(QValueAxisPrivate &d, QObject *parent)
    : QAbstractAxis(d, parent)
{

}

/*!
    Destroys the object
*/
QValueAxis::~QValueAxis()
{
    Q_D(QValueAxis);
    if (d->m_dataset)
        d->m_dataset->removeAxis(this);
}

void QValueAxis::setMin(qreal min)
{
    Q_D(QValueAxis);
    setRange(min, qMax(d->m_max, min));
}

qreal QValueAxis::min() const
{
    Q_D(const QValueAxis);
    return d->m_min;
}

void QValueAxis::setMax(qreal max)
{
    Q_D(QValueAxis);
    setRange(qMin(d->m_min, max), max);
}

qreal QValueAxis::max() const
{
    Q_D(const QValueAxis);
    return d->m_max;
}

/*!
  Sets range from \a min to \a max on the axis.
  If min is greater than max then this function returns without making any changes.
*/
void QValueAxis::setRange(qreal min, qreal max)
{
    Q_D(QValueAxis);
    bool changed = false;

    if (min > max)
        return;

    if (d->m_niceNumbers) {
        int ticks = d->m_tickCount;
        d->looseNiceNumbers(min, max, ticks);
        if (ticks != d->m_tickCount)
            setTickCount(ticks);
    }

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
        emit rangeChanged(min, max);
        d->emitUpdated();
    }
}

/*!
  Sets \a count for ticks on the axis.
*/
void QValueAxis::setTickCount(int count)
{
    Q_D(QValueAxis);
    if (d->m_tickCount != count && count >= 2) {
        d->m_tickCount = count;
        d->emitUpdated();
    }
}

/*!
  \fn int QValueAxis::tickCount() const
  Return number of ticks on the axis
*/
int QValueAxis::tickCount() const
{
    Q_D(const QValueAxis);
    return d->m_tickCount;
}

void QValueAxis::setNiceNumbersEnabled(bool enable)
{
    Q_D(QValueAxis);
    if (d->m_niceNumbers != enable) {
        d->m_niceNumbers = enable;
        if (enable && !qFuzzyIsNull(d->m_max - d->m_min))
            setRange(d->m_min, d->m_max);
    }
}

bool  QValueAxis::niceNumbersEnabled() const
{
    Q_D(const QValueAxis);
    return d->m_niceNumbers;
}

void QValueAxis::setLabelFormat(const QString &format)
{
    Q_D(QValueAxis);
    d->m_format = format;
}

QString QValueAxis::labelFormat() const
{
    Q_D(const QValueAxis);
    return d->m_format;
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QValueAxis::type() const
{
    return AxisTypeValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QValueAxisPrivate::QValueAxisPrivate(QValueAxis *q)
    : QAbstractAxisPrivate(q),
      m_min(0),
      m_max(0),
      m_tickCount(5),
      m_niceNumbers(false),
      m_format(QString::null)
{

}

QValueAxisPrivate::~QValueAxisPrivate()
{

}

void QValueAxisPrivate::handleDomainUpdated()
{
    Q_Q(QValueAxis);
    Domain *domain = qobject_cast<Domain *>(sender());
    Q_ASSERT(domain);

    if (orientation() == Qt::Horizontal)
        q->setRange(domain->minX(), domain->maxX());
    else if (orientation() == Qt::Vertical)
        q->setRange(domain->minY(), domain->maxY());
}


void QValueAxisPrivate::setMin(const QVariant &min)
{
    Q_Q(QValueAxis);
    bool ok;
    qreal value = min.toReal(&ok);
    if (ok)
        q->setMin(value);
}

void QValueAxisPrivate::setMax(const QVariant &max)
{

    Q_Q(QValueAxis);
    bool ok;
    qreal value = max.toReal(&ok);
    if (ok)
        q->setMax(value);
}

void QValueAxisPrivate::setRange(const QVariant &min, const QVariant &max)
{
    Q_Q(QValueAxis);
    bool ok1;
    bool ok2;
    qreal value1 = min.toReal(&ok1);
    qreal value2 = max.toReal(&ok2);
    if (ok1 && ok2)
        q->setRange(value1, value2);
}

ChartAxis *QValueAxisPrivate::createGraphics(ChartPresenter *presenter)
{
    Q_Q(QValueAxis);
    if (m_orientation == Qt::Vertical)
        return new ChartValueAxisY(q, presenter);
    return new ChartValueAxisX(q, presenter);
}

void QValueAxisPrivate::intializeDomain(Domain *domain)
{
    Q_Q(QValueAxis);
    if (qFuzzyCompare(m_max, m_min)) {
        if (m_orientation == Qt::Vertical)
            q->setRange(domain->minY(), domain->maxY());
        else
            q->setRange(domain->minX(), domain->maxX());
    } else {
        if (m_orientation == Qt::Vertical)
            domain->setRangeY(m_min, m_max);
        else
            domain->setRangeX(m_min, m_max);
    }
}

//algorithm defined by Paul S.Heckbert GraphicalGems I

void QValueAxisPrivate::looseNiceNumbers(qreal &min, qreal &max, int &ticksCount) const
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

qreal QValueAxisPrivate::niceNumber(qreal x, bool ceiling) const
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

#include "moc_qvalueaxis.cpp"
#include "moc_qvalueaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
