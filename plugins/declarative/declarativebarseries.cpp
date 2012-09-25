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
#include "qbarset.h"
#include "qvbarmodelmapper.h"
#include "qhbarmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeBarSet::DeclarativeBarSet(QObject *parent) :
    QBarSet("", parent)
{
    connect(this, SIGNAL(valuesAdded(int,int)), this, SLOT(handleCountChanged(int,int)));
    connect(this, SIGNAL(valuesRemoved(int,int)), this, SLOT(handleCountChanged(int,int)));
}

void DeclarativeBarSet::handleCountChanged(int index, int count)
{
    Q_UNUSED(index)
    Q_UNUSED(count)
    emit countChanged(QBarSet::count());
}

qreal DeclarativeBarSet::borderWidth() const
{
    return pen().widthF();
}

void DeclarativeBarSet::setBorderWidth(qreal width)
{
    if (width != pen().widthF()) {
        QPen p = pen();
        p.setWidthF(width);
        setPen(p);
        emit borderWidthChanged(width);
    }
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
    }
}

// Declarative bar series ======================================================================================
DeclarativeBarSeries::DeclarativeBarSeries(QDeclarativeItem *parent) :
    QBarSeries(parent),
    m_axisX(0),
    m_axisY(0)
{
}

void DeclarativeBarSeries::classBegin()
{
}

void DeclarativeBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
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
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

// Declarative stacked bar series ==============================================================================
DeclarativeStackedBarSeries::DeclarativeStackedBarSeries(QDeclarativeItem *parent) :
    QStackedBarSeries(parent),
    m_axisX(0),
    m_axisY(0)
{
}

void DeclarativeStackedBarSeries::classBegin()
{
}

void DeclarativeStackedBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
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

// Declarative percent bar series ==============================================================================
DeclarativePercentBarSeries::DeclarativePercentBarSeries(QDeclarativeItem *parent) :
    QPercentBarSeries(parent),
    m_axisX(0),
    m_axisY(0)
{
}

void DeclarativePercentBarSeries::classBegin()
{
}

void DeclarativePercentBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
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

// Declarative horizontal bar series ===========================================================================
DeclarativeHorizontalBarSeries::DeclarativeHorizontalBarSeries(QDeclarativeItem *parent) :
    QHorizontalBarSeries(parent),
    m_axisX(0),
    m_axisY(0)
{
}

void DeclarativeHorizontalBarSeries::classBegin()
{
}

void DeclarativeHorizontalBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if(qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if(qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativeHorizontalBarSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativeHorizontalBarSeries::appendSeriesChildren);
}

void DeclarativeHorizontalBarSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeHorizontalBarSeries::at(int index)
{
    QList<QBarSet*> setList = barSets();
    if (index >= 0 && index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeHorizontalBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QHorizontalBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

// Declarative horizontal stacked bar series ===================================================================
DeclarativeHorizontalStackedBarSeries::DeclarativeHorizontalStackedBarSeries(QDeclarativeItem *parent) :
    QHorizontalStackedBarSeries(parent),
    m_axisX(0),
    m_axisY(0)
{
}

void DeclarativeHorizontalStackedBarSeries::classBegin()
{
}

void DeclarativeHorizontalStackedBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if(qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if(qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativeHorizontalStackedBarSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativeHorizontalStackedBarSeries::appendSeriesChildren);
}

void DeclarativeHorizontalStackedBarSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeHorizontalStackedBarSeries::at(int index)
{
    QList<QBarSet*> setList = barSets();
    if (index >= 0 && index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeHorizontalStackedBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QHorizontalStackedBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

// Declarative horizontal percent bar series ===================================================================
DeclarativeHorizontalPercentBarSeries::DeclarativeHorizontalPercentBarSeries(QDeclarativeItem *parent) :
    QHorizontalPercentBarSeries(parent),
    m_axisX(0),
    m_axisY(0)
{
}

void DeclarativeHorizontalPercentBarSeries::classBegin()
{
}

void DeclarativeHorizontalPercentBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if(qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if(qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativeHorizontalPercentBarSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativeHorizontalPercentBarSeries::appendSeriesChildren);
}

void DeclarativeHorizontalPercentBarSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeHorizontalPercentBarSeries::at(int index)
{
    QList<QBarSet*> setList = barSets();
    if (index >= 0 && index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeHorizontalPercentBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QHorizontalPercentBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

#include "moc_declarativebarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
