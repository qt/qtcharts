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

/*!
    \qmlclass BarSeries QBarSeries

    \section1 Example Usage

    \beginfloatleft
    \image demos_qmlchart6.png
    \endfloat
    \clearfloat

    The following QML shows how to create a simple bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View6.qml 1
*/

/*!
    \qmlclass GroupedBarSeries QGroupedBarSeries

    \section1 Example Usage

    \beginfloatleft
    \image demos_qmlchart7.png
    \endfloat
    \clearfloat

    The following QML shows how to create a simple grouped bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View7.qml 1
*/

/*!
    \qmlclass StackedBarSeries QStackedBarSeries

    \section1 Example Usage

    \beginfloatleft
    \image demos_qmlchart8.png
    \endfloat
    \clearfloat

    The following QML shows how to create a simple stacked bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View8.qml 1
*/

/*!
    \qmlclass PercentBarSeries QPercentBarSeries

    \section1 Example Usage

    \beginfloatleft
    \image demos_qmlchart9.png
    \endfloat
    \clearfloat

    The following QML shows how to create a simple percent bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View9.qml 1
*/

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
        values.append(QVariant(at(i)));
    return values;
}

void DeclarativeBarSet::setValues(QVariantList values)
{
    while (count())
        remove(count() - 1);

    for (int i(0); i < values.count(); i++) {
        if (values.at(i).canConvert(QVariant::Double))
            append(values[i].toDouble());
    }
}

DeclarativeBarSeries::DeclarativeBarSeries(QDeclarativeItem *parent) :
    QBarSeries(parent)
{
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
    if (index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

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
    if (index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

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
    if (index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

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
    if (index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

#include "moc_declarativebarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
