#include "customtablemodel.h"

CustomTableModel::CustomTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_points.append(QPointF(10, 50));
    m_labels.append("Apples");
    m_points.append(QPointF(60, 70));
    m_labels.append("Oranges");
    m_points.append(QPointF(110, 50));
    m_labels.append("Bananas");
    m_points.append(QPointF(140, 40));
    m_labels.append("Lemons");
    m_points.append(QPointF(200, 150));
    m_labels.append("Plums");
}

int CustomTableModel::rowCount(const QModelIndex & parent) const
{
    return m_points.count();
}

int CustomTableModel::columnCount(const QModelIndex & parent) const
{
    return 3;
}

QVariant CustomTableModel::headerData (int section, Qt::Orientation orientation, int role ) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case 0:
            return "x";
        case 1:
            return "y";
        case 2:
            return "Fruit";
        default: "What?";
        }
    }
    else
        return QString("%1").arg(section + 1);
}

QVariant CustomTableModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0:
            return m_points[index.row()].x();
        case 1:
            return m_points[index.row()].y();
        case 2:
            return m_labels[index.row()];
        default:
            return QVariant();
        }
    }
    else if (role == Qt::EditRole)
    {
        switch(index.column())
        {
        case 0:
            return m_points[index.row()].x();
        case 1:
            return m_points[index.row()].y();
        case 2:
            return m_labels[index.row()];
        default:
            return QVariant();
        }
    }
}

bool CustomTableModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        switch(index.column())
        {
        case 0:
            m_points[index.row()].setX(value.toDouble());
            break;
        case 1:
            m_points[index.row()].setY(value.toDouble());
            break;
        case 2:
            m_labels.replace(index.row(), value.toString());
            break;
        default:
            return false;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags CustomTableModel::flags ( const QModelIndex & index ) const
{
    if (!index.isValid())
                return Qt::ItemIsEnabled;
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CustomTableModel::insertRows ( int row, int count, const QModelIndex & parent)
{
    beginInsertRows(QModelIndex(), row /*dataTable.count()*/, row + count - 1);
    for (int i = 0; i < count; i++)
    {
        m_points.append(QPointF());
        m_labels.append("");
    }
    endInsertRows();
    return true;
}
