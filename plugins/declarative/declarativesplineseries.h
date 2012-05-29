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

#ifndef DECLARATIVESPLINESERIES_H
#define DECLARATIVESPLINESERIES_H

#include "qchartglobal.h"
#include "qsplineseries.h"
#include "declarativexyseries.h"
#include <QDeclarativeParserStatus>
#include <QDeclarativeListProperty>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeSplineSeries : public QSplineSeries, public DeclarativeXySeries
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ penColor WRITE setPenColor)
    Q_PROPERTY(QDeclarativeListProperty<QObject> declarativeChildren READ declarativeChildren)
    Q_CLASSINFO("DefaultProperty", "declarativeChildren")

public:
    explicit DeclarativeSplineSeries(QObject *parent = 0);
    QDeclarativeListProperty<QObject> declarativeChildren();

public: // from QSplineSeries
    Q_INVOKABLE void append(qreal x, qreal y) { QSplineSeries::append(x, y); }
    Q_INVOKABLE void remove(qreal x, qreal y) { QSplineSeries::remove(x, y); }
    Q_INVOKABLE void clear() { QSplineSeries::removeAll(); }
    Q_INVOKABLE DeclarativeXyPoint *at(int index) { return DeclarativeXySeries::at(index); }

public Q_SLOTS:
    static void appendDeclarativeChildren(QDeclarativeListProperty<QObject> *list, QObject *element);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESPLINESERIES_H
