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

#include "charttablemodel.h"
#include <QVector>
#include <QTime>
#include <QRect>
#include <QColor>

QTCOMMERCIALCHART_USE_NAMESPACE

ChartTableModel::ChartTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    m_columnCount = 2;
    m_rowCount = 0;

    // m_data
    for (int i = 0; i < m_rowCount; i++) {
        QVector<QVariant>* dataVec = new QVector<QVariant>(m_columnCount);
        for (int k = 0; k < dataVec->size(); k++) {
            if (k%2 == 0)
                dataVec->replace(k, i * 50 + qrand()%20);
            else
                dataVec->replace(k, qrand()%100);
        }
        m_data.append(dataVec);
    }
}

int ChartTableModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int ChartTableModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant ChartTableModel::headerData (int section, Qt::Orientation orientation, int role ) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        if (section%2 == 0)
            return "x";
        else
            return "y";
    }
    else
        return QString("%1").arg(section + 1);
}

QVariant ChartTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::EditRole) {
        return m_data[index.row()]->at(index.column());
    }
    return QVariant();
}

bool ChartTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()]->replace(index.column(), value);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void ChartTableModel::insertRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    beginInsertRows(QModelIndex(), row, row);
    QVector<QVariant>* dataVec = new QVector<QVariant>(m_columnCount);
    m_data.insert(row, dataVec);
    endInsertRows();
}

//bool ChartTableModel::removeRow(int row, const QModelIndex &parent)
//{
//    Q_UNUSED(parent)
//    Q_ASSERT(row >= 0 && row < rowCount);

//    beginRemoveRows(parent, row, row);
//    m_data.removeAt(row);
//    endRemoveRows();
//    return true;
//}

bool ChartTableModel::removeRow(int row, const QModelIndex &parent)
{
    return QAbstractTableModel::removeRow(row, parent);
}

bool ChartTableModel::removeRows(int row, int count, const QModelIndex &parent)
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

Qt::ItemFlags ChartTableModel::flags ( const QModelIndex & index ) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

#include "moc_charttablemodel.cpp"
