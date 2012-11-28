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
#include "abstractdomain_p.h"
#include "chartdataset_p.h"
#include "chartpresenter_p.h"
#include "charttheme_p.h"


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
  \property QValueAxis::tickCount
  Defines the number of ticks on the axis. This indicates how many grid lines are draw on the chart.
  The default value is 5, and it can not be below 2.
*/
/*!
  \qmlproperty real ValueAxis::tickCount
   Defines the number of ticks on the axis. This indicates how many grid lines are draw on the chart.
  The default value is 5, and it can not be below 2.
*/

/*!
  \property QValueAxis::labelFormat
  Defines the label format for the axis.
  Supported specifiers are: d, i, o, x, X, f, F, e, E, g, G, c
  See QString::sprintf() for additional details.
*/
/*!
  \qmlproperty real ValueAxis::labelFormat
  Defines the label format for the axis.
  Supported specifiers are: d, i, o, x, X, f, F, e, E, g, G, c
  See QString::sprintf() for additional details.
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
  \fn void QValueAxis::tickCountChanged(int tickCount)
  Axis emits signal when number of ticks on axis have changed.
*/
/*!
  \qmlsignal ValueAxis::tickCountChanged(int tickCount)
  Axis emits signal when number of ticks on axis have changed.
*/

/*!
  \fn void QValueAxis::rangeChanged(qreal min, qreal max)
  Axis emits signal when \a min or \a max of axis has changed.
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
    if (d->m_chart)
        d->m_chart->removeAxis(this);
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
    d->setRange(min,max);
}

void QValueAxis::setTickCount(int count)
{
    Q_D(QValueAxis);
    if (d->m_tickCount != count && count >= 2) {
        d->m_tickCount = count;
        emit tickCountChanged(count);
    }
}

int QValueAxis::tickCount() const
{
    Q_D(const QValueAxis);
    return d->m_tickCount;
}

void QValueAxis::setNiceNumbersEnabled(bool enable)
{
    Q_D(QValueAxis);
    qWarning()<<"This function is depreciated, it can lead to unexpected behaviour.Use applyNiceNumbers(). ";
    if(enable) {
        QObject::connect(this,SIGNAL(rangeChanged(qreal,qreal)),this,SLOT(applyNiceNumbers()));
        QObject::connect(this,SIGNAL(tickCountChanged(int)),this,SLOT(applyNiceNumbers()));
        applyNiceNumbers();
    }
    else {
        QObject::disconnect(this,SIGNAL(rangeChanged(qreal,qreal)),this,SLOT(applyNiceNumbers()));
        QObject::disconnect(this,SIGNAL(tickCountChanged(int)),this,SLOT(applyNiceNumbers()));
    }
    d->m_niceNumbersEnabled=true;
}

bool QValueAxis::niceNumbersEnabled() const
{
    Q_D(const QValueAxis);
    qWarning()<<"This function is depreciated.Use applyNiceNumbers().";
    return d->m_niceNumbersEnabled;
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

void QValueAxis::applyNiceNumbers()
{
    Q_D(QValueAxis);
    if(d->m_applying) return;
    qreal min = d->m_min;
    qreal max = d->m_max;
    int ticks = d->m_tickCount;
    AbstractDomain::looseNiceNumbers(min,max,ticks);
    d->m_applying=true;
    d->setRange(min,max);
    setTickCount(ticks);
    d->m_applying=false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QValueAxisPrivate::QValueAxisPrivate(QValueAxis *q)
    : QAbstractAxisPrivate(q),
      m_min(0),
      m_max(0),
      m_tickCount(5),
      m_format(QString::null),
      m_applying(false),
      m_niceNumbersEnabled(false)
{

}

QValueAxisPrivate::~QValueAxisPrivate()
{

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

void QValueAxisPrivate::setRange(qreal min, qreal max)
{
	Q_Q(QValueAxis);
    bool changed = false;

    if (min > max)
        return;

    if (!qFuzzyCompare(m_min,min)) {
    	m_min = min;
        changed = true;
        emit q->minChanged(min);
    }

    if (!qFuzzyCompare(m_max,max)) {
        m_max = max;
        changed = true;
        emit q->maxChanged(max);
    }

    if (changed) {
        emit rangeChanged(min,max);
        emit q->rangeChanged(min, max);
    }
}

void QValueAxisPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QValueAxis);
    ChartAxis* axis(0);
    if (orientation() == Qt::Vertical)
        axis = new ChartValueAxisY(q,parent);
    if (orientation() == Qt::Horizontal)
        axis = new ChartValueAxisX(q,parent);

    m_item.reset(axis);
    QAbstractAxisPrivate::initializeGraphics(parent);
}


void QValueAxisPrivate::initializeDomain(AbstractDomain *domain)
{
    if (orientation() == Qt::Vertical) {
        if(!qFuzzyIsNull(m_max - m_min)) {
            domain->setRangeY(m_min, m_max);
        }
        else {
            setRange(domain->minY(), domain->maxY());
        }
    }
    if (orientation() == Qt::Horizontal) {
        if(!qFuzzyIsNull(m_max - m_min)) {
            domain->setRangeX(m_min, m_max);
        }
        else {
            setRange(domain->minX(), domain->maxX());
        }
    }
}

#include "moc_qvalueaxis.cpp"
#include "moc_qvalueaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
