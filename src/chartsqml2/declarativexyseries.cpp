/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/


#include "declarativexyseries.h"
#include "declarativexypoint.h"
#include <QtCharts/QVXYModelMapper>
#include <QtCharts/QHXYModelMapper>

QT_CHARTS_BEGIN_NAMESPACE

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

    foreach (QObject *child, series->children()) {
        if (qobject_cast<DeclarativeXYPoint *>(child)) {
            DeclarativeXYPoint *point = qobject_cast<DeclarativeXYPoint *>(child);
            series->append(point->x(), point->y());
        } else if (qobject_cast<QVXYModelMapper *>(child)) {
            QVXYModelMapper *mapper = qobject_cast<QVXYModelMapper *>(child);
            mapper->setSeries(series);
        } else if (qobject_cast<QHXYModelMapper *>(child)) {
            QHXYModelMapper *mapper = qobject_cast<QHXYModelMapper *>(child);
            mapper->setSeries(series);
        }
    }
}

void DeclarativeXySeries::append(qreal x, qreal y)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    series->append(x, y);
}

void DeclarativeXySeries::replace(qreal oldX, qreal oldY, qreal newX, qreal newY)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    series->replace(oldX, oldY, newX, newY);
}

void DeclarativeXySeries::replace(int index, qreal newX, qreal newY)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    series->replace(index, newX, newY);
}

void DeclarativeXySeries::remove(qreal x, qreal y)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    series->remove(x, y);
}

void DeclarativeXySeries::remove(int index)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    series->remove(index);
}

void DeclarativeXySeries::insert(int index, qreal x, qreal y)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    series->insert(index, QPointF(x, y));
}

void DeclarativeXySeries::clear()
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    series->clear();
}

QPointF DeclarativeXySeries::at(int index)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    if (index >= 0 || index < series->count())
        return series->points().at(index);
    return QPointF(0, 0);
}

QT_CHARTS_END_NAMESPACE
