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
#include <QPieSlice>
#include <QPieSeries>
#include <QDeclarativeParserStatus>
#include <QDeclarativeListProperty>
#include <QAbstractItemModel>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativePieSeries : public QPieSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QDeclarativeListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativePieSeries(QObject *parent = 0);
    QDeclarativeListProperty<QObject> seriesChildren();
    Q_INVOKABLE QPieSlice *at(int index);
    Q_INVOKABLE QPieSlice *find(QString label);
    Q_INVOKABLE QPieSlice *append(QString label, qreal value);
    Q_INVOKABLE bool remove(int index);
    Q_INVOKABLE void clear();

public:
    void classBegin();
    void componentComplete();

Q_SIGNALS:
    void sliceAdded(QPieSlice* slice);
    void sliceRemoved(QPieSlice* slice);

public Q_SLOTS:
    static void appendSeriesChildren(QDeclarativeListProperty<QObject> *list, QObject *element);
    void handleAdded(QList<QPieSlice*> slices);
    void handleRemoved(QList<QPieSlice*> slices);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEPIESERIES_H
