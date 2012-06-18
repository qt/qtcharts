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
#include "declarativechart.h"
#include <QXYSeries>
#include <QVXYModelMapper>
#include <QHXYModelMapper>
#include <QDeclarativeListProperty>

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
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);

    foreach(QObject *child, series->children()) {
        if (qobject_cast<DeclarativeXyPoint *>(child)) {
            DeclarativeXyPoint *point = qobject_cast<DeclarativeXyPoint *>(child);
            series->append(point->x(), point->y());
        } else if(qobject_cast<QVXYModelMapper *>(child)) {
            QVXYModelMapper *mapper = qobject_cast<QVXYModelMapper *>(child);
            mapper->setSeries(series);
        } else if(qobject_cast<QHXYModelMapper *>(child)) {
            QHXYModelMapper *mapper = qobject_cast<QHXYModelMapper *>(child);
            mapper->setSeries(series);
        }
    }
}

DeclarativeXyPoint *DeclarativeXySeries::at(int index)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    if (index < series->count()) {
        QPointF point = series->points().at(index);
        DeclarativeXyPoint *xyPoint = new DeclarativeXyPoint(series);
        xyPoint->setX(point.x());
        xyPoint->setY(point.y());
        return xyPoint;
    }
    return 0;
}


QTCOMMERCIALCHART_END_NAMESPACE
