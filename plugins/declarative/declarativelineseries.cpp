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

#include "declarativelineseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qlineseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeLineSeries::DeclarativeLineSeries(QObject *parent) :
    QLineSeries(parent)
{
    connect(this, SIGNAL(pointAdded(int)), this, SLOT(handleCountChanged(int)));
    connect(this, SIGNAL(pointRemoved(int)), this, SLOT(handleCountChanged(int)));
}

QXYSeries *DeclarativeLineSeries::xySeries()
{
    return this;
}

void DeclarativeLineSeries::setAxisX(QAbstractAxis *axis)
{
    chart()->setAxisX(axis,this);
}

QAbstractAxis *DeclarativeLineSeries::axisX()
{
    return chart()->axisX(this);
}

void DeclarativeLineSeries::setAxisY(QAbstractAxis *axis)
{
    chart()->setAxisY(axis,this);
}

QAbstractAxis *DeclarativeLineSeries::axisY()
{
    return chart()->axisY(this);
}

void DeclarativeLineSeries::handleCountChanged(int index)
{
    Q_UNUSED(index)
    emit countChanged(points().count());
}

QDeclarativeListProperty<QObject> DeclarativeLineSeries::declarativeChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &appendDeclarativeChildren);
}

void DeclarativeLineSeries::appendDeclarativeChildren(QDeclarativeListProperty<QObject> *list, QObject *element)
{
    Q_UNUSED(list)
    Q_UNUSED(element)
    // Empty implementation, childs are parsed in componentComplete
}

#include "moc_declarativelineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
