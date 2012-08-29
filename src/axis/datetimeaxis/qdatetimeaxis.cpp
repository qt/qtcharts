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

#include "qdatetimeaxis.h"
#include "qdatetimeaxis_p.h"
#include "chartdatetimeaxisx_p.h"
#include "chartdatetimeaxisy_p.h"
#include "domain_p.h"
#include <cmath>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QDateTimeAxis
    \brief The QDateTimeAxis class is used for manipulating chart's axis.
    \mainclass

    The labels can be configured by setting an appropriate DateTime format.
    Note that any date before 4714 BCE or after about 1.4 million CE may not be accurately stored.
    QDateTimeAxis can be setup to show axis line with tick marks, grid lines and shades.

    \image api_datatime_axis.png

    Example code on how to use QDateTimeAxis.
    \code
    QChartView *chartView = new QChartView;
    QLineSeries *series = new QLineSeries;

    QDateTime xValue;
    xValue.setDate(QDate(2012, 1 , 18));
    xValue.setTime(QTime(9, 34));
    series->append(xValue.toMSecsSinceEpoch(), 12);

    xValue.setDate(QDate(2013, 5 , 11));
    xValue.setTime(QTime(11, 14));
    series->append(xValue.toMSecsSinceEpoch(), 22);
    chartView->chart()->addSeries(series);

    // ...
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd-MM-yyyy h:mm");
    chartView->chart()->setAxisX(series, axisX);
    \endcode
*/

/*!
    \qmlclass DateTimeAxis QDateTimeAxis
    \brief The DateTimeAxis element is used for manipulating chart's axes

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
  \qmlproperty real ValuesAxis::min
  Defines the minimum value on the axis.
  When setting this property the max is adjusted if necessary, to ensure that the range remains valid.
*/

/*!
  \property QDateTimeAxis::max
  Defines the maximum value on the axis.
  When setting this property the min is adjusted if necessary, to ensure that the range remains valid.
*/
/*!
  \qmlproperty real ValuesAxis::max
  Defines the maximum value on the axis.
  When setting this property the min is adjusted if necessary, to ensure that the range remains valid.
*/

/*!
  \fn void QDateTimeAxis::minChanged(QDateTime min)
  Axis emits signal when \a min of axis has changed.
*/
/*!
  \qmlsignal ValuesAxis::onMinChanged(QDateTime min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QDateTimeAxis::maxChanged(QDateTime max)
  Axis emits signal when \a max of axis has changed.
*/
/*!
  \qmlsignal ValuesAxis::onMaxChanged(QDateTime max)
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
  \qmlproperty int ValuesAxis::tickCount
  The number of tick marks for the axis.
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QDateTimeAxis::QDateTimeAxis(QObject *parent) :
    QAbstractAxis(*new QDateTimeAxisPrivate(this),parent)
{

}

/*!
    \internal
*/
QDateTimeAxis::QDateTimeAxis(QDateTimeAxisPrivate &d,QObject *parent) : QAbstractAxis(d,parent)
{

}

/*!
    Destroys the object
*/
QDateTimeAxis::~QDateTimeAxis()
{

}

void QDateTimeAxis::setMin(QDateTime min)
{
    Q_D(QDateTimeAxis);
    if (min.isValid())
        setRange(min, qMax(d->m_max, min));
}

QDateTime QDateTimeAxis::min() const
{
    Q_D(const QDateTimeAxis);
    return d->m_min;
}

void QDateTimeAxis::setMax(QDateTime max)
{
    Q_D(QDateTimeAxis);
    if (max.isValid())
        setRange(qMin(d->m_min, max), max);
}

QDateTime QDateTimeAxis::max() const
{
    Q_D(const QDateTimeAxis);
    return d->m_max;
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

    bool changed = false;
    if (d->m_min != min) {
        d->m_min = min;
        changed = true;
        emit minChanged(min);
    }

    if (d->m_max != max) {
        d->m_max = max;
        changed = true;
        emit maxChanged(max);
    }

    if (changed) {
        emit rangeChanged(d->m_min,d->m_max);
        d->emitUpdated();
    }
}

/*!
  Sets \a format string that is used when creating label for the axis out of the QDateTime object.
  Check QDateTime documentation for information on how the string should be defined.
  \sa format()
*/
void QDateTimeAxis::setFormat(QString format)
{
    Q_D(QDateTimeAxis);
    d->m_format = format;
}

/*!
  Returns the format string that is used when creating label for the axis out of the QDateTime object.
  Check QDateTime documentation for information on how the string should be defined.
  \sa setFormat()
*/
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
    if (d->m_tickCount != count && count >=2) {
        d->m_tickCount = count;
        d->emitUpdated();
    }
}

/*!
  \fn int QDateTimeAxis::tickCount() const
  Return number of ticks on the axis
*/
int QDateTimeAxis::tickCount() const
{
    Q_D(const QDateTimeAxis);
    return d->m_tickCount;
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QDateTimeAxis::type() const
{
    return AxisTypeDateTime;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QDateTimeAxisPrivate::QDateTimeAxisPrivate(QDateTimeAxis* q):
    QAbstractAxisPrivate(q),
    m_tickCount(5)
{
    m_min = QDateTime::fromMSecsSinceEpoch(0);
    m_max = QDateTime::fromMSecsSinceEpoch(0);
    m_format = "dd-MM-yyyy\nh:mm";
}

QDateTimeAxisPrivate::~QDateTimeAxisPrivate()
{

}

void QDateTimeAxisPrivate::handleDomainUpdated()
{
    Q_Q(QDateTimeAxis);
    Domain* domain = qobject_cast<Domain*>(sender());
    Q_ASSERT(domain);

    if(orientation()==Qt::Horizontal){
        q->setRange(QDateTime::fromMSecsSinceEpoch(domain->minX()), QDateTime::fromMSecsSinceEpoch(domain->maxX()));
    }else if(orientation()==Qt::Vertical){
        q->setRange(QDateTime::fromMSecsSinceEpoch(domain->minY()), QDateTime::fromMSecsSinceEpoch(domain->maxY()));
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

ChartAxis* QDateTimeAxisPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QDateTimeAxis);
    if(m_orientation == Qt::Vertical){
        return new ChartDateTimeAxisY(q,presenter);
    }else{
        return new ChartDateTimeAxisX(q,presenter);
    }

}

void QDateTimeAxisPrivate::intializeDomain(Domain* domain)
{
    Q_Q(QDateTimeAxis);
    if(m_max == m_min) {
        if(m_orientation==Qt::Vertical){
            q->setRange(QDateTime::fromMSecsSinceEpoch(domain->minY()), QDateTime::fromMSecsSinceEpoch(domain->maxY()));
        }else{
            q->setRange(QDateTime::fromMSecsSinceEpoch(domain->minX()), QDateTime::fromMSecsSinceEpoch(domain->maxX()));
        }
    } else {
        if(m_orientation==Qt::Vertical){
            domain->setRangeY(m_min.toMSecsSinceEpoch(), m_max.toMSecsSinceEpoch());
        }else{
            domain->setRangeX(m_min.toMSecsSinceEpoch(), m_max.toMSecsSinceEpoch());
        }
    }
}

#include "moc_qdatetimeaxis.cpp"
#include "moc_qdatetimeaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
