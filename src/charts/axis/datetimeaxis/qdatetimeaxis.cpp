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

#include <QtCharts/QDateTimeAxis>
#include <private/qdatetimeaxis_p.h>
#include <private/chartdatetimeaxisx_p.h>
#include <private/chartdatetimeaxisy_p.h>
#include <private/polarchartdatetimeaxisangular_p.h>
#include <private/polarchartdatetimeaxisradial_p.h>
#include <private/abstractdomain_p.h>
#include <QtCharts/QChart>
#include <float.h>
#include <cmath>

QT_CHARTS_BEGIN_NAMESPACE
/*!
    \class QDateTimeAxis
    \inmodule Qt Charts
    \brief The QDateTimeAxis class is used for manipulating chart's axis.

    The labels can be configured by setting an appropriate DateTime format.
    QDateTimeAxis works correctly with dates from 4714 BCE to 287396 CE.
    There are also other limitiation related to QDateTime. Please refer to QDateTime documentation.
    QDateTimeAxis can be setup to show axis line with tick marks, grid lines and shades.

    Note: QDateTimeAxis is disabled on platforms that define qreal as float.

    \image api_datatime_axis.png

    QDateTimeAxis can be used with any QXYSeries.
    To add a data point to the series QDateTime::toMSecsSinceEpoch() is used.
    \code
    QLineSeries *series = new QLineSeries;

    QDateTime xValue;
    xValue.setDate(QDate(2012, 1 , 18));
    xValue.setTime(QTime(9, 34));
    qreal yValue = 12;
    series->append(xValue.toMSecsSinceEpoch(), yValue);

    xValue.setDate(QDate(2013, 5 , 11));
    xValue.setTime(QTime(11, 14));
    qreal yValue = 22;
    series->append(xValue.toMSecsSinceEpoch(), yValue);
    \endcode

    Adding the series to the chart and setting up the QDateTimeAxis.
    \code
    QChartView *chartView = new QChartView;
    chartView->chart()->addSeries(series);

    // ...
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd-MM-yyyy h:mm");
    chartView->chart()->setAxisX(axisX, series);
    \endcode
*/

/*!
    \qmltype DateTimeAxis
    \instantiates QDateTimeAxis
    \inqmlmodule QtCharts

    \brief The DateTimeAxis element is used for manipulating chart's axes.
    \inherits AbstractAxis

    The labels can be configured by setting an appropriate DateTime format.
    Note that any date before 4714 BCE or after about 1.4 million CE may not be accurately stored.
    DateTimeAxis can be setup to show axis line with tick marks, grid lines and shades.
*/

/*!
  \property QDateTimeAxis::min
  Defines the minimum value on the axis.
  When setting this property the max is adjusted if necessary, to ensure that the range remains valid.
*/
/*!
  \qmlproperty datetime DateTimeAxis::min
  Defines the minimum value on the axis.
  When setting this property the max is adjusted if necessary, to ensure that the range remains valid.
*/

/*!
  \property QDateTimeAxis::max
  Defines the maximum value on the axis.
  When setting this property the min is adjusted if necessary, to ensure that the range remains valid.
*/
/*!
  \qmlproperty datetime DateTimeAxis::max
  Defines the maximum value on the axis.
  When setting this property the min is adjusted if necessary, to ensure that the range remains valid.
*/

/*!
  \fn void QDateTimeAxis::minChanged(QDateTime min)
  Axis emits signal when \a min of axis has changed.
*/
/*!
  \qmlsignal DateTimeAxis::onMinChanged(datetime min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QDateTimeAxis::maxChanged(QDateTime max)
  Axis emits signal when \a max of axis has changed.
*/
/*!
  \qmlsignal DateTimeAxis::onMaxChanged(datetime max)
  Axis emits signal when \a max of axis has changed.
*/

/*!
  \fn void QDateTimeAxis::rangeChanged(QDateTime min, QDateTime max)
  Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
  \property QDateTimeAxis::tickCount
  The number of tick marks for the axis.
*/

/*!
  \qmlproperty int DateTimeAxis::tickCount
  The number of tick marks for the axis.
*/

/*!
  \property QDateTimeAxis::format
  The format string that is used when creating label for the axis out of a QDateTime object.
  Check QDateTime documentation for information on how the string should be defined.

  \sa QChart::locale
*/
/*!
  \qmlproperty string DateTimeAxis::format
  The format string that is used when creating label for the axis out of a QDateTime object.
  Check QDateTime documentation for information on how the string should be defined.
*/

/*!
  \fn void QDateTimeAxis::tickCountChanged(int tickCount)
  Axis emits signal when \a tickCount number on axis have changed.
*/
/*!
  \qmlsignal DateTimeAxis::tickCountChanged(int tickCount)
  Axis emits signal when \a tickCount number on axis have changed.
*/

/*!
  \fn void QDateTimeAxis::formatChanged(QString format)
  Axis emits signal when \a format of the axis has changed.
*/
/*!
  \qmlsignal DateTimeAxis::onFormatChanged(string format)
  Axis emits signal when \a format of the axis has changed.
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QDateTimeAxis::QDateTimeAxis(QObject *parent) :
    QAbstractAxis(*new QDateTimeAxisPrivate(this), parent)
{

}

/*!
    \internal
*/
QDateTimeAxis::QDateTimeAxis(QDateTimeAxisPrivate &d, QObject *parent) : QAbstractAxis(d, parent)
{

}

/*!
    Destroys the object.
*/
QDateTimeAxis::~QDateTimeAxis()
{
    Q_D(QDateTimeAxis);
    if (d->m_chart)
        d->m_chart->removeAxis(this);
}

void QDateTimeAxis::setMin(QDateTime min)
{
    Q_D(QDateTimeAxis);
    if (min.isValid())
        d->setRange(min.toMSecsSinceEpoch(), qMax(d->m_max, qreal(min.toMSecsSinceEpoch())));
}

QDateTime QDateTimeAxis::min() const
{
    Q_D(const QDateTimeAxis);
    return QDateTime::fromMSecsSinceEpoch(d->m_min);
}

void QDateTimeAxis::setMax(QDateTime max)
{
    Q_D(QDateTimeAxis);
    if (max.isValid())
        d->setRange(qMin(d->m_min, qreal(max.toMSecsSinceEpoch())), max.toMSecsSinceEpoch());
}

QDateTime QDateTimeAxis::max() const
{
    Q_D(const QDateTimeAxis);
    return QDateTime::fromMSecsSinceEpoch(d->m_max);
}

/*!
  Sets range from \a min to \a max on the axis.
  If min is greater than max then this function returns without making any changes.
*/
void QDateTimeAxis::setRange(QDateTime min, QDateTime max)
{
    Q_D(QDateTimeAxis);
    if (!min.isValid() || !max.isValid() || min > max)
        return;

    d->setRange(min.toMSecsSinceEpoch(),max.toMSecsSinceEpoch());
}

void QDateTimeAxis::setFormat(QString format)
{
    Q_D(QDateTimeAxis);
    if (d->m_format != format) {
        d->m_format = format;
        emit formatChanged(format);
    }
}

QString QDateTimeAxis::format() const
{
    Q_D(const QDateTimeAxis);
    return d->m_format;
}

/*!
  Sets \a count for ticks on the axis.
*/
void QDateTimeAxis::setTickCount(int count)
{
    Q_D(QDateTimeAxis);
    if (d->m_tickCount != count && count >= 2) {
        d->m_tickCount = count;
       emit tickCountChanged(count);
    }
}

/*!
  \fn int QDateTimeAxis::tickCount() const
  Return number of ticks on the axis.
*/
int QDateTimeAxis::tickCount() const
{
    Q_D(const QDateTimeAxis);
    return d->m_tickCount;
}

/*!
  Returns the type of the axis.
*/
QAbstractAxis::AxisType QDateTimeAxis::type() const
{
    return AxisTypeDateTime;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QDateTimeAxisPrivate::QDateTimeAxisPrivate(QDateTimeAxis *q)
    : QAbstractAxisPrivate(q),
      m_min(0),
      m_max(0),
      m_tickCount(5)
{
    m_format = QStringLiteral("dd-MM-yyyy\nh:mm");
}

QDateTimeAxisPrivate::~QDateTimeAxisPrivate()
{

}

void QDateTimeAxisPrivate::setRange(qreal min,qreal max)
{
    Q_Q(QDateTimeAxis);

    bool changed = false;

    if (m_min != min) {
        m_min = min;
        changed = true;
        emit q->minChanged(QDateTime::fromMSecsSinceEpoch(min));
    }

    if (m_max != max) {
        m_max = max;
        changed = true;
        emit q->maxChanged(QDateTime::fromMSecsSinceEpoch(max));
    }

    if (changed) {
        emit q->rangeChanged(QDateTime::fromMSecsSinceEpoch(min), QDateTime::fromMSecsSinceEpoch(max));
        emit rangeChanged(m_min,m_max);
    }
}


void QDateTimeAxisPrivate::setMin(const QVariant &min)
{
    Q_Q(QDateTimeAxis);
    if (min.canConvert(QVariant::DateTime))
        q->setMin(min.toDateTime());
}

void QDateTimeAxisPrivate::setMax(const QVariant &max)
{

    Q_Q(QDateTimeAxis);
    if (max.canConvert(QVariant::DateTime))
        q->setMax(max.toDateTime());
}

void QDateTimeAxisPrivate::setRange(const QVariant &min, const QVariant &max)
{
    Q_Q(QDateTimeAxis);
    if (min.canConvert(QVariant::DateTime) && max.canConvert(QVariant::DateTime))
        q->setRange(min.toDateTime(), max.toDateTime());
}

void QDateTimeAxisPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QDateTimeAxis);
    ChartAxisElement *axis(0);
    if (m_chart->chartType() == QChart::ChartTypeCartesian) {
        if (orientation() == Qt::Vertical)
            axis = new ChartDateTimeAxisY(q,parent);
        if (orientation() == Qt::Horizontal)
            axis = new ChartDateTimeAxisX(q,parent);
    }

    if (m_chart->chartType() == QChart::ChartTypePolar) {
        if (orientation() == Qt::Vertical)
            axis = new PolarChartDateTimeAxisRadial(q, parent);
        if (orientation() == Qt::Horizontal)
            axis = new PolarChartDateTimeAxisAngular(q, parent);
    }

    m_item.reset(axis);
    QAbstractAxisPrivate::initializeGraphics(parent);
}

void QDateTimeAxisPrivate::initializeDomain(AbstractDomain *domain)
{
    if (m_max == m_min) {
        if (orientation() == Qt::Vertical)
            setRange(domain->minY(), domain->maxY());
        else
            setRange(domain->minX(), domain->maxX());
    } else {
        if (orientation() == Qt::Vertical)
            domain->setRangeY(m_min, m_max);
        else
            domain->setRangeX(m_min, m_max);
    }
}

#include "moc_qdatetimeaxis.cpp"
#include "moc_qdatetimeaxis_p.cpp"

QT_CHARTS_END_NAMESPACE
