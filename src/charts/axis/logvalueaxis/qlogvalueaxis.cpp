/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCharts/QLogValueAxis>
#include <private/qlogvalueaxis_p.h>
#include <private/chartlogvalueaxisx_p.h>
#include <private/chartlogvalueaxisy_p.h>
#include <private/polarchartlogvalueaxisangular_p.h>
#include <private/polarchartlogvalueaxisradial_p.h>
#include <private/abstractdomain_p.h>
#include <float.h>
#include <cmath>

QT_CHARTS_BEGIN_NAMESPACE
/*!
    \class QLogValueAxis
    \inmodule Qt Charts
    \brief The QLogValueAxis class is used for manipulating chart's axis.

    \note If a QLogValueAxis is attached to a series with one or more points with
    negative or zero values on the associated dimension, the series will not be
    plotted at all. This is particularly relevant when XYModelMappers are used,
    since empty cells in models typically contain zero values.
*/

/*!
    \qmltype LogValueAxis
    \instantiates QLogValueAxis
    \inqmlmodule QtCharts

    \brief The LogValueAxis element is used for manipulating chart's axes.
    \inherits AbstractAxis

    \note If a LogValueAxis is attached to a series with one or more points with
    negative or zero values on the associated dimension, the series will not be
    plotted at all. This is particularly relevant when XYModelMappers are used,
    since empty cells in models typically contain zero values.
*/

/*!
  \property QLogValueAxis::min
  Defines the minimum value on the axis.
  When setting this property the max is adjusted if necessary, to ensure that the range remains valid.
  Value has to be greater than 0.
*/
/*!
  \qmlproperty real LogValueAxis::min
  Defines the minimum value on the axis.
  When setting this property the max is adjusted if necessary, to ensure that the range remains valid.
  Value has to be greater than 0.
*/

/*!
  \property QLogValueAxis::max
  Defines the maximum value on the axis.
  When setting this property the min is adjusted if necessary, to ensure that the range remains valid.
  Value has to be greater than 0.
*/
/*!
  \qmlproperty real LogValueAxis::max
  Defines the maximum value on the axis.
  When setting this property the min is adjusted if necessary, to ensure that the range remains valid.
  Value has to be greater than 0.
*/

/*!
  \property QLogValueAxis::base
  Defines the base of the logarithm.
  Value has to be greater than 0 and not equal 1
*/
/*!
  \qmlproperty real LogValueAxis::base
  Defines the maximum value on the axis.
  Defines the base of the logarithm.
  Value has to be greater than 0 and not equal 1
*/

/*!
  \property QLogValueAxis::labelFormat
  Defines the label format of the axis.
  Supported specifiers are: d, i, o, x, X, f, F, e, E, g, G, c
  See QString::sprintf() for additional details.
*/
/*!
  \qmlproperty real LogValueAxis::labelFormat
  Defines the label format of the axis.
  Supported specifiers are: d, i, o, x, X, f, F, e, E, g, G, c
  See QString::sprintf() for additional details.
*/

/*!
  \fn void QLogValueAxis::minChanged(qreal min)
  Axis emits signal when \a min of axis has changed.
*/
/*!
  \qmlsignal LogValueAxis::onMinChanged(qreal min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QLogValueAxis::maxChanged(qreal max)
  Axis emits signal when \a max of axis has changed.
*/
/*!
  \qmlsignal LogValueAxis::onMaxChanged(qreal max)
  Axis emits signal when \a max of axis has changed.
*/

/*!
  \fn void QLogValueAxis::rangeChanged(qreal min, qreal max)
  Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
  \fn void QLogValueAxis::labelFormatChanged(const QString &format)
  Axis emits signal when \a format of axis labels has changed.
*/
/*!
  \qmlsignal LogValueAxis::labelFormatChanged(const QString &format)
   Axis emits signal when \a format of axis labels has changed.
*/

/*!
  \fn void QLogValueAxis::baseChanged(qreal base)
  Axis emits signal when \a base of logarithm of the axis has changed.
*/
/*!
  \qmlsignal LogValueAxis::baseChanged(qreal base)
  Axis emits signal when \a base of logarithm of the axis has changed.
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QLogValueAxis::QLogValueAxis(QObject *parent) :
    QAbstractAxis(*new QLogValueAxisPrivate(this), parent)
{

}

/*!
    \internal
*/
QLogValueAxis::QLogValueAxis(QLogValueAxisPrivate &d, QObject *parent) : QAbstractAxis(d, parent)
{

}

/*!
    Destroys the object
*/
QLogValueAxis::~QLogValueAxis()
{
    Q_D(QLogValueAxis);
    if (d->m_chart)
        d->m_chart->removeAxis(this);
}

void QLogValueAxis::setMin(qreal min)
{
    Q_D(QLogValueAxis);
    setRange(min, qMax(d->m_max, min));
}

qreal QLogValueAxis::min() const
{
    Q_D(const QLogValueAxis);
    return d->m_min;
}

void QLogValueAxis::setMax(qreal max)
{
    Q_D(QLogValueAxis);
    setRange(qMin(d->m_min, max), max);
}

qreal QLogValueAxis::max() const
{
    Q_D(const QLogValueAxis);
    return d->m_max;
}

/*!
  Sets range from \a min to \a max on the axis.
  If min is greater than max then this function returns without making any changes.
*/
void QLogValueAxis::setRange(qreal min, qreal max)
{
    Q_D(QLogValueAxis);
    bool changed = false;

    if (min > max)
        return;

    if (min > 0) {
        if (!qFuzzyCompare(d->m_min, min)) {
            d->m_min = min;
            changed = true;
            emit minChanged(min);
        }

        if (!qFuzzyCompare(d->m_max, max)) {
            d->m_max = max;
            changed = true;
            emit maxChanged(max);
        }

        if (changed) {
            emit rangeChanged(min, max);
            emit d->rangeChanged(min,max);
        }
    }
}

void QLogValueAxis::setLabelFormat(const QString &format)
{
    Q_D(QLogValueAxis);
    d->m_format = format;
    emit labelFormatChanged(format);
}

QString QLogValueAxis::labelFormat() const
{
    Q_D(const QLogValueAxis);
    return d->m_format;
}

void QLogValueAxis::setBase(qreal base)
{
    // check if base is correct
    if (qFuzzyCompare(base, 1))
        return;

    if (base > 0) {
        Q_D(QLogValueAxis);
        d->m_base = base;
        emit baseChanged(base);
    }
}

qreal QLogValueAxis::base() const
{
    Q_D(const QLogValueAxis);
    return d->m_base;
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QLogValueAxis::type() const
{
    return AxisTypeLogValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QLogValueAxisPrivate::QLogValueAxisPrivate(QLogValueAxis *q)
    : QAbstractAxisPrivate(q),
      m_min(1),
      m_max(1),
      m_base(10),
      m_format(QString::null)
{
}

QLogValueAxisPrivate::~QLogValueAxisPrivate()
{

}

void QLogValueAxisPrivate::setMin(const QVariant &min)
{
    Q_Q(QLogValueAxis);
    bool ok;
    qreal value = min.toReal(&ok);
    if (ok)
        q->setMin(value);
}

void QLogValueAxisPrivate::setMax(const QVariant &max)
{

    Q_Q(QLogValueAxis);
    bool ok;
    qreal value = max.toReal(&ok);
    if (ok)
        q->setMax(value);
}

void QLogValueAxisPrivate::setRange(const QVariant &min, const QVariant &max)
{
    Q_Q(QLogValueAxis);
    bool ok1;
    bool ok2;
    qreal value1 = min.toReal(&ok1);
    qreal value2 = max.toReal(&ok2);
    if (ok1 && ok2)
        q->setRange(value1, value2);
}

void QLogValueAxisPrivate::setRange(qreal min, qreal max)
{
    Q_Q(QLogValueAxis);
    bool changed = false;

    if (min > max)
        return;

    if (min > 0) {
        if (!qFuzzyCompare(m_min, min)) {
            m_min = min;
            changed = true;
            emit q->minChanged(min);
        }

        if (!qFuzzyCompare(m_max, max)) {
            m_max = max;
            changed = true;
            emit q->maxChanged(max);
        }

        if (changed) {
            emit rangeChanged(min,max);
            emit q->rangeChanged(min, max);
        }
    }
}

void QLogValueAxisPrivate::initializeGraphics(QGraphicsItem *parent)
{
    Q_Q(QLogValueAxis);
    ChartAxisElement *axis(0);

    if (m_chart->chartType() == QChart::ChartTypeCartesian) {
        if (orientation() == Qt::Vertical)
            axis = new ChartLogValueAxisY(q,parent);
        if (orientation() == Qt::Horizontal)
            axis = new ChartLogValueAxisX(q,parent);
    }

    if (m_chart->chartType() == QChart::ChartTypePolar) {
        if (orientation() == Qt::Vertical)
            axis = new PolarChartLogValueAxisRadial(q, parent);
        if (orientation() == Qt::Horizontal)
            axis = new PolarChartLogValueAxisAngular(q, parent);
    }

    m_item.reset(axis);
    QAbstractAxisPrivate::initializeGraphics(parent);
}


void QLogValueAxisPrivate::initializeDomain(AbstractDomain *domain)
{
    if (orientation() == Qt::Vertical) {
        if (!qFuzzyCompare(m_max, m_min)) {
            domain->setRangeY(m_min, m_max);
        } else if ( domain->minY() > 0) {
            setRange(domain->minY(), domain->maxY());
        } else if (domain->maxY() > 0) {
            domain->setRangeY(m_min, domain->maxY());
        } else {
            domain->setRangeY(1, 10);
        }
    }
    if (orientation() == Qt::Horizontal) {
        if (!qFuzzyCompare(m_max, m_min)) {
            domain->setRangeX(m_min, m_max);
        } else if (domain->minX() > 0){
            setRange(domain->minX(), domain->maxX());
        } else if (domain->maxX() > 0) {
            domain->setRangeX(m_min, domain->maxX());
        } else {
            domain->setRangeX(1, 10);
        }
    }
}

#include "moc_qlogvalueaxis.cpp"
#include "moc_qlogvalueaxis_p.cpp"

QT_CHARTS_END_NAMESPACE
