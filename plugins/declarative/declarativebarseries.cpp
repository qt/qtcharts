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

#include "declarativebarseries.h"
#include "declarativechart.h"
#include <QBarSet>
#include <QVBarModelMapper>
#include <QHBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeBarSet::DeclarativeBarSet(QObject *parent) :
    QBarSet("", parent)
{
    connect(this, SIGNAL(valuesAdded(int,int)), this, SLOT(handleCountChanged(int, int)));
    connect(this, SIGNAL(valuesRemoved(int,int)), this, SLOT(handleCountChanged(int, int)));
}

void DeclarativeBarSet::handleCountChanged(int index, int count)
{
    Q_UNUSED(index)
    Q_UNUSED(count)
    emit countChanged(QBarSet::count());
}

QVariantList DeclarativeBarSet::values()
{
    QVariantList values;
    for (int i(0); i < count(); i++)
        values.append(QVariant(QBarSet::at(i)));
    return values;
}

void DeclarativeBarSet::setValues(QVariantList values)
{
    while (count())
        remove(count() - 1);

    for (int i(0); i < values.count(); i++) {
        if (values.at(i).canConvert(QVariant::Double))
            QBarSet::append(values[i].toDouble());
        else if (values.at(i).canConvert(QVariant::PointF))
            QBarSet::append(values[i].toPointF());
    }
}

DeclarativeBarSeries::DeclarativeBarSeries(QDeclarativeItem *parent) :
    QBarSeries(parent)
{
    connect(this, SIGNAL(barsetsAdded(QList<QBarSet*>)), this, SLOT(handleAdded(QList<QBarSet*>)));
    connect(this, SIGNAL(barsetsRemoved(QList<QBarSet*>)), this, SLOT(handleRemoved(QList<QBarSet*>)));
}

void DeclarativeBarSeries::handleAdded(QList<QBarSet* > barsets)
{
    foreach(QBarSet *b, barsets) {
        DeclarativeBarSet *barset = qobject_cast<DeclarativeBarSet *>(b);
        emit added(barset);
    }
}

void DeclarativeBarSeries::handleRemoved(QList<QBarSet* > barsets)
{
    foreach(QBarSet *b, barsets) {
        DeclarativeBarSet *barset = qobject_cast<DeclarativeBarSet *>(b);
        emit removed(barset);
    }
}

void DeclarativeBarSeries::classBegin()
{
}

void DeclarativeBarSeries::componentComplete()
{
    foreach(QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if(qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if(qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativeBarSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativeBarSeries::appendSeriesChildren);
}

void DeclarativeBarSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeBarSeries::at(int index)
{
    QList<QBarSet*> setList = barSets();
    if (index >= 0 && index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeBarSeries::insert(int index, QString label, QVariantList values)
{
    int insertIndex = index;
    if (insertIndex < 0)
        insertIndex = 0;
    else if (insertIndex > count())
        insertIndex = count();

    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QBarSeries::insert(insertIndex, barset))
        return barset;
    delete barset;
    return 0;
}

DeclarativeGroupedBarSeries::DeclarativeGroupedBarSeries(QDeclarativeItem *parent) :
    QGroupedBarSeries(parent)
{
}

void DeclarativeGroupedBarSeries::classBegin()
{
}

void DeclarativeGroupedBarSeries::componentComplete()
{
    foreach(QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if(qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if(qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativeGroupedBarSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativeBarSeries::appendSeriesChildren);
}

void DeclarativeGroupedBarSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeGroupedBarSeries::at(int index)
{
    QList<QBarSet*> setList = barSets();
    if (index >= 0 && index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeGroupedBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QGroupedBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

DeclarativeStackedBarSeries::DeclarativeStackedBarSeries(QDeclarativeItem *parent) :
    QStackedBarSeries(parent)
{
}

void DeclarativeStackedBarSeries::classBegin()
{
}

void DeclarativeStackedBarSeries::componentComplete()
{
    foreach(QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if(qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if(qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativeStackedBarSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativeBarSeries::appendSeriesChildren);
}

void DeclarativeStackedBarSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeStackedBarSeries::at(int index)
{
    QList<QBarSet*> setList = barSets();
    if (index >= 0 && index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeStackedBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QStackedBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

DeclarativePercentBarSeries::DeclarativePercentBarSeries(QDeclarativeItem *parent) :
    QPercentBarSeries(parent)
{
}

void DeclarativePercentBarSeries::classBegin()
{
}

void DeclarativePercentBarSeries::componentComplete()
{
    foreach(QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if(qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if(qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativePercentBarSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativeBarSeries::appendSeriesChildren);
}

void DeclarativePercentBarSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativePercentBarSeries::at(int index)
{
    QList<QBarSet*> setList = barSets();
    if (index >= 0 && index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativePercentBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QPercentBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

#include "moc_declarativebarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
