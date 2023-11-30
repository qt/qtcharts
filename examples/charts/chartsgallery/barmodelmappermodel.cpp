// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "barmodelmappermodel.h"

#include <QColor>
#include <QList>
#include <QRandomGenerator>
#include <QRect>

BarModelMapperModel::BarModelMapperModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 6;
    m_rowCount = 12;

    for (int i = 0; i < m_rowCount; i++) {
        auto dataList = new QList<qreal>(m_columnCount);
        for (int k = 0; k < dataList->size(); k++) {
            if (k % 2 == 0)
                dataList->replace(k, i * 50 + QRandomGenerator::global()->bounded(20));
            else
                dataList->replace(k, QRandomGenerator::global()->bounded(100));
        }
        m_data.append(dataList);
    }
}

BarModelMapperModel::~BarModelMapperModel()
{
    qDeleteAll(m_data);
}

int BarModelMapperModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int BarModelMapperModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_columnCount;
}

QVariant BarModelMapperModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("201%1").arg(section);
    else
        return QString("%1").arg(section + 1);
}

QVariant BarModelMapperModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::EditRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::BackgroundRole) {
        for (const QRect &rect : m_mapping) {
            if (rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));
        }
    }
    return QVariant();
}

bool BarModelMapperModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags BarModelMapperModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void BarModelMapperModel::addMapping(QString color, QRect area)
{
    m_mapping.insert(color, area);
}
