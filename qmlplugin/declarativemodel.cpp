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

////////////// XY model ///////////////////////

DeclarativeXyModel::DeclarativeXyModel(QObject *parent) :
    ChartTableModel(parent)
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

QDeclarativeListProperty<DeclarativeXyPoint> DeclarativeXyModel::points()
{
    return QDeclarativeListProperty<DeclarativeXyPoint>(this, 0, &DeclarativeXyModel::appendPoint);
}

void DeclarativeXyModel::appendPoint(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                                     DeclarativeXyPoint *point)
{
    DeclarativeXyModel *model = qobject_cast<DeclarativeXyModel *>(list->object);
    if (model)
        model->append(point);
    else
        qWarning() << "Illegal point item";
}

////////////// Pie model ///////////////////////

DeclarativePieModel::DeclarativePieModel(QObject *parent) :
    ChartTableModel(parent)
{
}

void DeclarativePieModel::append(QPieSlice* slice)
{
    qDebug() << "DeclarativePieModel::append:" << slice->label() << " " << slice->value();
    qDebug() << "rowCount:" << rowCount();
    qDebug() << "coolCount:" << columnCount();
    insertRow(rowCount());
    qDebug() << "new rowCount:" << rowCount();

    qDebug() << setData(createIndex(rowCount() - 1, 0), slice->value());
    qDebug() << setData(createIndex(rowCount() - 1, 1), slice->label());
}

void DeclarativePieModel::append(QVariantList slices)
{
    qDebug() << "append:" << slices;
    QString label = "";
    for (int i(0); i < slices.count(); i++) {
        if (i % 2) {
            bool ok(false);
            qreal value = slices.at(i).toReal(&ok);
            if (ok) {
                QPieSlice *slice = new QPieSlice(value, label);
                append(slice);
            } else {
                qWarning() << "Illegal slice item";
            }
        } else {
            label = slices.at(i).toString();
        }
    }
}

QDeclarativeListProperty<QPieSlice> DeclarativePieModel::slices()
{
    return QDeclarativeListProperty<QPieSlice>(this, 0, &DeclarativePieModel::appendSlice);
}

void DeclarativePieModel::appendSlice(QDeclarativeListProperty<QPieSlice> *list,
                                      QPieSlice *slice)
{
    DeclarativePieModel *pieModel = qobject_cast<DeclarativePieModel *>(list->object);
    if (pieModel)
        pieModel->append(slice);
    else
        qWarning() << "Illegal slice item";
}

#include "moc_declarativemodel.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
