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
#include <QXYModelMapper>
#include <QDeclarativeListProperty>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeXySeries::DeclarativeXySeries()
{
}

DeclarativeXySeries::~DeclarativeXySeries()
{
}

QColor DeclarativeXySeries::penColor()
{
    // All the inherited objects must be of type QXYSeries, so it is safe to cast
    QXYSeries *series = reinterpret_cast<QXYSeries *>(this);
    return series->pen().color();
}

void DeclarativeXySeries::setPenColor(QColor color)
{
    QXYSeries *series = reinterpret_cast<QXYSeries *>(this);
    QPen pen = series->pen();
    pen.setColor(color);
    series->setPen(pen);
}

DeclarativeXyPoint *DeclarativeXySeries::at(int index)
{
    QXYSeries *series = reinterpret_cast<QXYSeries *>(this);
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
