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

#include "qchartaxiscategories.h"
#include "qchartaxiscategories_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartAxisCategories::QChartAxisCategories():
d_ptr(new QChartAxisCategoriesPrivate(this))
{

}

QChartAxisCategories::~QChartAxisCategories()
{

}

void QChartAxisCategories::insert(const QBarCategories &categories)
{
    int i=1;
    foreach (const QString& string , categories) {
        d_ptr->m_map.insert(i,string);
        i++;
    }
    emit d_ptr->updated();
}

void QChartAxisCategories::insert(qreal value,QString label)
{
    d_ptr->m_map.insert(value,label);
    emit d_ptr->updated();
}

void QChartAxisCategories::remove(qreal value)
{
    d_ptr->m_map.remove(value);
    emit d_ptr->updated();
}

void QChartAxisCategories::clear()
{
    d_ptr->m_map.clear();
    emit d_ptr->updated();
}

int QChartAxisCategories::count()
{
    return d_ptr->m_map.count();
}

QList<qreal> QChartAxisCategories::values() const
{
    return d_ptr->m_map.keys();
}

QString QChartAxisCategories::label(qreal value) const
{
    return d_ptr->m_map.value(value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QChartAxisCategoriesPrivate::QChartAxisCategoriesPrivate(QChartAxisCategories *q):
q_ptr(q)
{

}

QChartAxisCategoriesPrivate::~QChartAxisCategoriesPrivate()
{

}

#include "moc_qchartaxiscategories.cpp"
#include "moc_qchartaxiscategories_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
