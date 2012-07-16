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
    Appends \a category to axis
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
    	}else{
            Range range = d->m_intervalsMap.value(d->m_intervals.last());
            d->m_intervalsMap.insert(intervalLabel, Range(range.second,interval));
            d->m_intervals.append(intervalLabel);
    	}
//        setRange(d->m_min,interval);
    }
}

void QIntervalsAxis::setFisrtIntervalMinimum(qreal min)
{
	 Q_D(QIntervalsAxis);
     if(d->m_intervals.isEmpty()){
         d->m_categoryMinimum = min;
	 }else{
         Range range = d->m_intervalsMap.value(d->m_intervals.first());
         d->m_intervalsMap.insert(d->m_intervals.first(), Range(min, range.second));
         setRange(min, d->m_min);
	 }
}

qreal QIntervalsAxis::intervalMin(const QString& intervalLabel) const
{
    Q_D(const QIntervalsAxis);
    return d->m_intervalsMap.value(intervalLabel).first;
}

qreal QIntervalsAxis::intervalMax(const QString& intervalLabel) const
{
    Q_D(const QIntervalsAxis);
    return d->m_intervalsMap.value(intervalLabel).second;
}

/*!
    Removes \a category from axis
*/
void QIntervalsAxis::remove(const QString &intervalLabel)
{
    Q_UNUSED(intervalLabel);
	//TODO
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
    return AxisTypeCategories;
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
    m_min = min;
    m_max = max;
//    m_ticksCount = count;
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
