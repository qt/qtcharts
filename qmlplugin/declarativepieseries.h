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

#ifndef DECLARATIVEPIESERIES_H
#define DECLARATIVEPIESERIES_H

#include "qchartglobal.h"
#include "qpieslice.h"
#include "qpieseries.h"
#include <QDeclarativeListProperty>
#include <QAbstractItemModel>
#include <QVariant>
#include "declarativemodel.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativePieSeries : public QPieSeries
{
    Q_OBJECT
    Q_PROPERTY(DeclarativePieModel *model READ pieModel WRITE setPieModel)

public:
    explicit DeclarativePieSeries(QObject *parent = 0);

public:
    Q_INVOKABLE QPieSlice *slice(int index);

public Q_SLOTS:

public:
    bool setPieModel(DeclarativePieModel *model);
    DeclarativePieModel *pieModel();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEPIESERIES_H
