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

#ifndef DECLARATIVEMODEL_H
#define DECLARATIVEMODEL_H

#include "qchartglobal.h"
#include "declarativexypoint.h"
#include "qpieslice.h"
#include "../src/charttablemodel.h" // TODO
#include <QDeclarativeListProperty>
#include <QVariant>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeXyModel : public ChartTableModel
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> points READ points)
    Q_CLASSINFO("DefaultProperty", "points")

public:
    explicit DeclarativeXyModel(QObject *parent = 0);
    QDeclarativeListProperty<DeclarativeXyPoint> points();

public Q_SLOTS:
    void append(DeclarativeXyPoint* point);
    void append(QVariantList points);
    static void appendPoint(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                            DeclarativeXyPoint *element);
};


class DeclarativePieModel : public ChartTableModel
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<QPieSlice> slices READ slices)
    Q_CLASSINFO("DefaultProperty", "slices")

public:
    explicit DeclarativePieModel(QObject *parent = 0);
    QDeclarativeListProperty<QPieSlice> slices();

public Q_SLOTS:
    void append(QPieSlice* slice);
    void append(QVariantList slices);
    static void appendSlice(QDeclarativeListProperty<QPieSlice> *list,
                            QPieSlice *element);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEMODEL_H
