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
    d->m_categories.append(categories);
    emit categoriesChanged();
}

/*!
    Appends \a category to axis
*/
void QCategoriesAxis::append(const QString &category)
{
    Q_D(QCategoriesAxis);
    d->m_categories.append(category);
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
        emit categoriesChanged();
    }
}

/*!
    Inserts \a category to axis at \a index
*/
void QCategoriesAxis::insert(int index, const QString &category)
{
    Q_D(QCategoriesAxis);
    d->m_categories.insert(index,category);
    emit categoriesChanged();
}

/*!
  Removes all categories.
 */
void QCategoriesAxis::clear()
{
    Q_D(QCategoriesAxis);
    d->m_categories.clear();
    emit categoriesChanged();
}

void QCategoriesAxis::setCategories(const QStringList &categories)
{
    Q_D(QCategoriesAxis);
    d->m_categories = categories;
    emit categoriesChanged();
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
    Sets minimum category to \a minCategory.
*/
void QCategoriesAxis::setMin(const QString& minCategory)
{
    Q_D(QCategoriesAxis);
    d->setMinCategory(minCategory);
}

/*!
    Sets maximum category to \a maxCategory.
*/
void QCategoriesAxis::setMax(const QString& maxCategory)
{
    Q_D(QCategoriesAxis);
    d->setMaxCategory(maxCategory);
}

/*!
    Sets range from \a minCategory to \a maxCategory
*/
void QCategoriesAxis::setRange(const QString& minCategory, const QString& maxCategory)
{
    Q_D(QCategoriesAxis);
    d->setRangeCategory(minCategory,maxCategory);
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

void QCategoriesAxisPrivate::setMinCategory(const QString& minCategory)
{
    // Convert the category to value
    int minIndex = m_categories.indexOf(minCategory);
    if (minIndex == -1) {
        return;
    }
    setRange(minIndex,m_max);
}

void QCategoriesAxisPrivate::setMaxCategory(const QString& maxCategory)
{
    // Convert the category to value
    int maxIndex = m_categories.indexOf(maxCategory);
    if (maxIndex == -1) {
        return;
    }
    setRange(m_min,maxIndex);
}

void QCategoriesAxisPrivate::setRangeCategory(const QString& minCategory, const QString& maxCategory)
{
    // TODO:
    int minIndex = m_categories.indexOf(minCategory);
    if (minIndex == -1) {
        return;
    }
    int maxIndex = m_categories.indexOf(maxCategory);
    if (maxIndex == -1) {
        return;
    }
    setRange(minIndex,maxIndex);
}

void QCategoriesAxisPrivate::setMin(const qreal min)
{
    setRange(min,m_max);
}

void QCategoriesAxisPrivate::setMax(const qreal max)
{
    setRange(m_min,max);
}

void QCategoriesAxisPrivate::setRange(const qreal min, const qreal max)
{
    Q_Q(QCategoriesAxis);
    bool changed = false;
    if (!qFuzzyIsNull(m_min - min)) {
        m_min = min;
        changed = true;
    }

    if (!qFuzzyIsNull(m_max - max)) {
        m_max = max;
        changed = true;
    }

    if (changed) {
        emit this->changed(m_min, m_max, m_ticksCount, false);
        emit q->categoriesChanged();
    }
}

int QCategoriesAxisPrivate::ticksCount() const
{
    return m_categories.count()+1;
}

void QCategoriesAxisPrivate::handleAxisRangeChanged(qreal min, qreal max,int count)
{
//   Q_Q(QCategoriesAxis);
//   q->setRange(min,max);
//   q->setTicksCount(count);
    m_min = min;
    m_max = max;
    m_ticksCount = count;

    // TODO?:
    //emit updated();
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

#include "moc_qcategoriesaxis.cpp"
#include "moc_qcategoriesaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
