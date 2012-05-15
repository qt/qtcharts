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
#include "qxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeAreaSeries::DeclarativeAreaSeries(QObject *parent) :
    QAreaSeries(new QLineSeries(parent), new QLineSeries(parent))
{
    QXYModelMapper *upperMapper = new QXYModelMapper(upperSeries());
    upperMapper->setMapX(0);
    upperMapper->setMapY(1);
    upperMapper->setFirst(0);
    upperMapper->setCount(-1);
    upperMapper->setOrientation(Qt::Vertical);
    upperSeries()->setModelMapper(upperMapper);

    QXYModelMapper *lowerMapper = new QXYModelMapper(lowerSeries());
    lowerMapper->setMapX(2);
    lowerMapper->setMapY(3);
    lowerMapper->setFirst(0);
    lowerMapper->setCount(-1);
    lowerMapper->setOrientation(Qt::Vertical);
    lowerSeries()->setModelMapper(lowerMapper);
}

bool DeclarativeAreaSeries::setDeclarativeUpperModel(DeclarativeTableModel *model)
{
    QAbstractItemModel *m = qobject_cast<QAbstractItemModel *>(model);
    bool value(false);
    if (m) {
        upperSeries()->setModel(m);
    } else {
        qWarning("DeclarativeAreaSeries: Illegal model");
    }
    return value;
}

DeclarativeTableModel *DeclarativeAreaSeries::declarativeUpperModel()
{
    return qobject_cast<DeclarativeTableModel *>(upperSeries()->model());
}

bool DeclarativeAreaSeries::setDeclarativeLowerModel(DeclarativeTableModel *model)
{
    QAbstractItemModel *m = qobject_cast<QAbstractItemModel *>(model);
    bool value(false);
    if (m) {
        lowerSeries()->setModel(m);
    } else {
        qWarning("DeclarativeAreaSeries: Illegal model");
    }
    return value;
}

DeclarativeTableModel *DeclarativeAreaSeries::declarativeLowerModel()
{
    return qobject_cast<DeclarativeTableModel *>(lowerSeries()->model());
}

QXYModelMapper* DeclarativeAreaSeries::upperModelMapper() const
{
    return upperSeries()->modelMapper();
}

QXYModelMapper* DeclarativeAreaSeries::lowerModelMapper() const
{
    return lowerSeries()->modelMapper();
}

#include "moc_declarativeareaseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
