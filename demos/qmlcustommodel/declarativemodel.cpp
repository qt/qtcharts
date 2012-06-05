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

#include "declarativemodel.h"
#include <qdeclarativelist.h>
#include <QStringList>
#include <QDebug>

////////////// Table model element ///////////////////

DeclarativeTableModelElement::DeclarativeTableModelElement(QObject *parent)
    : QObject(parent)
{
}

QVariantList DeclarativeTableModelElement::values()
{
    return m_values;
}

void DeclarativeTableModelElement::setValues(QVariantList values)
{
    m_values = values;
}

////////////// Table model  ///////////////////

DeclarativeTableModel::DeclarativeTableModel(QObject *parent) :
    CustomTableModel(parent)
{
}

void DeclarativeTableModel::classBegin()
{
}

void DeclarativeTableModel::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeTableModelElement *>(child)) {
            DeclarativeTableModelElement *element = qobject_cast<DeclarativeTableModelElement *>(child);
            append(element->values());
        }
    }
}

void DeclarativeTableModel::setVerticalHeaders(QStringList headers)
{
    for (int i(0); i < headers.count(); i++)
        setHeaderData(i, Qt::Vertical, headers.at(i));
}

QStringList DeclarativeTableModel::verticalHeaders()
{
    return QStringList();
}

QDeclarativeListProperty<QObject> DeclarativeTableModel::modelChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativeTableModel::appendModelChild);
}

void DeclarativeTableModel::appendModelChild(QDeclarativeListProperty<QObject> *list,
                                             QObject *child)
{
    // childs are added in componentComplete instead
    Q_UNUSED(list)
    Q_UNUSED(child)
}

void DeclarativeTableModel::append(QVariantList values)
{
//    qDebug() << "DeclarativeTableModel::append:" << values;

    while (columnCount() < values.count())
        insertColumn(columnCount());

    insertRow(rowCount());

    QModelIndex beginIndex = QModelIndex();
    QModelIndex endIndex = QModelIndex();
    for (int i(0); i < values.count(); i++) {
        QModelIndex modelIndex = createIndex(rowCount() - 1, i);
        if (i == 0)
            beginIndex = modelIndex;
        if (i == (values.count() - 1))
            endIndex = modelIndex;
        setData(modelIndex, values.at(i));
    }
    dataChanged(beginIndex, endIndex);
}

#include "moc_declarativemodel.cpp"
