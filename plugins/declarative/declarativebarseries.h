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

#ifndef DECLARATIVEBARSERIES_H
#define DECLARATIVEBARSERIES_H

#include "qchartglobal.h"
#include <QDeclarativeItem>
#include <QDeclarativeParserStatus>
#include <QGroupedBarSeries>
#include <QBarSet>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativeBarSet : public QBarSet
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues)
    Q_PROPERTY(QString name READ name WRITE setName)

public:
    explicit DeclarativeBarSet(QObject *parent = 0);
    QVariantList values();
    void setValues(QVariantList values);

public: // From QBarSet
    Q_INVOKABLE void append(qreal value) { QBarSet::append(value); }
    Q_INVOKABLE void append(qreal x, qreal y) { QBarSet::append(QPointF(x, y)); }
};

class DeclarativeBarSeries : public QBarSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QStringList barCategories READ barCategories WRITE setBarCategories)
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeBarSet> initialBarSets READ initialBarSets)
    Q_CLASSINFO("DefaultProperty", "initialBarSets")

public:
    explicit DeclarativeBarSeries(QDeclarativeItem *parent = 0);
    QDeclarativeListProperty<DeclarativeBarSet> initialBarSets();

    void setBarCategories(QStringList categories);
    QStringList barCategories();

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    static void appendInitialBarSets(QDeclarativeListProperty<DeclarativeBarSet> * /*list*/, DeclarativeBarSet * /*element*/) {}
};

class DeclarativeGroupedBarSeries : public QGroupedBarSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QStringList barCategories READ barCategories WRITE setBarCategories)
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeBarSet> initialBarSets READ initialBarSets)
    Q_CLASSINFO("DefaultProperty", "initialBarSets")

public:
    explicit DeclarativeGroupedBarSeries(QDeclarativeItem *parent = 0);
    QDeclarativeListProperty<DeclarativeBarSet> initialBarSets();

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public:
    void setBarCategories(QStringList categories);
    QStringList barCategories();

public Q_SLOTS:
    static void appendInitialBarSets(QDeclarativeListProperty<DeclarativeBarSet> * /*list*/, DeclarativeBarSet * /*element*/) {}
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEBARSERIES_H
