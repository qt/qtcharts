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

#include "declarativepieseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include <qdeclarativelist.h>
#include <QVPieModelMapper>
#include <QHPieModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativePieSeries::DeclarativePieSeries(QObject *parent) :
    QPieSeries(parent)
{
    connect(this, SIGNAL(added(QList<QPieSlice*>)), this, SLOT(handleAdded(QList<QPieSlice*>)));
    connect(this, SIGNAL(removed(QList<QPieSlice*>)), this, SLOT(handleRemoved(QList<QPieSlice*>)));
}

void DeclarativePieSeries::classBegin()
{
}

void DeclarativePieSeries::componentComplete()
{
    foreach(QObject *child, children()) {
        if (qobject_cast<QPieSlice *>(child)) {
            QPieSeries::append(qobject_cast<QPieSlice *>(child));
        } else if(qobject_cast<QVPieModelMapper *>(child)) {
            QVPieModelMapper *mapper = qobject_cast<QVPieModelMapper *>(child);
            mapper->setSeries(this);
        } else if(qobject_cast<QHPieModelMapper *>(child)) {
            QHPieModelMapper *mapper = qobject_cast<QHPieModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativePieSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativePieSeries::appendSeriesChildren);
}

void DeclarativePieSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

QPieSlice *DeclarativePieSeries::at(int index)
{
    QList<QPieSlice*> sliceList = slices();
    if (index >= 0 && index < sliceList.count())
        return sliceList[index];

    return 0;
}

QPieSlice* DeclarativePieSeries::find(QString label)
{
    foreach (QPieSlice *slice, slices()) {
        if (slice->label() == label)
            return slice;
    }
    return 0;
}

QPieSlice* DeclarativePieSeries::append(QString label, qreal value)
{
    // TODO: parameter order is wrong, switch it:
    QPieSlice *slice = new QPieSlice(this);
    slice->setLabel(label);
    slice->setValue(value);
    QPieSeries::append(slice);
    return slice;
}

bool DeclarativePieSeries::remove(QPieSlice *slice)
{
    return QPieSeries::remove(slice);
}

void DeclarativePieSeries::clear()
{
    QPieSeries::clear();
}

void DeclarativePieSeries::handleAdded(QList<QPieSlice*> slices)
{
    foreach(QPieSlice *slice, slices)
        emit sliceAdded(slice);
}

void DeclarativePieSeries::handleRemoved(QList<QPieSlice*> slices)
{
    foreach(QPieSlice *slice, slices)
        emit sliceRemoved(slice);
}

#include "moc_declarativepieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
