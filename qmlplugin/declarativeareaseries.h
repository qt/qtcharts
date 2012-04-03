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
#include "declarativexyseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeAreaSeries : public QAreaSeries, public DeclarativeXySeries
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> points READ points)
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> lowerPoints READ lowerPoints)

public:
    explicit DeclarativeAreaSeries(QObject *parent = 0);

public:
    QSeries *series();
    QDeclarativeListProperty<DeclarativeXyPoint> points();
    QDeclarativeListProperty<DeclarativeXyPoint> lowerPoints();

public Q_SLOTS:
    static void appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                             DeclarativeXyPoint *element);
    static void appendLowerPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                             DeclarativeXyPoint *element);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEAREASERIES_H
