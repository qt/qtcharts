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
#include <QTime>
#include <QRect>
#include <QColor>

CustomTableModel::CustomTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    m_columnCount = 7;
    m_rowCount = 10;

    m_labels.append("Apples");
    m_labels.append("Oranges");
    m_labels.append("Pears");
    m_labels.append("Peaches");
    m_labels.append("Coconuts");
    m_labels.append("Bananas");
    m_labels.append("Kiwis");
    m_labels.append("Grapes");
    m_labels.append("Plums");

    // m_data
    for (int i = 0; i < m_rowCount; i++)
    {
        QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
        for (int k = 0; k < dataVec->size(); k++)
        {
            if (k%2 == 0)
                dataVec->replace(k, i * 50 + qrand()%20);
            else
                dataVec->replace(k, qrand()%100);
        }
        m_data.append(dataVec);
        //        m_labels.append(QString("Row: %1").arg((i + 1)));
    }
}

int CustomTableModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int CustomTableModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;// + 1;
}

QVariant CustomTableModel::headerData (int section, Qt::Orientation orientation, int role ) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case 7:
            return "Fruit";
        case 1:
            return "Count";
        case 2:
            return "Ordered";
        default:
            if (section%2 == 0)
                return "x";
            else
                return "y";
        }
    }
    else
        return QString("%1").arg(section /*+ 1*/);
}

QVariant CustomTableModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
//        case 7:
//            return m_labels[index.row()];
        default:
            return m_data[index.row()]->at(index.column());
            break;
        }
    }
    else if (role == Qt::EditRole)
    {
        switch(index.column())
        {
//        case 7:
//            return m_labels[index.row()];
        default:
            return m_data[index.row()]->at(index.column());
            break;
        }
    }
    else if (role == Qt::BackgroundRole)
    {
        QRect rect;
        foreach(rect, m_mapping)
            if(rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));

        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

bool CustomTableModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        switch(index.column())
        {
        case 7:
            m_labels.replace(index.row(), value.toString());
            break;
        default:
            m_data[index.row()]->replace(index.column(), value.toDouble());
            break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags CustomTableModel::flags ( const QModelIndex & index ) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CustomTableModel::insertRows ( int row, int count, const QModelIndex & parent)
{
    Q_UNUSED(parent)

    if (row < 0)
        row = 0;
    beginInsertRows(QModelIndex(), row /*dataTable.count()*/, row + count - 1);
    for (int i = row; i < row + count; i++)
    {
        //        m_points.insert(row, QPointF(10,20));
        QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
        QVector<QColor>* colorVec = new QVector<QColor>(m_columnCount);
        for (int k = 0; k < dataVec->size(); k++)
        {
            if (k%2 == 0)
                //                dataVec->replace(k, i * 50 + qrand()%20);
            {
                int difference = 0;
                if (i < m_data.size())
                {
                    if (i - 1 >= 0)
                    {
                        if (row > 0)
                            difference = (int)((qAbs(m_data[i]->at(k) - m_data[row - 1]->at(k)))/count);
                        else
                            difference = (int)((qAbs(m_data[i]->at(k)/count)));
                        dataVec->replace(k, m_data[i - 1]->at(k) + qrand()%qMax(1, difference));
                    }
                    else
                        dataVec->replace(k, qrand()%40 + 10);
                }
                else
                {
                    if (i - 1 >= 0)
                    {
                        dataVec->replace(k, m_data[i - 1]->at(k) + qrand()%40 + 10);
                    }
                    else
                    {
                        dataVec->replace(k, qrand()%40 + 10);
                    }
                }
            }
            else
                dataVec->replace(k, qrand()%100);
            colorVec->replace(k, QColor(Qt::white));
        }
        m_data.insert(i, dataVec);
        m_labels.insert(i,(QString("Row: %1").arg(i + 1)));
    }
    endInsertRows();
    return true;
}

bool CustomTableModel::removeRows ( int row, int count, const QModelIndex & parent)
{
    if (row > this->rowCount() - 1)
        return false;
    if (row < 0)
        row = 0;
    if (row + count > rowCount())
        return false;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++)
    {
        QVector<qreal>* item = m_data.at(row);
        m_data.removeAt(row);
        delete item;
        m_labels.removeAt(row);
    }
    endRemoveRows();
    return true;
}

bool CustomTableModel::insertColumns ( int column, int count, const QModelIndex & parent)
{
    if (column < 0)
        column = 0;
    beginInsertColumns(parent, column, column + count - 1);
    m_columnCount += count;
    for (int i = column; i < column + count; i++)
        for (int k = 0; k < rowCount(); k++)
            if (k - 1 >= 0) {
                m_data[k]->insert(i, m_data[k - 1]->at(i) + qrand()%40 + 10);
            } else {
                m_data[k]->insert(i, qrand()%40);
            }
    endInsertColumns();
    return true;
}

bool CustomTableModel::removeColumns ( int column, int count, const QModelIndex & parent)
{
    if (column > columnCount() - 1)
        return false;
    if (column < 0)
        column = 0;
    if (column + count > columnCount())
        return false;
    beginRemoveColumns(parent, column, column + count -1);
    m_columnCount -= count;
    for (int i = column; i < column + count; i++)
        for (int k = 0; k < rowCount(); k++)
            m_data[k]->remove(column);
    endRemoveColumns();
    return true;
}

void CustomTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}

void CustomTableModel::addMapping(QString color, int left, int top, int right, int bottom)
{
    addMapping(color, QRect(QPoint(left, top), QPoint(right, bottom)));
}
