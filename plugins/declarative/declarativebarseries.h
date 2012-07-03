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
#include "qgroupedbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qbarset.h"
#include "qabstractaxis.h"
#include <QDeclarativeItem>
#include <QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class DeclarativeBarSet : public QBarSet
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit DeclarativeBarSet(QObject *parent = 0);
    QVariantList values();
    void setValues(QVariantList values);

public: // From QBarSet
    Q_INVOKABLE void append(qreal value) { QBarSet::append(value); }
    Q_INVOKABLE void remove(const int index, const int count = 1) { QBarSet::remove(index, count); }
    Q_INVOKABLE void replace(int index, qreal value) { QBarSet::replace(index, value); }
    Q_INVOKABLE qreal at(int index) { return QBarSet::at(index); }

Q_SIGNALS:
    void countChanged(int count);

private Q_SLOTS:
    void handleCountChanged(int index, int count);
};

class DeclarativeAbstractBarSeries : public QAbstractBarSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QDeclarativeListProperty<QObject> seriesChildren READ seriesChildren)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativeAbstractBarSeries(QDeclarativeItem *parent = 0);
    void setAxisX(QAbstractAxis *axis);
    QAbstractAxis *axisX();
    void setAxisY(QAbstractAxis *axis);
    QAbstractAxis *axisY();
    QDeclarativeListProperty<QObject> seriesChildren();
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QAbstractBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QAbstractBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

Q_SIGNALS:
    void added(DeclarativeBarSet *barset);
    void removed(DeclarativeBarSet *barset);

public Q_SLOTS:
    static void appendSeriesChildren(QDeclarativeListProperty<QObject> *list, QObject *element);
    void handleAdded(QList<QBarSet* > barsets);
    void handleRemoved(QList<QBarSet* > barsets);
};

class DeclarativeGroupedBarSeries : public QGroupedBarSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY)
    Q_PROPERTY(QDeclarativeListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativeGroupedBarSeries(QDeclarativeItem *parent = 0);
    void setAxisX(QAbstractAxis *axis);
    QAbstractAxis *axisX();
    void setAxisY(QAbstractAxis *axis);
    QAbstractAxis *axisY();
    QDeclarativeListProperty<QObject> seriesChildren();
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QGroupedBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QGroupedBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    static void appendSeriesChildren(QDeclarativeListProperty<QObject> *list, QObject *element);
};

class DeclarativeStackedBarSeries : public QStackedBarSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY)
    Q_PROPERTY(QDeclarativeListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativeStackedBarSeries(QDeclarativeItem *parent = 0);
    void setAxisX(QAbstractAxis *axis);
    QAbstractAxis *axisX();
    void setAxisY(QAbstractAxis *axis);
    QAbstractAxis *axisY();
    QDeclarativeListProperty<QObject> seriesChildren();
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QStackedBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QStackedBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    static void appendSeriesChildren(QDeclarativeListProperty<QObject> *list, QObject *element);
};

class DeclarativePercentBarSeries : public QPercentBarSeries, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY)
    Q_PROPERTY(QDeclarativeListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativePercentBarSeries(QDeclarativeItem *parent = 0);
    void setAxisX(QAbstractAxis *axis);
    QAbstractAxis *axisX();
    void setAxisY(QAbstractAxis *axis);
    QAbstractAxis *axisY();
    QDeclarativeListProperty<QObject> seriesChildren();
    Q_INVOKABLE DeclarativeBarSet *at(int index);
    Q_INVOKABLE DeclarativeBarSet *append(QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE DeclarativeBarSet *insert(int index, QString label, QVariantList values);
    Q_INVOKABLE bool remove(QBarSet *barset) { return QPercentBarSeries::remove(barset); }
    Q_INVOKABLE void clear() { return QPercentBarSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    static void appendSeriesChildren(QDeclarativeListProperty<QObject> *list, QObject *element);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEBARSERIES_H
