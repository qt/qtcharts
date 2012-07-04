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

#include "qcategoriesaxis.h"
#include "qcategoriesaxis_p.h"
#include "chartcategoriesaxisx_p.h"
#include "chartcategoriesaxisy_p.h"
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QCategoriesAxis::QCategoriesAxis(QObject *parent):
    QAbstractAxis(*new QCategoriesAxisPrivate(this),parent)
{
}

QCategoriesAxis::~QCategoriesAxis()
{
}

QCategoriesAxis::QCategoriesAxis(QCategoriesAxisPrivate &d,QObject *parent):QAbstractAxis(d,parent)
{

}

/*!
    Appends \a categories to axis
*/
void QCategoriesAxis::append(const QStringList &categories)
{
    Q_D(QCategoriesAxis);
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
void QCategoriesAxis::append(const QString &category)
{
	Q_D(QCategoriesAxis);
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
void QCategoriesAxis::remove(const QString &category)
{
    Q_D(QCategoriesAxis);
    if (d->m_categories.contains(category)) {
        d->m_categories.removeAt(d->m_categories.indexOf(category));
        setRange(d->m_categories.first(),d->m_categories.last());
        emit categoriesChanged();
    }
}

/*!
    Inserts \a category to axis at \a index
*/
void QCategoriesAxis::insert(int index, const QString &category)
{
    Q_D(QCategoriesAxis);
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
void QCategoriesAxis::clear()
{
    Q_D(QCategoriesAxis);
    d->m_categories.clear();
    setRange(QString::null,QString::null);
    emit categoriesChanged();
}

void QCategoriesAxis::setCategories(const QStringList &categories)
{
    Q_D(QCategoriesAxis);
    if(d->m_categories!=categories){
    d->m_categories = categories;
    setRange(categories.first(),categories.last());
    emit categoriesChanged();
    }
}

QStringList QCategoriesAxis::categories()
{
    Q_D(QCategoriesAxis);
    return d->m_categories;
}

/*!
  Returns number of categories.
 */
int QCategoriesAxis::count() const
{
    Q_D(const QCategoriesAxis);
    return d->m_categories.count();
}

/*!
    Returns category at \a index. Index must be valid.
*/
QString QCategoriesAxis::at(int index) const
{
    Q_D(const QCategoriesAxis);
    return d->m_categories.at(index);
}

/*!
    Sets minimum category to \a min.
*/
void QCategoriesAxis::setMin(const QString& min)
{
    Q_D(QCategoriesAxis);
    setRange(min,d->m_maxCategory);
}

/*!
    Returns minimum category.
*/
QString QCategoriesAxis::min() const
{
    Q_D(const QCategoriesAxis);
    return d->m_minCategory;
}

/*!
    Sets maximum category to \a max.
*/
void QCategoriesAxis::setMax(const QString& max)
{
    Q_D(QCategoriesAxis);
    setRange(d->m_minCategory,max);
}

/*!
    Returns maximum category
*/
QString QCategoriesAxis::max() const
{
    Q_D(const QCategoriesAxis);
    return d->m_maxCategory;
}

/*!
    Sets range from \a minCategory to \a maxCategory
*/
void QCategoriesAxis::setRange(const QString& minCategory, const QString& maxCategory)
{
    Q_D(QCategoriesAxis);

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
        changed = true;
    }

    if (!qFuzzyIsNull(d->m_max - (maxIndex))) {
        d->m_max = maxIndex;
        d->m_maxCategory = maxCategory;
        changed = true;
    }

    if ((changed)) {
        d->emitRange();
        emit categoriesChanged();
    }
}

/*!
    Returns the type of axis.
*/
QAbstractAxis::AxisType QCategoriesAxis::type() const
{
    return AxisTypeCategories;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QCategoriesAxisPrivate::QCategoriesAxisPrivate(QCategoriesAxis* q):
    QAbstractAxisPrivate(q)
{

}

QCategoriesAxisPrivate::~QCategoriesAxisPrivate()
{

}

void QCategoriesAxisPrivate::setMin(const QVariant &min)
{
    setRange(min,m_maxCategory);
}

void QCategoriesAxisPrivate::setMax(const QVariant &max)
{
    setRange(m_minCategory,max);
}

void QCategoriesAxisPrivate::setRange(const QVariant &min, const QVariant &max)
{
    Q_Q(QCategoriesAxis);
    QString value1 = min.toString();
    QString value2 = max.toString();
    q->setRange(value1,value2);
}

int QCategoriesAxisPrivate::ticksCount() const
{
    return m_categories.count()+1;
}

void QCategoriesAxisPrivate::handleAxisRangeChanged(qreal min, qreal max,int count)
{
    m_min = min;
    m_max = max;
    m_ticksCount = count;
}

ChartAxis* QCategoriesAxisPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q( QCategoriesAxis);
    if(m_orientation == Qt::Vertical){
        return new ChartCategoriesAxisY(q,presenter);
    }else{
        return new ChartCategoriesAxisX(q,presenter);
    }
}

void QCategoriesAxisPrivate::emitRange()
{
	Q_Q( QCategoriesAxis);
	if(!q->signalsBlocked()) {
		emit changed(m_min -0.5, m_max +0.5, qCeil(m_max + 0.5) -qCeil(m_min - 0.5) +1, false);
	}
}


#include "moc_qcategoriesaxis.cpp"
#include "moc_qcategoriesaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
