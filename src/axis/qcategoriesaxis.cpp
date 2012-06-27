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
    int minIndex = d->m_categories.indexOf(minCategory);
    if (minIndex == -1)
        return;
//    else
//        QAbstractAxis::setMin(minIndex);
}

/*!
    Sets maximum category to \a maxCategory.
*/
void QCategoriesAxis::setMax(const QString& maxCategory)
{
    Q_D(QCategoriesAxis);
    int maxIndex = d->m_categories.indexOf(maxCategory);
    if (maxIndex == -1)
        return;
//    else
//        QAbstractAxis::setMax(maxIndex);
}

/*!
    Sets range from \a minCategory to \a maxCategory
*/
void QCategoriesAxis::setRange(const QString& minCategory, const QString& maxCategory)
{
    // TODO: what if maxCategory < minCategory?
    setMin(minCategory);
    setMax(maxCategory);
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


void QCategoriesAxisPrivate::setMin(const QVariant& min)
{
    Q_Q(QCategoriesAxis);
    q->setMin(min.toString());
}

void QCategoriesAxisPrivate::setMax(const QVariant& max)
{
    Q_Q(QCategoriesAxis);
    q->setMax(max.toString());
}

void QCategoriesAxisPrivate::setRange(const QVariant& min, const QVariant& max)
{
   Q_Q(QCategoriesAxis);
   q->setRange(min.toString(),max.toString());
}

int QCategoriesAxisPrivate::ticksCount() const
{
    return m_categories.count()+1;
}

#include "moc_qcategoriesaxis.cpp"
#include "moc_qcategoriesaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
