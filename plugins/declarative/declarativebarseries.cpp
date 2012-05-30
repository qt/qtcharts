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

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeBarSet::DeclarativeBarSet(QObject *parent) :
    QBarSet("", parent)
{
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

QColor DeclarativeBarSet::color()
{
    return brush().color();
}

void DeclarativeBarSet::setColor(QColor color)
{
    QBrush b = brush();
    b.setColor(color);
    setBrush(b);
}

QColor DeclarativeBarSet::borderColor()
{
    return pen().color();
}

void DeclarativeBarSet::setBorderColor(QColor color)
{
    QPen p = pen();
    p.setColor(color);
    setPen(p);
}

QColor DeclarativeBarSet::labelColor()
{
    return labelBrush().color();
}

void DeclarativeBarSet::setLabelColor(QColor color)
{
    QBrush b = labelBrush();
    b.setColor(color);
    setLabelBrush(b);
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
        }
    }
}

QDeclarativeListProperty<DeclarativeBarSet> DeclarativeBarSeries::initialBarSets()
{
    return QDeclarativeListProperty<DeclarativeBarSet>(this, 0, &DeclarativeBarSeries::appendInitialBarSets);
}

void DeclarativeBarSeries::setBarCategories(QStringList categories)
{
    setCategories(categories);
}

QStringList DeclarativeBarSeries::barCategories()
{
    return categories();
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
        }
    }
}

QDeclarativeListProperty<DeclarativeBarSet> DeclarativeGroupedBarSeries::initialBarSets()
{
    return QDeclarativeListProperty<DeclarativeBarSet>(this, 0, &DeclarativeGroupedBarSeries::appendInitialBarSets);
}

void DeclarativeGroupedBarSeries::setBarCategories(QStringList categories)
{
    setCategories(categories);
}

QStringList DeclarativeGroupedBarSeries::barCategories()
{
    return categories();
}

DeclarativeBarSet *DeclarativeGroupedBarSeries::at(int index)
{
    QList<QBarSet*> setList = barSets();
    if (index < setList.count())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

#include "moc_declarativebarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
