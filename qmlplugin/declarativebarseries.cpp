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

#include "declarativebarseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qbarseries.h"
#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeBarSeries::DeclarativeBarSeries(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void DeclarativeBarSeries::componentComplete()
{
}

void DeclarativeBarSeries::setBarCategories(QStringList categories)
{
    m_categories = categories;

    if (m_series) {
        delete m_series;
        m_series = 0;
    }

    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(parent());
    if (declarativeChart) {
        QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        Q_ASSERT(chart);

        m_series = new QBarSeries(m_categories);

        // TODO: use data from model
        QBarSet *set0 = new QBarSet("Bub");
        QBarSet *set1 = new QBarSet("Bob");
        QBarSet *set2 = new QBarSet("Guybrush");

        *set0 << 1 << 2 << 3 << 4 << 5 << 6;
        *set1 << 5 << 1 << 2 << 4 << 1 << 7;
        *set2 << 3 << 5 << 8 << 13 << 8 << 5;

        m_series->appendBarSet(set0);
        m_series->appendBarSet(set1);
        m_series->appendBarSet(set2);

        chart->addSeries(m_series);
    }
}

QStringList DeclarativeBarSeries::barCategories()
{
    return m_categories;
}

#include "moc_declarativebarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
