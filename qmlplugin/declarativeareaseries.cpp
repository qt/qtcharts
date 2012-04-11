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

#include "declarativeareaseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qlineseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeAreaSeries::DeclarativeAreaSeries(QObject *parent) :
    QAreaSeries(new QLineSeries(parent), new QLineSeries(parent))
{
}

QAbstractSeries *DeclarativeAreaSeries::series()
{
    return this;
}

QDeclarativeListProperty<DeclarativeXyPoint> DeclarativeAreaSeries::points()
{
    return QDeclarativeListProperty<DeclarativeXyPoint>(this, 0, &DeclarativeAreaSeries::appendPoints);
}

QDeclarativeListProperty<DeclarativeXyPoint> DeclarativeAreaSeries::lowerPoints()
{
    return QDeclarativeListProperty<DeclarativeXyPoint>(this, 0, &DeclarativeAreaSeries::appendLowerPoints);
}

void DeclarativeAreaSeries::appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                                          DeclarativeXyPoint *element)
{
    QAreaSeries *series = qobject_cast<QAreaSeries *>(list->object);
    if (series) {
        QLineSeries *upper = series->upperSeries();
        upper->append(element->x(), element->y());
    }
}

void DeclarativeAreaSeries::appendLowerPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                                              DeclarativeXyPoint *element)
{
    QAreaSeries *series = qobject_cast<QAreaSeries *>(list->object);
    if (series) {
        QLineSeries *lower = series->lowerSeries();
        lower->append(element->x(), element->y());
    }
}

#include "moc_declarativeareaseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
