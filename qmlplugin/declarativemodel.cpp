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
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE


////////////// Table model row ///////////////////

DeclarativeTableModelRow::DeclarativeTableModelRow(QObject *parent)
    : QObject(parent)
{
}

QVariantList DeclarativeTableModelRow::values()
{
    return m_values;
}

void DeclarativeTableModelRow::setValues(QVariantList values)
{
    m_values = values;
}

////////////// Table model  ///////////////////

DeclarativeTableModel::DeclarativeTableModel(QObject *parent) :
    ChartTableModel(parent)
{
}

void DeclarativeTableModel::classBegin()
{
}

void DeclarativeTableModel::componentComplete()
{
    foreach (QObject *child, children())
        appendToModel(child);
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

void DeclarativeTableModel::appendToModel(QObject *object)
{
    if (qobject_cast<QBarSet *>(object)) {
        DeclarativeBarModel *model = qobject_cast<DeclarativeBarModel *>(this);
        Q_ASSERT(model);
        model->append(qobject_cast<QBarSet *>(object));
    } else if (qobject_cast<QPieSlice *>(object)) {
        // TODO
    } else if (qobject_cast<DeclarativeXyPoint *>(object)) {
        // TODO
        appendPoint(qobject_cast<DeclarativeXyPoint *>(object));
    } else if (qobject_cast<DeclarativeTableModel *>(this)) {
        append(qobject_cast<DeclarativeTableModelRow *>(object)->values());
    }
}

void DeclarativeTableModel::appendPoints(QVariantList points)
{
    qreal x = 0.0;
    for (int i(0); i < points.count(); i++) {
        if (i % 2) {
            bool ok(false);
            qreal y = points.at(i).toReal(&ok);
            if (ok) {
                DeclarativeXyPoint *point= new DeclarativeXyPoint();
                point->setX(x);
                point->setY(y);
                appendPoint(point);
            } else {
                qWarning() << "Illegal y value";
            }
        } else {
            bool ok(false);
            x = points.at(i).toReal(&ok);
            if (!ok) {
                qWarning() << "Illegal x value";
            }
        }
    }
}

void DeclarativeTableModel::appendPoint(DeclarativeXyPoint* point)
{
//    qDebug() << "DeclarativeTableModel::append:" << point->x() << " " << point->y();
    insertRow(rowCount());
    QModelIndex xModelIndex = createIndex(rowCount() - 1, 0);
    QModelIndex yModelIndex = createIndex(rowCount() - 1, 1);
    setData(xModelIndex, point->x());
    setData(yModelIndex, point->y());
    dataChanged(xModelIndex, yModelIndex);
}

////////////// Bar model ///////////////////////

DeclarativeBarModel::DeclarativeBarModel(QObject *parent) :
    DeclarativeTableModel(parent)
{
}

void DeclarativeBarModel::append(QBarSet* barSet)
{
    insertColumn(columnCount());
    for (int i(0); i < barSet->count(); i++) {
        if (rowCount() < (i + 1))
            insertRow(rowCount());
        setData(createIndex(i, columnCount() - 1), barSet->at(i));
//        insertRow(rowCount());
//        setData(createIndex(rowCount() - 1, 0), );
//        setData(createIndex(rowCount() - 1, 1), barSet->at(i));
    }
//    TODO: setModelMapping(0, 1, columnCount(), Qt::Vertical);
}

#include "moc_declarativemodel.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
