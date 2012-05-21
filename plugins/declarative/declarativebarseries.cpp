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

DeclarativeBarSeries::DeclarativeBarSeries(QDeclarativeItem *parent) :
    QGroupedBarSeries(parent)
{
}

void DeclarativeBarSeries::classBegin()
{
}

void DeclarativeBarSeries::componentComplete()
{
    foreach(QObject *child, children()) {
        if (qobject_cast<QBarSet *>(child)) {
            QBarSeries::append(qobject_cast<QBarSet *>(child));
        }
    }
}

QDeclarativeListProperty<DeclarativeBarSet> DeclarativeBarSeries::initialBarSets()
{
    return QDeclarativeListProperty<DeclarativeBarSet>(this, 0, &DeclarativeBarSeries::appendInitialBarSets);
}

bool DeclarativeBarSeries::setDeclarativeModel(DeclarativeTableModel *model)
{
    QAbstractItemModel *m = qobject_cast<QAbstractItemModel *>(model);
    bool value(false);
    if (m) {
        setModel(m);
        //setModelMapping(int categories, int bottomBoundary, int topBoundary, Qt::Orientation orientation = Qt::Vertical);
//        setModelMapping(0, 1, 1, Qt::Vertical);
    } else {
        qWarning("DeclarativeBarSeries: Illegal model");
    }
    return value;
}

DeclarativeTableModel *DeclarativeBarSeries::declarativeModel()
{
    return qobject_cast<DeclarativeTableModel *>(model());
}

void DeclarativeBarSeries::setBarCategories(QStringList categories)
{
    setCategories(categories);
}

QStringList DeclarativeBarSeries::barCategories()
{
    return categories();
}

#include "moc_declarativebarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
