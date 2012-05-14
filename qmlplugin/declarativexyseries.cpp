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
#include "qxyseries.h"
#include "declarativechart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeXySeries::DeclarativeXySeries()
{
}

DeclarativeXySeries::~DeclarativeXySeries()
{
}

bool DeclarativeXySeries::setDeclarativeModel(DeclarativeXyModel *model)
{
    QAbstractItemModel *m = qobject_cast<QAbstractItemModel *>(model);
    bool value(false);
    if (m) {
        // All the inherited objects must be of type QXYSeries, so it is safe to cast
        QXYSeries *series = reinterpret_cast<QXYSeries *>(this);
        value = series->setModel(m);
        series->setModelMapping(0, 1, Qt::Vertical);
    } else {
        qWarning("DeclarativeXySeries: Illegal model");
    }
    return value;
}

DeclarativeXyModel *DeclarativeXySeries::declarativeModel()
{
    // All the inherited objects must be of type QXYSeries, so it is safe to cast
    QXYSeries *series = reinterpret_cast<QXYSeries *>(this);
    Q_ASSERT(series);
    return qobject_cast<DeclarativeXyModel *>(series->model());
}

QTCOMMERCIALCHART_END_NAMESPACE
