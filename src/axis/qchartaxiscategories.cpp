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

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartAxisCategories::QChartAxisCategories()
{
    // TODO Auto-generated constructor stub

}

QChartAxisCategories::~QChartAxisCategories()
{
    // TODO Auto-generated destructor stub
}

void QChartAxisCategories::insert(const QBarCategories &categories)
{
    int i=1;
    foreach (QString string , categories) {
        m_map.insert(i,string);
        i++;
    }
    emit updated();
}

void QChartAxisCategories::insert(qreal value,QString label)
{
    m_map.insert(value,label);
    emit updated();
}

void QChartAxisCategories::remove(qreal value)
{
    m_map.remove(value);
    emit updated();
}

void QChartAxisCategories::clear()
{
    m_map.clear();
    emit updated();
}

int QChartAxisCategories::count()
{
    return m_map.count();
}

QList<qreal> QChartAxisCategories::values() const
{
    return m_map.keys();
}

QString QChartAxisCategories::label(qreal value) const
{
    return m_map.value(value);
}

#include "moc_qchartaxiscategories.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
