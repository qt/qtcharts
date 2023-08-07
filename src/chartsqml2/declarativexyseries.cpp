// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include "declarativexyseries_p.h"
#include "declarativexypoint_p.h"
#include <QtCharts/QVXYModelMapper>
#include <QtCharts/QHXYModelMapper>

QT_BEGIN_NAMESPACE

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

void DeclarativeXySeries::removePoints(int index, int count)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(xySeries());
    Q_ASSERT(series);
    series->removePoints(index, count);
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
    if (index >= 0 && index < series->count())
        return series->points().at(index);
    return QPointF(0, 0);
}

QT_END_NAMESPACE
