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

#ifndef DECLARATIVEPIEMODEL_H
#define DECLARATIVEPIEMODEL_H

#include "qchartglobal.h"
#include "qpieslice.h"
#include "qpieseries.h"
#include "../src/charttablemodel.h"
#include <QDeclarativeParserStatus>
#include <QDeclarativeListProperty>
#include <QAbstractItemModel>
#include <QVariant>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativePieModel : public ChartTableModel/*, public QDeclarativeParserStatus*/
{
//    Q_INTERFACES(QDeclarativeParserStatus)
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<QPieSlice> slices READ slices)
    Q_CLASSINFO("DefaultProperty", "slices")

public:
    explicit DeclarativePieModel(QObject *parent = 0);
    QDeclarativeListProperty<QPieSlice> slices();

//public: // from QDeclarativeParserStatus
//    virtual void classBegin();
//    virtual void componentComplete();

public Q_SLOTS:
    void append(QPieSlice* slice);
    void append(QVariantList slices);
    static void appendSlice(QDeclarativeListProperty<QPieSlice> *list,
                            QPieSlice *element);

public:
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEPIEMODEL_H
