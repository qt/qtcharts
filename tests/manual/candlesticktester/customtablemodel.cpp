// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include <QtCharts/QCandlestickSet>
#include <QtCore/QRect>
#include <QtCore/QList>
#include <QtGui/QColor>
#include "customtablemodel.h"

CustomTableModel::CustomTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_categories.append(QStringLiteral("Timestamp"));
    m_categories.append(QStringLiteral("Open"));
    m_categories.append(QStringLiteral("High"));
    m_categories.append(QStringLiteral("Low"));
    m_categories.append(QStringLiteral("Close"));
}

CustomTableModel::~CustomTableModel()
{
    qDeleteAll(m_data);
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_data.count();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_categories.count();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return m_categories[section];
    else
        return QStringLiteral("%1").arg(section);
}

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);

        return true;
    }

    return false;
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        // fall through
    case Qt::EditRole:
        return m_data[index.row()]->at(index.column());
    case Qt::BackgroundRole:
        foreach (QRect rect, m_mapping) {
            if (rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));
        }
        // cell is not mapped, return white color
        return QColor(Qt::white);
    default:
        return QVariant();
    }
}

Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CustomTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    m_data.append(new QList<qreal>(columnCount()));
    endInsertRows();

    return true;
}

bool CustomTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row + count; i >= row; --i)
        m_data.removeAt(i);
    endRemoveRows();

    return true;
}

void CustomTableModel::addRow(QCandlestickSet *set)
{
    bool changed = insertRows(m_data.count(), 1);

    if (changed) {
        QList<qreal> *row = m_data.last();
        row->insert(0, set->timestamp());
        row->insert(1, set->open());
        row->insert(2, set->high());
        row->insert(3, set->low());
        row->insert(4, set->close());
    }
}

void CustomTableModel::clearRows()
{
    bool changed = removeRows(0, m_data.count());
    if (changed)
        m_data.clear();
}

void CustomTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insert(color, area);
}

void CustomTableModel::clearMapping()
{
    m_mapping.clear();
}
