/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "qpieseries.h"
#include "shared_defines.h"

#ifdef CHARTS_FOR_QUICK2
#include <QtQuick/QQuickItem>
#include <QtQml/QQmlParserStatus>
#else
#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeParserStatus>
#endif

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QPieSlice;

class DeclarativePieSeries : public QPieSeries, public QDECLARATIVE_PARSER_STATUS
{
    Q_OBJECT
#ifdef CHARTS_FOR_QUICK2
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
#else
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QDeclarativeListProperty<QObject> seriesChildren READ seriesChildren)
#endif
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativePieSeries(QDECLARATIVE_ITEM *parent = 0);
    QDECLARATIVE_LIST_PROPERTY<QObject> seriesChildren();
    Q_INVOKABLE QPieSlice *at(int index);
    Q_INVOKABLE QPieSlice *find(QString label);
    Q_INVOKABLE QPieSlice *append(QString label, qreal value);
    Q_INVOKABLE bool remove(QPieSlice *slice);
    Q_INVOKABLE void clear();

public:
    void classBegin();
    void componentComplete();

Q_SIGNALS:
    void sliceAdded(QPieSlice *slice);
    void sliceRemoved(QPieSlice *slice);

public Q_SLOTS:
    static void appendSeriesChildren(QDECLARATIVE_LIST_PROPERTY<QObject> *list, QObject *element);
    void handleAdded(QList<QPieSlice *> slices);
    void handleRemoved(QList<QPieSlice *> slices);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEPIESERIES_H
