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
#include "qpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativePieSeries::DeclarativePieSeries(QObject *parent) :
    QPieSeries(parent)
{
    // TODO: set default model on init?
//    setModel(new DeclarativeTableModel());

    // TODO: Set default mapper parameters to allow easy to use PieSeries api?
    QPieModelMapper *mapper = modelMapper();//new QPieModelMapper();
    mapper->setMapLabels(0);
    mapper->setMapValues(1);
    mapper->setOrientation(Qt::Vertical);
    mapper->setFirst(0);
    mapper->setCount(-1);
//    setModelMapper(mapper);
}

void DeclarativePieSeries::classBegin()
{
}

void DeclarativePieSeries::componentComplete()
{
    foreach(QObject *child, children()) {
        if (qobject_cast<QPieSlice *>(child)) {
            QPieSeries::append(qobject_cast<QPieSlice *>(child));
        }
    }
}

QDeclarativeListProperty<QPieSlice> DeclarativePieSeries::initialSlices()
{
    return QDeclarativeListProperty<QPieSlice>(this, 0, &DeclarativePieSeries::appendInitialSlices);
}

QPieSlice *DeclarativePieSeries::at(int index)
{
    QList<QPieSlice*> sliceList = slices();
    if (index < sliceList.count())
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

QPieSlice* DeclarativePieSeries::append(QString name, qreal value)
{
    // TODO: parameter order is wrong, switch it:
    return QPieSeries::append(value, name);
}

void DeclarativePieSeries::setPieModel(DeclarativeTableModel *model)
{
    QAbstractItemModel *m = qobject_cast<QAbstractItemModel *>(model);
    if (m) {
        QPieSeries::setModel(m);
    } else {
        qWarning("DeclarativePieSeries: Illegal model");
    }
}

DeclarativeTableModel *DeclarativePieSeries::pieModel()
{
    return qobject_cast<DeclarativeTableModel *>(model());
}

#include "moc_declarativepieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
