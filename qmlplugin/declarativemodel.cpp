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

////////////// Table model (base) ///////////////////

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

void DeclarativeTableModel::appendToModel(QObject *object)
{
    if (qobject_cast<DeclarativeBarModel *>(this)) {
        DeclarativeBarModel *model = qobject_cast<DeclarativeBarModel *>(this);
        model->append(qobject_cast<QBarSet *>(object));
    } else if (qobject_cast<DeclarativePieModel *>(this)) {
        DeclarativePieModel *model = qobject_cast<DeclarativePieModel *>(this);
        model->append(qobject_cast<QPieSlice *>(object));
    } else if (qobject_cast<DeclarativeXyModel *>(this)) {
        DeclarativeXyModel *model = qobject_cast<DeclarativeXyModel *>(this);
        model->append(qobject_cast<DeclarativeXyPoint *>(object));
    }
}

////////////// XY model ///////////////////////

DeclarativeXyModel::DeclarativeXyModel(QObject *parent) :
    DeclarativeTableModel(parent)
{
}

void DeclarativeXyModel::append(DeclarativeXyPoint* point)
{
//    qDebug() << "DeclarativeXyModel::append:" << point->x() << " " << point->y();
    insertRow(rowCount());
    QModelIndex xModelIndex = createIndex(rowCount() - 1, 0);
    QModelIndex yModelIndex = createIndex(rowCount() - 1, 1);
    setData(xModelIndex, point->x());
    setData(yModelIndex, point->y());
    dataChanged(xModelIndex, yModelIndex);
}

void DeclarativeXyModel::append(QVariantList points)
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
                append(point);
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

////////////// Pie model ///////////////////////

DeclarativePieModel::DeclarativePieModel(QObject *parent) :
    DeclarativeTableModel(parent)
{
}

void DeclarativePieModel::append(QPieSlice* slice)
{
//    qDebug() << "DeclarativePieModel::append:" << slice->label() << " " << slice->value();
    insertRow(rowCount());

    setData(createIndex(rowCount() - 1, 0), slice->value());
    setData(createIndex(rowCount() - 1, 1), slice->label());
}

void DeclarativePieModel::append(QVariantList slices)
{
//    qDebug() << "append:" << slices;
    QString label = "";
    for (int i(0); i < slices.count(); i++) {
        if (i % 2) {
            bool ok(false);
            qreal value = slices.at(i).toReal(&ok);
            if (ok) {
                QPieSlice *slice = new QPieSlice(value, label);
                append(slice);
                // TODO: how to copy the properties to the newly added slice?
                // (DeclarativePieModel::append only copies the label and value to the model)
//                QPieSlice *addedSlice = append(slice);
//                addedSlice->setExploded(slice->isExploded());
            } else {
                qWarning() << "Illegal slice item";
            }
        } else {
            label = slices.at(i).toString();
        }
    }
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
