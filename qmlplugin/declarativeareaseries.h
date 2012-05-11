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

#ifndef DECLARATIVEAREASERIES_H
#define DECLARATIVEAREASERIES_H

#include "qchartglobal.h"
#include "qareaseries.h"
#include "declarativelineseries.h"
#include "declarativexyseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeAreaSeries : public QAreaSeries, public DeclarativeXySeries
{
    Q_OBJECT
    Q_PROPERTY(DeclarativeXyModel *upperModel READ declarativeUpperModel WRITE setDeclarativeUpperModel)
    Q_PROPERTY(DeclarativeXyModel *lowerModel READ declarativeLowerModel WRITE setDeclarativeLowerModel)

public:
    explicit DeclarativeAreaSeries(QObject *parent = 0);

public:
    bool setDeclarativeUpperModel(DeclarativeXyModel *model);
    DeclarativeXyModel *declarativeUpperModel();
    bool setDeclarativeLowerModel(DeclarativeXyModel *model);
    DeclarativeXyModel *declarativeLowerModel();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEAREASERIES_H
