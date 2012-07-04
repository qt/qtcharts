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

#include "qbarcategoriesaxis.h"
#include "qbarcategoriesaxis_p.h"
#include "chartcategoriesaxisx_p.h"
#include "chartcategoriesaxisy_p.h"
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QBarCategoriesAxis
    \brief The QBarCategoriesAxis class is used for manipulating chart's axis.
    \mainclass

    Axis can be setup to show axis line with tick marks, grid lines and shades.
*/

/*!
    \qmlclass Axis QBarCategoriesAxis
    \brief The Axis element is used for manipulating chart's axes.

    Axis can be setup to show axis line with tick marks, grid lines and shades.

    To access Axes you can use ChartView API. For example:
    \code
        ChartView {
            axisX.min: "Feb"
            axisX.max: "Jun"
            // Add a few series...
        }
    \endcode
*/

/*!
  \property QBarCategoriesAxis::categories
  Defines the categories of axis
*/
/*!
  \qmlproperty QStringList Axis::categories
  Defines the categories of axis
*/

/*!
  \property QBarCategoriesAxis::min
  Defines the minimum value on the axis.
*/
/*!
  \qmlproperty real Axis::min
  Defines the minimum value on the axis.
*/

/*!
  \property QBarCategoriesAxis::max
  Defines the maximum value on the axis.
*/
/*!
  \qmlproperty real Axis::max
  Defines the maximum value on the axis.
*/

/*!
  \fn void QBarCategoriesAxis::minChanged(const QString &min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QBarCategoriesAxis::maxChanged(const QString &max)
  Axis emits signal when \a max of axis has changed.
*/

/*!
  \fn void QBarCategoriesAxis::rangeChanged(const QString &min, const QString &max)
  Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QBarCategoriesAxis::QBarCategoriesAxis(QObject *parent):
    QAbstractAxis(*new QBarCategoriesAxisPrivate(this),parent)
{
}

/*!
    Destroys the object
*/
QBarCategoriesAxis::~QBarCategoriesAxis()
{
}

/*!
    \internal
*/
QBarCategoriesAxis::QBarCategoriesAxis(QBarCategoriesAxisPrivate &d,QObject *parent):QAbstractAxis(d,parent)
{

}

/*!
    Appends \a categories to axis
*/
void QBarCategoriesAxis::append(const QStringList &categories)
{
    Q_D(QBarCategoriesAxis);
    if (d->m_categories.isEmpty()) {
    	d->m_categories.append(categories);
    	setRange(categories.first(),categories.last());
    }else{
    	d->m_categories.append(categories);
    }

    emit categoriesChanged();
}

/*!
    Appends \a category to axis
*/
void QBarCategoriesAxis::append(const QString &category)
{
	Q_D(QBarCategoriesAxis);
	if (d->m_categories.isEmpty()) {
		d->m_categories.append(category);
		setRange(category,category);
	}else{
		d->m_categories.append(category);
	}
	emit categoriesChanged();
}

/*!
    Removes \a category from axis
*/
void QBarCategoriesAxis::remove(const QString &category)
{
    Q_D(QBarCategoriesAxis);
    if (d->m_categories.contains(category)) {
        d->m_categories.removeAt(d->m_categories.indexOf(category));
        setRange(d->m_categories.first(),d->m_categories.last());
        emit categoriesChanged();
    }
}

/*!
    Inserts \a category to axis at \a index
*/
void QBarCategoriesAxis::insert(int index, const QString &category)
{
    Q_D(QBarCategoriesAxis);
    if (d->m_categories.isEmpty()) {
    	d->m_categories.insert(index,category);
    	setRange(category,category);
    }else{

    }
    emit categoriesChanged();
}

/*!
  Removes all categories.
 */
void QBarCategoriesAxis::clear()
{
    Q_D(QBarCategoriesAxis);
    d->m_categories.clear();
    setRange(QString::null,QString::null);
    emit categoriesChanged();
}

void QBarCategoriesAxis::setCategories(const QStringList &categories)
{
    Q_D(QBarCategoriesAxis);
    if(d->m_categories!=categories){
    d->m_categories = categories;
    setRange(categories.first(),categories.last());
    emit categoriesChanged();
    }
}

QStringList QBarCategoriesAxis::categories()
{
    Q_D(QBarCategoriesAxis);
    return d->m_categories;
}

/*!
  Returns number of categories.
 */
int QBarCategoriesAxis::count() const
{
    Q_D(const QBarCategoriesAxis);
    return d->m_categories.count();
}

/*!
    Returns category at \a index. Index must be valid.
*/
QString QBarCategoriesAxis::at(int index) const
{
    Q_D(const QBarCategoriesAxis);
    return d->m_categories.at(index);
}

/*!
    Sets minimum category to \a min.
*/
void QBarCategoriesAxis::setMin(const QString& min)
{
    Q_D(QBarCategoriesAxis);
    setRange(min,d->m_maxCategory);
}

/*!
    Returns minimum category.
*/
QString QBarCategoriesAxis::min() const
{
    Q_D(const QBarCategoriesAxis);
    return d->m_minCategory;
}

/*!
    Sets maximum category to \a max.
*/
void QBarCategoriesAxis::setMax(const QString& max)
{
    Q_D(QBarCategoriesAxis);
    setRange(d->m_minCategory,max);
}

/*!
    Returns maximum category
*/
QString QBarCategoriesAxis::max() const
{
    Q_D(const QBarCategoriesAxis);
    return d->m_maxCategory;
}

/*!
    Sets range from \a minCategory to \a maxCategory
*/
void QBarCategoriesAxis::setRange(const QString& minCategory, const QString& maxCategory)
{
    Q_D(QBarCategoriesAxis);

    int minIndex = d->m_categories.indexOf(minCategory);
    if (minIndex == -1) {
        return;
    }
    int maxIndex = d->m_categories.indexOf(maxCategory);
    if (maxIndex == -1) {
        return;
    }

    if (maxIndex <= minIndex) {
        // max must be greater than min
        return;
    }

    bool changed = false;
    if (!qFuzzyIsNull(d->m_min - (minIndex))) {
    	d->m_minCategory = minCategory;
        d->m_min = minIndex;
        emit minChanged(minCategory);
        changed = true;
    }

    if (!qFuzzyIsNull(d->m_max - (maxIndex))) {
        d->m_max = maxIndex;
        d->m_maxCategory = maxCategory;
        emit maxChanged(maxCategory);
        changed = true;
    }

    if ((changed)) {
        d->emitRange();
        emit categoriesChanged();
    }
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QBarCategoriesAxis::type() const
{
    return AxisTypeCategories;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarCategoriesAxisPrivate::QBarCategoriesAxisPrivate(QBarCategoriesAxis* q):
    QAbstractAxisPrivate(q)
{

}

QBarCategoriesAxisPrivate::~QBarCategoriesAxisPrivate()
{

}

void QBarCategoriesAxisPrivate::setMin(const QVariant &min)
{
    setRange(min,m_maxCategory);
}

void QBarCategoriesAxisPrivate::setMax(const QVariant &max)
{
    setRange(m_minCategory,max);
}

void QBarCategoriesAxisPrivate::setRange(const QVariant &min, const QVariant &max)
{
    Q_Q(QBarCategoriesAxis);
    QString value1 = min.toString();
    QString value2 = max.toString();
    q->setRange(value1,value2);
}

int QBarCategoriesAxisPrivate::ticksCount() const
{
    return m_categories.count()+1;
}

void QBarCategoriesAxisPrivate::handleAxisRangeChanged(qreal min, qreal max,int count)
{
    m_min = min;
    m_max = max;
    m_ticksCount = count;
}

ChartAxis* QBarCategoriesAxisPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q( QBarCategoriesAxis);
    if(m_orientation == Qt::Vertical){
        return new ChartCategoriesAxisY(q,presenter);
    }else{
        return new ChartCategoriesAxisX(q,presenter);
    }
}

void QBarCategoriesAxisPrivate::emitRange()
{
	Q_Q( QBarCategoriesAxis);
	if(!q->signalsBlocked()) {
		emit changed(m_min -0.5, m_max +0.5, qCeil(m_max + 0.5) -qCeil(m_min - 0.5) +1, false);
	}
}


#include "moc_qbarcategoriesaxis.cpp"
#include "moc_qbarcategoriesaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
