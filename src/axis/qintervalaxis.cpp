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

#include "qintervalaxis.h"
#include "qintervalaxis_p.h"
#include "chartcategoriesaxisx_p.h"
#include "chartcategoriesaxisy_p.h"
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QIntervalAxis
    \brief The QIntervalAxis class is used for manipulating chart's axis.
    \mainclass

    Axis can be setup to show axis line with tick marks, grid lines and shades.
*/

/*!
    \qmlclass Axis QIntervalAxis
    \brief The Axis element is used for manipulating chart's axes.

    Axis can be setup to show axis line with tick marks, grid lines and shades.

    To access Axes you can use ChartView API. For example:
    \code
    // TODO :)
    \endcode
*/


QIntervalAxis::QIntervalAxis(QObject *parent):
    QValuesAxis(*new QIntervalAxisPrivate(this),parent)
{
}

QIntervalAxis::~QIntervalAxis()
{
}

QIntervalAxis::QIntervalAxis(QIntervalAxisPrivate &d,QObject *parent):QValuesAxis(d,parent)
{

}

/*!
    Appends \a categories to axis
*/
void QIntervalAxis::append(const QString& category, qreal x)
{
    Q_D(QIntervalAxis);
    if (!d->m_categories.contains(category))
    {
    	if(d->m_categories.isEmpty()){
    		Range range(d->m_categoryMinimum,x);
    		d->m_categoriesMap.insert(category,range);
    		d->m_categories.append(category);
    	}else{
    		Range range = d->m_categoriesMap.value(d->m_categories.last());
    		d->m_categoriesMap.insert(category,Range(range.first,x));
    		d->m_categories.append(category);
    	}
    	setRange(d->m_min,x);
    }
}

void QIntervalAxis::setFisrtCategoryMinimum(qreal x)
{
	 Q_D(QIntervalAxis);
	 if(d->m_categories.isEmpty()){
		 d->m_categoryMinimum=x;
	 }else{
		 Range range = d->m_categoriesMap.value(d->m_categories.first());
		 d->m_categoriesMap.insert(d->m_categories.first(),Range(x,range.second));
		 setRange(x,d->m_min);
	 }
}

/*!
    Removes \a category from axis
*/
void QIntervalAxis::remove(const QString &category)
{
	Q_UNUSED(category);
	//TODO
}

QStringList QIntervalAxis::categories()
{
    Q_D(QIntervalAxis);
    return d->m_categories;
}

/*!
  Returns number of categories.
 */
int QIntervalAxis::count() const
{
    Q_D(const QIntervalAxis);
    return d->m_categories.count();
}

/*!
    Returns the type of axis.
*/
QAbstractAxis::AxisType QIntervalAxis::type() const
{
    return AxisTypeCategories;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QIntervalAxisPrivate::QIntervalAxisPrivate(QIntervalAxis* q):
    QValuesAxisPrivate(q),
    m_categoryMinimum(0)
{

}

QIntervalAxisPrivate::~QIntervalAxisPrivate()
{

}

int QIntervalAxisPrivate::ticksCount() const
{
    return m_categories.count()+1;
}

void QIntervalAxisPrivate::handleAxisRangeChanged(qreal min, qreal max,int count)
{
    m_min = min;
    m_max = max;
    m_ticksCount = count;
}

ChartAxis* QIntervalAxisPrivate::createGraphics(ChartPresenter* presenter)
{
	Q_UNUSED(presenter);
   // Q_Q( QCategoriesAxis);
    if(m_orientation == Qt::Vertical){
        return 0;
    }else{
        return 0;
    }
}

#include "moc_qintervalaxis.cpp"
#include "moc_qintervalaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
