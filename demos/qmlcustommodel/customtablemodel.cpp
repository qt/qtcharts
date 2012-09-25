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

#include "customtablemodel.h"
#include <QVector>
#include <QRect>
#include <QColor>
#include <QDebug>

CustomTableModel::CustomTableModel(QObject *parent) :
    QAbstractTableModel(parent),
    m_columnCount(0),
    m_rowCount(0)
{
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical) {
        if (m_verticalHeaders.count() > section)
            return m_verticalHeaders[section];
        else
            return QAbstractTableModel::headerData(section, orientation, role);
    } else {
        return QAbstractTableModel::headerData(section, orientation, role);
    }
}

bool CustomTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (orientation == Qt::Vertical) {
        while (m_verticalHeaders.count() <= section)
            m_verticalHeaders.append(QVariant());
        m_verticalHeaders.replace(section, value);
    } else {
        return QAbstractTableModel::setHeaderData(section, orientation, value, role);
    }
    emit headerDataChanged(orientation, section, section);
    return true;
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::EditRole) {
        return m_data[index.row()]->at(index.column());
    }
    return QVariant();
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()]->replace(index.column(), value);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant CustomTableModel::at(int row, int column)
{
    return data(index(row, column));
}

void CustomTableModel::insertColumn(int column, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column);
    m_columnCount++;
    endInsertColumns();
}

void CustomTableModel::insertRow(int row, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row);
    QVector<QVariant>* dataVec = new QVector<QVariant>(m_columnCount);
    m_data.insert(row, dataVec);
    endInsertRows();
}

bool CustomTableModel::removeRow(int row, const QModelIndex &parent)
{
    return QAbstractTableModel::removeRow(row, parent);
}

bool CustomTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    bool removed(false);
    for (int i(row); i < (row + count); i++) {
        m_data.removeAt(i);
        removed = true;
    }
    endRemoveRows();
    return removed;
}

Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

#include "moc_customtablemodel.cpp"
