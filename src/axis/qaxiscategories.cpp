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

#include "qaxiscategories.h"
#include "qaxiscategories_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QAxisCategories
    \brief The QAxisCategoriess class is used for manipulating axis's categories.
    \mainclass

    Each axis can have categories instead of numerical representation. The typical use case
    is bar chart, where categories are always show on X axis.
*/


QAxisCategories::QAxisCategories():
d_ptr(new QAxisCategoriesPrivate(this))
{

}

/*!
  Destroys the object.
*/
QAxisCategories::~QAxisCategories()
{

}

/*!
  Inserts \a categories to axis. First item in list is assumed to be at x = 0, next at x = 1 and so on
 */
void QAxisCategories::insert(const QStringList &categories)
{
    int i=0;
    foreach (const QString& string , categories) {
        d_ptr->m_map.insert(i,string);
        i++;
    }
    emit d_ptr->updated();
}


/*!
  Inserts category, instead of \a value on axis a \a label will be shown.
 */
void QAxisCategories::insert(qreal value,QString label)
{
    d_ptr->m_map.insert(value,label);
    emit d_ptr->updated();
}

/*!
  Removes category for \a value.
 */
void QAxisCategories::remove(qreal value)
{
    d_ptr->m_map.remove(value);
    emit d_ptr->updated();
}

/*!
  Removes all categories.
 */
void QAxisCategories::clear()
{
    d_ptr->m_map.clear();
    emit d_ptr->updated();
}

/*!
  Returns number of categories.
 */
int QAxisCategories::count()
{
    return d_ptr->m_map.count();
}

/*!
  Returns all values of categories.
 */
QList<qreal> QAxisCategories::values() const
{
    return d_ptr->m_map.keys();
}

/*!
  Returns label for given \a value.
 */
QString QAxisCategories::label(qreal value) const
{
    return d_ptr->m_map.value(value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAxisCategoriesPrivate::QAxisCategoriesPrivate(QAxisCategories *q):
q_ptr(q)
{

}

QAxisCategoriesPrivate::~QAxisCategoriesPrivate()
{

}

#include "moc_qaxiscategories.cpp"
#include "moc_qaxiscategories_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
