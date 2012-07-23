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

#include "qintervalsaxis.h"
#include "qintervalsaxis_p.h"
#include "chartintervalsaxisx_p.h"
#include "chartintervalsaxisy_p.h"
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \internal
    \class QIntervalsAxis
    \brief The QIntervalsAxis class is used for manipulating chart's axis.
    \mainclass

    Axis can be setup to show axis line with tick marks, grid lines and shades.
*/

/*!
    \qmlclass Axis QIntervalsAxis
    \brief The Axis element is used for manipulating chart's axes.

    Axis can be setup to show axis line with tick marks, grid lines and shades.

    To access Axes you can use ChartView API. For example:
    \code
    // TODO :)
    \endcode
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QIntervalsAxis::QIntervalsAxis(QObject *parent):
    QValuesAxis(*new QIntervalsAxisPrivate(this),parent)
{
}

/*!
    Destroys the object
*/
QIntervalsAxis::~QIntervalsAxis()
{
}

/*!
    \internal
*/
QIntervalsAxis::QIntervalsAxis(QIntervalsAxisPrivate &d,QObject *parent):QValuesAxis(d,parent)
{

}

/*!
    Appends new interval to the axis with an \a intervalLabel.
    Parameter \a interval specifies the high end limit of the interval.
*/
void QIntervalsAxis::append(const QString& intervalLabel, qreal interval)
{
    Q_D(QIntervalsAxis);

    if (!d->m_intervals.contains(intervalLabel))
    {
        if(d->m_intervals.isEmpty()){
            Range range(d->m_categoryMinimum,interval);
            d->m_intervalsMap.insert(intervalLabel, range);
            d->m_intervals.append(intervalLabel);
        }else if (interval > intervalMax(d->m_intervals.last())){
            Range range = d->m_intervalsMap.value(d->m_intervals.last());
            d->m_intervalsMap.insert(intervalLabel, Range(range.second,interval));
            d->m_intervals.append(intervalLabel);
        }
    }
}

/*!
    Sets to \a min the low end limit of the first interval on the axis.
*/
void QIntervalsAxis::setFisrtIntervalMinimum(qreal min)
{
    Q_D(QIntervalsAxis);
    if(d->m_intervals.isEmpty()){
        d->m_categoryMinimum = min;
    }else{
        Range range = d->m_intervalsMap.value(d->m_intervals.first());
        d->m_intervalsMap.insert(d->m_intervals.first(), Range(min, range.second));
    }
}

/*!
    Returns the low end limit of the interval specified by an \a intervalLabel
*/
qreal QIntervalsAxis::intervalMin(const QString& intervalLabel) const
{
    Q_D(const QIntervalsAxis);
    return d->m_intervalsMap.value(intervalLabel).first;
}

/*!
    Returns the high end limit of the interval specified by an \a intervalLabel
*/
qreal QIntervalsAxis::intervalMax(const QString& intervalLabel) const
{
    Q_D(const QIntervalsAxis);
    return d->m_intervalsMap.value(intervalLabel).second;
}

/*!
    Removes \a interval from axis
*/
void QIntervalsAxis::remove(const QString &intervalLabel)
{
    Q_D(QIntervalsAxis);
    int labelIndex = d->m_intervals.indexOf(intervalLabel);

    // check if such label exists
    if (labelIndex != -1) {
        d->m_intervals.removeAt(labelIndex);
        d->m_intervalsMap.remove(intervalLabel);

        // the range of the interval that follows (if exists) needs to be updated
        if (labelIndex < d->m_intervals.count()) {
            QString label = d->m_intervals.at(labelIndex);
            Range range = d->m_intervalsMap.value(label);

            // set the range
            if (labelIndex == 0) {
                range.first = d->m_categoryMinimum;
                d->m_intervalsMap.insert(label, range);
            } else {
                range.first = d->m_intervalsMap.value(d->m_intervals.at(labelIndex - 1)).second;
                d->m_intervalsMap.insert(label, range);
            }
        }
    }
}

QStringList QIntervalsAxis::intervalsLabels()
{
    Q_D(QIntervalsAxis);
    return d->m_intervals;
}

/*!
  Returns number of categories.
 */
int QIntervalsAxis::count() const
{
    Q_D(const QIntervalsAxis);
    return d->m_intervals.count();
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QIntervalsAxis::type() const
{
    return QAbstractAxis::AxisTypeIntervals;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QIntervalsAxisPrivate::QIntervalsAxisPrivate(QIntervalsAxis* q):
    QValuesAxisPrivate(q),
    m_categoryMinimum(0)
{

}

QIntervalsAxisPrivate::~QIntervalsAxisPrivate()
{

}

int QIntervalsAxisPrivate::ticksCount() const
{
    return m_intervals.count() + 1;
}

void QIntervalsAxisPrivate::handleAxisRangeChanged(qreal min, qreal max,int count)
{
    Q_UNUSED(count);
    Q_UNUSED(min);
    Q_UNUSED(max);
    //m_min = min;
    //m_max = max;
}

ChartAxis* QIntervalsAxisPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QIntervalsAxis);
    if(m_orientation == Qt::Vertical){
        return new ChartIntervalAxisY(q,presenter);
    }else{
        return new ChartIntervalAxisX(q,presenter);
    }
}

#include "moc_qintervalsaxis.cpp"
#include "moc_qintervalsaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
