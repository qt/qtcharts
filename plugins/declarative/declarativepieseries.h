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
#include "declarativemodel.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativePieSlice: public QPieSlice
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)

public:
    explicit DeclarativePieSlice(QObject *parent = 0);
    QColor color();
    void setColor(QColor color);
    QColor borderColor();
    void setBorderColor(QColor color);
    int borderWidth();
    void setBorderWidth(int width);
};

class DeclarativePieSeries : public QPieSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QDeclarativeListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativePieSeries(QObject *parent = 0);
    QDeclarativeListProperty<QObject> seriesChildren();
    Q_INVOKABLE DeclarativePieSlice *at(int index);
    Q_INVOKABLE DeclarativePieSlice* find(QString label);
    Q_INVOKABLE DeclarativePieSlice* append(QString label, qreal value);

public:
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    static void appendSeriesChildren(QDeclarativeListProperty<QObject> *list, QObject *element);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEPIESERIES_H
