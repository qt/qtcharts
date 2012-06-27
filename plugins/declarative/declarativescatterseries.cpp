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

#include "declarativescatterseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qscatterseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeScatterSeries::DeclarativeScatterSeries(QObject *parent) :
    QScatterSeries(parent)
{
    connect(this, SIGNAL(pointAdded(int)), this, SLOT(handleCountChanged(int)));
    connect(this, SIGNAL(pointRemoved(int)), this, SLOT(handleCountChanged(int)));
}

QXYSeries *DeclarativeScatterSeries::xySeries()
{
    return this;
}

void DeclarativeScatterSeries::setAxisX(QAbstractAxis *axis)
{
    chart()->setAxisX(this, axis);
}

QAbstractAxis *DeclarativeScatterSeries::axisX()
{
    return chart()->axisX(this);
}

void DeclarativeScatterSeries::setAxisY(QAbstractAxis *axis)
{
    chart()->setAxisY(this, axis);
}

QAbstractAxis *DeclarativeScatterSeries::axisY()
{
    return chart()->axisY(this);
}

void DeclarativeScatterSeries::handleCountChanged(int index)
{
    Q_UNUSED(index)
    emit countChanged(QScatterSeries::count());
}

QDeclarativeListProperty<QObject> DeclarativeScatterSeries::declarativeChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &appendDeclarativeChildren);
}

void DeclarativeScatterSeries::appendDeclarativeChildren(QDeclarativeListProperty<QObject> *list, QObject *element)
{
    Q_UNUSED(list)
    Q_UNUSED(element)
    // Empty implementation, childs are parsed in componentComplete
}

#include "moc_declarativescatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
