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

#include "qcategoryaxis.h"
#include "qcategoryaxis_p.h"
#include "chartcategoryaxisx_p.h"
#include "chartcategoryaxisy_p.h"
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QCategoryAxis
    \brief The QCategoryAxis class is used for manipulating chart's axis.
    \mainclass
*/

/*!
    \qmlclass CategoryAxis QCategoryAxis
    \brief The Axis element is used for manipulating chart's axes.
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QCategoryAxis::QCategoryAxis(QObject *parent):
    QValueAxis(*new QCategoryAxisPrivate(this),parent)
{
}

/*!
    Destroys the object
*/
QCategoryAxis::~QCategoryAxis()
{
    //    Q_D(QValueAxis);
    //    if(d->m_dataset) {
    //        d->m_dataset->removeAxis(this);
    //    }
}

/*!
    \internal
*/
QCategoryAxis::QCategoryAxis(QCategoryAxisPrivate &d,QObject *parent):QValueAxis(d,parent)
{

}

/*!
    Appends new interval to the axis with an \a intervalLabel.
    Interval label has to be unique.
    Parameter \a intervalEnd specifies the high end limit of the interval.
    It has to be greater than the high end limit of the previous interval.
    Otherwise the method returns without adding a new interval.
*/
void QCategoryAxis::append(const QString& intervalLabel, qreal intervalEnd)
{
    Q_D(QCategoryAxis);

    if (!d->m_intervals.contains(intervalLabel))
    {
        if(d->m_intervals.isEmpty()){
            Range range(d->m_categoryMinimum, intervalEnd);
            d->m_intervalsMap.insert(intervalLabel, range);
            d->m_intervals.append(intervalLabel);
        }else if (intervalEnd > intervalMax(d->m_intervals.last())){
            Range range = d->m_intervalsMap.value(d->m_intervals.last());
            d->m_intervalsMap.insert(intervalLabel, Range(range.second, intervalEnd));
            d->m_intervals.append(intervalLabel);
        }
    }
}

/*!
    Sets to \a min the low end limit of the first interval on the axis.
*/
void QCategoryAxis::setFisrtIntervalMinimum(qreal min)
{
    Q_D(QCategoryAxis);
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
qreal QCategoryAxis::intervalMin(const QString& intervalLabel) const
{
    Q_D(const QCategoryAxis);
    return d->m_intervalsMap.value(intervalLabel).first;
}

/*!
    Returns the high end limit of the interval specified by an \a intervalLabel
*/
qreal QCategoryAxis::intervalMax(const QString& intervalLabel) const
{
    Q_D(const QCategoryAxis);
    return d->m_intervalsMap.value(intervalLabel).second;
}

/*!
    Removes an interval specified by the \a intervalLabel from the axis
*/
void QCategoryAxis::remove(const QString &intervalLabel)
{
    Q_D(QCategoryAxis);
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
        d->emitUpdated();
    }
}

/*!
  Replaces \a oldLabel of an existing interval with a \a newLabel
  If the old label does not exist the method returns without making any changes.
 */
void QCategoryAxis::replaceLabel(const QString& oldLabel, const QString& newLabel)
{
    Q_D(QCategoryAxis);
    int labelIndex = d->m_intervals.indexOf(oldLabel);

    // check if such label exists
    if (labelIndex != -1) {
        d->m_intervals.replace(labelIndex, newLabel);
        Range range = d->m_intervalsMap.value(oldLabel);
        d->m_intervalsMap.remove(oldLabel);
        d->m_intervalsMap.insert(newLabel, range);
        d->emitUpdated();
    }

}

/*!
  Returns the list of the intervals labels
 */
QStringList QCategoryAxis::intervalsLabels()
{
    Q_D(QCategoryAxis);
    return d->m_intervals;
}

/*!
  Returns number of intervals.
 */
int QCategoryAxis::count() const
{
    Q_D(const QCategoryAxis);
    return d->m_intervals.count();
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QCategoryAxis::type() const
{
    return QAbstractAxis::AxisTypeCategory;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QCategoryAxisPrivate::QCategoryAxisPrivate(QCategoryAxis* q):
    QValueAxisPrivate(q),
    m_categoryMinimum(0)
{

}

QCategoryAxisPrivate::~QCategoryAxisPrivate()
{

}

int QCategoryAxisPrivate::ticksCount() const
{
    return m_intervals.count() + 1;
}

void QCategoryAxisPrivate::handleAxisRangeChanged(qreal min, qreal max,int count)
{
    Q_UNUSED(count);
    Q_UNUSED(min);
    Q_UNUSED(max);
    //m_min = min;
    //m_max = max;
}

ChartAxis* QCategoryAxisPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QCategoryAxis);
    if(m_orientation == Qt::Vertical){
        return new ChartCategoryAxisY(q,presenter);
    }else{
        return new ChartCategoryAxisX(q,presenter);
    }
}

#include "moc_qcategoryaxis.cpp"
#include "moc_qcategoryaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
