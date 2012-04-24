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

//#include "DeclarativeXySeries.h"
#include "declarativexyseries.h"
#include "qxyseries.h"
#include "declarativechart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeXySeries::DeclarativeXySeries()
{
}

DeclarativeXySeries::~DeclarativeXySeries()
{
}

void DeclarativeXySeries::classBegin()
{
}

void DeclarativeXySeries::componentComplete()
{
    QAbstractSeries *thisObj = reinterpret_cast<QAbstractSeries *>(series());
    DeclarativeChart *declarativeChart = qobject_cast<DeclarativeChart *>(thisObj->parent());

    if (declarativeChart) {
        QChart *chart = qobject_cast<QChart *>(declarativeChart->m_chart);
        Q_ASSERT(chart);
        chart->addSeries(thisObj);
    }
}

void DeclarativeXySeries::appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                                       DeclarativeXyPoint *element)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(list->object);
    if (series)
        series->append(element->x(), element->y());
}

QTCOMMERCIALCHART_END_NAMESPACE
