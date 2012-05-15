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
#include <QXYSeries>
#include <QXYModelMapper>
#include "declarativechart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeXySeries::DeclarativeXySeries()
{
    // All the inherited objects must be of type QXYSeries, so it is safe to cast
    QXYSeries *series = reinterpret_cast<QXYSeries *>(this);
    QXYModelMapper *mapper = new QXYModelMapper(series);
    mapper->setMapX(0);
    mapper->setMapY(1);
    mapper->setFirst(0);
    mapper->setCount(-1);
    mapper->setOrientation(Qt::Vertical);
    series->setModelMapper(mapper);
}

DeclarativeXySeries::~DeclarativeXySeries()
{
}

bool DeclarativeXySeries::setDeclarativeModel(DeclarativeTableModel *model)
{
    QAbstractItemModel *m = qobject_cast<QAbstractItemModel *>(model);
    bool value(false);
    if (m) {
        // All the inherited objects must be of type QXYSeries, so it is safe to cast
        QXYSeries *series = reinterpret_cast<QXYSeries *>(this);
        series->setModel(m);
//        QXYModelMapper *mapper = new QXYModelMapper;
//        mapper->setMapX(0);
//        mapper->setMapY(1);
//        series->setModelMapper(mapper);
    } else {
        qWarning("DeclarativeXySeries: Illegal model");
    }
    return value;
}

DeclarativeTableModel *DeclarativeXySeries::declarativeModel()
{
    // All the inherited objects must be of type QXYSeries, so it is safe to cast
    QXYSeries *series = reinterpret_cast<QXYSeries *>(this);
    return qobject_cast<DeclarativeTableModel *>(series->model());
}

QTCOMMERCIALCHART_END_NAMESPACE
