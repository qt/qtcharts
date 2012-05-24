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
#include <QVariant>
#include "declarativemodel.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativePieSeries : public QPieSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(DeclarativeTableModel *model READ pieModel WRITE setPieModel)
    Q_PROPERTY(QDeclarativeListProperty<QPieSlice> initialSlices READ initialSlices)
    Q_CLASSINFO("DefaultProperty", "initialSlices")

public:
    explicit DeclarativePieSeries(QObject *parent = 0);
    QDeclarativeListProperty<QPieSlice> initialSlices();
    DeclarativeTableModel *pieModel();
    void setPieModel(DeclarativeTableModel *model);
    Q_INVOKABLE QPieSlice *at(int index);
    Q_INVOKABLE QPieSlice* find(QString label);
    Q_INVOKABLE QPieSlice* append(QString label, qreal value);

public:
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    static void appendInitialSlices(QDeclarativeListProperty<QPieSlice> * /*list*/, QPieSlice * /*element*/) {}
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEPIESERIES_H
