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

#ifndef DECLARATIVE_XY_SERIES_H
#define DECLARATIVE_XY_SERIES_H

#include "qchartglobal.h"
#include "declarativexypoint.h"
#include <QDeclarativeParserStatus>
#include <QDeclarativeListProperty>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;
class QAbstractSeries;

class DeclarativeXySeries : public QDeclarativeParserStatus
{
    Q_INTERFACES(QDeclarativeParserStatus)

public:
    explicit DeclarativeXySeries();
    ~DeclarativeXySeries();

public: // from QDeclarativeParserStatus
    virtual void classBegin();
    virtual void componentComplete();

public:
    virtual QAbstractSeries *series() = 0;
    virtual QDeclarativeListProperty<DeclarativeXyPoint> points() = 0;

public Q_SLOTS:
    static void appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                             DeclarativeXyPoint *element);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVE_XY_SERIES_H
